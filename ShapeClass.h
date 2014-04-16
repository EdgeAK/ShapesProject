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
    double x;
    double y;
};
struct Box
{
    double height;
    double width;
};
struct Scale
{
    double x = 1;
    double y = 1;
};

//Base Class
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
    _currentPoint.x = x;
    _currentPoint.y = y;
}
void Shape::setBox(double height, double width)
{
    _boundingBox.height = height;
    _boundingBox.width = width;
}
void Shape::scaled(double x, double y)
{
    _shapeScale.x = x;
    _shapeScale.y = y;
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
    postScript << _currentPoint.x << " " << _currentPoint.y << " moveto" << endl;
    draw(postScript);
    postScript.close();
}

//Derived Classes
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
    
    postScript << _currentPoint.x << " " << _currentPoint.y << " translate " << endl;
    postScript << "gsave" << endl;
    postScript << _rotationDegree << " rotate" << endl;
    postScript <<  _shapeScale.x << " " << _shapeScale.y << " scale circle" << endl;
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
    postScript << "moveto " << _currentPoint.x-(width/2) << " " << _currentPoint.y-(height/2) << endl;
    postScript << "lineto " << _currentPoint.x+(width/2) << " " << _currentPoint.y-(height/2) << endl;
    postScript << "lineto " << _currentPoint.x+(width/2) << " " << _currentPoint.y+(height/2) << endl;
    postScript << "lineto " << _currentPoint.x-(width/2) << " " << _currentPoint.y+(height/2) << endl;
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

//Decorators
//Rotation
class Rotation : public Shape
{
public:
    typedef double rotation_angle;
    Rotation(Shape & shape, rotation_angle angle);
    void draw(ofstream & postScript);
    void draw();
private:
    Shape * shape;
    rotation_angle angle;
};
Rotation::Rotation(Shape & s, rotation_angle a) : shape(&s), angle(a)
{
    if(a==90 || a==270) {
        auto temp = _boundingBox.height;
        _boundingBox.height = _boundingBox.width;
        _boundingBox.width = temp;
    }
}
void Rotation::draw(ofstream & postScript)
{
    postScript << angle << " rotate" << endl;
    shape->draw(postScript);
}
void Rotation::draw(){Shape::draw();}

//Scale

#endif
