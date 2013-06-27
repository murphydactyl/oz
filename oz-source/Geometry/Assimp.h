#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Scene/Node.h"
namespace geom {

  typedef math::Mat4f Mat4;
  scene::Nodef* LoadTriangleMeshFromFile(std::string filename);
  Mat4 convertAsimppBoneOffsetMatrixToNodeTransform(aiNode* asimppNode);
  scene::Nodef* cloneAsimppNodeAsOzNode(aiNode* asimppNode);
}
