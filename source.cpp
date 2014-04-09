#include <iostream>
using std::cout;

struct Point
{
    int x;
    int y;
};

struct Box
{
    int height;
    int width;
};

class Shape
{
public:
    virtual ~Sshape();
    virtual void draw() const = 0;
private:
    Point current_point;
    Box bounding_box;
};
