//
//  keyboardlistener.h
//  GLFW
//
//  Created by Murphy M Stein on 10/5/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//

#ifndef __GLFW__keyboardlistener__
#define __GLFW__keyboardlistener__

#include <iostream>
#include "keyboard.h"

class KeyboardListener {

public:
  virtual void keyDown(key_code_t code) {};
  virtual void keyUp(key_code_t code) {};
  virtual void keyStillDown(key_code_t code) {};
  virtual void keyStillUp(key_code_t code) {};
};

#endif /* defined(__GLFW__keyboardlistener__) */
