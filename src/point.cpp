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
Point & Point::operator =(const Point &source)
{
    if(this == &source)
        return *this;
    this->x = source.x;
    this->y = source.y;
    return *this;

}
std::string Point::toString()
{
    return std::to_string(x)+","+std::to_string(y);
}

bool Point::operator >=(const Point &source)
{
    return (this->x >= source.x && this->y >= source.y);
}
