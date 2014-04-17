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
using std::unique_ptr;
#include <utility>
using std::move;

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
    virtual ~Shape() = default;

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
};
Polygon::Polygon(unsigned sides, double length) : sides(sides), length(length)
{
    //TODO calculate to determine box and point
    set_point(0, 0);
    set_box(0, 0);
}
void Polygon::draw(ofstream & postScript)
{
    //TODO calculate to impliment drawing
}

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

//Decorator
class Decorator : public Shape
{
public:
    virtual ~Decorator() throw(); //TODO ask Hartman why this is necessary
    using Shape::draw;
    virtual void decorate(ofstream & postScript) =0;
    virtual void draw(ofstream & postScript);
protected:
    unique_ptr<Shape> shape_ptr;
};
Decorator::~Decorator() throw() {} //TODO ask Hartman why this is necessary
void Decorator::draw(ofstream & postScript)
{
    postScript << "gsave" << endl;
    shape_ptr->set_point(point.x, point.y);
    decorate(postScript);
    shape_ptr->draw(postScript);
    postScript << "grestore" << endl;
}

//Decorators
//Rotation
class Rotation : public Decorator
{
public:
    typedef double RotationAngle;
    Rotation(unique_ptr<Shape> shape, RotationAngle rotation_angle);
    void decorate(ofstream & postScript);
private:
    RotationAngle rotation_angle;
};
Rotation::Rotation(unique_ptr<Shape> shape, RotationAngle rotation_angle) : rotation_angle(rotation_angle)
{
    shape_ptr = move(shape);
    box = shape_ptr->get_box();
    if(rotation_angle==90 || rotation_angle==270) {
        auto temp = box.height;
        box.height = box.width;
        box.width = temp;
    }
}
void Rotation::decorate(ofstream & postScript)
{
    postScript << rotation_angle << " rotate" << endl;
    if(rotation_angle==90) shape_ptr.get()->set_point((shape_ptr.get()->get_point().y), -(shape_ptr.get()->get_point().x));
    if(rotation_angle==180) shape_ptr.get()->set_point(-(shape_ptr.get()->get_point().x), -(shape_ptr.get()->get_point().y));
    if(rotation_angle==270) shape_ptr.get()->set_point(-(shape_ptr.get()->get_point().y), (shape_ptr.get()->get_point().x));
}

//Scale
class Scaled : public Decorator
{
public:
    Scaled(unique_ptr<Shape> shape, double fx, double fy);
    void decorate(ofstream & postScript);
private:
    double scale_x;
    double scale_y;
};
Scaled::Scaled(unique_ptr<Shape> shape, double fx, double fy) : scale_x(fx), scale_y(fy)
{
    shape_ptr = move(shape);
    box = shape_ptr->get_box();
}
void Scaled::decorate(ofstream & postScript)
{
    postScript << scale_x << " " << scale_y << " scale" << endl;
	shape_ptr.get()->set_point((shape_ptr.get()->get_point().x)/scale_x, (shape_ptr.get()->get_point().y)/scale_y);
}

//Layered
class Layered : public Decorator
{
public:
    Layered(/*TODO multiple shapes passed in here*/);
    void draw(ofstream & postScript);
private:
    unsigned shapes;
};
Layered::Layered(/*TODO multiple shapes passed in here*/)
{
    //TODO Make shape_ptr into an indexable array of Shapes, using the arguments as an initialiver list..
    box.height=0;
    box.width=0;
    for(unsigned i=0; i<shapes; ++i) {
        box.width+=shape_ptr.get()[i].get_box().width;
        box.height+=shape_ptr.get()[i].get_box().height;
    }
    point.x=box.width/2;
    point.y=box.height/2;
}
void Layered::draw(ofstream & postScript)
{
    for(unsigned i=0; i<shapes; ++i) {
        postScript << "gsave" << endl;
        shape_ptr.get()[i].draw(postScript);
        postScript << "grestore" << endl;
    }
}

//Vertical
class Vertical : public Decorator
{
public:
    Vertical(/*TODO multiple shapes passed in here*/);
    void draw(ofstream & postScript);
private:
    unsigned shapes;
};
Vertical::Vertical(/*TODO multiple shapes passed in here*/)
{
    //TODO Make shape_ptr into an indexable array of Shapes, using the arguments as an initialiver list..
    box.height=0;
    box.width=0;
    for(unsigned i=0; i<shapes; ++i) {
        box.height+=shape_ptr.get()[i].get_box().height;
        if(shape_ptr.get()[i].get_box().width>box.width) box.width=shape_ptr.get()[i].get_box().width;
    }
    point.x=box.width/2;
    point.y=box.height/2;
}
void Vertical::draw(ofstream & postScript)
{
    postScript << "gsave" << endl;
    postScript << -box.width/2 << " " << 0 << " translate" << endl;
    postScript << shape_ptr.get()[0].get_box().width << " " << 0 << " translate" << endl;
    for(unsigned i=0; i<shapes; ++i) {
        if(i) {
            postScript << 0 << " " << shape_ptr.get()[i-1].get_box().height/2 << " translate" << endl;
            postScript << 0 << " " << shape_ptr.get()[i].get_box().height/2 << " translate" << endl;
        }
        postScript << "gsave" << endl;
        shape_ptr.get()[i].draw(postScript);
        postScript << "grestore" << endl;
    }
    postScript << "grestore" << endl;
}

//Horizontal
class Horizontal : public Decorator
{
public:
    Horizontal(/*TODO multiple shapes passed in here*/);
    void draw(ofstream & postScript);
private:
    unsigned shapes;
};
Horizontal::Horizontal(/*TODO multiple shapes passed in here*/)
{
    //TODO Make shape_ptr into an indexable array of Shapes, using the arguments as an initialiver list..
    box.height=0;
    box.width=0;
    for(unsigned i=0; i<shapes; ++i) {
        box.width+=shape_ptr.get()[i].get_box().width;
        if(shape_ptr.get()[i].get_box().height>box.height) box.height=shape_ptr.get()[i].get_box().height;
    }
    point.x=box.width/2;
    point.y=box.height/2;
}
void Horizontal::draw(ofstream & postScript)
{
    postScript << "gsave" << endl;
    postScript << 0 << " " << -box.height/2 << " translate" << endl;
    postScript << 0 << " " << shape_ptr.get()[0].get_box().height << " translate" << endl;
    for(unsigned i=0; i<shapes; ++i) {
        if(i) {
            postScript << shape_ptr.get()[i-1].get_box().height/2 << " " << 0 << " translate" << endl;
            postScript << shape_ptr.get()[i].get_box().height/2 << " " << 0 << " translate" << endl;
        }
        postScript << "gsave" << endl;
        shape_ptr.get()[i].draw(postScript);
        postScript << "grestore" << endl;
    }
    postScript << "grestore" << endl;
}

#endif
