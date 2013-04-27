//
//  mouse.h
//  ModelVis
//
//  Created by Murphy M Stein on 12/2/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//

#ifndef __ModelVis__mouse__
#define __ModelVis__mouse__

#include <iostream>
#include <GL/glfw.h>
#include <vector>
#include <list>

#define BUTTON_DOWN GLFW_PRESS
#define BUTTON_UP	 GLFW_RELEASE
#define MAX_BUTTON_CODE GLFW_MOUSE_BUTTON_LAST

typedef int button_status_t;
typedef int button_code_t;

using namespace std;

class MouseListener;

class Mouse {
public:
	Mouse();
	~Mouse() { delete listeners; }
	bool isDown(button_code_t);
	bool isUp(button_code_t);
	bool addListener(MouseListener*);
	bool removeListener(MouseListener*);
	void poll();
	int x() { return _x; };
	int y() { return _y; };
	int scroll() { return _scroll; };
	
protected:

	void handleRelease(button_code_t);
	void handlePress(button_code_t);
	void handleMove();
	void handleScroll();
	
	int _x;
	int _y;
	int _prev_x;
	int _prev_y;
	int _start_drag_x;
	int _start_drag_y;
	int _scroll;
	int _prev_scroll;
	bool _is_dragging = false;
	vector<button_status_t> _state;
	vector<button_status_t> _prev_state;
	list<MouseListener*> *listeners;
	
};
#endif /* defined(__ModelVis__mouse__) */
