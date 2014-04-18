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
#define _USE_MATH_DEFINES //needed for M_PI 
#include<math.h>
using std::sin;
using std::cos;


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
    //virtual ~Shape() = default;
    virtual void draw() = 0;
    virtual ofstream createFile(string fileName);
    void setPoint(double x, double y);
    void setBox(double height, double width);
    void scaled(double x, double y);
    void rotate(double rotDegree);
    
    //    Point getCurPoint();
    //    Scale getScale();
    //    double getRotation();
    
protected:
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

void Shape::scaled(double x, double y)
{
    _shapeScale._x = x;
    _shapeScale._y = y;
}

void Shape::rotate(double r)
{
    _rotationDegree = r;
}

//Point Shape::getCurPoint()
//{
//    return _currentPoint;
//}
//Scale Shape::getScale()
//{
//    return _shapeScale;
//}
//
//double Shape::getRotation()
//{
//    return _rotationDegree;
//}


class Rectangle : public Shape
{
public:
    Rectangle(double length, double width, Point point);
    void draw(string fileName);
private:
    double length;
    double width;
};

Rectangle::Rectangle(double l, double w, Point point)
{
    _currentPoint = point;
    length = l;
    width = w;
}

void Rectangle::draw(string fileName)
{
    ofstream postScriptOut = createFile(fileName + ".ps");
    
    postScriptOut << "/rectangle{" << endl;
    postScriptOut << "0 0 moveto" << endl;
    postScriptOut << width << " " << 0 << " rlineto" << endl;
    postScriptOut << 0 << " " << length << " rlineto" << endl;
    postScriptOut << -1*width << " " << 0 << " rlineto" << endl;
    postScriptOut << "closepath" << endl;
    postScriptOut << "stroke}def" << endl;
    
    postScriptOut << _currentPoint._x << " " << _currentPoint._y << " translate " << endl;
    postScriptOut << "gsave" << endl;
    postScriptOut << _rotationDegree << " rotate" << endl;
    postScriptOut <<  _shapeScale._x << " " << _shapeScale._y << " scale rectangle" << endl;
    postScriptOut << "grestore" << endl;
    postScriptOut << "showpage" << endl;
    
}

class Circle : public Shape
{
public:
    Circle(double x, double y, double radius);
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
    postScriptOut << "newpath 0 0 " << _radius << " 0 360 arc closepath stroke} def" << endl;
    
    postScriptOut << _currentPoint._x << " " << _currentPoint._y << " translate " << endl;
    postScriptOut << "gsave" << endl;
    postScriptOut << _rotationDegree << " rotate" << endl;
    postScriptOut <<  _shapeScale._x << " " << _shapeScale._y << " scale circle" << endl;
    postScriptOut << "grestore" << endl;
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
	determineBox(edgeLength, numberOfEdges);
}

void Polygon::determineBox(double edgeLength, int numberOfEdges)
{

	if (numberOfEdges % 2 != 0)
		setBox(edgeLength * ( 1+ cos ( M_PI / numberOfEdges )) / ( 2*sin ( M_PI / numberOfEdges )), (edgeLength * sin ( M_PI * (-1) / 2 * numberOfEdges)) / (sin(M_PI/numberOfEdges)));

	if (numberOfEdges % 4 == 0)
		setBox( (edgeLength* ( cos( M_PI / numberOfEdges))) / ( sin( M_PI / numberOfEdges)), (edgeLength * cos( M_PI / numberOfEdges)) / ( sin( M_PI / numberOfEdges)));

	if (numberOfEdges % 4 != 0 && numberOfEdges % 2 == 0)
		setBox( (edgeLength*( cos( M_PI / numberOfEdges))) / ( sin(M_PI / numberOfEdges)), edgeLength / sin( M_PI / numberOfEdges));
}

void Polygon::draw()
{

}

#endif
