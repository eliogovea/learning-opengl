#include <GL/glew.h>

#include "object.hpp"

object::object(const std::vector<vertex>& vertices, const std::vector<GLuint>& indices) : vertices_(vertices), indices_(indices) {
  init();
}

object::object(const std::string& file_path) {
  // TODO
}

object::~object() {
  // TODO
}

void object::init() {
  glGenVertexArrays(1, &va_);
  glBindVertexArray(va_);

  glGenBuffers(1, &vb_);
  glBindBuffer(GL_ARRAY_BUFFER, vb_);
  glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(vertex), &vertices_[0], GL_STATIC_DRAW);

  // TODO eb_
//  glGenBuffers(1, &eb_);
//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb_);
//  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint), &indices_[0], GL_STATIC_DRAW);
}

void object::render() {
  glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vb_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
}
