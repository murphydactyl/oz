//
//  app.cpp
//  GLFW
//
//  Created by Murphy M Stein on 9/21/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//

#include "AppBasic/AppBasic.h"
#include "Geometry/Assimp.h"
#include "Geometry/Primitives.h"
#include "Geometry/TriangleMesh.h"
#include "GL/Texture2D.h"
#include <sstream>

int main(int argc, char* argv[])
{
  App* app = new AppBasic();

  app->run();

  return EXIT_SUCCESS;
}

AppBasic::AppBasic() {

  windows_.push_back(new Window(640, 480, "Untitled"));

  myScene = new scene::Scene();
  scene::Cameraf* cam = new scene::CameraPerspective<float>(4/3., 1, 1, 100);
  cam->translate(0,0,-5);
  myScene->camera(cam);
//  geom::Geometry* model = geom::makeQuad();
//  geom::Geometry* cube = geom::makeCube(1.0);

//  scene::Nodef* node = new scene::Nodef();
//  node->geometry(cube);
//  node->local().translate(.1, 0, 0);
//  node->local().rotateZ(.01);
//  node->local().rotateX(.04);

  stringstream ss;
  ss << MODELS_DIR << "/lib_hand_model/hand_palm_parent_medium_wrist.dae";
  auto model = geom::LoadTriangleMeshFromFile(ss.str());

  uint32_t imWidth, imHeight;
  ss.str("");
  ss.clear();
  ss << MODELS_DIR << "/lib_hand_model/hand_texture_image.png";

  auto image = reinterpret_cast<gl::rgba8888_t*>(image::LoadPNGRGBA8888(ss.str(), imWidth, imHeight));
  auto tex = new gl::Texture2D<gl::rgba8888_t>(image, imWidth, imHeight);
  auto node = new scene::Nodef();
  auto node2 = new scene::Nodef();

  node->geometry(model);

  myScene->root()->addChild(node);
  myScene->print();
  tex->copy2GPU();
  ((geom::TriangleMesh<>*)(model))->attachTexture(tex);

}

void AppBasic::update() {
  glClearColor(0.3, 0.3, 0.3, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
  myScene->render();
  stringstream ss;
  ss << _fps;
  windows_[0]->title(ss.str());
}

void AppBasic::onMouseDrag(double dx, double dy) {
  double sx = windows_[0]->width();
  double sy = windows_[0]->height() * 2;
  double azimuth = -dx / sx;
  double elevation = dy / sy;
  myScene->camera()->anim().setRotationX(azimuth);
  myScene->camera()->anim().rotateY(-elevation);
}

void AppBasic::onMouseUp(double x, double y) {
  myScene->camera()->makeAnimationPermanent();
}


void AppBasic::charDown(char c, bool isRepeat) {
  float scale = 0.1;
  switch(c) {
    case 'W':
      myScene->camera()->translate(0, 0, scale);
      break;
    case 'S':
      myScene->camera()->translate(0, 0, -scale);
      break;
    case 'A':
      myScene->camera()->translate(scale, 0, 0);
      break;
    case 'D':
      myScene->camera()->translate(-scale, 0, 0);
      break;
    case 'R':
      myScene->camera()->translate(0, -scale, 0);
      break;
    case 'F':
      myScene->camera()->translate(0, scale, 0);
      break;
  }
}


