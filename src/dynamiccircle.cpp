#include "dynamiccircle.h"

DynamicCircle::DynamicCircle(float _posX, float _posY)
{
    m_posX = _posX;
    m_posY = _posY;
    m_mass = ((double) rand() / (RAND_MAX));
}
void DynamicCircle::detectCollision()
{

}

void DynamicCircle::draw(bool _xray)
{
    int points = 30;
    GLfloat twicePi = 2.0f * PI; //Store me as a macro too!
    if(_xray)
    {
        glBegin(GL_TRIANGLE_FAN); //Solid
        glColor3f(0.2f, m_mass, 0.5f);
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
        glColor3f(0.2f, m_mass, 0.5f);
        glVertex2f(m_posX, m_posY);
        for(int i = 0; i <= points;i++)
        {
            glVertex2f(m_posX + (m_radius * cos(i * twicePi / points)), m_posY + (m_radius * sin(i * twicePi / points)));
        }
        glEnd();
    }
}
