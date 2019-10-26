#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include "object.hpp"

object::object(const std::vector<vertex>& vertices, const std::vector<GLuint>& indices) : vertices_(vertices), indices_(indices) {
  // init();
}

object::object(const std::string& file_path) {
  std::ifstream input(file_path.data(), std::ios::in);
  std::string line;
  while (getline(input, line)) {
    std::stringstream stream(line);
    std::string op;
    stream >> op;
    if (op == "v") {
      float x, y, z;
      stream >> x >> y >> z;
      vertices_.push_back({{x, y, z}});
    }
    // TODO 
  }
}

object::~object() {
  glDeleteBuffers(1, &vb_);
  glDeleteVertexArrays(1, &va_);
}

void object::init() {
  glGenVertexArrays(1, &va_);
  glGenBuffers(1, &vb_);
  glGenBuffers(1, &eb_);

  glBindVertexArray(va_);
    glBindBuffer(GL_ARRAY_BUFFER, vb_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(vertex), &vertices_[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint), &indices_[0], GL_STATIC_DRAW);
  glBindVertexArray(0);
}

void object::render() {
  glBindVertexArray(va_);
    glEnableVertexAttribArray(0); // position
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (vertex), (GLvoid*)0);
    glEnableVertexAttribArray(1); // color
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof (vertex), (GLvoid*)(3 * sizeof (GLfloat)));
    glEnableVertexAttribArray(2); // texture
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof (vertex), (GLvoid*)(6 * sizeof (GLfloat)));
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
	  glDisableVertexAttribArray(0);
	  glDisableVertexAttribArray(1);
  glBindVertexArray(0);
}


