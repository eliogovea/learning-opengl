#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "window.hpp"
#include "object.hpp"

namespace objects {
  std::vector<vertex> vertices_1 = {
    {{0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
    {{0.0f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}
  };

  object triangle_1{vertices_1, std::vector<GLuint>{0, 1, 2}};

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
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "usage: ./app vertex_shader_path fragment_shader_path" << std::endl;
    return 1;
  }

  auto window = Window(16 * 50, 9 * 50, "hello");

  shader shader_{argv[1], argv[2]};
  
  int step = 0;

  glm::mat4 model{1.0f};

  glm::mat4 view = glm::lookAt(glm::vec3(0, 0, -5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

  shader_.bind();
  glUniformMatrix4fv(shader_.locate_uniform("view"), 1, GL_FALSE, &view[0][0]);
  glUniformMatrix4fv(shader_.locate_uniform("proj"), 1, GL_FALSE, &proj[0][0]);

  objects::cube.init(); // !!!
  objects::triangle_1.init();
  
  // main loop
	while (!window.is_closed()) {
    window.clear();

    step++;

    float v = 2.0 * sin((float)step / 100.0);

    // pyramid
    model = glm::mat4(1.0f);
    model = glm::translate(glm::vec3(-0.5, -0.5, 0.0)) * model;
    model = glm::scale(glm::vec3(0.5, 0.5, 0.5))       * model;
    model = glm::translate(glm::vec3(v, v, 0))         * model;

    shader_.bind();
    glUniformMatrix4fv(shader_.locate_uniform("model"), 1, GL_FALSE, &model[0][0]);

    objects::cube.render();

    // triangle_1
    model = glm::mat4(1.0f);
    model = glm::translate(glm::vec3(-0.5, -0.5, 0.0)) * model;
    model = glm::scale(glm::vec3(0.5, 0.5, 0.5))       * model;
    model = glm::translate(glm::vec3(v, -v, 0))        * model;

    shader_.bind();
    glUniformMatrix4fv(shader_.locate_uniform("model"), 1, GL_FALSE, &model[0][0]);

    objects::triangle_1.render();

    window.update();
	}

	return 0;
}
