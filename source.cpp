//
//  ShapeClass.h
//  ShapesProject
//
//  Created by Nicholas Mardeusz on 4/13/14.
//  Copyright (c) 2014 Edge. All rights reserved.
//

#include "ShapeClass.h"
#include <iostream>
using std::cout;
using std::endl;
#include <memory>
using std::shared_ptr;
using std::make_shared;
#include<fstream>
using std::ofstream;

int main()
{
    Circle C = Circle(216, 216, 72);
    C.draw("circle");
    
    C.scaled(3, 1);
    C.draw("scaled");

    C.rotate(90);
    C.draw("rotated");
    
    Point p;
    p._x = 72;
    p._y = 72;
    Rectangle R = Rectangle(72, 144, p);
    R.draw("rectangle");
    
    R.scaled(3, 1);
    R.draw("scaled");
    
    R.rotate(90);
    R.draw("rotated");
    
}