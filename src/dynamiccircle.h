#ifndef DYNAMICCIRCLE_H
#define DYNAMICCIRCLE_H
#include "dynamicobject.h"

class DynamicCircle : public DynamicObject
{
public:
  DynamicCircle(float _posX, float _posY);
  void draw(bool _xray);
};

#endif // DYNAMICCIRCLE_H
