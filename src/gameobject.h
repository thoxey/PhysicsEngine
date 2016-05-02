#ifndef GameObject_H
#define GameObject_H
#ifdef __APPLE__
#include <SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
#include <cmath>
#include <vector>
#define PI 3.141592653589793
#define TWOPI 6.283185307
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @author Tom Hoxey
/// @version 1.0
/// @date 28/04/16 \n

/// @class GameObject
/// @brief This is the parent class for all the possible objects, static objects inherit directly from this
//--------------------------------------------------------------------------------------------------------------------------------------------
class GameObject
{
public:
    /// @brief GameObject::GameObject The constructor for the GameObject Class
    GameObject();
    /// @brief GameObject::draw The draw for GameObject is pure virtuak as it cannot be drawn
    virtual void draw(bool _xray) = 0;
    /// @brief m_posY         is the Y position of the object in the -1 to 1 range
    double m_posY      = 0;
    /// @brief m_posX         is the X position of the object in the -1 to 1 range
    double m_posX      = 0;
    /// @brief m_velX         is the X velocity of the object (m_posX * World.m_elapsedTime)
    double m_velX      = 0.0;
    /// @brief m_velY         is the Y velocity of the object (m_posY * World::m_elapsedTime)
    double m_velY      = 0.0;
    /// @brief m_bounce       is the bouncienesss of the object, must be between -1 and 0
    float m_bounce     = -0.6f;
    /// @brief m_radius       the radius of the object, it is between a random range, but defaukts to 0.1
    float m_radius     = 0.1f;
    /// @brief m_mass         the mass of the object, it is based on the radius size for dynamic objects
    float m_mass       = 1.0f;
    /// @brief m_radMod       the range in which the random values for the radius fall into, it is able to be changed during runtime
    int m_radMod       = 0;
    /// @brief m_isColliding  this bool can be used for debugging purposes it is set to true on collision
    bool m_isColliding = false;
    /// @brief m_isDynamic    bool used to add velocity etc to only the dynamic objects
    bool m_isDynamic   = false;
    /// @brief m_g            gravity constant
    const float m_g = 9.8f;
protected:
    /// @brief m_col          is used for modifying the colour of the given object
    float m_col       = 0.0f;
};
#endif // GameObject_H
