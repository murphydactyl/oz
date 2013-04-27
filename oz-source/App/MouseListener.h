//
//  mouselistener.h
//  ModelVis
//
//  Created by Murphy M Stein on 12/2/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//

#ifndef __ModelVis__mouselistener__
#define __ModelVis__mouselistener__

#include <iostream>
#include "App/Mouse.h"

class MouseListener {
	
public:
	virtual void mouseDown(button_code_t id, int x, int y) {};
	virtual void mouseUp(button_code_t id, int x, int y) {};
	virtual void mouseMove(int x, int y) {};
	virtual void mouseMoveDelta(int dx, int dy) {};
	virtual void mouseDrag(int dx, int dy) {};
	virtual void mouseScroll(int s) {};
};
#endif /* defined(__ModelVis__mouselistener__) */
