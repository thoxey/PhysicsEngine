///  @file world.cpp
/// @brief This class is the backbone of the program, it handles the SDL/GL window and rendering and the collision detection, and reaction for the objects
#include "world.h"
#define DAMPNER 0.03
#define BOUND 1 //one by default, set lower to make smaller space, for testing (or fun!)
//--------------------------------------------------------------------------------------------------------------------------------------------
World::World() : m_startTime(0.0),m_elapsedTime(0.0),m_isInit(false)
{
    m_shapeSize = 5;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
World::~World(){}
//--------------------------------------------------------------------------------------------------------------------------------------------
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
void World::draw() {
    if (!m_isInit) return;
    // Clear the display buffer
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

}
//--------------------------------------------------------------------------------------------------------------------------------------------
void World::collisionDetection()
{
    for(uint16_t i = 0; i < m_masterList.size(); ++i)
    {
        for(uint16_t j = i+1; j < m_masterList.size(); ++j) //Nested loop to only compare collisions once i.e A -> B and not B -> A as well
        {
            if( m_masterList[i]->m_isCircle && m_masterList[j]->m_isCircle)
            {
                double dX = m_masterList[i]->m_posX - m_masterList[j]->m_posX;
                double dY = m_masterList[i]->m_posY - m_masterList[j]->m_posY;
                double sumOfRads = m_masterList[i]->m_radius + m_masterList[j]->m_radius;  //Note to self:DONT change these to floats again, it will break it... again
                double massRatI = m_masterList[i]->m_mass/(m_masterList[i]->m_mass+m_masterList[j]->m_mass);
                double massRatJ = 1-massRatI; //Should be m_masterList[j]->m_mass/(m_masterList[i]->m_mass+m_masterList[j]->m_mass) but faster this way
                double sumOfSquares = sqrt((dX*dX)+(dY*dY));
                double hyp = asin(dY/sumOfSquares)*(sumOfRads-sumOfSquares);
                if(hyp == 0)
                    hyp = 0.001; //Just in case
                if(sumOfRads > sumOfSquares)
                {
                    if(m_masterList[i]->m_isDynamic)
                    {
                        reaction(i, hyp, massRatI, dX, dY);
                    }
                    if(m_masterList[j]->m_isDynamic)
                    {
                        reaction(j, -hyp, -massRatJ, -dX, -dY);
                    }
                }
                else
                {
                    m_masterList[j]->m_isColliding = false;
                }
            }
            //WORK IN PROGRESS
//            else if(m_masterList[i]->m_isCircle && !m_masterList[j]->m_isCircle)
//            {
//                float circleX = m_masterList[i]->m_posX;
//                float lineX1 = m_masterList[j]->m_posX;
//                float lineX2 = m_masterList[j]->m_posX2;

//                if(circleX > lineX1 && circleX < lineX2)
//                    m_masterList[i]->m_posY = m_masterList[j]->m_posY+m_masterList[i]->m_radius;
//            }
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void World::calcVelX()
{
    for(auto& i : m_masterList)
    {
        if(i->m_posX > BOUND-i->m_radius)
        {
            i->m_posX = BOUND-i->m_radius;
            i->m_velX *= i->m_bounce;
        }
        else if(i->m_posX < -BOUND+i->m_radius)
        {
            i->m_posX = -BOUND+i->m_radius;
            i->m_velX *= i->m_bounce;
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void World::calcVelY()
{
    for(auto& i : m_masterList)
    {
        if(i->m_posY >  (BOUND-0.1)-i->m_radius) //0.1 left for UI
        {
            i->m_posY = (BOUND-0.1)-i->m_radius;
            i->m_velY *= i->m_bounce;
        }
        else if(i->m_posY < -BOUND+i->m_radius)
        {
            i->m_posY = -BOUND+i->m_radius;
            i->m_velY *= i->m_bounce;
        }
        if(m_gravOn)
        {
            i->m_velY -= i->m_g/5;
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void World::updateObjectsVel()
{
    //std::cout<<m_startTime<<std::endl;
    calcVelX();
    calcVelY();
    collisionDetection();
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void World::updateObjectsPos()
{
    struct timeval tim;
    gettimeofday(&tim, NULL);
    double now =tim.tv_sec+(tim.tv_usec * 1e-6);
    m_elapsedTime = std::abs(m_startTime - now)*1e-12;
    for(auto& i : m_masterList)
    {
        if(i->m_isDynamic)
        {
            if(!isnan(i->m_velX)) //Safety check, can return nan and make object disapear!
                i->m_posX += (i->m_velX*m_elapsedTime)/m_calcs;
            if(!isnan(i->m_velY))
                i->m_posY += (i->m_velY*m_elapsedTime)/m_calcs;
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void World::reaction(int _i, double _hyp, double _massRat, double _dX, double _dY)
{
    m_masterList[_i]->m_isColliding = true;
    m_masterList[_i]->m_posX += _dX*DAMPNER; //Stops overlap being possible
    m_masterList[_i]->m_velX += _hyp*_massRat;
    m_masterList[_i]->m_velX *= _hyp*_massRat*m_masterList[_i]->m_bounce; //Removing _hyp*_massRat cripples performance, confusing
    m_masterList[_i]->m_posY += _dY*DAMPNER;
    m_masterList[_i]->m_velY += _hyp*_massRat;
    m_masterList[_i]->m_velY *= _hyp*_massRat*m_masterList[_i]->m_bounce;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
