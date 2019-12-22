#include "vulpch.h"
#include "ModelLoader.h"

#include "Mesh.h"
#include "Model.h"

namespace Vulture {
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct Texture {
		unsigned int id;
		std::string type;
	};

	void ModelLoader::AddNewModel(std::string path, bool flipUVs, bool triangulate)
	{
		// Extract name from filepath
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			VUL_CORE_ASSERT(false, "Model loader cannot load the file");
			return;
		}
		std::string name = getFileName(path);
		std::string filepath = "./assets/models/" + name + ".vulmodel";

		struct zip_t *zip = zip_open(filepath.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
			if(zip) processNode(scene->mRootNode, scene, zip);
		zip_close(zip);
	}

	void ModelLoader::LoadVulModel(std::string path, ModelLibrary* modelLibrary)
	{
		VUL_CORE_TRACE("Openning vul_model : {0}", path);

		struct zip_t *zip = zip_open(path.c_str(), 0, 'r');
		VUL_CORE_ASSERT(zip, "Cannot find the specified model file");
		
		int n = zip_total_entries(zip);
		std::unordered_map<std::string, std::unordered_map<std::string, Ref<MeshData>>> files;

		Ref<Model> model;
		model.reset(new Model());

		for (unsigned int i = 0; i < n; i++) {
			zip_entry_openbyindex(zip, i);
			{
				const char* name = zip_entry_name(zip);
				std::string fileName = name;
				auto lastDot = fileName.rfind('.');
				auto count = lastDot == std::string::npos ? path.size() : lastDot;
				std::string meshName = fileName.substr(0, count);
				std::string type = fileName.substr(count + 1, path.size());
				
				size_t bufsize = zip_entry_size(zip);

				files[meshName][type].reset(new MeshData(bufsize, malloc(bufsize)));
				zip_entry_noallocread(zip, (void *)files[meshName][type]->m_Data, bufsize);
			}
			zip_entry_close(zip);
		}
		zip_close(zip);

		for (std::pair<std::string, std::unordered_map<std::string, Ref<MeshData>>> file : files) {
			Ref<VulMesh> mRef;
			mRef.reset(new VulMesh());
			for (std::pair<std::string, Ref<MeshData>> elem : file.second) {
				if (elem.first == "vertices") {
					mRef->m_Vertices = (Vertex*)elem.second->m_Data;
					mRef->m_VerticesSize = elem.second->m_Size;
					VUL_CORE_TRACE("loading vul_mesh data: {0}.{1}", file.first, elem.first);
				}
				else if (elem.first == "indices") {
					VUL_CORE_TRACE("loading vul_mesh data: {0}.{1}", file.first, elem.first);
					mRef->m_Indices = (unsigned int *)elem.second->m_Data;
					mRef->m_IndicesSize = elem.second->m_Size;
				}
				else {
					VUL_CORE_ASSERT(false, "Unknown file type in mesh loader");
				}
			}
			mRef->SetupMesh();
			model->AddMesh(mRef);
		}

		modelLibrary->AddModel(getFileName(path), model);
	}

	std::string ModelLoader::getFileName(std::string path)
	{
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		std::string name = path.substr(lastSlash, count);
		return name;
	}

	void ModelLoader::processNode(aiNode * node, const aiScene * scene, zip_t* zip)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			processMesh(mesh, scene, zip);
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], scene, zip);
		}
	}

	void ModelLoader::processMesh(aiMesh * mesh, const aiScene * scene, zip_t* zip)
	{
		std::string meshName = (std::string)mesh->mName.C_Str();
		
		std::string verticesFileName = meshName + ".vertices";
		std::string indicesFileName = meshName + ".indices";

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		
 		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			Vertex v;
			glm::vec3 vec;

			vec.x = mesh->mVertices[i].x;
			vec.y = mesh->mVertices[i].y;
			vec.z = mesh->mVertices[i].z;

			v.Position = vec;

			vec.x = mesh->mNormals[i].x;
			vec.y = mesh->mNormals[i].y;
			vec.z = mesh->mNormals[i].z;

			v.Normal = vec;

			if (mesh->mTextureCoords[0]) {
				glm::vec2 vec;

				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;

				v.TexCoords = vec;
			}
			else {
				v.TexCoords = glm::vec2(0.0f, 0.0f);
			}
			vertices.push_back(v);
		}
		
		
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		zip_entry_open(zip, verticesFileName.c_str());
		{
			zip_entry_write(zip, &vertices[0], sizeof(Vertex)*vertices.size());
		}
		zip_entry_close(zip);

		zip_entry_open(zip, indicesFileName.c_str());
		{
			zip_entry_write(zip, &indices[0], sizeof(unsigned int)*indices.size());
		}
		zip_entry_close(zip);
	}
}