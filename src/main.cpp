#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
// #include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "window.hpp"
#include "object.hpp"
#include "camera.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "usage: ./app vertex_shader_path fragment_shader_path" << std::endl;
    return 0;
  }

  auto window = Window(16 * 50, 9 * 50, "hello");

  // load and compile shaders

  std::cout << "loading vetex shader" << std::endl;
  auto code_vs = shader::load(argv[1]);
  std::cout << "vertex shader code:\n" << code_vs << std::endl;

  std::cout << "loading fragment shader" << std::endl;
  auto code_fs = shader::load(argv[2]);
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

  GLuint id_model = glGetUniformLocation(id_prog, "model");
  GLuint id_view  = glGetUniformLocation(id_prog, "view");
  GLuint id_proj  = glGetUniformLocation(id_prog, "proj");
  
  int step = 0;

  // glm::mat4 scale = glm::scale(glm::vec3(0.5, 0.5, 0.5));
  glm::mat4 translate = glm::translate(glm::vec3(-0.5, -0.5, 0.0));
  glm::mat4 model = translate;

  glm::mat4 view = glm::lookAt(glm::vec3(0, 0, -5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  // glm::mat4 view = glm::lookAt(glm::vec3(-4, 3, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

  // glm::mat4 proj = glm::mat4(1.0f);
  glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

  std::vector<vertex> vertices_1 = {
    {{0.0f, 0.0f, 0.0f}},
    {{0.5f, 0.0f, 0.0f}},
    {{0.0f, 0.5f, 0.0f}}
  };

  object triangle_1{vertices_1, std::vector<GLuint>{0, 1, 2}};

  std::vector<vertex> vertices_pyramid = {
    {{0.0f, 0.0f, 0.0f}},
    {{1.0f, 0.0f, 0.0f}},
    {{1.0f, 1.0f, 0.0f}},
    {{0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f}} // top
  };

  std::vector<GLuint> triangles_pyramid = {
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
  };

  object pyramid{vertices_pyramid, triangles_pyramid};

  std::vector<vertex> vertices_cube = {
    {{0.0f, 0.0f, 0.0f}},
    {{1.0f, 0.0f, 0.0f}},
    {{1.0f, 1.0f, 0.0f}},
    {{0.0f, 1.0f, 0.0f}},
    
    {{0.0f, 0.0f, 1.0f}},
    {{1.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, 1.0f}},
    {{0.0f, 1.0f, 1.0f}}
  };

  std::vector<GLuint> triangles_cube = {
    0, 1, 2,
    2, 3, 0, 

    0, 1, 4,
    4, 5, 1,

    1, 2, 5,
    5, 6, 2, 

    2, 3, 6,
    6, 7, 3,

    3, 0, 7,
    7, 4, 0,

    4, 5, 6,
    6, 7, 4
  };

  object cube{vertices_cube, triangles_cube};

  // main loop
	while (!window.is_closed()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // move to window

		glUseProgram(id_prog);

    step++;
    float v = 2 * sin((float)step / 100.0);
    model = glm::translate(glm::vec3(-0.5, -0.5, 0.0)) * glm::translate(glm::vec3(v, 0, 0));

    glUniformMatrix4fv(id_model, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(id_view, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(id_proj, 1, GL_FALSE, &proj[0][0]);

    // triangle_1.render();
    // pyramid.render();
    cube.render();
    
    window.update();
	}

  glDeleteProgram(id_prog);

	return 0;
}
