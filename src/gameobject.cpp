///  @file gameobject.cpp
/// @brief This is the parent class for all the possible objects, static objects inherit directly from this
#include "gameobject.h"
//--------------------------------------------------------------------------------------------------------------------------------------------
GameObject::GameObject()
{
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void GameObject::draw(bool _xray)
{
    if(_xray)
        return;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void GameObject::setPos2(double _x2, double _y2)
{
    m_posX2 = _x2;
    m_posY2 = _y2;
}
