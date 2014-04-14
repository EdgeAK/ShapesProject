#include <iostream>
using std::cout;

struct Point
{
    int _x;
    int _y;
};

struct Box
{
    int height;
    int width;
};

class Shape
{
public:
    virtual ~Shape();
    virtual void draw() const = 0;
    void setPoint(double x, double y);
private:
    Point _currentPoint;
    Box _boundingBox;
};

void Shape::setPoint(double x, double y):_currentPoint._x(x), _currentPoint._y(y)
{}


class Circle : public Shape
{
public:
    void setRadius(double rad);
    
private:
    double _radius;
};

void Circle::setRadius(double rad):_radius(rad),_boundingBox.height(rad*2), _boundingBox.width(rad*2)
{
}
