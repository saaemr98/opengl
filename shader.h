#include <string>
#include <GL\glew.h>
#include "transform.h"

class Shader {
public:
	Shader(const std::string& filename);		// takes in adress of the filename, the file has the shader programs

	void Bind(); // tells gpu to stop using any other shader functions and to use this class' shader functions instead
	void Update(const Transform& transform);

	virtual ~Shader();

private:
	static const unsigned int NUM_SHADERS = 2;	// 2 shaders: vector shader and fragment shader
	GLuint m_program;	//OpenGL's way of knowing where the program is, it a handle. m-program stores a number to refer to the shader program
	GLuint m_shaders[NUM_SHADERS];	// the number of shaders, for our case it is just the vector shader and fragment shader

	enum {
		TRANSFORM_U,

	    NUM_UNIFORMS
	};

	GLuint m_uniform[NUM_UNIFORMS];

	GLuint CreateShader(const std::string& text, GLenum shaderType);
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
};

