#include <memory>
using std::unique_ptr;
#include <utility>
using std::move;
#include "ShapeClass.h"

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

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

int main()
{
    rectangle_test();
    circle_test();
    spacer_test();
    return 0;
}
