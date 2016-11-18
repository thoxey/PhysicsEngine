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
                //Note to Note to self: These floats are doubles
                double massRatI = m_masterList[i]->m_mass/(m_masterList[i]->m_mass+m_masterList[j]->m_mass);
                double massRatJ = 1-massRatI; //Should be m_masterList[j]->m_mass/(m_masterList[i]->m_mass+m_masterList[j]->m_mass) but faster this way
                double sumOfSquares = sqrt((dX*dX)+(dY*dY));
                double hyp = asin(dY/sumOfSquares)*(sumOfRads-sumOfSquares);//Provides direction of reaction
                if(sumOfRads > sumOfSquares)
                {
                    m_masterList[j]->m_isColliding = true;
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
            else if(m_masterList[i]->m_isCircle != m_masterList[j]->m_isCircle)
            {
                double circleX,circleY,radius,lineX1,lineX2,lineY1,lineY2;
                char circIdx;
                if(m_masterList[i]->m_isCircle && !m_masterList[j]->m_isCircle)
                {
                    circleX = m_masterList[i]->m_posX;
                    circleY = m_masterList[i]->m_posY;
                    radius  = m_masterList[i]->m_radius;
                    circIdx = i;
                    lineX1  = m_masterList[j]->m_posX;
                    lineX2  = m_masterList[j]->m_posX2;
                    lineY1  = m_masterList[j]->m_posY;
                    lineY2  = m_masterList[j]->m_posY2;
                }
                else if(!m_masterList[i]->m_isCircle && m_masterList[j]->m_isCircle)
                {
                    circleX = m_masterList[j]->m_posX;
                    circleY = m_masterList[j]->m_posY;
                    radius  = m_masterList[j]->m_radius;
                    circIdx = j;
                    lineX1  = m_masterList[i]->m_posX;
                    lineX2  = m_masterList[i]->m_posX2;
                    lineY1  = m_masterList[i]->m_posY;
                    lineY2  = m_masterList[i]->m_posY2;
                }
                Vector2d lineVec      =  Vector2d(lineX2-lineX1, lineY2-lineY1);
                Vector2d p1c          =  Vector2d(circleX-lineX1, circleY-lineY1);
                Vector2d lineVecUnit  =  lineVec/lineVec.mag();
                double projVLen       =  p1c.dot(lineVecUnit);
                Vector2d projV        =  lineVecUnit*projVLen;
                double closeX         =  lineX1+projV.m_x;
                double closeY         =  lineY1+projV.m_y;
                if(projV.dot(lineVecUnit) <= 0)
                {
                    closeX     =  lineX1;
                    closeY     =  lineY1;
                }
                else if(projV.dot(lineVecUnit)>lineVec.mag())
                {
                    closeX     =  lineX2;
                    closeY     =  lineY2;
                }
                //Vector2d normalVec   = Vector2d(lineVec.m_y, -lineVec.m_x);
                //double dist = p1c.dot(normalVec);

                Vector2d distV = Vector2d(circleX-closeX, circleY-closeY);
                if(distV.mag()<radius)//if(std::abs(dist) < m_masterList[i]->m_radius)
                {
                    reaction(circIdx, distV.dot(lineVec), 1, circleX-closeX, circleY-closeY );

                }

            }
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
    m_masterList[_i]->m_posX += _dX*DAMPNER; //Stops overlap being possible
    m_masterList[_i]->m_velX += _hyp*_massRat;
    m_masterList[_i]->m_velX *= _hyp*m_masterList[_i]->m_bounce; //Removing _hyp*_massRat cripples performance, confusing
    m_masterList[_i]->m_posY += _dY*DAMPNER;
    m_masterList[_i]->m_velY += _hyp*_massRat;
    m_masterList[_i]->m_velY *= _hyp*_massRat*m_masterList[_i]->m_bounce;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void World::roll(GameObject _circ, Vector2d _normalVec)
{
    //Coming soon...
}
