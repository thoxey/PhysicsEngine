#include "dynamiccircle.h"

DynamicCircle::DynamicCircle(float _posX, float _posY)
{
    m_posX = _posX;
    m_posY = _posY;
    m_mass = ((double) rand() / (RAND_MAX));
    m_radius = rand() % 5 + 10;
    m_radius /= 100;
}
void DynamicCircle::draw(bool _xray)
{
    int points = 30;
    GLfloat twicePi = TWOPI;
    if(_xray)
    {
        glBegin(GL_TRIANGLE_FAN); //Solid
        glColor3f(1.0f-m_mass, m_mass, 1.0f);
        glVertex2f(m_posX, m_posY);
        for(int i = 0; i <= points;i++)
        {
            glVertex2f(m_posX + (m_radius * cos(i * twicePi / points)), m_posY + (m_radius * sin(i * twicePi / points)));
        }
        glEnd();
    }
    else
    {
        glBegin(GL_LINE_LOOP); //HOLLOW
        glColor3f(1.0f-m_mass, m_mass, 1.0f);
        glVertex2f(m_posX, m_posY);
        for(int i = 0; i <= points;i++)
        {
            glVertex2f(m_posX + (m_radius * cos(i * twicePi / points)), m_posY + (m_radius * sin(i * twicePi / points)));
        }
        glEnd();
    }
}
