#include "dynamiccircle.h"
//--------------------------------------------------------------------------------------------------------------------------------------------
DynamicCircle::DynamicCircle(float _posX, float _posY, int _radMod)
{
    m_radMod = _radMod;
    m_posX = _posX;
    m_posY = _posY;
    m_radius = rand() % _radMod + _radMod;
    m_radius /= 100;
    m_mass += m_radius;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void DynamicCircle::draw(bool _xray)
{
    int points = 5*m_radMod+5;
    std::cout<<5*m_radMod+5<<std::endl;
    if(_xray)
    {
        glBegin(GL_TRIANGLE_FAN); //Solid
        glColor3f(1.0f/m_radMod, m_mass, 1.0f);
        for(int i = 0; i <= points;i++)
        {
            glVertex2f(m_posX + (m_radius * cos(i * TWOPI / points)), m_posY + (m_radius * sin(i * TWOPI / points)));
        }
        glEnd();
    }
    else
    {
        glBegin(GL_LINE_LOOP); //HOLLOW
        glColor3f(1.0f/m_radMod, m_mass, 1.0f);
        for(int i = 0; i <= points;i++)
        {
            glVertex2f(m_posX + (m_radius * cos(i * TWOPI / points)), m_posY + (m_radius * sin(i * TWOPI / points)));
        }
        glEnd();
    }
}
