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
    double _x;
    double _y;
};

class Shape
{
public:

    virtual void draw() = 0;
    virtual ofstream createFile(string fileName);
    void setPoint(double x, double y);
    void setBox(double height, double width);
    Point getCurPoint();
    void scaled(double x, double y);
    Scale getScale();
    double getRotation();
    
private:
    Point _currentPoint;
    Box _boundingBox;
    Scale _shapeScale;
    double _rotationDegree;
    
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

Point Shape::getCurPoint()
{
    return _currentPoint;
}


void Shape::scaled(double x, double y)
{
    _shapeScale._x = x;
    _shapeScale._y = y;
}

Scale Shape::getScale()
{
    return _shapeScale;
}

double Shape::getRotation()
{
    return _rotationDegree;
}

class Circle : public Shape
{
public:

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

void Circle::draw()
{
    string fileName;
    cout << "Name of file: " << endl;
    cin >> fileName;
    ofstream postScriptOut = createFile(fileName + ".ps");
    
    postScriptOut << "/circle{" << endl;
    postScriptOut << getCurPoint()._x << " " << getCurPoint()._y << " " << _radius << " 0 360 arc closepath}" << endl;
    postScriptOut << "def" << endl;
    postScriptOut << getScale()._x << " " << getScale()._y << " scale circle" << endl;
    postScriptOut << "stroke" << endl;
    postScriptOut << "showpage" << endl;
    postScriptOut.close();
}

class Polygon : public Shape
{
public:

    Polygon(double x, double y, double edgeLength, int numberOfEdges);
    void setEdgeLength(double length);
	void setNumberOfEdges(int numberOfEdges);
	void determineBox(double edgeLength, int numberOfEdges);
    void draw();

private:
    double _edgeLength;
	int _numberOfEdges;
};

Polygon::Polygon(double x, double y, double edgeLength, int numberOfEdges)
{
    setPoint(x, y);
    _edgeLength = edgeLength;
	_numberOfEdges = numberOfEdges;
}

void determineBox(double edgeLength, int numberOfEdges)
{


}

void Polygon::draw()
{

}

#endif
