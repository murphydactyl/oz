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
#include "Geometry/Wire.h"
#include "GL/Texture2D.h"
#include "GL/VertexWriter.h"
#include <sstream>

int main(int argc, char* argv[])
{
  App* app = new AppBasic();

  app->run();

  return EXIT_SUCCESS;
}

AppBasic::AppBasic() {

  windows_.push_back(new Window(1024, 768, "Untitled"));

  auto dfltSPTextured = new gl::ShaderProgram("TriangleMeshWithTexture.v.glsl", "TriangleMeshWithTexture.f.glsl");
  auto dfltSPVertexColors = new gl::ShaderProgram("triangle.v.glsl", "triangle.f.glsl");
  auto dfltSPLine = new gl::ShaderProgram("line.v.glsl", "line.f.glsl");

  myScene = new scene::Scene();
  scene::Cameraf* cam = new scene::CameraPerspective<float>(4/3., 1, 1, 100);
  cam->translate(0,0,20);
  myScene->camera(cam);
  myScene->print();
  myScene->setShader(dfltSPTextured);

  boneView = new scene::Scene();
  boneView->camera(cam);
  boneView->setShader(dfltSPLine);

  //  geom::Geometry* quad = geom::makeQuad(1.0);
//  geom::Geometry* box = geom::makeBox(.1, .1, .1);
//  geom::Geometry* cone = geom::makeCone();

//  myScene->root()->addChild(new scene::Nodef("trunk"));
//  myScene->root()->findByName("trunk")->setGeometry(box);
//  myScene->root()->findByName("trunk")->mLocal.rotate(1, 0, 1).translate(0, 2, 0);

//  myScene->root()->findByName("trunk")->addChild(new scene::Nodef("left"));
//  myScene->root()->findByName("left")->setGeometry(box);
//  myScene->root()->findByName("left")->mLocal.rotate(0, 1, 1).translate(-1, 0, 0);

//  myScene->root()->findByName("trunk")->addChild(new scene::Nodef("right"));
//  myScene->root()->findByName("right")->setGeometry(box);
//  myScene->root()->findByName("right")->mLocal.rotate(1.57, -.2, 0).translate(.1, .5, .5);

//  myScene->root()->findByName("right")->addChild(new scene::Nodef("right2"));
//  myScene->root()->findByName("right2")->setGeometry(box);
//  myScene->root()->findByName("right2")->mLocal.rotate(1.57, 0, 0).translate(.1, -.5, -.5);
//  myScene->root()->findByName("right2")->addBone(new geom::Bone());
//  myScene->root()->findByName("right2")->bone()->offset.rotate(1, 1, 1);

    stringstream ss;
    ss << MODELS_DIR << "/lib_hand_model/hand_palm_parent_medium_wrist.dae";
    auto model = geom::loadHandModel(ss.str());
    uint32_t imWidth, imHeight;
    ss.str("");
    ss.clear();
    ss << MODELS_DIR << "/lib_hand_model/hand_texture_image.png";
    auto image = reinterpret_cast<gl::rgba8888_t*>(image::LoadPNGRGBA8888(ss.str(), imWidth, imHeight));
    auto tex = new gl::Texture2D<gl::rgba8888_t>(image, imWidth, imHeight);
    myScene->root()->addChild(model);
    tex->copy2GPU();
    // TODO:
    // figure this shit out
    // If I don't add the mesh to Armature, then the whole node hierarchy is off.
    // Not sure why I can't just add it to the node 'hand_mesh'
    geom::Mesh* hand = (geom::Mesh*)model->findByName("Armature")->geometry();
    hand->attachTexture(tex);
    for (int i = 0; i < hand->bones()->size(); i++) {
      cout << "Bone: " << hand->bones()->at(i)->name << endl;
      hand->bones()->at(i)->offset.pprint();
    }
}

void AppBasic::update() {
  handlePressedKeys();
  glClearColor(0.1, 0.1, 0.1, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
  myScene->render(0, 0, 1024, 768);
//  boneView->render(0, 0, 1024, 768);
  stringstream ss;
  ss << _fps;
  windows_[0]->title(ss.str());
}

void AppBasic::onMouseDrag(double dx, double dy) {
  double sx = windows_[0]->width() / 2.0f;
  double sy = windows_[0]->height() / 2.0f;
  double azimuth = -dx / sx;
  double elevation = dy / sy;
  myScene->camera()->anim() = math::Mat4f::Rotation(azimuth, 0, 0);
  myScene->camera()->anim().rotate(0, -elevation, 0);
}

void AppBasic::onMouseUp(double x, double y) {
  myScene->camera()->makeAnimationPermanent();
}

void AppBasic::handlePressedKeys() {
  float scale = 0.05;

  for (auto& kv : keys->down) {
    char c = kv.first;
    switch(c) {
      case 'W':
        myScene->camera()->translate(0, 0, -scale);
        break;
      case 'S':
        myScene->camera()->translate(0, 0, scale);
        break;
      case 'A':
        myScene->camera()->translate(-scale, 0, 0);
        break;
      case 'D':
        myScene->camera()->translate(scale, 0, 0);
        break;
      case 'R':
        myScene->camera()->translate(0, scale, 0);
        break;
      case 'F':
        myScene->camera()->translate(0, -scale, 0);
        break;
    }
  }
}

void AppBasic::charDown(char c, bool isRepeat) {

}


