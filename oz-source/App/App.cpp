//
//  app.cpp
//  GLFW
//
//  Created by Murphy M Stein on 9/21/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//


#include <chrono>

#include "App/App.h"

random_device App::rd;
mt19937 App::rng;

App* App::gApp = nullptr;
bool App::isExiting = false;

void App::window(int width, int height, string title) {
  Window* newWindow = new Window(width, height, title);
  windows_.push_back(newWindow);
}

App::App() {
  init();
  gApp = this;
}

App::~App() {
  cout << "inside destructor" << endl;
  isExiting = true;
  shutdown(1);
}

void App::onGLFWError(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

void App::onMouseEnterOrLeave(GLFWwindow* h, int msg) {

  Window* w = findWindowByHandle(h);
  if (w == nullptr) {
    cout << "Uh-oh, exited or found unknown window";
  } else {
    if (msg == GL_TRUE) {
      w->onMouseEnter();
    } else {
      w->onMouseLeave();
    }
  }
}

void App::onMouseMove(GLFWwindow* h, double x, double y) {
  Window* w = findWindowByHandle(h);
  if (w == nullptr) {
    cout << "UH-OH, requested window not found for mouse move event" << endl;
  } else {
    w->onMouseMove(x, y);
    gApp->onMouseMove(x, y);
    if (gApp->isDraggingLeft_) {
      gApp->onMouseDrag(w->mouseX() - gApp->startDragXLeft_, w->mouseY() - gApp->startDragYLeft_);
    }
  }
}

void App::onMouseButton(GLFWwindow* h, int button, int action) {
  Window* w = findWindowByHandle(h);
  if (w == nullptr) {
    cout << "UH-OH, requested window not found for onMouseButton." << endl;
  } else {
    double x = w->mouseX();
    double y = w->mouseY();
    if (action == GLFW_PRESS) {
      if (button == GLFW_MOUSE_BUTTON_LEFT) {
        gApp->startDragXLeft_ = x;
        gApp->startDragYLeft_ = y;
        gApp->isDraggingLeft_ = true;
        cout << "start dragging " << gApp->startDragXLeft_ << " " << gApp->startDragYLeft_ << endl;
        w->onMouseDownLeft(x, y);
      } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        w->onMouseDownRight(x, y);
      }
    } else if (action == GLFW_RELEASE) {
      if (button == GLFW_MOUSE_BUTTON_LEFT) {
        gApp->isDraggingLeft_ = false;
        w->onMouseUpLeft(x, y);
        gApp->onMouseUp(x, y);
      } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        w->onMouseUpRight(x, y);
      }
    }
  }
}

void App::onKeyPressed(GLFWwindow* h, int key, int action) {
  Window* w = findWindowByHandle(h);
  if (w == nullptr) {
    cout << "UH-OH, requested window not found for keypress" << endl;
  } else {
    char c = static_cast<char>(key);

    switch (action) {
      case GLFW_PRESS:
        w->onCharDown(c);
        w->onKeyDown(key);
        gApp->charDown(c, false);
        gApp->keys->makeDown(c);
        break;
      case GLFW_RELEASE:
        w->onCharUp(c);
        w->onKeyUp(key);
        gApp->keys->makeUp(c);
        break;
      case GLFW_REPEAT:
        w->onCharRepeat(c);
        w->onKeyRepeat(key);
        gApp->keys->makeDown(c);
        break;
    }

    bool superr_down =   glfwGetKey(h, GLFW_KEY_RSUPER) == GLFW_PRESS;
    bool superl_down =  glfwGetKey(h, GLFW_KEY_LSUPER) == GLFW_PRESS;
    if (key == GLFW_KEY_Q && (superr_down || superl_down)) {
      cout << "Super-Q caught..." << endl;
      gApp->shutdown(1);
    }
  }
}

Window* App::findWindowByHandle(GLFWwindow *request) {
  Window* w = nullptr;

  for (int i = 0; i < gApp->windows_.size(); i++) {
    if (gApp->windows_[i]->handle() == request) {
      w = gApp->windows_[i];
      break;
    }
  }

  return w;
}

void App::init() {  
  int glfw_init_done = glfwInit();
  if (glfw_init_done != GL_TRUE) {
    shutdown(0);
  } else {
    cout << "glfw initalized..." << endl;
  }

  glfwSetErrorCallback(App::onGLFWError);

  _frames = 0;
  _prev_fps_clock_time = chrono::high_resolution_clock::now();

  startDragXLeft_ = 0;
  startDragYLeft_ = 0;
  isDraggingLeft_ = false;

  keys = new Keyboard();
}

void App::run() {
  while (!isExiting) {

    updateFPS();
    for (int i = 0; i < windows_.size(); i++) {
      Window* w = windows_[i];
      if (w->isActive()) {
        glfwMakeContextCurrent(w->handle());
        update();
        //        w->onUpdate();
        //        w->onDraw();
        glfwSwapBuffers(w->handle());
      }
    }


    glfwPollEvents();
    uint32_t nDestroyed = 0;
    for (int i = 0; i < windows_.size(); i++) {
      Window* w = windows_[i];
      if (w->isActive() && glfwWindowShouldClose(w->handle())) {
        w->onClose();
        glfwDestroyWindow(w->handle());
      }
      if (w->isDestroyed()) {
        nDestroyed++;
      }
    }
    if (nDestroyed == windows_.size()) {
      isExiting = true;
    }
  }
  shutdown(1);
}

void App::freeResources()
{
  cout << "freeing resources..." << endl;
  cout << "freed resources." << endl;
}

void App::shutdown(int return_code)
{
  cout << "App is Shutting down..." << endl;
  App::isExiting = true;
  freeResources();
  glfwTerminate();
  exit(return_code);
}

void App::updateFPS() {
  using namespace chrono;
  auto now = high_resolution_clock::now();
  auto us = duration_cast<microseconds>(now - _prev_fps_clock_time).count();
  if (us >= 1e6) {
    _fps = ((float)1e6 / us) * (float)(_frames);
    _frames = 1;
    _prev_fps_clock_time = now;
  }
  _frames++;
}

double App::time() {
  using namespace chrono;
  auto now = high_resolution_clock::now();
  uint64_t us = duration_cast<microseconds>(now.time_since_epoch()).count();
  return us / 1000.0;
}
