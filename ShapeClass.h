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
struct Scale
{
    double _x = 1;
    double _y = 1;
};

//Shape
class Shape
{
public:
    //virtual ~Shape() = default;
    virtual void draw(ofstream & postScript) = 0;
    virtual void draw();
    void setPoint(double x, double y);
    void setBox(double height, double width);
    void scaled(double x, double y);
    void rotate(double rotDegree);
protected:
    Point _currentPoint;
    Box _boundingBox;
    Scale _shapeScale;
    double _rotationDegree = 0;
};
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
void Shape::scaled(double x, double y)
{
    _shapeScale._x = x;
    _shapeScale._y = y;
}
void Shape::rotate(double r)
{
    _rotationDegree = r;
}
void Shape::draw()
{
    string filename;
    cout << "Enter a file name to draw to: ";
    getline(cin, filename);
    ofstream postScript;
    postScript.open(filename.c_str());
    draw(postScript);
    postScript.close();
}

//Circle
class Circle : public Shape
{
public:
    Circle(double x, double y, double radius);
    void draw(ofstream & postScript);
    void draw();
private:
    double _radius;
};
Circle::Circle(double x, double y, double radius) : _radius(radius)
{
    setPoint(x, y);
    setBox(radius*2, radius*2);
}
void Circle::draw(ofstream & postScript)
{
    postScript << "/circle{" << endl;
    postScript << "newpath 0 0 " << _radius << " 0 360 arc closepath stroke} def" << endl;
    
    postScript << _currentPoint._x << " " << _currentPoint._y << " translate " << endl;
    postScript << "gsave" << endl;
    postScript << _rotationDegree << " rotate" << endl;
    postScript <<  _shapeScale._x << " " << _shapeScale._y << " scale circle" << endl;
    postScript << "grestore" << endl;
    postScript << "showpage" << endl;
}
void Circle::draw() {Shape::draw();}

//Polygon

//Rectangle
class Rectangle : public Shape
{
public:
    Rectangle(double x, double y, double h, double w);
    void draw(ofstream & postScript);
    void draw();
private:
    double height;
    double width;
};
Rectangle::Rectangle(double x, double y, double h, double w) : height(h), width(w)
{
    setPoint(x, y);
    setBox(h, w);
}
void Rectangle::draw(ofstream & postScript)
{
    postScript << "newpath" << endl;
    postScript << "moveto " << _currentPoint._x-(width/2) << " " << _currentPoint._y-(height/2) << endl;
    postScript << "lineto " << _currentPoint._x+(width/2) << " " << _currentPoint._y-(height/2) << endl;
    postScript << "lineto " << _currentPoint._x+(width/2) << " " << _currentPoint._y+(height/2) << endl;
    postScript << "lineto " << _currentPoint._x-(width/2) << " " << _currentPoint._y+(height/2) << endl;
    postScript << "closepath" << endl;
    postScript << "stroke" << endl;
    postScript << "showpage" << endl;
}
void Rectangle::draw() {Shape::draw();}

//Spacer
class Spacer : public Shape
{
public:
    Spacer(double x, double y, double h, double w);
    void draw(ofstream & postScript);
    void draw();
private:
};
Spacer::Spacer(double x, double y, double h, double w)
{
    setPoint(x, y);
    setBox(h, w);
}
void Spacer::draw(ofstream & postScript) {}
void Spacer::draw() {Shape::draw();}

//Rotation

//Scale

#endif
