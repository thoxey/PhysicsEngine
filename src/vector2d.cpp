#include "vector2d.h"

Vector2d::Vector2d(double _x, double _y)
{
    m_x = _x;
    m_y = _y;
}
Vector2d Vector2d::operator * (double _scalar)
{
    return Vector2d(m_x*_scalar, m_y*_scalar);
}
Vector2d Vector2d::operator + (Vector2d _v)
{
    return Vector2d(m_x+_v.m_x, m_y+_v.m_y);
}
Vector2d Vector2d::operator - (Vector2d _v)
{
    return Vector2d(m_x-_v.m_x, m_y-_v.m_y);
}
Vector2d Vector2d::operator / (Vector2d _v)
{
    return Vector2d(m_x/_v.m_x, m_y/_v.m_y);
}
bool Vector2d::operator == (Vector2d _v)
{
    return ((m_x == _v.m_x)&&(m_y == _v.m_y));
}
bool Vector2d::operator >= (Vector2d _v)
{
    return (((m_x == _v.m_x)&&(m_y == _v.m_y))
         || ((m_x == _v.m_x)>(m_y == _v.m_y)));
}
bool Vector2d::operator <= (Vector2d _v)
{
    return (((m_x == _v.m_x)&&(m_y == _v.m_y))
         || ((m_x == _v.m_x)<(m_y == _v.m_y)));
}
bool Vector2d::operator >  (Vector2d _v)
{
    return ((m_x == _v.m_x)>(m_y == _v.m_y));
}
bool Vector2d::operator <  (Vector2d _v)
{
    return ((m_x == _v.m_x)<(m_y == _v.m_y));
}
