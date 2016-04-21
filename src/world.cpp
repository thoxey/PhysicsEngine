#include "world.h"

// Use this to keep track of the times
#include <sys/time.h>

#define DAMPNER 50
/**
 * @brief World::World
 */
World::World() : m_isInit(false),m_startTime(0.0),m_elapsedTime(0.0)
{
}

/**
 * @brief World::~World destructorize this thing. Make sure to eliminate dynamically allocated memory.
 */
World::~World() {
}

/**
 * @brief World::init initialises the GL World, enabling features that are needed
 */
void World::init() {
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

/**
 * @brief World::resize needs to set up the camera paramaters (i.e. projection matrix) and the viewport
 * @param w Width of window
 * @param h Height of window
 */
void World::resize(int w, int h) {
    if (!m_isInit) return;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
    glViewport(0,0,w,h);
    glMatrixMode(GL_MODELVIEW);

}

/**
 * @brief World::draw draws the World to the current GL context. Called a lot - make this fast!
 */
void World::draw() {
    if (!m_isInit) return;

    // Clear the display buffer
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

}
void World::collisionDetection()
{

  for(int i = 0; i < masterList.size(); ++i)
  {
    for(int j = i+1; j < masterList.size(); ++j)
    {
      double dX = masterList[i]->m_posX - masterList[j]->m_posX;
      double dY = masterList[i]->m_posY - masterList[j]->m_posY;
      double sumOfSquares = sqrt(dX*dX + dY*dY);
      double massRatI = 1; //masterList[j]->m_mass*(masterList[i]->m_mass/masterList[j]->m_mass);
      double massRatJ = 1; //masterList[i]->m_mass*(masterList[j]->m_mass/masterList[i]->m_mass);
      if(masterList[i]->m_radius*2 > sumOfSquares)
      {
        double hyp = (2*masterList[i]->m_radius)-sumOfSquares;
        if(masterList[i]->m_isDynamic)
        {
            masterList[i]->m_isColliding = true;
            double alpha = asin(dY/sumOfSquares);
            masterList[i]->m_posX += hyp*cos(alpha) * (dX > 0 ? 0.1 : -0.1);
            masterList[i]->m_velX += dX*massRatI;
            masterList[i]->m_velX += masterList[j]->m_bounce*dX;
            masterList[i]->m_posY += hyp*sin(alpha);
            masterList[i]->m_velY += dY*massRatI;
            masterList[i]->m_velY += masterList[j]->m_bounce*dY;
          }
          if(masterList[j]->m_isDynamic)
          {
              masterList[j]->m_isColliding = true;
              double alpha = asin(dY/sumOfSquares);
              masterList[j]->m_velX -= dX*massRatJ;
              masterList[j]->m_posX -= hyp*cos(alpha) * (dX > 0 ? 0.1 : -0.1);
              masterList[j]->m_velX -= masterList[j]->m_bounce*dX;
              masterList[j]->m_posY -= hyp*sin(alpha);
              masterList[j]->m_velY -= dY*massRatJ;
              masterList[j]->m_velY -= masterList[j]->m_bounce*dY;
          }
          break;
      }
      else
      {
          masterList[j]->m_isColliding = false;
      }
    }
  }
}
void World::calcVelX()
{
  for(auto& i : masterList)
  {
      if(i->m_posX > 0.9)
      {
          i->m_posX = 0.9;
          i->m_velX *= i->m_bounce;
      }
      else if(i->m_posX < -0.9f)
      {
          i->m_posX = -0.9;
          i->m_velX *= i->m_bounce;
      }
  }
}
void World::calcVelY()
{
  for(auto& i : masterList)
  {
    if(i->m_posY > 0.9)
    {
        i->m_posY = 0.9;
        i->m_velY *= i->m_bounce;
    }
    else if(i->m_posY < -0.9f)
    {
        i->m_posY = -0.9;
        i->m_velY *= i->m_bounce;
    }
    if(m_gravOn)
    {
        i->m_velY -= i->m_g;
    }
  }
}
void World::updateObjects()
{
  m_startTime += 0.001;
  calcVelX();
  calcVelY();
  collisionDetection();
  m_elapsedTime = m_startTime;
  m_startTime = 0;
  for(auto& i : masterList)
  {
    if(i->m_isDynamic)
    {
      i->m_oldPosY = i->m_posY;
      i->m_oldPosX = i->m_posX;
      i->m_posY += i->m_velY*m_elapsedTime*0.2;
      i->m_posX += i->m_velX*m_elapsedTime*0.2;
    }
  }
}
