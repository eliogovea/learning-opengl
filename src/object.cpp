#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include "tiny_obj_loader.h"

#include "object.hpp"

object::object(const std::vector<vertex>& vertices, const std::vector<GLuint>& indices) : vertices_(vertices), indices_(indices) {
  // init();
}

object::object(const std::string& file_path) {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  std::string warn;
  std::string err;

  bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, file_path.c_str());

  if (!warn.empty()) {
    std::cout << warn << std::endl;
  }

  if (!err.empty()) {
    std::cerr << err << std::endl;
  }

  for (auto& shape: shapes) {
    size_t offset = 0;
    for (auto& face_size: shape.mesh.num_face_vertices) {
      for (size_t vertex_id = 0; vertex_id < face_size; vertex_id++) {
        auto idx = shape.mesh.indices[offset + vertex_id];

        auto vx = attrib.vertices[3 * idx.vertex_index + 0];
        auto vy = attrib.vertices[3 * idx.vertex_index + 1];
        auto vz = attrib.vertices[3 * idx.vertex_index + 2];

        GLfloat nx = 0.0f;
        GLfloat ny = 0.0f;
        GLfloat nz = 0.0f;
        if (3 * idx.normal_index + 2 < attrib.normals.size()) {
          nx = attrib.normals[3 * idx.normal_index + 0];
          ny = attrib.normals[3 * idx.normal_index + 1];
          nz = attrib.normals[3 * idx.normal_index + 2];
        }

        GLfloat tx = 0.0f;
        GLfloat ty = 0.0f;
        if (2 * idx.texcoord_index + 1 < attrib.texcoords.size()) {
          tx = attrib.texcoords[2 * idx.texcoord_index + 0];
          ty = attrib.texcoords[2 * idx.texcoord_index + 1];
        }

        GLfloat r = 0.0f;
        GLfloat g = 0.0f;
        GLfloat b = 0.0f;
        if (3 * idx.vertex_index + 2 < attrib.colors.size()) {
          r = attrib.colors[2 * idx.vertex_index + 0];
          g = attrib.colors[2 * idx.vertex_index + 1];
          b = attrib.colors[2 * idx.vertex_index + 2];
        }

        vertices_.emplace_back(glm::vec3{vx, vy, vz}, glm::vec3{r, g, b}, glm::vec2{tx, ty});
      }
      offset += face_size;
    }
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
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0); // position
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof (vertex), (GLvoid*)(3 * sizeof (GLfloat)));
    glEnableVertexAttribArray(1); // color
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof (vertex), (GLvoid*)(6 * sizeof (GLfloat)));
    glEnableVertexAttribArray(2); // texture
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint), &indices_[0], GL_STATIC_DRAW);
  glBindVertexArray(0);
}

void object::render() {
  glBindVertexArray(va_);
  glDrawArrays(GL_TRIANGLES, 0, vertices_.size());
//    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}


