#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
  public:
    Window(int width, int height, const std::string& title);
    virtual ~Window();
    bool is_closed() const noexcept;
    void update();
  private:
    GLFWwindow* window_; // TODO use unique ptr
    bool is_closed_{true}; // should use atomic ???
};
