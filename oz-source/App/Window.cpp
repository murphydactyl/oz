#include "Window.h"


Window::Window(int width, int height, std::string title) {

  width_ = width;
  height_ = height;
  title_ = title;
  isDestroyed_ = false;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  //glfwWindowHint(GLFW_DECORATED, GL_FALSE);
  //glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 2);

  handle_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if (!handle_) {
    App::requestShutDown();
  }

  glfwSetCursorEnterCallback(handle_, App::onMouseEnterOrLeave);
  glfwSetCursorPosCallback(handle_, App::onMouseMove);
  glfwSetKeyCallback(handle_, App::onKeyPressed);
  glfwSetMouseButtonCallback(handle_, App::onMouseButton);

  int major, minor, rev;
  major = glfwGetWindowParam(handle_, GLFW_CONTEXT_VERSION_MAJOR);
  minor = glfwGetWindowParam(handle_, GLFW_CONTEXT_VERSION_MINOR);
  rev = glfwGetWindowParam(handle_, GLFW_CONTEXT_REVISION);
  fprintf(stderr, "OpenGL version recieved: %d.%d.%d\n", major, minor, rev);

  glEnable(GL_BLEND);
  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glfwMakeContextCurrent(handle_);
  glfwShowWindow(handle_);

}

void Window::onDraw() {
  glClearColor(0.2, 0.2, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Window::onUpdate() {

}

void Window::onMouseEnter() {
  cout << "mouse ENTERED window " << title_ << endl;
}

void Window::onMouseLeave() {
  cout << "mouse EXITED window " << title_ << endl;
}

void Window::onMouseMove(double x, double y) {
  mouseX_ = y;
  mouseY_ = x;
  if (isFocused()) {
    //    cout << title_ << " says: " << "mouse @ " << mouseX_ << " " << mouseY_ << endl;
  }
}

void Window::onMouseDownLeft(double x, double y) {
  mouseWasDownLeft_ = mouseDownLeft_;
  mouseDownLeft_ = true;

  if (isFocused()) {
    //    cout << title_ << " says: " << " LEFT BUTTON PRESSED." << endl;
  }
}

void Window::onMouseUpLeft(double x, double y) {
  mouseWasDownLeft_ = mouseDownLeft_;
  mouseDownLeft_ = false;
  if (isFocused()) {
    //    cout << title_ << " says: " << " LEFT BUTTON RELEASED." << endl;
  }
}

void Window::onMouseDownRight(double x, double y) {
  if (isFocused()) {
    //    cout << title_ << " says: " << " RIGHT BUTTON PRESSED." << endl;
  }
}

void Window::onMouseUpRight(double x, double y) {
  if (isFocused()) {
    //    cout << title_ << " says: " << " RIGHT BUTTON RELEASED." << endl;
  }
}

void Window::onCharDown(char c) {
  //  cout << title_ << " says: " << "char " << c << " was PRESSED." << endl;
}

void Window::onCharUp(char c) {
  //  cout << title_ << " says: " << "char " << c << " was RELEASED." << endl;
}

void Window::onCharRepeat(char c) {
  //  cout << title_ << " says: " << "char " << c << " was REPEAT." << endl;
}

void Window::onKeyDown(int c) {
  //  cout << title_ << " says: " << "key code " << c << " was PRESSED." << endl;
}

void Window::onKeyUp(int c) {
  //  cout << title_ << " says: " << "key code " << c << " was RELEASED." << endl;
}

void Window::onKeyRepeat(int c) {
  //  cout << title_ << " says: " << "key code " << c << " was REPEAT." << endl;
}

void Window::title(string title) {
  title_ = title;
  glfwSetWindowTitle(handle_, title.c_str());
}


void Window::onClose() {
  glfwPollEvents();
  bool superlkey = glfwGetKey(handle_, GLFW_KEY_LSUPER) == GLFW_PRESS;
  bool superrkey = glfwGetKey(handle_, GLFW_KEY_RSUPER) == GLFW_PRESS;
  if (superrkey || superlkey) {
    cout << title_ << " caught quit " << endl;
    App::requestShutDown();
  }
  cout << "Should close window named: " << title_ << endl;
  isDestroyed_ = true;
}
