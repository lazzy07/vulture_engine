#include "vulpch.h"
#include "Material.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Vulture {
	Material::Material(const std::string name, const std::string shaderName, Ref<ShaderLibrary> shaderLibrary, Ref<TextureLibrary> textureLibrary) 
		: m_Name(name), m_ShaderLibrary(shaderLibrary), m_TextureLibrary(textureLibrary)
	{
		m_Configurations.SetString("material", "name", name);
		m_Configurations.SetString("shader", "name", shaderName);

		m_Shader = m_ShaderLibrary->Get(m_Configurations.GetString("shader", "name", "default"));
	}

	Material::~Material() {

	}

	Ref<Shader> Material::GetShader()
	{
		return m_Shader;
	}

	void Material::SetShader(std::string shaderName)
	{
		m_Configurations.SetString("shader", "name", shaderName);
		m_Shader = m_ShaderLibrary->Get(m_Configurations.GetString("shader", "name", "default"));
	}

	void Material::SetFloat(std::string name, float value)
	{
		m_Configurations.SetFloat("variable", name, value);
		m_Configurations.SetString("vartype", name, "float");
	}

	void Material::SetVec2(std::string name, glm::vec2 value)
	{
		m_Configurations.SetVec2("variable", name, value);
		m_Configurations.SetString("vartype", name, "vec2");
	}

	void Material::SetVec3(std::string name, glm::vec3 value)
	{
		m_Configurations.SetVec3("variable", name, value);
		m_Configurations.SetString("vartype", name, "vec3");
	}

	void Material::SetVec4(std::string name, glm::vec4 value)
	{
		m_Configurations.SetVec4("variable", name, value);
		m_Configurations.SetString("vartype", name, "vec4");
	}

	void Material::SetMat3(std::string name, glm::mat3 value)
	{
		m_Configurations.SetMat3("variable", name, value);
		m_Configurations.SetString("vartype", name, "mat3");
	}

	void Material::SetMat4(std::string name, glm::mat4 value)
	{
		m_Configurations.SetMat4("variable", name, value);
		m_Configurations.SetString("vartype", name, "mat4");
	}

	void Material::SetTexture(std::string name, float textureSlot)
	{
		m_Configurations.SetFloat("variable", name, textureSlot);
		m_Configurations.SetString("vartype", name, "texture");
	}

	void Material::LoadVariables()
	{
		std::unordered_map<std::string, std::string> vars;
		std::unordered_map<std::string, std::string> varTypes;

		m_Configurations.GetAll("variable", &vars);
		m_Configurations.GetAll("vartype", &varTypes);

		VUL_CORE_ASSERT(vars.size() == varTypes.size(), "Count of variables and count of variable types are different");

		for (std::pair<std::string, std::string> elem : varTypes) {
			if (elem.second == "float") {
				m_Floats[elem.first] = m_Configurations.GetFloat("variable", elem.first);
			}
			else if (elem.second == "vec2") {
				m_Vec2s[elem.first] = m_Configurations.GetVec2("variable", elem.first);
			}
			else if (elem.second == "vec3") {
				m_Vec3s[elem.first] = m_Configurations.GetVec3("variable", elem.first);
			}
			else if (elem.second == "vec4") {
				m_Vec4s[elem.first] = m_Configurations.GetVec4("variable", elem.first);
			}
			else if (elem.second == "mat3") {
				m_Mat3s[elem.first] = m_Configurations.GetMat3("variable", elem.first);
			}
			else if (elem.second == "mat4") {
				m_Mat4s[elem.first] = m_Configurations.GetMat4("variable", elem.first);
			}
			else if (elem.second == "texture") {
				m_Textures[elem.first] = m_Configurations.GetFloat("variable", elem.first);
			}
		}
	}

	void Material::Bind()
	{
		for (std::pair<std::string, float> elem : m_Textures) {
			Ref<Texture2D> tex = m_TextureLibrary->GetTexture(elem.first);
			tex->Bind(elem.second);
		}

		for (std::pair<std::string, float> elem : m_Floats) {
			//TODO:: Temparory
			std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat(elem.first, elem.second);
		}

		for (std::pair<std::string, glm::vec2> elem : m_Vec2s) {
			//TODO:: Temparory
			std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat2(elem.first, elem.second);
		}

		for (std::pair<std::string, glm::vec3> elem : m_Vec3s) {
			//TODO:: Temparory
			std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat3(elem.first, elem.second);
		}

		for (std::pair<std::string, glm::vec4> elem : m_Vec4s) {
			//TODO:: Temparory
			std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat4(elem.first, elem.second);
		}

		for (std::pair<std::string, glm::mat3> elem : m_Mat3s) {
			//TODO:: Temparory
			std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformMat3(elem.first, elem.second);
		}

		for (std::pair<std::string, glm::mat4> elem : m_Mat4s) {
			//TODO:: Temparory
			std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformMat4(elem.first, elem.second);
		}
	}
}