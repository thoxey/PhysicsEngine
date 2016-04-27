#include "world.h"
#define DAMPNER 0.03
#define BOUND 0.9
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @brief World::World Constructor and sets the starting shape size
World::World() : m_isInit(false),m_startTime(0.0),m_elapsedTime(0.0)
{
    m_shapeSize = 5;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
///@brief World::~World destructorize this thing. Make sure to eliminate dynamically allocated memory.
World::~World(){}
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @brief World::init initialises the GL World, enabling features that are needed
void World::init()
{
    if (m_isInit) return;
    glFrontFace(GL_CCW);
    glEnable(GL_NORMALIZE);
    // Set the background colour
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    // Set our start time by using the gettimeofday function (accurate to 10 nanosecs)
    struct timeval tim;
    gettimeofday(&tim, NULL);
    m_startTime = tim.tv_sec+(tim.tv_usec * 1e-6);
    m_isInit = true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @brief World::resize needs to set up the camera paramaters (i.e. projection matrix) and the viewport
/// @param w Width of window
/// @param h Height of window
void World::resize(int w, int h)
{
    if (!m_isInit) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
    glViewport(0,0,w,h);
    glMatrixMode(GL_MODELVIEW);
}
//--------------------------------------------------------------------------------------------------------------------------------------------
///@brief World::draw draws the World to the current GL context. Called a lot - make this fast!
void World::draw() {
    if (!m_isInit) return;
    // Clear the display buffer
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

}
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @brief World::collisionDetection detects whether two objects are colliding, then calls the reaction if they are
void World::collisionDetection()
{
    for(int i = 0; i < masterList.size(); ++i)
    {
        for(int j = i+1; j < masterList.size(); ++j)
        {
            double dX = masterList[i]->m_posX - masterList[j]->m_posX;
            double dY = masterList[i]->m_posY - masterList[j]->m_posY;
            double sumOfRads = masterList[i]->m_radius + masterList[j]->m_radius;
            double massRatI = masterList[j]->m_mass*(masterList[i]->m_mass/masterList[j]->m_mass);
            double massRatJ = masterList[i]->m_mass*(masterList[j]->m_mass/masterList[i]->m_mass);
            double sumOfSquares = sqrt(dX*dX + dY*dY);
            double hyp = asin(dY/sumOfSquares)*(sumOfRads-sumOfSquares);

            if(sumOfRads > sumOfSquares)
            {
                if(masterList[i]->m_isDynamic)
                {
                    reaction(i, hyp, massRatI, dX, dY);
                }
                if(masterList[j]->m_isDynamic)
                {
                    reaction(j, -hyp, massRatJ, -dX, -dY);
                }
            }
            else
            {
                masterList[j]->m_isColliding = false;
            }
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @brief This applies the reaction forces to the shapes
/// @param _i this is the number in the master list of the object reacting
/// @param _hyp this is the distance of intersection of the two objects
/// @param _massRat This is the ratio of the masses, which are semi-random and based on size
/// @param _dX the distance between the centres of the shapes on the x axis
/// @param _dX the distance between the centres of the shapes on the y axis
void World::reaction(int _i, double _hyp, double _massRat, double _dX, double _dY)
{
    masterList[_i]->m_isColliding = true;
    masterList[_i]->m_posX += _dX*DAMPNER;
    masterList[_i]->m_velX *= _hyp*_massRat*masterList[_i]->m_bounce*DAMPNER;
    masterList[_i]->m_posY += _dY*DAMPNER;
    masterList[_i]->m_velY *= _hyp*_massRat*masterList[_i]->m_bounce*DAMPNER;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @brief This calculates the X velocity, and keeps it in the x bounds
void World::calcVelX()
{
    for(auto& i : masterList)
    {
        if(i->m_posX > 1-i->m_radius)
        {
            i->m_posX = 1-i->m_radius;
            i->m_velX *= i->m_bounce;
        }
        else if(i->m_posX < -1+i->m_radius)
        {
            i->m_posX = -1+i->m_radius;
            i->m_velX *= i->m_bounce;
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @brief This calculates the Y velocity, and keeps it in the y bounds (with room for buttons at the top)
void World::calcVelY()
{
    for(auto& i : masterList)
    {
        if(i->m_posY > 0.9-i->m_radius)
        {
            i->m_posY = 0.9-i->m_radius;
            i->m_velY *= i->m_bounce;
        }
        else if(i->m_posY < -1+i->m_radius)
        {
            i->m_posY = -1+i->m_radius;
            i->m_velY *= i->m_bounce;
        }
        if(m_gravOn)
        {
            i->m_velY -= i->m_g/5;
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @brief This calls all of the velocity changing functions and handles the timer
void World::updateObjectsVel()
{
    m_startTime += 0.001;
    calcVelX();
    calcVelY();
    collisionDetection();
    m_elapsedTime = m_startTime;
    m_startTime = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @brief This updates the position of the objects once the velocities have been updated
void World::updateObjectsPos()
{
    for(auto& i : masterList)
    {
        if(i->m_isDynamic)
        {
            i->m_posY += (i->m_velY*m_elapsedTime)/m_calcs;
            i->m_posX += (i->m_velX*m_elapsedTime)/m_calcs;
        }
    }
}
