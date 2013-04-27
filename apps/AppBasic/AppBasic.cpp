//
//  app.cpp
//  GLFW
//
//  Created by Murphy M Stein on 9/21/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//

#include "App/app.h"


int main(int argc, char* argv[])
{
  App* app = new App(1024, 768);

  app->run();

  return EXIT_SUCCESS;
}