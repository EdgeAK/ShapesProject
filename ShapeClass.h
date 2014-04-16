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
#include<fstream>
using std::ofstream;
#include<string>
using std::string;

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
    void set_point(double x, double y);
    void set_box(double height, double width);
    Bounding_Box get_box();
    Current_Point get_point();
protected:
    Current_Point point;
    Bounding_Box box;
};
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
void Shape::draw()
{
    string filename;
    cout << "Enter a file name to draw to: ";
    getline(cin, filename);
    ofstream postScript;
    postScript.open(filename.c_str());
    postScript << point.x << " " << point.y << " moveto" << endl;
    draw(postScript);
    postScript << endl << "showpage" << endl;
    postScript.close();
}

//Derived Classes
//Circle
class Circle : public Shape
{
public:
    Circle(double x, double y, double radius);
    void draw(ofstream & postScript);
private:
    double _radius;
};
Circle::Circle(double x, double y, double radius) : _radius(radius)
{
    set_point(x, y);
    set_box(radius*2, radius*2);
}
void Circle::draw(ofstream & postScript)
{
    postScript << "newpath 0 0 " << _radius << " 0 360 arc closepath stroke" << endl;
}

//Polygon
//TODO

//Rectangle
class Rectangle : public Shape
{
public:
    Rectangle(double x, double y, double h, double w);
    void draw(ofstream & postScript);
private:
    double height;
    double width;
};
Rectangle::Rectangle(double x, double y, double h, double w) : height(h), width(w)
{
    set_point(x, y);
    set_box(h, w);
}
void Rectangle::draw(ofstream & postScript)
{
    postScript << "newpath" << endl;
    postScript << "moveto " << point.x-(width/2) << " " << point.y-(height/2) << endl;
    postScript << "lineto " << point.x+(width/2) << " " << point.y-(height/2) << endl;
    postScript << "lineto " << point.x+(width/2) << " " << point.y+(height/2) << endl;
    postScript << "lineto " << point.x-(width/2) << " " << point.y+(height/2) << endl;
    postScript << "closepath" << endl;
    postScript << "stroke" << endl;
}

//Spacer
class Spacer : public Shape
{
public:
    Spacer(double x, double y, double h, double w);
};
Spacer::Spacer(double x, double y, double h, double w)
{
    set_point(x, y);
    set_box(h, w);
}

//Decorator
class Decorator : public Shape
{
public:
    using Shape::draw;
    virtual void decorate(ofstream & postScript) =0;
    virtual void draw(ofstream & postScript);
protected:
    Shape * shape_ptr;
};
void Decorator::draw(ofstream & postScript)
{
    postScript << "gsave" << endl;
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
    Rotation(Shape & shape, RotationAngle rotation_angle);
    void decorate(ofstream & postScript);
private:
    RotationAngle rotation_angle;
};
Rotation::Rotation(Shape & shape, RotationAngle rotation_angle) : rotation_angle(rotation_angle)
{
    shape_ptr = &shape;
    if(rotation_angle==90 || rotation_angle==270) {
        auto temp = box.height;
        box.height = box.width;
        box.width = temp;
    }
}
void Rotation::decorate(ofstream & postScript)
{
    postScript << rotation_angle << " rotate" << endl;
}

//Scale
class Scaled : public Decorator
{
    Scaled(Shape & shape, double fx, double fy);
    void decorate(ofstream & postScript);
private:
    double scale_x;
    double scale_y;
};
Scaled::Scaled(Shape & shape, double fx, double fy) : scale_x(fx), scale_y(fy)
{
    shape_ptr = &shape;
    box = shape.get_box();
}
void Scaled::decorate(ofstream & postScript)
{
    postScript << scale_x << " " << scale_y << " scale" << endl;
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
    //Make shape_ptr into an indexable array of Shapes, using the arguments as an initialiver list..
}
void Layered::draw(ofstream & postScript)
{
    for(auto i=0; i<shapes; ++i) {
        postScript << "gsave" << endl;
        shape_ptr[i].draw(postScript);
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
    //Make shape_ptr into an indexable array of Shapes, using the arguments as an initialiver list..
    box.height=0;
    box.width=0;
    for(auto i=0; i<shapes; ++i) {
        box.height+=shape_ptr[i].get_box().height;
        if(shape_ptr[i].get_box().width>box.width) box.width=shape_ptr[i].get_box().width;
    }
}
void Vertical::draw(ofstream & postScript)
{
    postScript << "gsave" << endl;
    for(auto i=0; i<shapes; ++i) {
        if(i) {
            postScript << 0 << " " << shape_ptr[i-1].get_box().height/2 << " translate" << endl;
            postScript << 0 << " " << shape_ptr[i].get_box().height/2 << " translate" << endl;
        }
        postScript << "gsave" << endl;
        shape_ptr[i].draw(postScript);
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
    //Make shape_ptr into an indexable array of Shapes, using the arguments as an initialiver list..
    box.height=0;
    box.width=0;
    for(auto i=0; i<shapes; ++i) {
        box.width+=shape_ptr[i].get_box().width;
        if(shape_ptr[i].get_box().height>box.height) box.height=shape_ptr[i].get_box().height;
    }
}
void Horizontal::draw(ofstream & postScript)
{
    postScript << "gsave" << endl;
    for(auto i=0; i<shapes; ++i) {
        if(i) {
            postScript << shape_ptr[i-1].get_box().height/2 << " " << 0 << " translate" << endl;
            postScript << shape_ptr[i].get_box().height/2 << " " << 0 << " translate" << endl;
        }
        postScript << "gsave" << endl;
        shape_ptr[i].draw(postScript);
        postScript << "grestore" << endl;
    }
    postScript << "grestore" << endl;
}

#endif
