#include "Geometry/Geometry.h"
#include "Geometry/Assimp.h"
#include "Geometry/TriangleMesh.h"
#include <iostream>

using namespace std;
using namespace geom;
Geometry* geom::LoadTriangleMeshFromFile(string filename) {

  Assimp::Importer importer;
  const aiScene* inScene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate );

  auto g = new TriangleMesh<geom::TRIANGLE>();
  auto faces = g->faces();
  auto positions = g->positions();
  auto normals = g->normals();
  auto colors = g->colors();
  auto texcoords = g->texcoords();

  if (inScene != nullptr) {
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

    return g;

  } else {
    cout << "WARNING: couldn't load scene from: " << filename << endl;
    cout << "Assimp said: " << importer.GetErrorString() << endl;
  }
  return nullptr;
}

