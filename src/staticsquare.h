#ifndef STATICSQUARE_H
#define STATICSQUARE_H
#include "gameobject.h"

class StaticSquare : public GameObject
{
public:
  StaticSquare(float _posX, float _posY);
  void draw(bool _xray);
};

#endif // STATICSQUARE_H
