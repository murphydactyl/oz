//
//  keyboard.h
//  GLFW
//
//  Created by Murphy M Stein on 9/28/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//

#ifndef __GLFW__keyboard__
#define __GLFW__keyboard__

#include <iostream>
#include <GL/glfw.h>
#include <map>
#include <list>

using namespace std;

typedef int key_code_t;
typedef int key_state_t;

class KeyboardListener;

#define KEY_DOWN GLFW_PRESS
#define KEY_UP GLFW_RELEASE
#define VERBOSE_KEYEVENTS
class Keyboard {
  
public:
  Keyboard();
  ~Keyboard();
  void poll();
  void update(key_code_t, key_state_t);
  void release(int);
  void press(int);
  bool isDown(int);
  bool isUp(int);
  bool addListener(KeyboardListener*);
  bool removeListener(KeyboardListener*);
  list<KeyboardListener*>* listeners;
  
protected:
  key_state_t _state[256];
  key_state_t _prev_state[256];
};

#endif /* defined(__GLFW__keyboard__) */
