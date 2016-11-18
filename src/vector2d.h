#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <cmath>

class Vector2d
{
public:
    Vector2d(double _x, double _y);
    double m_x = 0;
    double m_y = 0;
    //--------------------------------------------------------------------------------------------------------------------------------------------
    Vector2d operator * (double _scalar);
    Vector2d operator + (Vector2d _v);
    Vector2d operator - (Vector2d _v);
    Vector2d operator / (double _s);
    double operator ^ (Vector2d _v);
    //--------------------------------------------------------------------------------------------------------------------------------------------
    bool operator == (Vector2d _v);
    bool operator >= (Vector2d _v);
    bool operator <= (Vector2d _v);
    bool operator >  (Vector2d _v);
    bool operator <  (Vector2d _v);
    double mag();
    double dot(Vector2d &_RHS);

};

#endif // VECTOR2D_H
