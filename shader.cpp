#include <iostream>
#include <fstream>
#include "shader.h"

Shader::Shader(const std::string& fileName) {
	m_program = glCreateProgram();		// Telling OpenGL that we are creating a new shader program, creates some space in the gpu.

	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);		// creating the vertex shader using the shader file specified
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);		// creating the fragment shader using the shader file specified (different extensions used to differentiate between the 2 shaders files)

	for (int i = 0; i < NUM_SHADERS; ++i) {
		glAttachShader(m_program, m_shaders[i]);	// adds the shaders to the shader program 
	}

	glBindAttribLocation(m_program, 0, "position");		// give each attribute its index so that the mesh can be coded, will look for these attributes in the shader files
	glBindAttribLocation(m_program, 1, "texCoord");

	glLinkProgram(m_program);	// Links the files attached to the program for compilation
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader Program Failed To Link: ");	// if program not linked properly then will show error

	glValidateProgram(m_program);	// Makes sure whether we have ended up with a valid shader at the end of the process even if it has linked.
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program Is Not Valid: ");		// if program not valid then will show error

	m_uniform[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

void Shader::Bind() {
	glUseProgram(m_program);	// tells gpu to use shaders from shader program instead of any other for this program
}

void Shader::Update(const Transform& transform) {
	glm::mat4 model = transform.GetModel();

	glUniformMatrix4fv(m_uniform[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

Shader::~Shader() {
	for (int i = 0; i < NUM_SHADERS; ++i) {
		glDetachShader(m_program, m_shaders[i]);		// when deleteting shaders, first detach the shader from the shader program then delete it.
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);		// deletes program handle to delete the whole shader program
}

GLuint Shader::CreateShader(const std::string& text, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);		// creates a shader with specified shader type (vertex/fragment/geometric)

	if (shader == 0) {
		std::cerr << "Error: Shader Creation Failed" << std::endl;	// if the shader = 0; then OpenGL has not really given us a shader, most likely because there is no memory space
	}

	const GLchar* shaderSourceStrings[1];	// size is 1 because we have only one file for each shader, but we have the option to have multiple files for one shader
	GLint shaderSourceStringLenghts[1];		// OpenGL likes to know the lenght of the shader file string (in terms of bytes)

	shaderSourceStrings[0] = text.c_str();	// strings are in C API, storing the location of the shader file
	shaderSourceStringLenghts[0] = text.length();	// stores the length of the shader file

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLenghts);		// This method is implemented differently for different grpahics cards. Sends source code to OpenGL, '1' is defined to be the number of different source strings for the shader.
	glCompileShader(shader);	// compile the shader

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader Compilation Failed: ");	// if compilation fails send this error

	return shader;	// return the created shader
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
