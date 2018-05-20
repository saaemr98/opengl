#include <glm\glm.hpp>
#include <GL\glew.h>

class Vertex {
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord) {
		this->pos = pos;	// constructor makes the this pointer point to
		this->texCoord = texCoord;
	}

	inline glm::vec3* getPos() { return &pos; }		// these 2 accessors created so that push_back() can access the vertex data
	inline glm::vec2* getTexCoord() { return &texCoord; }

private:
	glm::vec3 pos;	// hold the vertex's data in [x y z]' form
	glm::vec2 texCoord;		// coordinate on the texture image
};

class Mesh {
public:
	Mesh(Vertex* vertices, unsigned int numVertices);	// Mesh takes in the list of the vertices and the total number of vertices

	void Draw();

	virtual ~Mesh();

private:
	enum {
		POSITION_VB,		// VB = virtual buffer
		TEXCOORD_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;		// refers to mesh data that will go to the gpu
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];		// creates an array of buffers that will be used by the gpu
	unsigned int m_drawCount;		// how many objects/vertices we want to draw. when we reach this limit we can stop the draw function.
};

// OpenGl refers to blocks of data in the gpu as buffers, thats how we have to handle our data with buffers



