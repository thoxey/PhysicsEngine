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
