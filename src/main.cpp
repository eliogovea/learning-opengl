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
#include "texture.hpp"
#include "camera.hpp"

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cout << "usage: ./app obj_path vertex_shader_path fragment_shader_path texture_path" << std::endl;
    return 1;
  }

  auto window = Window(16 * 50, 9 * 50, "hello");

  object obj{argv[1]};
  obj.init();

  shader shader_{argv[2], argv[3]};
  texture texture_{argv[4]};
  
  int step = 0;

  glm::mat4 model{1.0f};

  camera camera_{glm::vec3{0, 10, 10}, glm::vec3{0, 0, 0}, glm::vec3{0, 1, 0}};

  glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

  shader_.bind();
  glUniformMatrix4fv(shader_.locate_uniform("proj"), 1, GL_FALSE, &proj[0][0]);

  // empty triangles 
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  // main loop
	while (!window.is_closed()) {
    window.clear();

    step++;

    float angle = step / 100.0;
    double cx = 5 * cos(angle);
    double cz = 5 * sin(angle);

    camera_.move(glm::vec3{cx + cx, 0, cz + cx});

    float v = sin((float)step / 10000.0);

    model = glm::mat4(1.0f);
    model = glm::scale(glm::vec3(0.5, 0.5, 0.5))       * model;
//    model = glm::translate(glm::vec3(-0.5, -0.5, 0.0)) * model;
//    model = glm::translate(glm::vec3(v, 0, 0))         * model;

    shader_.bind();

    glUniformMatrix4fv(shader_.locate_uniform("model"), 1, GL_FALSE, &model[0][0]);

    glm::mat4 view = camera_.get_matrix();
    glUniformMatrix4fv(shader_.locate_uniform("view"), 1, GL_FALSE, &view[0][0]);

    texture_.bind();

    obj.render();

    window.update();
	}

	return 0;
}
