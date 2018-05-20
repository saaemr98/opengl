#include "mesh.h"
#include <vector>		// vector is like an array bit is dynamically allocated unlike array which requires us to give it an initial capacity which can not be altered

Mesh::Mesh(Vertex* vertices, unsigned int numVertices) {
	m_drawCount = numVertices;			// will be explained later

	glGenVertexArrays(1, &m_vertexArrayObject);		// We want to create 1 vertex array and we want to store it in address of m_vertexArrayObject
	glBindVertexArray(m_vertexArrayObject);		// any operation that would affect a vertex array object will affect the m_vertexArrayObject and nothing else

	std::vector<glm::vec3> positions;   // a vector that will hold the vertex coordinates
	std::vector<glm::vec2> texCoords;	// a vector that will hold all the texture coordinates

	positions.reserve(numVertices);		// although the space needed is dynamically allocated in a vector, we should still reserve the space (which is the number of vertices) just to be safe
	texCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; ++i) {		// creating an array of each attribute so that you dont have to handle with any offsets 
		positions.push_back(*vertices[i].getPos());			// pushing back the data from each vertices, retains order
		texCoords.push_back(*vertices[i].getTexCoord());
	}

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);		// this will generate the number of buffers we want and store those buffers in the m_vertexArrayBuffers array
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);		// any operation that would affect a buffer array will affect the specified buffer array, the GL_ARRAY_BUFFER tells OpenGL that we are passing the buffer as an array
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);		// this will take the vertex data and store it in the buffer, the 2nd parameter specifier the size in bytes required to store the vertices, GL_STATIC_DRAW tells the gpu where the datashould be stored in the gpu, static draw means that the data will not be modified so it stores it someplace else.

	glEnableVertexAttribArray(0);		// this will divide our data into attributes of a vertex, i.e. the member variables of the vertex. It helps the gpu go through only 1 specific member variable of every vertex at a time, then go through the next member variable. As our vertex has only 1 member variable, the data is already in sequential order and dont need it to be divided by attributes.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);		// tells OpenGL how to look at the attribute as an array. 1st param: index of the attribute that must be modified (we have 1 attribute) 2nd param: how many pieces of data in a vertex 3rd param: data stored as floating point 4th param: whether we want to normalise it (dont) 5th param: how much data it should skip to get to the next same attribute 6th param: How much from the beginning it need to start to find the very first attribute of the first data
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);		// this will stop the binding to the m_vertexArrayObject so that it is not affected anymore

}


Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_vertexArrayObject);		// We want to delete the data of the vertex so that the gpu does not have access to them anymore
}

void Mesh::Draw() {
	glBindVertexArray(m_vertexArrayObject);		// binding the vertex array back so that the gpu can make changes to only it

	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);		// draw an array of data, param 1: the mode, param 2: where we want to start on the array, param 3: how much do you want to read

	glBindVertexArray(0);		// after we are done using the draw method we need to unbind so no unwanted changes happen to the vertex array
}
