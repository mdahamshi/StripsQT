#include "point.h"

Point::Point()
{


}

Point::Point(int a, int b)
{
    x = a;
    y = b;
}

bool Point::operator <(const Point &source)
{
    return (this->x < source.x && this->y < source.y);
}
bool Point::operator >(const Point &source)
{
    return (this->x > source.x && this->y > source.y);
}
bool Point::operator <=(const Point &source)
{
    return (this->x <= source.x && this->y <= source.y);
}
bool Point::operator >=(const Point &source)
{
    return (this->x >= source.x && this->y >= source.y);
}
