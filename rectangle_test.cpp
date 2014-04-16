#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include "ShapeClass.h"

int main()
{
    Rectangle rect = Rectangle(5, 5, 5, 5);
    Rotation rot(rect, 90);
    rot.draw();
    return 0;
}
