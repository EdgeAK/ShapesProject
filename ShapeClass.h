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
#include <fstream>
using std::ofstream;
#include <string>
using std::string;
#include <memory>
using std::shared_ptr;
#include <vector>
using std::vector;
#include <cmath>

struct Current_Point
{
    double x;
    double y;
};
struct Bounding_Box
{
    double height;
    double width;
};

//Base Class
//Shape
class Shape
{
public:
    virtual ~Shape();

    virtual void draw(ofstream & postScript) = 0;
    void draw();
    void draw(double x, double y);
    void draw(const string & filename);
    void draw(const string & filename, double x, double y);

    void set_point(double x, double y);
    void set_box(double height, double width);
    Bounding_Box get_box();
    Current_Point get_point();
protected:
    Current_Point point;
    Bounding_Box box;
};
Shape::~Shape() {}
void Shape::draw()
{
    string filename;
    cout << "Enter a file name to draw to: ";
    getline(cin, filename);
    ofstream postScript;
    postScript.open(filename.c_str());
    postScript << "%!" << endl;
    draw(postScript);
    postScript << endl << "showpage" << endl;
    postScript.close();
}
void Shape::draw(double x, double y)
{
    string filename;
    cout << "Enter a file name to draw to: ";
    getline(cin, filename);
    ofstream postScript;
    postScript.open(filename.c_str());
    set_point(x, y);
    postScript << "%!" << endl;
    draw(postScript);
    postScript << endl << "showpage" << endl;
    postScript.close();
}
void Shape::draw(const string & filename)
{
    ofstream postScript;
    postScript.open(filename.c_str());
    postScript << "%!" << endl;
    draw(postScript);
    postScript << endl << "showpage" << endl;
    postScript.close();
}
void Shape::draw(const string & filename, double x, double y)
{
    ofstream postScript;
    postScript.open(filename.c_str());
    set_point(x, y);
    postScript << "%!" << endl;
    draw(postScript);
    postScript << endl << "showpage" << endl;
    postScript.close();
}
void Shape::set_point(double x, double y)
{
    point.x = x;
    point.y = y;
}
void Shape::set_box(double height, double width)
{
    box.height = height;
    box.width = width;
}
Bounding_Box Shape::get_box() {return box;}
Current_Point Shape::get_point() {return point;}

//Derived Classes
//Circle
class Circle : public Shape
{
public:
    Circle(double r);
    Circle(double x, double y, double r);
    void draw(ofstream & postScript);
private:
    double radius;
};
Circle::Circle(double r) : radius(r)
{
    set_point(0, 0);
    set_box(radius*2, radius*2);
}
Circle::Circle(double x, double y, double r) : radius(r)
{
    set_point(x, y);
    set_box(radius*2, radius*2);
}
void Circle::draw(ofstream & postScript)
{
    postScript << "newpath" << endl;
    postScript << point.x << " " << point.y << " " << radius << " 0 360 arc" << endl;
    postScript << "closepath" << endl;
    postScript << "stroke" << endl;
}

//Polygon
class Polygon : public Shape
{
public:
    Polygon(unsigned sides, double length);
    void draw(ofstream & postScript);
private:
    unsigned sides;
    double length;
    double interior_angle;
};
Polygon::Polygon(unsigned sides, double length) : sides(sides), length(length)
{
    set_point(0, 0);
    interior_angle=360.0/sides;
    if (sides%2!=0) set_box(length*(1+cos(M_PI/sides)) / (2*sin(M_PI/sides)), (length*sin (M_PI*(-1)/2*sides)) / (sin(M_PI/sides)));
	else if (sides%4==0) set_box(length*(cos(M_PI/sides)) / (sin(M_PI/sides)), (length*cos(M_PI/sides)) / (sin(M_PI/sides)));
	else if (sides%4!=0 && sides%2==0) set_box(length*(cos(M_PI/sides)) / (sin(M_PI/sides)), length/sin(M_PI/sides));
}
void Polygon::draw(ofstream & postScript)
{
    double half_angle = interior_angle / 2;
    double radius = length / (2*sin(M_PI/sides));
    double x[sides];
    double y[sides];
    for(auto n=0; n<sides; ++n) {
        x[n] = radius * cos(2*M_PI*n/sides) + point.x;
        y[n] = radius * sin(2*M_PI*n/sides) + point.y;
    }
    postScript << "newpath" << endl;
    postScript << x[0] << " " << y[0] << " moveto" << endl;
    for(auto n=1; n<sides; ++n) {
        postScript << x[n] << " " << y[n] << " lineto" << endl;
    }
    postScript << "closepath" << endl;
    postScript << "stroke" << endl;
}

