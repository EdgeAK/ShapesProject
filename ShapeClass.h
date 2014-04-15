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
using std::cin;
using std::endl;
#include <memory>
using std::shared_ptr;
using std::make_shared;
#include<fstream>
using std::ofstream;
#include<string>
using std::string;


struct Point
{
    double _x;
    double _y;
};

struct Box
{
    double height;
    double width;
};


class Shape
{
public:
    //virtual ~Shape() = 0;
    virtual void draw() = 0;
    virtual ofstream createFile(string fileName);
    void setPoint(double x, double y);
    void setBox(double height, double width);
    Point getCurPoint(Shape *cur);
    //virtual void rotate(Shape &s, double degree) = 0;
    //void scaled(Shape &s, double x, double y);
    
private:
    Point _currentPoint;
    Box _boundingBox;
};




ofstream Shape::createFile(string fileName)
{
    ofstream postScriptOut;
    postScriptOut.open (fileName);
    postScriptOut << "%!" << endl;
    postScriptOut << "newpath" << endl;
    return postScriptOut;
}

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

//void Shape::scaled(Shape &s, double x, double y)
//{
//    
//}

class Circle : public Shape
{
public:
    //virtual ~Circle() = 0;
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

//void Circle::setRadius(double rad)
//{
//    _radius = rad;
//    setBox(rad*2, rad*2);
//}

void Circle::draw()
{
    string fileName;
    cout << "Name of file: " << endl;
    cin >> fileName;
    ofstream postScriptOut = createFile(fileName + ".ps");
    
    postScriptOut << getCurPoint(this)._x << " " << getCurPoint(this)._y << " " << _radius << " 0 360 arc closepath" << endl;
    postScriptOut << "stroke" << endl;
    postScriptOut << "showpage" << endl;
    postScriptOut.close();
}

#endif
