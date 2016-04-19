#ifndef STATICCIRCLE_H
#define STATICCIRCLE_H

#include "gameobject.h"

class StaticCircle : public GameObject
{
public:
  StaticCircle(float _posX, float _posY);

  void draw(bool _xray);
  void detectCollision();
  float updateX(float _posX);
  float updateY(float _posY);
};

#endif // STATICCIRCLE_H
