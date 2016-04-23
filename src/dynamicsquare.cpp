#include "dynamicsquare.h"

DynamicSquare::DynamicSquare(float _posX, float _posY)
{
    m_posX = _posX;
    m_posY = _posY;
    m_isCircle = false;
}

void DynamicSquare::draw(bool _xray)
{
    if(!_xray)
    {
      glBegin(GL_LINE_LOOP);
      glColor3f(1.0f, m_mass, 0.6f);
      glVertex2f( m_posX-m_radius, m_posY+m_radius);
      glVertex2f( m_posX-m_radius, m_posY-m_radius);
      glVertex2f( m_posX+m_radius, m_posY-m_radius);
      glVertex2f( m_posX+m_radius, m_posY+m_radius);
      glEnd();
    }
    else
    {
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1.0f, m_mass, 0.6f);
        glVertex2f( m_posX-m_radius, m_posY-m_radius);
        glVertex2f( m_posX-m_radius, m_posY+m_radius);
        glVertex2f( m_posX+m_radius, m_posY-m_radius);
        glVertex2f( m_posX+m_radius, m_posY+m_radius);
        glEnd();
    }
}
