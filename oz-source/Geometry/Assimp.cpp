#include "Geometry/Geometry.h"
#include "Geometry/Assimp.h"
#include "Geometry/TriangleMesh.h"
#include <iostream>
#include "Vector/Vector.h"
#include <queue>

using namespace std;
using namespace geom;

typedef scene::Nodef Node;

Mat4 geom::convertAsimppBoneOffsetMatrixToNodeTransform(aiNode* asimppNode) {
    float* pf = asimppNode->mTransformation[0];
    Mat4 ret(pf);
    return ret;
}

Node* geom::cloneAsimppNodeAsOzNode(aiNode* asimppNode) {
  Node* clonedNode = new Node();
  clonedNode->setName(asimppNode->mName.C_Str());
  clonedNode->local() = convertAsimppBoneOffsetMatrixToNodeTransform(asimppNode);
  return clonedNode;
}

Node* geom::LoadTriangleMeshFromFile(string filename) {

  Assimp::Importer importer;
  const aiScene* inScene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate );

  if (inScene != nullptr) {


    auto root = new Node();
    // LOAD BONES
    // Clone Asimpp bone tree as Node tree
    // *  push mRootNode onto stack
    // *  pop topmost asimpp node off the top of the stack or stop
    //    * create new node
    //    * attach tree to corresponding parent in new tree
    //    * copy offset matrix
    //    * push asimpp nodes children to stack and recurse
//    Vector<aiNode*> unprocessedNodes;
//    unprocessedNodes.push_back(inScene->mRootNode);
//    while (! unprocessedNodes.isEmpty()) {

//      // POP
//      aiNode* asimppNode = unprocessedNodes.pop_back();

//      // CLONE NODE EXCEPT PARENT INFO
//      Node* clonedNode = cloneAsimppNodeAsOzNode(asimppNode);

//      if (asimppNode->mParent == nullptr) {
//        Node* parentOfClonedNode = root->findByName(asimppNode->mParent->mName.C_Str());
//        clonedNode->setParent(parentOfClonedNode);
//      } else {
//        clonedNode->setParent(nullptr);
//      }

//      for (size_t i = 0; i < asimppNode->mNumChildren; i++) {
//        unprocessedNodes.push_back(asimppNode->mChildren[i]);
//      }
//    }


    auto g = new TriangleMesh<geom::TRIANGLE>();
    auto faces = g->faces();
    auto positions = g->positions();
    auto normals = g->normals();
    auto colors = g->colors();
    auto texcoords = g->texcoords();

    root->setGeometry(g);

    cout << "Loaded scene from: " << filename << endl;
    aiMesh* inMesh = inScene->mMeshes[0];

    uint64_t nVerts = inMesh->mNumVertices;
    uint64_t nFaces = inMesh->mNumFaces;

    if (inMesh->HasPositions()) {
      positions.resize(Eigen::NoChange, nVerts);
      colors.resize(Eigen::NoChange, nVerts);

      for (int i = 0; i < nVerts; i++) {
        positions(0, i) = inMesh->mVertices[i].x;
        positions(1, i) = inMesh->mVertices[i].y;
        positions(2, i) = inMesh->mVertices[i].z;
        colors(0, i) = 1.0;
        colors(1, i) = 1.0;
        colors(2, i) = 1.0;
        colors(3, i) = 1.0;
      }
    }

    if (inMesh->HasNormals()) {
      normals.resize(Eigen::NoChange, nVerts);
      for (int i = 0; i < nVerts; i++) {
        normals(0, i) = inMesh->mNormals[i].x;
        normals(1, i) = inMesh->mNormals[i].y;
        normals(2, i) = inMesh->mNormals[i].z;
      }
    }

    if (inMesh->HasTextureCoords(0)) {
      texcoords.resize(Eigen::NoChange, nVerts);
      for (int i = 0; i < nVerts; i++) {
        texcoords(0, i) = inMesh->mTextureCoords[0][i].x;
        texcoords(1, i) = inMesh->mTextureCoords[0][i].y;
      }
    }

    if (inMesh->HasFaces()) {
      faces.resize(Eigen::NoChange, nFaces);
      cout << faces.rows() << endl;
      cout << faces.cols() << endl;
      for (int i = 0; i < nFaces; i++) {
        faces(0, i) = inMesh->mFaces[i].mIndices[0];
        faces(1, i) = inMesh->mFaces[i].mIndices[1];
        faces(2, i) = inMesh->mFaces[i].mIndices[2];
      }
    }

    g->name(inMesh->mName.C_Str());
    g->nVerts(nVerts);
    g->nFaces(nFaces);
    g->vao()->bind();
    g->vbo()->reserveNBytesOnGPU(nVerts * (4 + 4 + 4) * 4);
    g->vbo()->copy2GPUPoints(positions.data(), nVerts);
    g->vbo()->copy2GPUColors(colors.data(), nVerts);
    g->vbo()->copy2GPUTexcoords(texcoords.data(), nVerts);
    g->vao()->unbind();

    g->ebo()->bind();
    g->ebo()->reserveNBytesOnGPU(nFaces * 3 * 2);
    g->ebo()->copy2GPU(faces.data(), faces.cols(), faces.rows());
    g->ebo()->unbind();

    // load bones


    //    Vector<aiNode*> unprocessedNodes;
//    unprocessedNodes.push_back(inScene->mRootNode);

//    while (unprocessedNodes.isNotEmpty()) {
//      aiNode* inTop = unprocessedNodes.pop_back();
//      auto newNode = new scene::Nodef();
//      float* pf = inTop->mTransformation[0];
//      Eigen::Map<Eigen::Matrix4f> map(pf, 4, 4);
//      newNode->local().matrix() = map.transpose();
//      newNode->name(inTop->mName.C_Str());
//      for (int i = 0; i < inTop->mNumChildren; i++) {
//        unprocessedNodes.push_back(inTop->mChildren[i]);
//      }
//    }


    return root;

  } else {
    cout << "WARNING: couldn't load scene from: " << filename << endl;
    cout << "Assimp said: " << importer.GetErrorString() << endl;
  }
  return nullptr;
}

