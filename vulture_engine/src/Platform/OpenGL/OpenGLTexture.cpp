#include "vulpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Vulture {
	OpenGLTexture2D::OpenGLTexture2D(const std::string & path) : m_Path(path)
	{
		int width, height, channels;
		//stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		VUL_CORE_ASSERT(data, "Image couldn't be loaded");

		m_Width = width;
		m_Height = height;

		GLint noOfChannels = 0;
		GLint type = 0;
		if (channels == 3) {
			noOfChannels = GL_RGB;
			type = GL_RGB8;
		}
		else if (channels == 4) {
			noOfChannels = GL_RGBA;
			type = GL_RGBA8;
		}
		else {
			VUL_CORE_ASSERT(false, "Unsupported number of channels of image");
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, type, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, noOfChannels, GL_UNSIGNED_BYTE, data);

		//Later handle this to be retained if needed
		stbi_image_free(data);
	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}