#ifndef __OZ__SCENE__SCENE__H
#define __OZ__SCENE__SCENE__H

#include "Scene/Camera.h"
#include "Scene/Light.h"
#include "Scene/Node.h"
#include "GL/ShaderProgram.h"
#include "GL/Texture.h"
#include "Vector/Vector.h"
#include "Geometry/TriangleMesh.h"
#include "Geometry/Wire.h"

namespace scene {

  class Scene {
    public:

      Scene();
      ~Scene();

      void                root(Node<float>* root) { root_ = root; }
      Node<float>*        root() { return root_; }
      Cameraf*            camera() { return camera_; }
      void                camera(Cameraf* camera) { camera_ = camera; }
      void                render(int x, int y, int width, int height);
      void                updatePerNodeWorldTransform();
      void                renderRecursively();
      void                print();
      gl::ShaderProgram*  shader();
      void                setShader(gl::ShaderProgram* newShader);
      void                renderHierarchy();


    protected:                // member variables
      Nodef*                  root_;
      Cameraf*                camera_;
      gl::ShaderProgram*      shader_;
      gl::ShaderProgram*      lineShader_;
      Vector<Nodef*>          nStack_;
      Vector<Nodef*>          rNodes_;
      geom::Geometry*         cube_;
      bool                    bOwnsRoot_;
      bool                    bShowBones_;
      Vector<geom::Bone*>*    bones_;
      Nodef*                  lineNode_;
      geom::Wire*             lines_;
  };
}
#endif
