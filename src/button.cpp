#include "button.h"
//--------------------------------------------------------------------------------------------------------------------------------------------
Button::Button()
{
    m_width = (2.0f/m_buttTot)-0.1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void Button::draw()
{
    float i = -0.98f;
    float col = 1.0f/m_buttTot;
    for(int it = 0; it <= m_buttTot; ++it)
    {
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(col*it, 0.2f, 1.0f);
        glVertex2f(i+(it*m_width) , 0.9f);
        m_leftBounds.push_back(i+(it*m_width));
        glVertex2f(i+(it*m_width) , 1.0f);
        glVertex2f(i+0.3f+(m_width*it) , 0.9f);
        m_rightBounds.push_back(i+0.3f+(m_width*it));
        glVertex2f(i+0.3f+(m_width*it) , 1.0f);
        glEnd();
        i += 0.1f;
    }
}
