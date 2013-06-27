#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Scene/Node.h"
namespace geom {

  typedef Eigen::Transform<float, 3, Eigen::Affine> Aff3;

  scene::Nodef* LoadTriangleMeshFromFile(std::string filename);
  Aff3 convertAsimppBoneOffsetMatrixToNodeTransform(aiNode* asimppNode);
  scene::Nodef* cloneAsimppNodeAsOzNode(aiNode* asimppNode);
}
