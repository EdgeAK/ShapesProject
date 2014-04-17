#include <memory>
using std::make_shared;
using std::shared_ptr;
#include "ShapeClass.h"

/*map<Shape, string> shape_names {
    make_pair<Shape*, string>(Shape, "shape"),
    make_pair<Shape*, string>(Rectangle, "rectangle"),
    make_pair<Shape*, string>(Circle, "circle"),
    make_pair<Shape*, string>(Spacer, "spacer")
};*/

/*void test_suite(Shape * test_shape)
{
    test_shape = test_shape(50, 40);
    rectangle.draw("rectangle.ps", 100, 100);

    test_shape = test_shape(50, 40);
    Rotation rotated(test_shape, 90);
    rotated.draw("rotated_rectangle.ps", 100, 100);

    test_shape = test_shape(50, 40);
    Scaled scaled(test_shape, 2, 3);
    scaled.draw("rotated_rectangle.ps", 300, 300);

    test_shape = test_shape(50, 40);
    Scaled scaled(test_shape, 2, 3);
    Rotated rotated(scaled, 90);
    rotated.draw("scaled_rotated_rectangle.ps", 300, 300);

    test_shape = test_shape(50, 40);
    Rotated rotated(test_shape, 2, 3);
    Scaled scaled(scaled, 90);
    scaled.draw("rotated_scaled_"+test_shape+".ps", 300, 300);
}*/

int main()
{
    //objects to be tested
    shared_ptr<Shape> rectangle = make_shared<Rectangle>(50, 40);
    shared_ptr<Shape> circle = make_shared<Circle>(50);
    shared_ptr<Shape> spacer = make_shared<Spacer>(50, 40);
    shared_ptr<Shape> rotation = make_shared<Rotation>(rectangle, 90);
    shared_ptr<Shape> scaled = make_shared<Scaled>(rectangle, 2, 3);

    //Tests
    //Recatngle
    rectangle = make_shared<Rectangle>(50, 40);
    rectangle->draw("rectangle.ps", 100, 100);

    rectangle = make_shared<Rectangle>(50, 40);
    rotation = make_shared<Rotation>(rectangle, 90);
    rotation->draw("rotated_rectangle.ps", 100, 100);

    rectangle = make_shared<Rectangle>(50, 40);
    scaled = make_shared<Scaled>(rectangle, 2, 3);
    scaled->draw("scaled_rectangle.ps", 300, 300);

    rectangle = make_shared<Rectangle>(50, 40);
    scaled = make_shared<Scaled>(rectangle, 2, 3);
    rotation = make_shared<Rotation>(scaled, 90);
    rotation->draw("scaled_rotated_rectangle.ps", 300, 300);

    rectangle = make_shared<Rectangle>(50, 40);
    rotation = make_shared<Rotation>(rectangle, 90);
    scaled = make_shared<Scaled>(rotation, 2, 3);
    scaled->draw("rotated_scaled_rectangle.ps", 300, 300);
/*
    //Circle
    circle = make_shared<Circle>(50);
    circle->draw("circle.ps", 100, 100);

    circle = make_shared<Circle>(50);
    rotation = make_shared<Rotation>(circle, 90);
    rotation->draw("rotated_circle.ps", 100, 100);

    circle = make_shared<Circle>(50);
    scaled = make_shared<Scaled>(circle, 2, 3);
    scaled->draw("scaled_circle.ps", 300, 300);

    circle = make_shared<Circle>(50);
    scaled = make_shared<Scaled>(circle, 2, 3);
    rotation = make_shared<Rotation>(scaled, 90);
    rotation->draw("scaled_rotated_circle.ps", 300, 300);

    circle = make_shared<Circle>(50);
    rotation = make_shared<Rotation>(circle, 2, 3);
    scaled = make_shared<Scaled>(rotation, 90);
    scaled->draw("rotated_scaled_circle.ps", 300, 300);
*/
    return 0;
}
