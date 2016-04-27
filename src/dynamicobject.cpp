#include "dynamicobject.h"
//--------------------------------------------------------------------------------------------------------------------------------------------
DynamicObject::DynamicObject()
{
  m_isDynamic = true;
  m_mass = ((double) rand() / (RAND_MAX));
}

