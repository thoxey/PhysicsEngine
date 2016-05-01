///  @file button.cpp
/// @brief This class handles the buttons at the top of the screen, it stores thier positions, handles the texturing and the mouse coordinate conversion
#include "button.h"
//--------------------------------------------------------------------------------------------------------------------------------------------
Button::Button()
{
    m_width = (2.0f/m_buttTot)-0.1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void Button::draw()
{
    /// The following section is from :-
    /// Tim Jones (2011). SDL Tip - SDL Surface to OpenGL Texture [online]. [Accessed 2016].
    /// Available from: <http://www.sdltutorials.com/sdl-tip-sdl-surface-to-opengl-texture>.
    glEnable(GL_TEXTURE_2D);
    GLuint TextureID = 0;
    SDL_Surface* Surface = IMG_Load("banner.png");
    if(Surface == NULL)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        exit(0);
    }
    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);
    int Mode = GL_RGBA;
    if(Surface->format->BytesPerPixel == 4)
    {
        Mode = GL_RGBA;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, Mode, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE, Surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    // For Ortho mode, of course
    float X = -1;
    float Y = 0.9;
    float Width = 2;
    float Height = 0.1;

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0, 0);
    glVertex3f(X, Y, 0);
    glTexCoord2f(1, 0);
    glVertex3f(X + Width, Y, 0);
    glTexCoord2f(1, 1);
    glVertex3f(X + Width, Y + Height, 0);
    glTexCoord2f(0, 1);
    glVertex3f(X, Y + Height, 0);
    glEnd();
    /// end of Citation
    float i = -0.98f;
    for(int it = 0; it <= m_buttTot; ++it)
    {
        m_leftBounds.push_back(i+(it*m_width));
        m_rightBounds.push_back(i+0.3f+(m_width*it));
        i += 0.1f;
    }
    glDisable(GL_TEXTURE_2D);
}
//--------------------------------------------------------------------------------------------------------------------------------------------
float Button::convertPixCoorX(int _x)
{
    float f = static_cast<float>(_x);
    f = static_cast<float>((f/WIDTH)*2-1);
    return f;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
float Button::convertPixCoorY(int _y)
{
    float f = static_cast<float>(_y);
    float flippedHeight =  std::abs(HEIGHT-f);
    f = static_cast<float>((flippedHeight/HEIGHT)*2-1);
    return f;
}
