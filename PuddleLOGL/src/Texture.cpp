#include "pudpch.h"
#include "Texture.h"

#include "glad/glad.h"
#include "stb_image.h"

void setVFlip(bool b)
{
	stbi_set_flip_vertically_on_load(b);
}

unsigned int loadTexture(const char* file, unsigned int format, unsigned char slot)
{
	unsigned int texture;
	glGenTextures(1, &texture);

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* tData;
	int tWidth, tHeight, tChannels;
	tData = stbi_load("assets/container.jpg", &tWidth, &tHeight, &tChannels, 0);

	if (tData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, format, GL_UNSIGNED_BYTE, tData);
		glGenerateMipmap(texture);
	}
	else
	{
		std::cerr << "Failed To Load Texture From " << file << " to Slot " << slot << "\n";
		stbi_image_free(tData);
		return 0;
	}

	stbi_image_free(tData);
	return texture;
}