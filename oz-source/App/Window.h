#ifndef __OZ__APP__WINDOW__H__
#define __OZ__APP__WINDOW__H__

#include <iostream>
#include "App/App.h"

using namespace std;

class Window {
public:
  Window(int width = 512, int height = 512, string title = "untitled");
  ~Window();

  virtual void onDraw();
  virtual void onUpdate();
  virtual void onClose();
  virtual void onMouseEnter();
  virtual void onMouseLeave();
  virtual void onMouseMove(double x, double y);
  virtual void onMouseDownLeft(double x, double y);
  virtual void onMouseUpLeft(double x, double y);
  virtual void onMouseDownRight(double x, double y);
  virtual void onMouseUpRight(double x, double y);
  virtual void onCharDown(char c);
  virtual void onCharUp(char c);
  virtual void onCharRepeat(char c);
  virtual void onKeyDown(int key);
  virtual void onKeyUp(int key);
  virtual void onKeyRepeat(int ket);
  virtual double mouseX() { return mouseX_; }
  virtual double mouseY() { return mouseY_; }
  virtual bool mouseDown() { return mouseDownLeft_; }
  virtual bool mouseUp() { return !mouseDownLeft_; }
  uint32_t width() { return width_; }
  uint32_t height() { return height_; }

  bool isActive() { return !isDestroyed_; };

  virtual GLFWwindow* handle() { return handle_; }
  virtual string title() { return title_; }
  virtual void title(string title);
  virtual bool isFocused() { return glfwGetWindowParam(handle_, GLFW_FOCUSED); }
  virtual bool isVisible() { return glfwGetWindowParam(handle_, GLFW_VISIBLE); }
  virtual bool isIconified() { return glfwGetWindowParam(handle_, GLFW_ICONIFIED); }
  virtual bool isDecorated() { return glfwGetWindowParam(handle_, GLFW_DECORATED); }
  virtual bool isResizable() { return glfwGetWindowParam(handle_, GLFW_RESIZABLE); }
  virtual bool isDestroyed() { return isDestroyed_; };

protected:
  GLFWwindow* handle_;
  uint32_t width_;
  uint32_t height_;
  string title_;
  double mouseX_;
  double mouseY_;
  bool mouseDownLeft_;
  bool mouseWasDownLeft_;
  bool mouseDownRight_;
  bool mouseWasDownRight_;
  bool isDestroyed_;

};

#endif
