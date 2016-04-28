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
/// @brief The Scene class
class World
{
public:
    World();
    virtual ~World();
    virtual void init();
    virtual void resize(int w, int h);
    virtual void draw();
    std::vector<GameObject*> masterList;
    bool m_xray = true;
    bool m_gravOn = true;
    bool m_shapeSwitch = true;
    int m_calcs = 5;
    int m_shapeSize = 5;
    void updateObjectsPos();
    void updateObjectsVel();
private:
    bool m_isInit;
    double m_startTime;
    double m_elapsedTime;
    void collisionDetection();
    void calcVelX();
    void calcVelY();
    void reaction(int _i, double _hyp, double _massRat, double _dX, double _dY);
};
#endif // WORLD_H
