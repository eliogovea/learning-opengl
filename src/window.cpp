#include <iostream>

#include "window.hpp"

Window::Window(int width, int height, const std::string& title) {
  if (!glfwInit()) {
    std::cout << "glfw init filed" << std::endl;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if (!window_) {
    std::cout << "failed to create window" << std::endl;
  }

  is_closed_ = false;

  glfwMakeContextCurrent(window_);

	glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    std::cout << "failed to init glew" << std::endl;
  }

  glfwSetInputMode(window_, GLFW_STICKY_KEYS, GL_TRUE);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

void Window::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::is_closed() const noexcept {
  return is_closed_;
}

void Window::update() {
  if (glfwGetKey(window_, GLFW_KEY_ESCAPE ) == GLFW_PRESS) {
    is_closed_ = true;
    return;
  }
  if (glfwWindowShouldClose(window_)) {
    is_closed_ = true;
    return;
  }
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

Window::~Window() {
  glfwTerminate();
  std::cout << "destroy window" << std::endl;
}
