#pragma once

#include "ModelLibrary.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <zip/zip.h>

namespace Vulture {
	class ModelLoader {
	public:
		static void AddNewModel(std::string path, bool flipUVs = true, bool triangulate = true);
		static void LoadVulModel(std::string path, ModelLibrary* modelLibrary);
	private:
		static std::string getFileName(std::string path);
		static void processNode(aiNode* node, const aiScene* scene, zip_t* zip);
		static void processMesh(aiMesh* mesh, const aiScene* scene, zip_t* zip);

		struct MeshData {
			uint32_t m_Size;
			void* m_Data;

			MeshData(size_t size, void* data) : m_Size(size), m_Data(data) {

			}
		};
	};
}
