//
//  app.h
//  ModelVis
//
//  Created by Murphy M Stein on 4/20/13.
//  Copyright (c) 2013 Murphy M Stein. All rights reserved.
//

#ifndef __ModelVis__APP__
#define __ModelVis__APP__

#include <iostream>
#include <random>
#include <chrono>

#include "App/Keyboard.h"
#include "App/KeyboardListener.h"
#include "App/Mouse.h"
#include "App/MouseListener.h"

using namespace std;

class App : public KeyboardListener, MouseListener {
public:
  App(int width = 512, int height = 512);
  ~App();
  virtual void run();
  uint32_t getWidth();
  uint32_t getHeight();
  void setWindowTitle(string title);
	
protected:
  int screen_width;
  int screen_height;
  void init(void);
	
  virtual void draw(void);
  virtual void update();
  virtual void shutDown(int);
  void freeResources(void);
  void onReshape(int,int);
	
  void checkError(string msg="", bool always_print = false);
  
  static App* gApp;
	
  virtual void keyStillDown(key_code_t);
  virtual void keyUp(key_code_t);
  virtual void keyDown(key_code_t);
  virtual void mouseDrag(int, int);
  virtual void mouseScroll(int);
  static int handleWindowClose(void);
  static Keyboard* keys;
  static Mouse* mouse;
  static bool isExiting;
	
  // STATE VARIABLES ///////////////////////////////////////////////////////////
  bool _bShowNormals;

  // CLOCK & FPS ///////////////////////////////////////////////////////////////
  chrono::time_point<std::chrono::high_resolution_clock> _prev_fps_clock_time;
  float _fps;
  int _frames = 1;
  void updateFPS();
  uint64_t time();

  //----------------------------------------------------------------------------
  // STATIC MEMBERS
  //----------------------------------------------------------------------------
  static std::random_device rd;
  static std::mt19937 rng;
	
private:
  int initResources(void);
	
};

#endif /* defined(__ModelVis__app__) */
