#include "gameobject.h"
GameObject::GameObject()
{
    //m_mass = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}
void GameObject::draw(bool _xray)
{

}

void GameObject::initDeltaTime()
{
  m_timer += 0.0001;
}
void GameObject::setDeltaTime()
{
  m_deltaTime = m_timer;
}
void GameObject::initGameObject()
{

}
