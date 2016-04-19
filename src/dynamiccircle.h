#ifndef DYNAMICCIRCLE_H
#define DYNAMICCIRCLE_H
#include "dynamicobject.h"

class DynamicCircle : public DynamicObject
{
public:
  int i =0;
  DynamicCircle(float _posX, float _posY);
  void detectCollision();
  void draw(bool _xray);
  void updateX(float m_posX, float _velX);
  void updateY(float m_posY, float _velY);

};

#endif // DYNAMICCIRCLE_H
