//
//  app.h
//  OZ
//
//  Created by Murphy M Stein on 4/20/13.
//  Copyright (c) 2013 Murphy M Stein. All rights reserved.
//

#ifndef __OZ__APP__APP__H__
#define __OZ__APP__APP__H__

#include <iostream>
#include <random>
#include <chrono>
#include <sstream>
#include <GL/glfw3.h>
#include <OpenGL/gl3.h>
#include "App/Window.h"
#include "Vector/Vector.h"

using namespace std;

class Window;

class App {
public:
  App();
  ~App();
  void run();
  virtual void update()=0;
  virtual void charDown(char c, bool isRepeat) {};
  virtual void onMouseMove(double x, double y) {};
  virtual void onMouseDrag(double dx, double dy) {};
  virtual void onMouseUp(double x, double y) {};
  void window(int width = 512, int height = 512, string title = "untitled");

  //----------------------------------------------------------------------------
  // STATIC MEMBERS
  //----------------------------------------------------------------------------
  static void requestShutDown() { isExiting = true; }
  static void onGLFWError(int error, const char* description);
  static void onMouseEnterOrLeave(GLFWwindow* win, int msg);
  static void onMouseMove(GLFWwindow* win, double x, double y);
  static void onKeyPressed(GLFWwindow* win, int key, int action);
  static void onMouseButton(GLFWwindow* win, int button, int action);

protected:
  void init(void);
	
  virtual void shutdown(int);
  void freeResources(void);

  Vector<Window*> windows_;

  // CLOCK & FPS ///////////////////////////////////////////////////////////////
  chrono::time_point<std::chrono::high_resolution_clock> _prev_fps_clock_time;
  float _fps;
  int _frames = 1;
  void updateFPS();
  double time();
  double startDragXLeft_;
  double startDragYLeft_;
  bool isDraggingLeft_;

  //----------------------------------------------------------------------------
  // STATIC MEMBERS
  //----------------------------------------------------------------------------
  static std::random_device rd;
  static std::mt19937 rng;
  static App* gApp;
  static bool isExiting;
  static Window* findWindowByHandle(GLFWwindow* request);
	
};

#endif
