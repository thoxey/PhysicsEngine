#ifndef BUTTON_H
#define BUTTON_H
#ifdef __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glut.h>
#endif
#include <vector>
#include <iostream>
//--------------------------------------------------------------------------------------------------------------------------------------------
class Button
{
public:
    Button();
    double m_posY = 0;
    double m_posX = 0;
    float m_width = 0.1f;
    int m_buttTot = 6;

    void draw();
    float convertPixCoorX(int _x);
    float convertPixCoorY(int _Y);
    std::vector<float> m_leftBounds;
    std::vector<float> m_rightBounds;

};
#endif // BUTTON_H
