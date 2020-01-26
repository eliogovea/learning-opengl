#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "window.hpp"
#include "object.hpp"
#include "texture.hpp"
#include "camera.hpp"

#include "filter.hpp"

#include "util.hpp"

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

  object axis{"../resources/objects/cylinder.obj"};
  axis.init();

  texture x_axis_texture{"../resources/textures/blue.jpeg"};
  texture y_axis_texture{"../resources/textures/red.jpeg"};
  texture z_axis_texture{"../resources/textures/green.jpeg"};
  
  glm::mat4 model{1.0f};

  camera camera_{glm::vec3{10, 0, 5}, glm::vec3{0, 0, 0} - glm::vec3{10, 0, 5}, glm::vec3{0, 0, 1}};

  glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

  shader_.bind();
  glUniformMatrix4fv(shader_.locate_uniform("proj"), 1, GL_FALSE, &proj[0][0]);

  // empty triangles 
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //

  reader serial{"/dev/ttyACM0", 19200};
  mpu mpu_{serial};

  filter_0 filter_mock{mpu_};
  filter_complementary cf{mpu_};

  const glm::vec3 world_x{1, 0, 0};
  const glm::vec3 world_y{0, 1, 0};
  const glm::vec3 world_z{0, 0, 1};

  filter& filter_ = filter_mock;
  // filter& filter_ = cf;

  // main loop
  while (!window.is_closed()) {
    // input
    filter_.update();

    window.clear();

    shader_.bind();
    glm::mat4 view = camera_.get_matrix();
    glUniformMatrix4fv(shader_.locate_uniform("view"), 1, GL_FALSE, &view[0][0]);

    // axis_y
    model = glm::mat4(1.0f);
    model = glm::scale(glm::vec3(0.1, 1, 0.1)) * model;
    model = filter_.model()                    * model;

    shader_.bind();
    glUniformMatrix4fv(shader_.locate_uniform("model"), 1, GL_FALSE, &model[0][0]);

    y_axis_texture.bind();
    axis.render();
 
    // axis_x
    model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)(0.5f * M_PI), glm::vec3{0.0f, 0.0f, 1.0f});
    model = glm::scale(glm::vec3(1, 0.1, 0.1)) * model;
    model = filter_.model()                    * model;

    shader_.bind();
    glUniformMatrix4fv(shader_.locate_uniform("model"), 1, GL_FALSE, &model[0][0]);

    x_axis_texture.bind();
    axis.render();

    // axis_z
    model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)(0.5f * M_PI), glm::vec3{1.0f, 0.0f, 0.0f});
    model = glm::scale(glm::vec3(0.1, 0.1, 1)) * model;
    model = filter_.model()                    * model;

    shader_.bind();
    glUniformMatrix4fv(shader_.locate_uniform("model"), 1, GL_FALSE, &model[0][0]);

    z_axis_texture.bind();
    axis.render();

    // obj
    model = glm::mat4(1.0f);
    model = glm::scale(glm::vec3(0.5, 0.5, 0.5)) * model;
    model = filter_.model()                    * model;

    shader_.bind();
    glUniformMatrix4fv(shader_.locate_uniform("model"), 1, GL_FALSE, &model[0][0]);

    texture_.bind();

    obj.render();

    window.update();
  }
  return 0;
}
