#include "button.h"
//--------------------------------------------------------------------------------------------------------------------------------------------
Button::Button()
{
    m_width = (2.0f/m_buttTot)-0.1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------
void Button::draw()
{
    GLuint TextureID = 0;

    SDL_Surface* Surface = IMG_Load("UVMap.jpg");

    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    int Mode = GL_RGB;

    if(Surface->format->BytesPerPixel == 4) {
        Mode = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, Mode, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE, Surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, TextureID);

    // For Ortho mode, of course
    int X = 0;
    int Y = 0;
    int Width = 100;
    int Height = 100;

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(X, Y, 0);
        glTexCoord2f(1, 0); glVertex3f(X + Width, Y, 0);
        glTexCoord2f(1, 1); glVertex3f(X + Width, Y + Height, 0);
        glTexCoord2f(0, 1); glVertex3f(X, Y + Height, 0);
    glEnd();



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
