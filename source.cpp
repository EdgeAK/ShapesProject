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
    Circle C = Circle(216, 216, 216);
    C.draw();
    C.Shape::scaled(2, 1);
    C.draw();

    
}