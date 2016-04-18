#include "staticcircle.h"

StaticCircle::StaticCircle(float _posX, float _posY)
{
    m_posX = _posX;
    m_posY = _posY;
}
void StaticCircle::draw()
{
    int points = 30;
    GLfloat twicePi = TWOPI;
    //glBegin(GL_TRIANGLE_FAN); //Solid
    glBegin(GL_LINE_LOOP); //HOLLOW
    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex2f(m_posX, m_posY);
    for(int i = 0; i <= points;i++)
    {
        glVertex2f(m_posX + (m_radius * cos(i * twicePi / points)), m_posY + (m_radius * sin(i * twicePi / points)));
    }
    glEnd();
}

