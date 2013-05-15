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
      typedef Eigen::Transform<Scalar, 3, Eigen::Affine> Aff3;

      // GETTERS ................................................................
      Aff3&               local() { return local_; }
      Node*               parent() { return parent_; }
      geom::Geometry*     geometry() { return geometry_; }


      // SETTERS ................................................................
      void                parent(Node* p) { parent_ = p; }
      void                geometry(geom::Geometry* g) { geometry_ = g; }

      // CONSTRUCTOR ............................................................
      Node() {
        local_ = Aff3::Identity();
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
        child->parent(this);
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

      Node* child(uint32_t i) {
        if (i >= children_.size()) {
          return nullptr;
        }
        return children_[i];
      }

      uint32_t nChildren() { return children_.size(); }
      Vector<Node*>     children() { return children_; }

    protected:
      Aff3                local_;
      Vector<Node*>       children_;
      static uint64_t     nNodes;
      geom::Geometry*     geometry_;
      Node*               parent_;
  };

  /**
   nNodes
   -- Keeps track of total nodes created of this type
  **/
  template<typename Scalar> uint64_t     Node<Scalar>::nNodes = 0;

  typedef Node<float> Nodef;
  typedef Node<double> Noded;

}


#endif
