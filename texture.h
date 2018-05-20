#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>

class Texture {
public:
	Texture(const std::string& fileName);	// loads texture from file

	void Bind(unsigned int unit);	// can bind upto 32 textures, unit represents the 32 textures. Range of input is 0-31.

	virtual ~Texture();

private:
	GLuint m_texture; // stores handle to the texture
};

#endif