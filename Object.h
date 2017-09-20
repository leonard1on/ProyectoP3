#pragma once
class Object {
  public:
    Object ();
    virtual ~Object ();

    Object* operator+(Object* object);
};
