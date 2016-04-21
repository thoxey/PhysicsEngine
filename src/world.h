#ifndef WORLD_H
#define WORLD_H

#ifdef __APPLE__
#include <SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
// Include the header file for our current scene
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
/**
 * @brief The Scene class
 */
class World
{
public:

    /// A constructor, called when this class is instanced in the form of an object
    World();

    /// A virtual destructor, in case we want to inherit from this class
    virtual ~World();

    /// Initialises the scene, called before render().
    virtual void init();

    /// Called when the window size changes (for example, if the user maximises the window).
    virtual void resize(int w, int h);

    /// Called most frequently, redraws the scene.
    virtual void draw();

    std::vector<GameObject*> masterList;

    void updateObjects();

    bool m_xray = true;

private: // Protected means that it is accessible to derived classes
    /// Keep track of whether this has been initialised - otherwise it won't be ready to draw!
    bool m_isInit;

    /// The time since the object was initialised, which is used for animation purposes
    double m_startTime;

    /// A member that is updated when update() is called indicating the elapsed time
    double m_elapsedTime;

    void collisionDetection();

    void calcVelX();

    void calcVelY();

};

#endif // WORLD_H
