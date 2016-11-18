///  @file dynamiccircle.cpp
/// @brief This class handles the construction and drawing of the dynaimc circles on the screen
#include "dynamiccircle.h"
//--------------------------------------------------------------------------------------------------------------------------------------------
DynamicCircle::DynamicCircle(float _posX, float _posY, int _radMod)
{
    m_radMod = _radMod;
    m_posX = _posX;
    m_posY = _posY;
    m_radius = _radMod;
    m_radius /= 50;
    m_mass = (m_radius*m_radius);
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void DynamicCircle::draw(bool _xray)
{
    int points = 200*m_radius+10;
    if(_xray)
    {
        glBegin(GL_TRIANGLE_FAN); //Solid
        glColor3f(0.6f, m_col, 0.8f);
        for(int i = 0; i <= points;i++)
        {
            glVertex2f(m_posX + (m_radius * cos(i * TWOPI / points)), m_posY + (m_radius * sin(i * TWOPI / points)));
        }
        glEnd();
    }
    else
    {
        glBegin(GL_LINE_LOOP); //HOLLOW
        glColor3f(0.6f, m_col, 0.8f);
        for(int i = 0; i <= points;i++)
        {
            glVertex2f(m_posX + (m_radius * cos(i * TWOPI / points)), m_posY + (m_radius * sin(i * TWOPI / points)));
        }
        glEnd();
    }
}
