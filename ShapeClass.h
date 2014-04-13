//
//  ShapeClass.h
//  ShapesProject
//
//  Created by Nicholas Mardeusz on 4/13/14.
//  Copyright (c) 2014 Edge. All rights reserved.
//

#ifndef ShapesProject_ShapeClass_h
#define ShapesProject_ShapeClass_h

#include <iostream>
using std::cout;
using std::endl;
#include <memory>
using std::shared_ptr;
using std::make_shared;
#include<fstream>
using std::ofstream;



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
    virtual ~Shape() = default;
    virtual void draw() = 0;
    void createFile();
    void setPoint(double x, double y);
    void setBox(double height, double width);
    Point getCurPoint(Shape *cur);
private:
    Point _currentPoint;
    Box _boundingBox;
};


//void Shape::createFile()
//{
//    ofstream postScriptOut;
//    postScriptOut.open ("ShapesOutput.ps");
//    postScriptOut << "%!" << endl;
//    postScriptOut << "newpath" << endl;
//}
void Shape::setPoint(double x, double y)
{
    _currentPoint._x = x;
    _currentPoint._y = y;
}

void Shape::setBox(double height, double width)
{
    _boundingBox.height = height;
    _boundingBox.width = width;
}

Point Shape::getCurPoint(Shape *cur)
{
    return _currentPoint;
}

class Circle : public Shape
{
public:
    virtual ~Circle() = default;
    Circle(double x, double y, double radius);
    void setRadius(double rad);
    void draw();
private:
    double _radius;
};

Circle::Circle(double x, double y, double radius)
{
    setPoint(x, y);
    _radius = radius;
    setBox(radius*2, radius*2);
}

void Circle::setRadius(double rad)
{
    _radius = rad;
    setBox(rad*2, rad*2);
}

void Circle::draw()
{
    //createFile();
    ofstream postScriptOut;
    postScriptOut.open ("ShapesOutput.ps");
    postScriptOut << "%!" << endl;
    postScriptOut << "newpath" << endl;
    postScriptOut << getCurPoint(this)._x << " " << getCurPoint(this)._y << " " << _radius << " 0 360 arc closepath" << endl;
    postScriptOut << "stroke" << endl;
    postScriptOut << "showpage" << endl;
    postScriptOut.close();
}
#endif
