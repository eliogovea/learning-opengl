#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "window.hpp"

int main() {
  auto window = Window(16 * 50, 9 * 50, "hello");

  // load and compile shaders

  std::cout << "loading vetex shader" << std::endl;
  auto code_vs = shader::load("../src/example.vertexshader");
  std::cout << "vertex shader code:\n" << code_vs << std::endl;

  std::cout << "loading fragment shader" << std::endl;
  auto code_fs = shader::load("../src/example.fragmentshader");
  std::cout << "fragment shader code:\n" << code_fs << std::endl;

  std::cout << "compiling vertex shader" << std::endl;
  auto id_vs = shader::compile(GL_VERTEX_SHADER, code_vs);
  std::cout << "vertex shader id: " << id_vs << std::endl;

  std::cout << "compiling fragment shader" << std::endl;
  auto id_fs = shader::compile(GL_FRAGMENT_SHADER, code_fs);
  std::cout << "fragment shader id: " << id_fs << std::endl;

  std::cout << "linking ..." << std::endl;
  auto id_prog = shader::link({id_vs, id_fs});
  std::cout << "program id: " << id_prog << std::endl;

  // triangle vertices
  static const GLfloat vertices[] {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

  GLuint id_va; // vertex array
  glGenVertexArrays(1, &id_va);
  glBindVertexArray(id_va);

	GLuint id_vb; // vertex buffer
	glGenBuffers(1, &id_vb);
	glBindBuffer(GL_ARRAY_BUFFER, id_vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // main loop
	while (true) {
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(id_prog);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, id_vb);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);

    window.update();
    // TODO check if ESC waw pressed
	}

	glDeleteBuffers(1, &id_vb);
	glDeleteVertexArrays(1, &id_va);
	glDeleteProgram(id_prog);

	glfwTerminate();

	return 0;
}

