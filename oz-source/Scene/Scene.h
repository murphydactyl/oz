#ifndef __OZ__SCENE__SCENE__H
#define __OZ__SCENE__SCENE__H

#include "Scene/Camera.h"
#include "Scene/Light.h"
#include "Scene/Node.h"
#include "GL/ShaderProgram.h"
#include "GL/Texture.h"
#include "Vector/Vector.h"
#include "Geometry/TriangleMesh.h"

namespace scene {

  class Scene {
    public:

      Scene();
      ~Scene();

      void            root(Node<float>* root) { root_ = root; }
      Node<float>*    root() { return root_; }
      Cameraf*        camera() { return camera_; }
      void            camera(Cameraf* camera) { camera_ = camera; }
      void            render();
      void            render(gl::ShaderProgram* shader);
      void            renderWithTexture(gl::Texture* tex);
      void            print();
      void            drawCube(gl::ShaderProgram* shader);

    protected:

      Nodef*                  root_;
      Cameraf*                camera_;
      gl::ShaderProgram*      dfltSPTextured_;
      gl::ShaderProgram*      dfltSPVertexColors_;
      gl::ShaderProgram*      defaultShader_;
      Vector<Nodef*>          nStack_;
      Vector<Nodef::Mat4>     tStack_;
      geom::Geometry*         cube_;

  };
}

#endif
