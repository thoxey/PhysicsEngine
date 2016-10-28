/// @file staticcircle.cpp
/// @brief This class handles the construction and drawing of the static circles on the screen
#include "staticcircle.h"
//--------------------------------------------------------------------------------------------------------------------------------------------
StaticCircle::StaticCircle(float _posX, float _posY, int _radMod)
{
  m_mass = ((double) rand() / (RAND_MAX));
  m_radMod = _radMod;
  m_posX = _posX;
  m_posY = _posY;
  m_radius = rand() % _radMod + _radMod;
  m_radius /= 100;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void StaticCircle::draw(bool _xray)
{
  int points = 30;
  GLfloat twicePi = TWOPI;
  if(_xray)
  {
    glBegin(GL_TRIANGLE_FAN); //Solid
    glColor3f(1.0f/m_radMod, 1.0f, m_mass);
    for(int i = 0; i <= points;i++)
    {
      glVertex2f(m_posX + (m_radius * cos(i * twicePi / points)), m_posY + (m_radius * sin(i * twicePi / points)));
    }
    glEnd();
  }
  else
  {
    glBegin(GL_LINE_LOOP); //HOLLOW
    glColor3f(1.0f/m_radMod, 1.0f, m_mass);
    for(int i = 0; i <= points;i++)
    {
      glVertex2f(m_posX + (m_radius * cos(i * twicePi / points)), m_posY + (m_radius * sin(i * twicePi / points)));
    }
    glEnd();
  }
}

