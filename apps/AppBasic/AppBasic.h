//
//  app.h
//  ModelVis
//
//  Created by Murphy M Stein on 4/20/13.
//  Copyright (c) 2013 Murphy M Stein. All rights reserved.
//

#ifndef __APP__BASIC__H__
#define __APP__BASIC__H__

#define MODELS_DIR "../models"

#include "App/App.h"
#include "Scene/Scene.h"
#include "Geometry/Assimp.h"

class AppBasic : public App {
public:
  AppBasic();
  void update();
  void charDown(char c, bool isRepeat);
  void onMouseDrag(double x, double y);
  void onMouseUp(double x, double y);
  void handlePressedKeys();

protected:
  scene::Scene* myScene;
  scene::Scene* boneView;
};

#endif /* defined(__ModelVis__app__) */
