#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& fileName) {
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4); // this will load the texture data

	if (imageData == NULL) {	// make sure imageData is not pointing to NULL, then there is no image data.
		std::cerr << "Texture loading failed for texture" << fileName << std::endl;
	}

	glGenTextures(1, &m_texture);	// we want to generate 1 texture from the specified address of the handle. 
	glBindTexture(GL_TEXTURE_2D, m_texture);	// we are binding a 2D m_texture 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// we are passing in a 2D texture, WRAP_S controls texture wrapping on the x axis, GL_REPEAT indicates that it will repeat the texture if the mesh created is too small
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// we are passing in a 2D texture, WRAP_T controls texture wrapping on the y axis, GL_REPEAT indicates that it will repeat the texture if the mesh created is too small

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// minification filter: if we have a 10x10 pixel texture but then view it at 5x5, GL_LINEAR will try to use linear exptrpolation with the existing pixel to try and create the most accurate image in that 5x5 pixel space.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// magnification filter: if we have a 10x10 pixel texture but then view it at 20x20, GL_LINEAR will try to use linear exptrpolation with the existing pixel to try and create the most accurate image in that 20x20 pixel space.
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);	// sends the texture to the gpu, param 2: mipmapping, store different resolutions of the same image and display them depending on where the camera is placed, param 3: how OpenGL stores individual pixels on the gpu, param 7: format of the data sending to gpu, param 8: how is that data stored (char = bytes), param 9: pointer to all of the data being sent to gpu.

	stbi_image_free(imageData);	// delete the texture data as we dont care about it anymore
}

Texture::~Texture() {
	glDeleteTextures(1, &m_texture);	// we want to delete 1 texture, where the address of the handle is &m_texture
}

void Texture::Bind(unsigned int unit) {
	assert(unit >= 0 && unit <= 31);	// makes sure the unit is between 0-31, otherwise will stop

	glActiveTexture(GL_TEXTURE0 + unit);	// activate a texture from a bunch of different textures from 0-31
	glBindTexture(GL_TEXTURE_2D, m_texture);	// makes sure that any furture opertions depending on a texture happens only to m_texture.
}
