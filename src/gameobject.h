#ifndef GameObject_H
#define GameObject_H
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
#include <cmath>
#include <vector>
#define PI 3.141592653589793
#define TWOPI 6.283185307
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @author Tom Hoxey
/// @version 1.0
/// @date 28/04/16 \n

/// \class NAME OF YOUR CLASS GOES HERE
/// \brief PUT A BRIEF DESCRIPTION OF THE CLASS HERE
//--------------------------------------------------------------------------------------------------------------------------------------------
class GameObject
{
public:
  GameObject();
  virtual void draw(bool _xray);
  void detectCollision();
  double m_posY      = 0;
  double m_posX      = 0;
  double m_velX      = 0.0;
  double m_velY      = 0.0;
  double m_col;
  float m_bounce     = -0.6f;
  float m_radius     = 0.1f;
  int m_radMod       = 5;
  float m_mass       = 1.0f;
  bool m_isColliding = false;
  bool m_isDynamic   = false;
  double m_timer;
  double m_deltaTime;
  /// World Variables
  const float m_g = 9.8f/10;
  int m_oldTime;
  int m_curTime;
};
#endif // GameObject_H
