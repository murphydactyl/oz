#ifndef __OZ__SCENE__NODE__H
#define __OZ__SCENE__NODE__H

#include <vector>
#include "Math/Math.h"
#include "Geometry/Geometry.h"
#include "Geometry/Bone.h"
#include "Scene/Object.h"
#include <sstream>

namespace scene {

  template<typename Scalar>
  class Node : public Object {

    public:
      typedef math::Mat4f Mat4;

      // GETTERS ................................................................
      Node*               parent() { return parent_; }
      geom::Geometry*     geometry() { return geometry_; }

      // SETTERS ................................................................
      void                setParent(Node* p) { parent_ = p; }
      void                setGeometry(geom::Geometry* g) { geometry_ = g; }

      // CONSTRUCTOR ............................................................
      Node() : Node("Untitled"){}

      Node(std::string name) {
        mLocal = Mat4(1.0);
        name_ = name;
        geometry_ = nullptr;
        parent_ = nullptr;
        children_ = new std::vector<Node*>();
        bone_ = nullptr;
        std::cout << "Created node named " << name_ << std::endl;
      }

      virtual ~Node() {
        delete children_;
        std::cout << "Destructor called for node named " << name_ << std::endl;
      }

      Node* addChild(Node* child) {
        child->setParent(this);
        children_->push_back(child);
        return child;
      }

      void print() {
        std::cout << name_;
        if (geometry_ != nullptr) {
          std::cout << " (G) ";
        }
        if (hasBone()) {
          std::cout << " (B) ";
        }

        if (parent() == nullptr) {
          std::cout << "(child of root)";
        } else {
          std::cout << "(child of " << parent()->name() << ")";
        }
        std::cout << std::endl;
//        std<<cout << "Matrix: ";
//        mLocal.pprint();
        for (int i = 0; i < nChildren(); i++) {
          getChild(i)->print();
        }
      }

      Node* getChild(uint32_t i) {
        if (i >= nChildren()) {
          return nullptr;
        }
        return children_->at(i);
      }

      uint32_t nChildren() { return children_->size(); }
      std::vector<Node*>*&   children() { return children_; }

      Node* findByName(std::string name2LookFor) {
        if (name_.compare(name2LookFor) == 0) {
          return this;
        }
        Node* foundNode = nullptr;
        for (size_t i = 0; i < nChildren(); i++) {
          foundNode = getChild(i)->findByName(name2LookFor);
          if (foundNode != nullptr) {
            return foundNode;
          }
        }
        return nullptr;
      }

      void addBone(geom::Bone* bone) {
        if (bone_ != nullptr) {
          delete bone_;
        }
        bone_ = bone;
      }

      bool hasBone() {
        return bone_ != nullptr;
      }

      geom::Bone* bone() { return bone_; }

      Mat4                  mLocal;
      Mat4                  mWorld;

    protected:
      std::vector<Node*>*   children_;
      geom::Geometry*       geometry_;
      Node*                 parent_;
      geom::Bone*           bone_;
  };

  typedef Node<float> Nodef;
  typedef Node<double> Noded;

}


#endif
