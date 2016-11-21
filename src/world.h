#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <cmath>
#include "gameobject.h"
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @author Tom Hoxey & Richard Southern
/// @version 1.0
/// @date 28/04/16

/// @class World
/// @brief This class is the backbone of the program, it handles the SDL/GL window and rendering and the collision detection, and reaction for the objects
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @brief The Scene class, contains all the collision code
class World
{
public:
    /// @brief World::World             Constructor and sets the starting shape size
    World();
    ///@brief World::~World             destructorize this thing. Make sure to eliminate dynamically allocated memory.
    virtual ~World();
    /// @brief World::init              initialises the GL World, enabling features that are needed
    virtual void init();
    /// @brief World::resize            needs to set up the camera paramaters (i.e. projection matrix) and the viewport
    /// @param w Width of window
    /// @param h Height of window
    virtual void resize(int w, int h);
    ///@brief World::draw               Draws the World to the current GL context
    virtual void draw();
    /// @brief World::updateObjectsPos  This updates the position of the objects once the velocities have been updated
    void updateObjectsPos();
    /// @brief World::updateObjectsVel  This calls all of the velocity changing functions and handles the timer
    void updateObjectsVel();
    /// @brief m_masterList             The list that contains all GameObjects in the scene
    std::vector<GameObject*> m_masterList;
    /// @brief m_xray                   This bool allows for the swapping between the 'solid and 'hollow' draw methods
    bool m_xray = true;
    /// @brief m_gravOn                 This bool allows for turning gravity on and off
    bool m_gravOn = true;
    /// @brief m_calcs                  This is how many times the objects are updated before drawing
    int m_calcs = 5;
    /// @brief m_shapeSize              This is changes the GameObject.m_radMod during runtime via the arrow keys or UI
    int m_shapeSize = 5;
    ///@brief m_startTime                  This is used for
    double m_startTime;
    ///@brief m_
    double m_elapsedTime;
    //--------------------------------------------------------------------------------------------------------------------------------------------
private:
    /// @brief World::collisionDetection   Detects whether two objects are colliding, then calls the reaction if they are
    void collisionDetection();
    /// @brief World::calcVelX             This calculates the X velocity, and keeps it in the x bounds
    void calcVelX();
    /// @brief World::calcVelY             This calculates the Y velocity, and keeps it in the y bounds (with room for buttons at the top)
    void calcVelY();
    /// @brief Wolrd::reaction             This applies the reaction forces to the shapes
    /// @param _i                           The number in the master list of the object reacting
    /// @param _hyp                         The distance of intersection of the two objects
    /// @param _massRat                     The ratio of the masses, which are semi-random and based on size
    /// @param _dX                          The distance between the centres of the shapes on the x axis
    /// @param _dX                          The distance between the centres of the shapes on the y axis
    void reaction(int _i, double _hyp, double _massRat, double _dX, double _dY);
    //void roll(GameObject _circ, Vector2d _normalVec);
    ///@brief m_isInit                     Used for a sanity check, making sure the world is initialised before continuing
    bool m_isInit;

    //--------------------------------------------------------------------------------------------------------------------------------------------
};
#endif // WORLD_H
