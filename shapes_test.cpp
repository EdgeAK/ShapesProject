#include <memory>
using std::unique_ptr;
#include <utility>
using std::move;
#include "ShapeClass.h"

void rectangle_test()
{
    string shape_name = "rectangle.ps";
    unique_ptr<Shape> shape = make_unique<Rectangle>(50, 40);
    unique_ptr<Shape> rotation = make_unique<Rotation>(move(shape), 90);
                      shape = make_unique<Rectangle>(50, 40);
    unique_ptr<Shape> scaled = make_unique<Scaled>(move(shape), .5, 2);

    shape = make_unique<Rectangle>(50, 40);
    shape->draw(shape_name, 300, 300);
    auto dump_ptr = move(shape);

    shape = make_unique<Rectangle>(50, 40);
    rotation = make_unique<Rotation>(move(shape), 90);
    rotation->draw("rotated_"+shape_name, 300, 300);
    shape = make_unique<Rectangle>(50, 40);
    scaled = make_unique<Scaled>(move(shape), .5, 2);
    scaled->draw("scaled_"+shape_name, 300, 300);

    shape = make_unique<Rectangle>(50, 40);
    scaled = make_unique<Scaled>(move(shape), .5, 2);
    rotation = make_unique<Rotation>(move(scaled), 90);
    rotation->draw("scaled_rotated_"+shape_name, 300, 300);

    shape = make_unique<Rectangle>(50, 40);
    rotation = make_unique<Rotation>(move(shape), 90);
    scaled = make_unique<Scaled>(move(rotation), .5, 2);
    scaled->draw("rotated_scaled_"+shape_name, 300, 300);
}
void circle_test()
{
    string shape_name = "circle.ps";
    unique_ptr<Shape> shape = make_unique<Circle>(50);
    unique_ptr<Shape> rotation = make_unique<Rotation>(move(shape), 90);
                      shape = make_unique<Circle>(50);
    unique_ptr<Shape> scaled = make_unique<Scaled>(move(shape), .5, 2);

    shape = make_unique<Circle>(50);
    shape->draw(shape_name, 300, 300);

    shape = make_unique<Circle>(50);
    rotation = make_unique<Rotation>(move(shape), 90);
    rotation->draw("rotated_"+shape_name, 300, 300);

    shape = make_unique<Circle>(50);
    scaled = make_unique<Scaled>(move(shape), .5, 2);
    scaled->draw("scaled_"+shape_name, 300, 300);

    shape = make_unique<Circle>(50);
    scaled = make_unique<Scaled>(move(shape), .5, 2);
    rotation = make_unique<Rotation>(move(scaled), 90);
    rotation->draw("scaled_rotated_"+shape_name, 300, 300);

    shape = make_unique<Circle>(50);
    rotation = make_unique<Rotation>(move(shape), 90);
    scaled = make_unique<Scaled>(move(rotation), .5, 2);
    scaled->draw("rotated_scaled_"+shape_name, 300, 300);
}
void spacer_test()
{
    string shape_name = "spacer.ps";
    unique_ptr<Shape> shape = make_unique<Spacer>(50, 40);
    unique_ptr<Shape> rotation = make_unique<Rotation>(move(shape), 90);
                      shape = make_unique<Spacer>(50, 40);
    unique_ptr<Shape> scaled = make_unique<Scaled>(move(shape), .5, 2);

    shape = make_unique<Spacer>(50, 40);
    shape->draw(shape_name, 300, 300);

    shape = make_unique<Spacer>(50, 40);
    rotation = make_unique<Rotation>(move(shape), 90);
    rotation->draw("rotated_"+shape_name, 300, 300);

    shape = make_unique<Spacer>(50, 40);
    scaled = make_unique<Scaled>(move(shape), .5, 2);
    scaled->draw("scaled_"+shape_name, 300, 300);

    shape = make_unique<Spacer>(50, 40);
    scaled = make_unique<Scaled>(move(shape), .5, 2);
    rotation = make_unique<Rotation>(move(scaled), 90);
    rotation->draw("scaled_rotated_"+shape_name, 300, 300);

    shape = make_unique<Spacer>(50, 40);
    rotation = make_unique<Rotation>(move(shape), 90);
    scaled = make_unique<Scaled>(move(rotation), .5, 2);
    scaled->draw("rotated_scaled_"+shape_name, 300, 300);
}
void multiple_test()
{
	string shape_name = "multiple.ps";
	unique_ptr<Shape> rectangle = make_unique<Rectangle>(50, 40);
    unique_ptr<Shape> spacer = make_unique<Spacer>(50, 40);
    unique_ptr<Shape> circle = make_unique<Circle>(50);

    rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
    unique_ptr<Shape> layered = make_unique<Layered>(move(rectangle), move(spacer), move(circle));

	rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
    unique_ptr<Shape> vertical = make_unique<Vertical>(move(rectangle), move(spacer), move(circle));

	rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
	unique_ptr<Shape> horizontal = make_unique<Horizontal>(move(rectangle), move(spacer), move(circle));
}

int main()
{
    rectangle_test();
    circle_test();
    spacer_test();
	multiple_test();
    return 0;
}
