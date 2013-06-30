#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Scene/Node.h"
#include "Geometry/TriangleMesh.h"

namespace geom {
  scene::Nodef* cloneAsimppNodeAsOzNode(const aiNode* asimppNode);
  scene::Nodef* extractNodes(aiNode* scNode);
  void extractBones(const aiMesh* srcMesh, TriangleMesh* outMesh, scene::Nodef* outRoot);
  TriangleMesh* extractMesh(const aiMesh* srcMesh);
  scene::Nodef* loadHandModel(std::string filename);
}
