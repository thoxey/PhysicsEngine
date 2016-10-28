/// @file staticline.cpp
/// @brief This class handles the construction and drawing of the static lines on the screen
#include "staticline.h"

StaticLine::StaticLine(float _x1, float _y1, float _x2, float _y2)
{
    m_isCircle = false;
    m_posX = _x1;
    m_posY = _y1;
    m_posX2 = _x2;
    m_posY2 = _y2;

}
void StaticLine::draw(bool _xray)
{
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(m_posX, m_posY);
    glVertex2f(m_posX2, m_posY2);
    glEnd();
}
