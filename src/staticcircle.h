#ifndef STATICCIRCLE_H
#define STATICCIRCLE_H
#include "gameobject.h"
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @author Tom Hoxey
/// @version 1.0
/// @date 28/04/16 \n

/// @class StaticCircle
/// @brief This class handles the construction and drawing of the static circles on the screen
//--------------------------------------------------------------------------------------------------------------------------------------------
class StaticCircle : public GameObject
{
public:
    /// @brief StaicCircle::StaticCircle this creates a circle at the current mouse coordinates and changes the shape size range
    /// @param _posX   The X position of the mouse, with -1 being the far left and 1 being the far right
    /// @param _posY   The Y position of the mouse, with -1 being the far left and 1 being the far right
    /// @param _radMod The modifier used with the random number generator to change the range of possible values
  StaticCircle(float _posX, float _posY, int _radMod);
  /// @brief StaticCircle::draw This handles the drawing of the circle onto the screen
  /// @param _xray The boolean that determines the type of shape drawing method used, traingle fan (solid) or line loop (xray)
  void draw(bool _xray);
};
#endif // STATICCIRCLE_H
