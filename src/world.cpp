#include "world.h"

// Use this to keep track of the times
#include <sys/time.h>

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
    // Sanity check - if we've already initialised this class we shouldn't be here
    if (m_isInit) return;

    // Enable texturing
    glDisable(GL_TEXTURE_2D);

    // Enable counter clockwise face ordering
    glFrontFace(GL_CCW);

    glEnable(GL_NORMALIZE);

    // Make our points lovely and smooth
    glEnable( GL_POINT_SMOOTH );
    glEnable( GL_MULTISAMPLE_ARB);
    glEnable(GL_DEPTH_TEST);

    // Set the background colour
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

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
void World::collisionDetection(std::vector<GameObject*> _list)
{

  for(int i = 0; i < _list.size(); ++i)
  {
    for(int j = i+1; j < _list.size(); ++j)
    {
      double sumOfSquares = sqrt(pow((_list[i]->m_posX - _list[j]->m_posX), 2)+pow((_list[i]->m_posY - _list[j]->m_posY), 2));
      float massRatA = _list[j]->m_mass/(_list[i]->m_mass*_list[j]->m_mass);
      if(_list[i]->m_radius*2 > sumOfSquares)
      {
          _list[j]->m_isColliding = true;
          _list[j]->m_velY += (_list[j]->m_posY-_list[i]->m_posY)*massRatA;
          _list[j]->m_velX += (_list[j]->m_posX - _list[i]->m_posX)*massRatA;
          break;
      }
      else
      {
          _list[j]->m_isColliding = false;
      }
    }
  }
}
void World::calcVelX()
{
  for(auto& i : masterList)
  {
    if(i->m_isColliding)
        i->m_velX *= i->m_bounce;
    if(i->m_posX >= 0.9 || i->m_posX <= -0.9)
      i->m_velX *= i->m_bounce;
  }
}
void World::calcVelY()
{
  for(auto& i : masterList)
  {
    i->m_velY -= i->m_g;
    if(i->m_isColliding)
        i->m_velY *= i->m_bounce;
    if(i->m_posY >= 0.9 || i->m_posY <= -0.9f)
    {
      i->m_velY *= i->m_bounce;
    }
  }
}
void World::updateObjects(std::vector<GameObject*> _list)
{
  m_startTime += 0.001;
  calcVelX();
  calcVelY();
  collisionDetection(_list);
  m_elapsedTime = m_startTime;
  m_startTime = 0;
  for(auto& i : _list)
  {
    if(i->m_isDynamic)
    {
      i->m_posY += i->m_velY*m_elapsedTime;
      i->m_posX += i->m_velX*m_elapsedTime;
    }
  }
}
