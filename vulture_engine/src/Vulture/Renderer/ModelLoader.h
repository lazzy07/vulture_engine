#pragma once

#include "ModelLibrary.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <zip/zip.h>

#include "Vulture/Core/Configurations.h"

namespace Vulture {
	class ModelLoader {
	public:
		void AddNewModel(std::string path, bool flipUVs = true, bool triangulate = true);
		void LoadVulModel(std::string path, ModelLibrary* modelLibrary);
	private:
		std::string getFileName(std::string path);
		void processNode(aiNode* node, const aiScene* scene, zip_t* zip, Configurations* conf);
		void processMesh(aiMesh* mesh, const aiScene* scene, zip_t* zip, Configurations* conf);

		struct MeshData {
			uint32_t m_Size;
			void* m_Data;

			MeshData(size_t size, void* data) : m_Size((uint32_t)size), m_Data(data) {

			}
		};
	};
}
