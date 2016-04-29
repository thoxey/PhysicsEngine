#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H
#include "gameobject.h"
#include <ctime>
//--------------------------------------------------------------------------------------------------------------------------------------------
/// @author Tom Hoxey
/// @version 1.0
/// @date 28/04/16 \n

/// @class DynamicObject
/// @brief This class sets any children to be dynamic
//--------------------------------------------------------------------------------------------------------------------------------------------
class DynamicObject : public GameObject
{
public:
  /// @brief This is the constructor for the Dynamic Object class, it sets the m_isDynamic bool to true
  DynamicObject();
};
#endif // DYNAMICOBJECT_H
