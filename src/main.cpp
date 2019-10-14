#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "window.hpp"
#include "object.hpp"

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

/*
  std::vector<vertex> vertices = {
    {{-0.5f, -0.5f, 0.0f}},
    {{0.5f, -0.5f, 0.0f}},
    {{0.0f, 0.5f, 0.0f}}
  };
  std::vector<GLuint> indices = {0, 1, 2};
*/

/*
  std::vector<vertex> vertices = {
    {{-0.5f, -0.5f, 0.0f}},
    {{0.5f, -0.5f, 0.0f}},
    {{-0.5f, 0.5f, 0.0f}},

    {{0.5f, -0.5f, 0.0f}},
    {{-0.5f, 0.5f, 0.0f}},
    {{0.5f, 0.5f, 0.0f}},
  };
*/

  std::vector<vertex> vertices = {
    {{-0.5f, -0.5f, 0.0f}},
    {{0.5f, -0.5f, 0.0f}},
    {{-0.5f, 0.5f, 0.0f}},
    {{0.5f, 0.5f, 0.0f}},
  };

  std::vector<GLuint> indices = {
    0, 1, 2,
    0, 1, 3
  };

  object obj{vertices, indices};

  // main loop
	while (true) {
		glClear(GL_COLOR_BUFFER_BIT); // move to window

		glUseProgram(id_prog);

    // triangle.render();
    obj.render();
    
    window.update();
    // TODO check if ESC waw pressed
	}

	glfwTerminate();

	return 0;
}
