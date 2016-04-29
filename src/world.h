#ifndef WORLD_H
#define WORLD_H
#ifdef __APPLE__
#include <SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glut.h>
#endif
#include <vector>
#include <cmath>
#include "gameobject.h"
//--------------------------------------------------------------------------------------------------------------------------------------------
/// \author Tom Hoxey
/// \version 1.0
/// \date 28/04/16 \n

/// \class NAME OF YOUR CLASS GOES HERE
/// \brief PUT A BRIEF DESCRIPTION OF THE CLASS HERE
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @brief The Scene class, contains all the collision code
class World
{
public:
    /// @brief World::World Constructor and sets the starting shape size
    World();
    ///@brief World::~World destructorize this thing. Make sure to eliminate dynamically allocated memory.
    virtual ~World();
    /// @brief World::init initialises the GL World, enabling features that are needed
    virtual void init();
    /// @brief World::resize needs to set up the camera paramaters (i.e. projection matrix) and the viewport
    /// @param w Width of window
    /// @param h Height of window
    virtual void resize(int w, int h);
    ///@brief World::draw draws the World to the current GL context. Called a lot - make this fast!
    virtual void draw();
    /// @brief This updates the position of the objects once the velocities have been updated
    void updateObjectsPos();
    /// @brief This calls all of the velocity changing functions and handles the timer
    void updateObjectsVel();

    std::vector<GameObject*> masterList;
    bool m_xray = true;
    bool m_gravOn = true;
    bool m_shapeSwitch = true;
    int m_calcs = 5;
    int m_shapeSize = 5;
//--------------------------------------------------------------------------------------------------------------------------------------------
private:
    /// @brief World::collisionDetection detects whether two objects are colliding, then calls the reaction if they are
    void collisionDetection();
    /// @brief This calculates the X velocity, and keeps it in the x bounds
    void calcVelX();
    /// @brief This calculates the Y velocity, and keeps it in the y bounds (with room for buttons at the top)
    void calcVelY();
    /// @brief This applies the reaction forces to the shapes
    /// @param _i this is the number in the master list of the object reacting
    /// @param _hyp this is the distance of intersection of the two objects
    /// @param _massRat This is the ratio of the masses, which are semi-random and based on size
    /// @param _dX the distance between the centres of the shapes on the x axis
    /// @param _dX the distance between the centres of the shapes on the y axis
    void reaction(int _i, double _hyp, double _massRat, double _dX, double _dY);

    bool m_isInit;
    double m_startTime;
    double m_elapsedTime;
//--------------------------------------------------------------------------------------------------------------------------------------------
};
#endif // WORLD_H
