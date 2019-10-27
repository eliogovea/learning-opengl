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

  for (size_t s = 0; s < shapes.size(); s++) {
    // Loop over faces(polygon)
    size_t index_offset = 0;
    for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
      int fv = shapes[s].mesh.num_face_vertices[f];

      // Loop over vertices in the face.
      for (size_t v = 0; v < fv; v++) {
        // access to vertex
        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
        tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
        tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
        tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
        tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
        tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
        tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
        tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
        tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];
        // Optional: vertex colors
        tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
        tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
        tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];

        vertices_.emplace_back(glm::vec3{vx, vy, vz}, glm::vec3{red, green, blue}, glm::vec2{tx, ty});
      }
      index_offset += fv;
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


