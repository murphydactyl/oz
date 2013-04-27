//
//  keyboard.cpp
//  GLFW
//
//  Created by Murphy M Stein on 9/28/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//

#include "App/Keyboard.h"
#include "App/KeyboardListener.h"

using namespace std;

Keyboard::Keyboard() {
  listeners = nullptr;
  for (int i = 0; i < 256; i++) {
    update(i, glfwGetKey(i));
    _prev_state[i] = _state[i];
  }
  listeners = new list<KeyboardListener*>();
}

Keyboard::~Keyboard() {
  delete listeners;
}

void Keyboard::update(key_code_t i, key_state_t state) {
  _prev_state[i] = _state[i];
  if (state == GLFW_PRESS) {
    press(i);
  } else {
    release(i);
  }
}

void Keyboard::release(key_code_t keyCode) {
  _state[keyCode] = KEY_UP;
	if (listeners != nullptr)
		for (auto l : *listeners) {
			l->keyUp(keyCode);
		}
}

void Keyboard::press(key_code_t keyCode) {
  _state[keyCode] = KEY_DOWN;
	if (listeners != nullptr)
		for (auto l : *listeners) {
				l->keyDown(keyCode);
		}
}

void Keyboard::poll() {
  for (int k = 0; k < 256; k++) {
		key_code_t newState = glfwGetKey(k);
		if (_state[k] != newState)
			update(k, newState);
		else if (isDown(k))
			for (auto l : *listeners)
				l->keyStillDown(k);
    else
			for (auto l : *listeners)
				l->keyStillUp(k);
	}
}

bool Keyboard::isDown(key_code_t i) {
  return _state[i] == KEY_DOWN;
}

bool Keyboard::isUp(key_code_t i) {
  return _state[i] == KEY_UP;
}

bool Keyboard::addListener(KeyboardListener *newListener) {
	for (auto l : *listeners) {
		if (l == newListener)
      return false;
  }
  
  listeners->push_back(newListener);
  return true;
}
