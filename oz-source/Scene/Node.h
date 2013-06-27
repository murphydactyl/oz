#ifndef __OZ__SCENE__NODE__H
#define __OZ__SCENE__NODE__H

#include "Vector/Vector.h"
#include "../Math/Math.h"
#include "../Geometry/Geometry.h"
#include "Scene/Object.h"
#include <sstream>

namespace scene {

  template<typename Scalar>
  class Node : public Object {

    public:
      typedef math::Mat4f Mat4;

      // GETTERS ................................................................
      Mat4&               local() { return local_; }
      Node*               parent() { return parent_; }
      geom::Geometry*     geometry() { return geometry_; }

      // SETTERS ................................................................
      void                setParent(Node* p) { parent_ = p; }
      void                setGeometry(geom::Geometry* g) { geometry_ = g; }

      // CONSTRUCTOR ............................................................
      Node() {
        local_ = Mat4(1.0);
        std::stringstream ss;
        ss << "Untitled Node " << nNodes++;
        name_ = ss.str();
        geometry_ = nullptr;
        parent_ = nullptr;
      }

      virtual ~Node() {
        std::cout << "Destructor called for node named " << name_ << std::endl;
      }

      void addChild(Node* child) {
        child->setParent(this);
        children_.push_back(child);
      }

      void print() {
        cout << name_;
        if (geometry_ != nullptr)
          cout << " (G) ";
        cout << endl;

        for (int i = 0; i < children_.size(); i++) {
          children_[i]->print();
        }
      }

      Node* getChild(uint32_t i) {
        if (i >= children_.size()) {
          return nullptr;
        }
        return children_[i];
      }

      uint32_t nChildren() { return children_.size(); }
      Vector<Node*>     children() { return children_; }

      Node* findByName(string name2LookFor) {
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

    protected:
      Mat4                local_;
      Vector<Node*>       children_;
      static uint64_t     nNodes;
      geom::Geometry*     geometry_;
      Node*               parent_;
  };

  /**
   nNodes
   -- Keeps track of total nod  es created of this type
  **/
  template<typename Scalar> uint64_t     Node<Scalar>::nNodes = 0;

  typedef Node<float> Nodef;
  typedef Node<double> Noded;

}


#endif