class Triangle : public Polygon
{
public:
    Triangle(double length) : Polygon(3, length) {}
};

class Square : public Polygon
{
public:
    Square(double length) : Polygon(4, length) {}
};

//Rectangle
class Rectangle : public Shape
{
public:
    Rectangle(double h, double w);
    Rectangle(double x, double y, double h, double w);
    void draw(ofstream & postScript);
};
Rectangle::Rectangle(double h, double w)
{
    set_point(0, 0);
    set_box(h, w);
}
Rectangle::Rectangle(double x, double y, double h, double w)
{
    set_point(x, y);
    set_box(h, w);
}
void Rectangle::draw(ofstream & postScript)
{
    postScript << "newpath" << endl;
    postScript << point.x-(box.width/2) << " " << point.y-(box.height/2) << " moveto" << endl;
    postScript << point.x+(box.width/2) << " " << point.y-(box.height/2) << " lineto" << endl;
    postScript << point.x+(box.width/2) << " " << point.y+(box.height/2) << " lineto" << endl;
    postScript << point.x-(box.width/2) << " " << point.y+(box.height/2) << " lineto" << endl;
    postScript << "closepath" << endl;
    postScript << "stroke" << endl;
}

//Spacer
class Spacer : public Shape
{
public:
    Spacer(double h, double w);
    Spacer(double x, double y, double h, double w);
    void draw(ofstream & postScript);
};
Spacer::Spacer(double h, double w)
{
    set_point(0, 0);
    set_box(h, w);
}
Spacer::Spacer(double x, double y, double h, double w)
{
    set_point(x, y);
    set_box(h, w);
}
void Spacer::draw(ofstream & postScript) {}

//Rotation
class Rotation : public Shape
{
public:
    typedef double RotationAngle;
    Rotation(shared_ptr<Shape> shape, RotationAngle rotation_angle);
    void draw(ofstream & postScript);
private:
    shared_ptr<Shape> shape_ptr;
    RotationAngle rotation_angle;
};
Rotation::Rotation(shared_ptr<Shape> shape, RotationAngle rotation_angle) : rotation_angle(rotation_angle)
{
    shape_ptr = shape;
    box = shape_ptr->get_box();
    if(rotation_angle==90 || rotation_angle==270) {
        auto temp = box.height;
        box.height = box.width;
        box.width = temp;
    }
}
void Rotation::draw(ofstream & postScript)
{
    postScript << "gsave" << endl;
    shape_ptr->set_point(point.x, point.y);
    postScript << rotation_angle << " rotate" << endl;
    if(rotation_angle==90) shape_ptr.get()->set_point((shape_ptr.get()->get_point().y), -(shape_ptr.get()->get_point().x));
    if(rotation_angle==180) shape_ptr.get()->set_point(-(shape_ptr.get()->get_point().x), -(shape_ptr.get()->get_point().y));
    if(rotation_angle==270) shape_ptr.get()->set_point(-(shape_ptr.get()->get_point().y), (shape_ptr.get()->get_point().x));
    shape_ptr->draw(postScript);
    postScript << "grestore" << endl;
}

