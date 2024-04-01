#include "OpenGL/Graphics/Resources/Texture.hpp"
#include "OpenGL/Graphics/ShaderProgram.hpp"

#include <glad/glad.h>
#include <stb_image/stb_image.h>

Texture::Texture(const char* i_imagePath)
{
	Image image;
	stbi_set_flip_vertically_on_load(true);
	image.bytes = stbi_load(i_imagePath, &image.width, &image.height, &image.colorChannels, 0);

	glGenTextures(1, &this->m_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)image.bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(image.bytes);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->m_id);
}
