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
  
  shader shader_{argv[1], argv[2]};
  shader_.locate_uniform("model");
  shader_.locate_uniform("view");
  shader_.locate_uniform("proj");

  
  int step = 0;

  // glm::mat4 scale = glm::scale(glm::vec3(0.5, 0.5, 0.5));
  glm::mat4 translate = glm::translate(glm::vec3(-0.5, -0.5, 0.0));
  glm::mat4 model = translate;

  glm::mat4 view = glm::lookAt(glm::vec3(0, 0, -5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  // glm::mat4 view = glm::lookAt(glm::vec3(-4, 3, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

  // glm::mat4 proj = glm::mat4(1.0f);
  glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

  static std::vector<vertex> vertices_1 = {
    {{0.0f, 0.0f, 0.0f}},
    {{0.5f, 0.0f, 0.0f}},
    {{0.0f, 0.5f, 0.0f}}
  };

  static object triangle_1{vertices_1, std::vector<GLuint>{0, 1, 2}};

  static std::vector<vertex> vertices_pyramid = {
    {{0.0f, 0.0f, 0.0f}},
    {{1.0f, 0.0f, 0.0f}},
    {{1.0f, 1.0f, 0.0f}},
    {{0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f}} // top
  };

  static std::vector<GLuint> triangles_pyramid = {
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
  };

  static object pyramid{vertices_pyramid, triangles_pyramid};

  static std::vector<vertex> vertices_cube = {
    {{0.0f, 0.0f, 0.0f}},
    {{1.0f, 0.0f, 0.0f}},
    {{1.0f, 1.0f, 0.0f}},
    {{0.0f, 1.0f, 0.0f}},
    
    {{0.0f, 0.0f, 1.0f}},
    {{1.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, 1.0f}},
    {{0.0f, 1.0f, 1.0f}}
  };

  static std::vector<GLuint> triangles_cube = {
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

  static object cube{vertices_cube, triangles_cube};


    // main loop
	while (!window.is_closed()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // move to window

		glUseProgram(shader_.program_id());

    step++;
    float v = 2 * sin((float)step / 100.0);
    model = glm::translate(glm::vec3(-0.5, -0.5, 0.0)) * glm::translate(glm::vec3(v, 0, 0));

    glUniformMatrix4fv(shader_.locate_uniform("model"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(shader_.locate_uniform("view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(shader_.locate_uniform("proj"), 1, GL_FALSE, &proj[0][0]);

    // triangle_1.render();
    // pyramid.render();
    cube.render();
    
    window.update();
	}

	return 0;
}
