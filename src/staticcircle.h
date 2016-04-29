#ifndef STATICCIRCLE_H
#define STATICCIRCLE_H
#include "gameobject.h"
//--------------------------------------------------------------------------------------------------------------------------------------------
/// \author Tom Hoxey
/// \version 1.0
/// \date 28/04/16 \n

/// \class NAME OF YOUR CLASS GOES HERE
/// \brief PUT A BRIEF DESCRIPTION OF THE CLASS HERE
//--------------------------------------------------------------------------------------------------------------------------------------------
class StaticCircle : public GameObject
{
public:
  StaticCircle(float _posX, float _posY, int _radMod);
  void draw(bool _xray);
  void detectCollision();
  float updateX(float _posX);
  float updateY(float _posY);
};
#endif // STATICCIRCLE_H
