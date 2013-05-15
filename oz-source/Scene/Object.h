#ifndef __OZ__SCENE__OBJECT__H__
#define __OZ__SCENE__OBJECT__H__
namespace scene {

  class Visitor;

  class Object {
  public:
    virtual             ~Object() {}
    void                name(std::string name) { name_ = name; }
    std::string         name() { return name_; }
    virtual void        print() {}
  protected:
    std::string         name_;
  };

}
#endif