//Scale
class Scaled : public Shape
{
public:
    Scaled(shared_ptr<Shape> shape, double fx, double fy);
    void draw(ofstream & postScript);
private:
    shared_ptr<Shape> shape_ptr;
    double scale_x;
    double scale_y;
};
Scaled::Scaled(shared_ptr<Shape> shape, double fx, double fy) : scale_x(fx), scale_y(fy)
{
    shape_ptr = shape;
    box = shape_ptr->get_box();
}
void Scaled::draw(ofstream & postScript)
{
    postScript << "gsave" << endl;
    shape_ptr->set_point(point.x, point.y);
    postScript << scale_x << " " << scale_y << " scale" << endl;
	shape_ptr.get()->set_point((shape_ptr.get()->get_point().x)/scale_x, (shape_ptr.get()->get_point().y)/scale_y);
    shape_ptr->draw(postScript);
    postScript << "grestore" << endl;
}

//Layered
class Layered : public Shape
{
public:
    Layered(vector<shared_ptr<Shape>> & input);
    void draw(ofstream & postScript);
private:
    vector<shared_ptr<Shape>> shape_vec;
};
Layered::Layered(vector<shared_ptr<Shape>> & input)
{
    box.height=0;
    box.width=0;
    shape_vec.resize(input.size());
	for(unsigned index=0; index<input.size(); ++index) {
		shape_vec[index] = input[index];
        if(shape_vec[index].get()->get_box().width>box.width) box.width=shape_vec[index].get()->get_box().width;
        if(shape_vec[index].get()->get_box().height>box.height) box.height=shape_vec[index].get()->get_box().height;
	}
}
void Layered::draw(ofstream & postScript)
{
    for(unsigned index=0; index<shape_vec.size(); ++index) {
        postScript << "gsave" << endl;
        shape_vec[index].get()->set_point(point.x, point.y);
        shape_vec[index].get()->draw(postScript);
        postScript << "grestore" << endl;
    }
}

//Vertical
class Vertical : public Shape
{
public:
    Vertical(vector<shared_ptr<Shape>> & input);
    void draw(ofstream & postScript);
private:
    vector<shared_ptr<Shape>> shape_vec;
};
Vertical::Vertical(vector<shared_ptr<Shape>> & input)
{
    box.height=0;
    box.width=0;
    shape_vec.resize(input.size());
    for(unsigned index=0; index<input.size(); ++index) {
		shape_vec[index] = input[index];
        box.height+=shape_vec[index].get()->get_box().height;
        if(shape_vec[index].get()->get_box().width>box.width) box.width=shape_vec[index].get()->get_box().width;
	}
}
void Vertical::draw(ofstream & postScript)
{
    postScript << "gsave" << endl;
    double height = shape_vec[0].get()->get_box().height/2 - box.height/2 + point.y;
    for(unsigned index=0; index<shape_vec.size(); ++index) {
        if(index) height+=shape_vec[index-1].get()->get_box().height/2+shape_vec[index].get()->get_box().height/2;
        shape_vec[index].get()->set_point(point.x, height);
        postScript << "gsave" << endl;
        shape_vec[index].get()->draw(postScript);
        postScript << "grestore" << endl;
    }
    postScript << "grestore" << endl;
}

//Horizontal
class Horizontal : public Shape
{
public:
    Horizontal(vector<shared_ptr<Shape>> & input);
    void draw(ofstream & postScript);
private:
    vector<shared_ptr<Shape>> shape_vec;
};
Horizontal::Horizontal(vector<shared_ptr<Shape>> & input)
{
    box.height=0;
    box.width=0;
    shape_vec.resize(input.size());
    for(unsigned index=0; index<input.size(); ++index) {
		shape_vec[index] = input[index];
        box.width+=shape_vec[index].get()->get_box().width;
        if(shape_vec[index].get()->get_box().height>box.height) box.height=shape_vec[index].get()->get_box().height;
	}
}
void Horizontal::draw(ofstream & postScript)
{
    postScript << "gsave" << endl;
    double length = shape_vec[0].get()->get_box().width/2 - box.width/2 + point.x;
    for(unsigned index=0; index<shape_vec.size(); ++index) {
        if(index) length+=shape_vec[index-1].get()->get_box().width/2+shape_vec[index].get()->get_box().width/2;
        shape_vec[index].get()->set_point(length, point.y);
        postScript << "gsave" << endl;
        shape_vec[index].get()->draw(postScript);
        postScript << "grestore" << endl;
    }
    postScript << "grestore" << endl;
}

#endif
