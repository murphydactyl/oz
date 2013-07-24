#include "Geometry/Geometry.h"
#include "Geometry/Assimp.h"
#include "Geometry/TriangleMesh.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using namespace geom;

typedef scene::Nodef Node;
typedef math::Mat4f Mat4;

typedef struct boneidweight_t {
    float weight;
    uint32_t id;

    bool operator < (const struct boneidweight_t& rhs) const
    {
      // RETURN DESCENDING
      return (!(weight < rhs.weight));
    }
} boneidweight;

Node* geom::cloneAsimppNodeAsOzNode(const aiNode* assimpNode) {
  Node* clonedNode = new Node(assimpNode->mName.C_Str());
  const float* pf = assimpNode->mTransformation[0];
  clonedNode->mLocal = Mat4(pf);
  return clonedNode;
}

Node* geom::extractNodes(aiNode* src) {

  // CREATE ROOT NODE
  auto root = geom::cloneAsimppNodeAsOzNode(src);
  root->setParent(nullptr);

  // LOAD NODES
  vector<aiNode*> unprocessedNodes;
  unprocessedNodes.push_back(src);
  while (! unprocessedNodes.empty()) {

    // POP
    aiNode* ain = unprocessedNodes.back();
    unprocessedNodes.pop_back();

    cout << "Processing aiNode named " << ain->mName.C_Str() << endl;

    Node* ozNode = root->findByName(ain->mName.C_Str());
    if (ozNode == nullptr) {
      // CLONE NODE EXCEPT PARENT INFO
      cout << "Couldn't find oz node named " << ain->mName.C_Str() << endl;
      ozNode = cloneAsimppNodeAsOzNode(ain);
      cout << "This new node has \t\t" << ain->mNumMeshes << " meshes" << endl;
      cout << "                  \t\t" << ain->mNumChildren << " children" << endl;
    } else {
    }

    if (ozNode != root) {
      if (ain->mParent != nullptr) {
        cout << "trying to find ainode's parent named " << ain->mParent->mName.C_Str() << "...";
        Node* ozNodeParent = root->findByName(ain->mParent->mName.C_Str());
        if (ozNodeParent == nullptr) {
          cout << "Failed." << endl;
          root->addChild(ozNode);
        } else {
          cout << "Success." << endl;
          ozNodeParent->addChild(ozNode);
        }
      }
    }

    for (size_t i = 0; i < ain->mNumChildren; i++) {
      unprocessedNodes.push_back(ain->mChildren[i]);
    }
  }
  return root;

}

