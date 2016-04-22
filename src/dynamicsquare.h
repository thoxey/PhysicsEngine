#ifndef DYNAMICSQUARE_H
#define DYNAMICSQUARE_H
#include "dynamicobject.h"

class DynamicSquare : public DynamicObject
{
public:
    DynamicSquare(float _posX, float _posY);
    void draw(bool _xray);
};

#endif // DYNAMICSQUARE_H
