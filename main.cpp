#include <iostream>
#include <GL\glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"

int main(int argc, char* args[]) {
	Display display(800, 600, "OpenGL");

	Shader shader(".\\res\\basicShader");

	Texture texture(".\\res\\test.jpg");

	Transform transform;

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)), 
					   	  Vertex(glm::vec3(0, 0.5, 0),     glm::vec2(0.5, 1.0)), 
					      Vertex(glm::vec3(0.5, -0.5, 0),  glm::vec2(1.0, 0)) };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	float counter = 0.0f;

	while (!display.IsClosed()) {
		display.Clear(0.0f, 0.15, 0.3f, 1.0f);

		transform.GetPos().x = sinf(counter);
		transform.GetRot().z = counter;
		transform.SetScale(glm::vec3(cosf(counter), cosf(counter), cosf(counter)));


		shader.Bind();
		shader.Update(transform);
		texture.Bind(0);
		mesh.Draw();
		display.Update();

		counter += 0.001f;
	}

	return 0;
}