Mesh* geom::extractMesh(const aiMesh* srcMesh) {

  auto g = new Mesh();
  auto faces = g->faces();
  auto positions = g->positions();
  auto normals = g->normals();
  auto colors = g->colors();
  auto texcoords = g->texcoords();
  auto boneweights = g->boneweights();
  auto boneids = g->boneids();

  uint64_t nVerts = srcMesh->mNumVertices;
  uint64_t nFaces = srcMesh->mNumFaces;

  if (srcMesh->HasPositions()) {
    positions.resize(Eigen::NoChange, nVerts);
    colors.resize(Eigen::NoChange, nVerts);

    for (int i = 0; i < nVerts; i++) {
      positions(0, i) = srcMesh->mVertices[i].x;
      positions(1, i) = srcMesh->mVertices[i].y;
      positions(2, i) = srcMesh->mVertices[i].z;
      colors(0, i) = 1.0;
      colors(1, i) = 1.0;
      colors(2, i) = 1.0;
      colors(3, i) = 1.0;
    }
  }

  if (srcMesh->HasNormals()) {
    normals.resize(Eigen::NoChange, nVerts);
    for (int i = 0; i < nVerts; i++) {
      normals(0, i) = srcMesh->mNormals[i].x;
      normals(1, i) = srcMesh->mNormals[i].y;
      normals(2, i) = srcMesh->mNormals[i].z;
    }
  }

  if (srcMesh->HasTextureCoords(0)) {
    texcoords.resize(Eigen::NoChange, nVerts);
    for (int i = 0; i < nVerts; i++) {
      texcoords(0, i) = srcMesh->mTextureCoords[0][i].x;
      texcoords(1, i) = srcMesh->mTextureCoords[0][i].y;
    }
  }

  if (srcMesh->HasBones()) {
    boneweights.resize(Eigen::NoChange, nVerts);
    boneids.resize(Eigen::NoChange, nVerts);
    boneweights.fill(0);
    boneids.fill(gl::NO_OP_BONE_INDEX);

    vector< vector<boneidweight> > tmpWeights(nVerts);
    for (uint32_t i = 0; i < srcMesh->mNumBones; i++) {
      aiBone* aib = srcMesh->mBones[i];
      for (uint32_t j = 0; j < aib->mNumWeights; j++) {
        aiVertexWeight weight = aib->mWeights[j];
        size_t vertId = weight.mVertexId;
        tmpWeights[vertId].push_back({weight.mWeight, i});
      }
    }
    for (int i = 0; i < nVerts; i++) {
      auto vertweights = tmpWeights[i];
      std::sort(vertweights.begin(), vertweights.end());
      for (int j = 0; j < gl::MAX_BONES_PER_VERTEX; j++) {
        if (j == vertweights.size()) break;
        boneweights(j, i) = vertweights.at(j).weight;
        boneids(j, i) = vertweights.at(j).id;
      }
    }

    for (int i = 0; i < nVerts; i++) {
      float totalWeight = boneweights.col(i).sum();
      boneweights.col(i) /= totalWeight;
      assert(abs(boneweights.col(i).sum() - 1) < 1e-4);
    }
  }

  // PRINT WEIGHTS FOR DEBUG
  //  for (int i = 0; i < nVerts; i++) {
  //    for (int j = 0; j < gl::MAX_BONES_PER_VERTEX; j++) {
  //      cout << boneweights(j,i) << " ";
  //    }
  //    cout << "<==>";
  //    for (int j = 0; j < gl::MAX_BONES_PER_VERTEX; j++) {
  //      cout << boneids(j, i) << " ";
  //    }
  //    cout << endl;
  //  }

  if (srcMesh->HasFaces()) {
    faces.resize(Eigen::NoChange, nFaces);
    cout << faces.rows() << endl;
    cout << faces.cols() << endl;
    for (int i = 0; i < nFaces; i++) {
      faces(0, i) = srcMesh->mFaces[i].mIndices[0];
      faces(1, i) = srcMesh->mFaces[i].mIndices[1];
      faces(2, i) = srcMesh->mFaces[i].mIndices[2];
    }
  }

  g->name(srcMesh->mName.C_Str());
  g->nVerts(nVerts);
  g->nFaces(nFaces);
  g->vao()->bind();
  g->vbo()->reserveNBytesOnGPU(nVerts * (4 + 4 + 4 + 4 * 4) * 4);
  g->vbo()->copyVertDataToGPU(positions.data(), nVerts, gl::vposition);
  g->vbo()->copyVertDataToGPU(colors.data(), nVerts, gl::vcolor);
  g->vbo()->copyVertDataToGPU(texcoords.data(), nVerts, gl::vtexcoord);
  g->vbo()->copyVertDataToGPU(boneweights.data(), nVerts, gl::vboneweight);
  g->vbo()->copyVertDataToGPU(boneids.data(), nVerts, gl::vboneid);
  g->vao()->unbind();

  g->ebo()->bind();
  g->ebo()->reserveNBytesOnGPU(nFaces * 3 * 2);
  g->ebo()->copy2GPU(faces.data(), faces.cols(), faces.rows());
  g->ebo()->unbind();

  return g;

}

void geom::extractBones(const aiMesh* srcMesh, Mesh* outMesh, Node* outRoot) {

  outRoot->print();

  if (srcMesh->HasBones()) {
    for (uint32_t i = 0; i < srcMesh->mNumBones; i++) {
      auto aib = srcMesh->mBones[i];
      auto ourBoneNode = outRoot->findByName(aib->mName.C_Str());
      auto ourBone = new Bone();
      ourBone->offset = Mat4(reinterpret_cast<float*>(aib->mOffsetMatrix[0]));
      ourBoneNode->addBone(ourBone);
      outMesh->bones().push_back(ourBone);
    }
  } else {
    cout << "Warning!  No bones found in input mesh." << endl;
  }
}

Node* geom::loadHandModel(std::string filename) {

  Assimp::Importer importer;
  const aiScene* inScene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate );

  aiNode* srcNode = inScene->mRootNode->FindNode("root");
  aiMesh* srcMesh = inScene->mMeshes[0];
  Node* outRoot = extractNodes(srcNode);
  Mesh *outMesh = extractMesh(srcMesh);
  extractBones(srcMesh, outMesh, outRoot);
  outRoot->setGeometry(outMesh);

  return outRoot;
}
