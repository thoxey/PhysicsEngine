#ifndef STATICLINE_H
#define STATICLINE_H
#include "gameobject.h"
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @author Tom Hoxey
/// @version 1.0
/// @date 28/10/16 \n

/// @class StaticLine
/// @brief This class handles the construction and drawing of the static lines on the screen
//--------------------------------------------------------------------------------------------------------------------------------------------
class StaticLine : public GameObject
{
public:
    /// @brief StatticLine::StatticLine this creates a line from the current mouse coordinates to another point
    /// @param _posX   The X position of the mouse, with -1 being the far left and 1 being the far right
    /// @param _posY   The Y position of the mouse, with -1 being the far left and 1 being the far right
    StaticLine(float _x1,  float _y1, float _x2, float _y2);
    /// @brief StaticLine::draw This handles the drawing of the line onto the scree
    void draw(bool _xray);

    double m_posX2;
    double m_posY2;
};

#endif // STATICLINE_H
