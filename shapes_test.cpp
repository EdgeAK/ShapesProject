#include <memory>
using std::make_shared;
using std::shared_ptr;
#include "ShapeClass.h"


void rectangle_test()
{
    shared_ptr<Shape> shape = make_shared<Rectangle>(50, 40);
    string shape_name = "rectangle.ps";

    shared_ptr<Shape> rotation = make_shared<Rotation>(shape, 90);
    shared_ptr<Shape> scaled = make_shared<Scaled>(shape, 2, 3);

    shape = make_shared<Rectangle>(50, 40);
    shape->draw(shape_name, 100, 100);

    shape = make_shared<Rectangle>(50, 40);
    rotation = make_shared<Rotation>(shape, 90);
    rotation->draw("rotated_"+shape_name, 100, 100);

    shape = make_shared<Rectangle>(50, 40);
    scaled = make_shared<Scaled>(shape, 2, 3);
    scaled->draw("scaled_"+shape_name, 300, 300);

    shape = make_shared<Rectangle>(50, 40);
    scaled = make_shared<Scaled>(shape, 2, 3);
    rotation = make_shared<Rotation>(scaled, 90);
    rotation->draw("scaled_rotated_"+shape_name, 300, 300);

    shape = make_shared<Rectangle>(50, 40);
    rotation = make_shared<Rotation>(shape, 90);
    scaled = make_shared<Scaled>(rotation, 2, 3);
    scaled->draw("rotated_scaled_"+shape_name, 300, 300);
}
void circle_test()
{
    shared_ptr<Shape> shape = make_shared<Circle>(50);
    string shape_name = "circle.ps";

    shared_ptr<Shape> rotation = make_shared<Rotation>(shape, 90);
    shared_ptr<Shape> scaled = make_shared<Scaled>(shape, 2, 3);

    shape = make_shared<Circle>(50);
    shape->draw(shape_name, 100, 100);

    shape = make_shared<Circle>(50);
    rotation = make_shared<Rotation>(shape, 90);
    rotation->draw("rotated_"+shape_name, 100, 100);

    shape = make_shared<Circle>(50);
    scaled = make_shared<Scaled>(shape, 2, 3);
    scaled->draw("scaled_"+shape_name, 300, 300);

    shape = make_shared<Circle>(50);
    scaled = make_shared<Scaled>(shape, 2, 3);
    rotation = make_shared<Rotation>(scaled, 90);
    rotation->draw("scaled_rotated_"+shape_name, 300, 300);

    shape = make_shared<Circle>(50);
    rotation = make_shared<Rotation>(shape, 90);
    scaled = make_shared<Scaled>(rotation, 2, 3);
    scaled->draw("rotated_scaled_"+shape_name, 300, 300);
}
void spacer_test()
{
    shared_ptr<Shape> shape = make_shared<Spacer>(50, 40);
    string shape_name = "spacer.ps";

    shared_ptr<Shape> rotation = make_shared<Rotation>(shape, 90);
    shared_ptr<Shape> scaled = make_shared<Scaled>(shape, 2, 3);

    shape = make_shared<Spacer>(50, 40);
    shape->draw(shape_name, 100, 100);

    shape = make_shared<Spacer>(50, 40);
    rotation = make_shared<Rotation>(shape, 90);
    rotation->draw("rotated_"+shape_name, 100, 100);

    shape = make_shared<Spacer>(50, 40);
    scaled = make_shared<Scaled>(shape, 2, 3);
    scaled->draw("scaled_"+shape_name, 300, 300);

    shape = make_shared<Spacer>(50, 40);
    scaled = make_shared<Scaled>(shape, 2, 3);
    rotation = make_shared<Rotation>(scaled, 90);
    rotation->draw("scaled_rotated_"+shape_name, 300, 300);

    shape = make_shared<Spacer>(50, 40);
    rotation = make_shared<Rotation>(shape, 90);
    scaled = make_shared<Scaled>(rotation, 2, 3);
    scaled->draw("rotated_scaled_"+shape_name, 300, 300);
}

int main()
{
    rectangle_test();
    circle_test();
    spacer_test();
    return 0;
}
