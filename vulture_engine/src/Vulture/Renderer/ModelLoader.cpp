#include "vulpch.h"
#include "ModelLoader.h"

#include "Mesh.h"
#include "Model.h"


namespace Vulture {
	void ModelLoader::AddNewModel(std::string path, bool flipUVs, bool triangulate)
	{
		// Extract name from filepath
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		std::string name = path.substr(lastSlash, count);

		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			VUL_CORE_ASSERT(false, "Model loader cannot load the file");
			return;
		}

		std::string filepath = "./assets/models/" + name + ".vulmodel";

		struct zip_t *zip = zip_open(filepath.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
			if(zip) processNode(scene->mRootNode, scene, zip);
		zip_close(zip);
	}

	void ModelLoader::LoadVulModel(std::string path, Ref<ModelLibrary> modelLibrary)
	{
		Ref<Model> model; 
		model.reset(new Model());

		struct zip_t *zip = zip_open(path.c_str(), 0, 'r');
		zip_close(zip);
		//modelLibrary->AddModel("smt", model);
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
		std::string indeciesFileName = meshName + ".indecies";

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
				indices.push_back(face.mIndices[i]);
			}
		}

		zip_entry_open(zip, verticesFileName.c_str());
		{
			zip_entry_write(zip, &vertices[0], sizeof(Vertex)*vertices.size());
		}
		zip_entry_close(zip);

		zip_entry_open(zip, indeciesFileName.c_str());
		{
			zip_entry_write(zip, &indices[0], sizeof(unsigned int)*vertices.size());
		}
		zip_entry_close(zip);
	}
}