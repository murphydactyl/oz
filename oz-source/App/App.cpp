//
//  app.cpp
//  GLFW
//
//  Created by Murphy M Stein on 9/21/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//


#include <chrono>

#include "App/app.h"


Keyboard* App::keys = nullptr;
Mouse* App::mouse = nullptr;
App* App::gApp = nullptr;
bool App::isExiting = false;

random_device App::rd;
mt19937 App::rng;

void App::mouseDrag(int x, int y) {
}

void App::mouseScroll(int s) {
}


void App::keyUp(key_code_t keyCode) {
  char keyChar = static_cast<char>(keyCode);
  switch (keyChar) {
    case 'L':
      break;
    case 'N':
      break;
    }
}

void App::keyDown(key_code_t keyCode) {
}

void App::keyStillDown(key_code_t keyCode) {
  char keyChar = static_cast<char>(keyCode);
  switch (keyChar) {
    case 'S':
      break;
    }
}

App::App(int width, int height) {
  screen_width = width;
  screen_height = height;
  init();
  gApp = this;
}

App::~App() {
  cout << "inside destructor" << endl;
  isExiting = true;
  shutDown(1);
}


int App::initResources()
{
  _frames = 0;
  _prev_fps_clock_time = chrono::high_resolution_clock::now();

  return 1;
}

void App::init() {
  
  int glfw_init_done = glfwInit();
  if (glfw_init_done != GL_TRUE) {
      shutDown(0);
    } else {
      cout << "glfw initalized..." << endl;
    }
  
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
  glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwOpenWindowHint( GLFW_REFRESH_RATE, 60 );																		// doesn't seem to go past 60
  //glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 2);

  if (! glfwOpenWindow(screen_width, screen_height,
                       32, 32, 32, 32, 24, 8, GLFW_WINDOW)) {
      shutDown(1);
    }
  int major, minor, rev;
  glfwGetGLVersion(&major, &minor, &rev);
  fprintf(stderr, "OpenGL version recieved: %d.%d.%d\n", major, minor, rev);
  
  glfwSetWindowTitle("App");
  glfwSetWindowCloseCallback(handleWindowClose);
  glfwSwapInterval(1);																													// 1 = vsync, 0 = no vsync
  glEnable(GL_BLEND);
  //glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  App::keys = new Keyboard();
  App::keys->addListener(this);
  App::mouse = new Mouse();
  App::mouse->addListener(this);

  initResources();
}

void App::run() {
  while(!isExiting)
    {
      keys->poll();
      mouse->poll();
      update();
      draw();
      glfwSwapBuffers();
    }
  shutDown(1);
}

void App::update() {
  updateFPS();
}

void App::draw() {
  glClearColor(0.2, 0.2, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

int GLFWCALL App::handleWindowClose() {
  cout << "Window is closing..." << endl;
  App::isExiting = true;
  gApp->shutDown(1);
  return 1;
}

void App::freeResources()
{
  cout << "freeing resources..." << endl;
  delete keys;
  delete mouse;
  cout << "freed resources." << endl;
}

void App::shutDown(int return_code)
{
  cout << "App is Shutting down..." << endl;
  App::isExiting = true;
  freeResources();
  glfwTerminate();
  exit(return_code);
}

void App::onReshape(int width, int height) {
  screen_width = width;
  screen_height = height;
  glViewport(0, 0, screen_width, screen_height);
}

uint32_t App::getWidth() {
  return screen_width;
}

uint32_t App::getHeight() {
  return screen_height;
}

void App::setWindowTitle(string title) {
  glfwSetWindowTitle(title.c_str());
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

uint64_t App::time() {
  using namespace chrono;
  auto now = high_resolution_clock::now();
  uint64_t ms = duration_cast<milliseconds>(now.time_since_epoch()).count();
  return ms;
}
