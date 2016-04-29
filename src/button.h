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
#include <cmath>
#define WIDTH 1000
#define HEIGHT 1000
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @author Tom Hoxey
/// @version 1.0
/// @date 28/04/16

/// @class Buttons
/// @brief This class handles the buttons at the top of the screen, it stores thier positions, handles the texturing and the mouse coordinate conversion
//--------------------------------------------------------------------------------------------------------------------------------------------
class Button
{
public:
    /// @brief Button::Button The constructor for the GUI class, it sets the size of the button depending on how many are needed
    Button();
    /// @brief Button::draw This function renders the texture for the UI and sets the boundaries for the buttons
    void draw();
    /// @brief Button::convertPixCoorX This function converts the pixel coordinates in the X to a -1 , 1 range, for use with openGl\
    /// @param int _x The X coordinate of the mouse
    float convertPixCoorX(int _x);
    /// @brief Button::convertPixCoorX This function converst the pixel coordinates in the Y to a -1 , 1 range, for use with openGl\
    /// @param int _y This is the Y coordinate of the mouse
    float convertPixCoorY(int _Y);
    /// @brief m_width The width of the buttons
    float m_width;
    /// @brief m_buttTot The total amount of buttons on the GUI
    int m_buttTot = 6;
    /// @brief m_leftBounds A vector of the left boundaries of the buttons
    std::vector<float> m_leftBounds;
    /// @brief m_rightBounds A vector of all the right side boundaries of the buttons
    std::vector<float> m_rightBounds;

};
#endif // BUTTON_H
