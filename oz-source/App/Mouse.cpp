//
//  mouse.cpp
//  ModelVis
//
//  Created by Murphy M Stein on 12/2/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//

#include "App/Mouse.h"
#include "App/MouseListener.h"

Mouse::Mouse() {

	listeners = new list<MouseListener*>();
	_state.resize(MAX_BUTTON_CODE);
	_prev_state.resize(MAX_BUTTON_CODE);
	
}

void Mouse::handleRelease(button_code_t id) {
	if (id < 0 || id >= _state.size()) {
		return;
	}
	
	_prev_state[id] = _state[id];
	_state[id] = BUTTON_UP;
	
	if (listeners != nullptr) {
		for (auto l : *listeners) {
			l->mouseUp(id, x(), y());
		}
	}
}

void Mouse::handlePress(button_code_t id) {
	if (id < 0 || id >= _state.size()) {
		return;
	}
	
	_prev_state[id] = _state[id];
	_state[id] = BUTTON_DOWN;
	
	if (listeners != nullptr) {
		for (auto l : *listeners) {
			l->mouseDown(id, x(), y());
		}
	}
}

void Mouse::handleMove() {
	if (listeners != nullptr) {
		for (auto l: *listeners) {
			l->mouseMove(_x, _y);
			l->mouseMoveDelta(_x - _prev_x, _y - _prev_y);
			if (_is_dragging) {
				l->mouseDrag(_x - _prev_x, _y - _prev_y);
			}
		}
	}
}

void Mouse::handleScroll() {
	if (listeners != nullptr) {
		for (auto l: *listeners) {
			l->mouseScroll(_scroll - _prev_scroll);
		}
	}
}


bool Mouse::isDown(button_code_t id) {
	if (id < 0 || id >= _state.size()) {
		return false;
	}
	return _state[id] == BUTTON_DOWN;
}

bool Mouse::isUp(button_code_t id) {
	if (id < 0 || id >= _state.size()) {
		return false;
	}
	return _state[id] == BUTTON_UP;
}

bool Mouse::addListener(MouseListener* listener) {
	for (auto l : *listeners)
		if (l == listener)
			return false;
	listeners->push_back(listener);
	return true;
}

bool Mouse::removeListener(MouseListener * listener) {
	for (auto l : *listeners) {
		if (l == listener) {
			listeners->remove(l);
			return true;
		}
	}
	return false;
}

void Mouse::poll() {
	int newX, newY;
	glfwGetMousePos(&newX, &newY);
	if (newX != _x || newY != _y) {
		_prev_x = _x;
		_prev_y = _y;
		_x = newX;
		_y = newY;
		handleMove();
	}
	
	for (int i = 0; i < _state.size(); i++) {
		button_status_t newState = glfwGetMouseButton(i);
		if (newState != _state[i]) {
			if (newState == BUTTON_DOWN) {
				_start_drag_x = _x;
				_start_drag_y = _y;
				_is_dragging = true;
				handlePress(i);
			} else {
				_is_dragging = false;
				handleRelease(i);
			}
		}
	}
	
	int newScroll = glfwGetMouseWheel();
	if (newScroll != _scroll) {
		_prev_scroll = _scroll;
		_scroll = newScroll;
		handleScroll();
	}
}
