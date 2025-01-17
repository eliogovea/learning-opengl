project(simple_triangle)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_STANDARD 14)

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS         "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG   "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(PkgConfig REQUIRED)

# OpenGL
find_package(OpenGL REQUIRED)

# GLEW
find_package(GLEW REQUIRED STATIC)
include_directories(${GLEW_INCLUDE_DIRS})

# GLFW
find_package(glfw3 REQUIRED)

set(
  SOURCE_FILES 
  src/window.cpp
  src/shader.cpp
  src/object.cpp
  src/stb_image.c
  src/texture.cpp
  src/tiny_obj_loader.cpp
  src/main.cpp
)

add_executable(app ${SOURCE_FILES})
target_link_libraries(
  app 
  OpenGL::GL 
  GLEW::GLEW
  glfw
) 
