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
    shape->draw("01_"+shape_name, 300, 300);
    auto dump_ptr = move(shape);

    shape = make_unique<Rectangle>(50, 40);
    rotation = make_unique<Rotation>(move(shape), 90);
    rotation->draw("02_rotated_"+shape_name, 300, 300);
    shape = make_unique<Rectangle>(50, 40);
    scaled = make_unique<Scaled>(move(shape), .5, 2);
    scaled->draw("03_scaled_"+shape_name, 300, 300);

    shape = make_unique<Rectangle>(50, 40);
    scaled = make_unique<Scaled>(move(shape), .5, 2);
    rotation = make_unique<Rotation>(move(scaled), 90);
    rotation->draw("04_scaled_rotated_"+shape_name, 300, 300);

    shape = make_unique<Rectangle>(50, 40);
    rotation = make_unique<Rotation>(move(shape), 90);
    scaled = make_unique<Scaled>(move(rotation), .5, 2);
    scaled->draw("05_rotated_scaled_"+shape_name, 300, 300);
}
void circle_test()
{
    string shape_name = "circle.ps";
    unique_ptr<Shape> shape = make_unique<Circle>(50);
    unique_ptr<Shape> rotation = make_unique<Rotation>(move(shape), 90);
                      shape = make_unique<Circle>(50);
    unique_ptr<Shape> scaled = make_unique<Scaled>(move(shape), .5, 2);

    shape = make_unique<Circle>(50);
    shape->draw("06_"+shape_name, 300, 300);

    shape = make_unique<Circle>(50);
    rotation = make_unique<Rotation>(move(shape), 90);
    rotation->draw("07_rotated_"+shape_name, 300, 300);

    shape = make_unique<Circle>(50);
    scaled = make_unique<Scaled>(move(shape), .5, 2);
    scaled->draw("08_scaled_"+shape_name, 300, 300);

    shape = make_unique<Circle>(50);
    scaled = make_unique<Scaled>(move(shape), .5, 2);
    rotation = make_unique<Rotation>(move(scaled), 90);
    rotation->draw("09_scaled_rotated_"+shape_name, 300, 300);

    shape = make_unique<Circle>(50);
    rotation = make_unique<Rotation>(move(shape), 90);
    scaled = make_unique<Scaled>(move(rotation), .5, 2);
    scaled->draw("10_rotated_scaled_"+shape_name, 300, 300);
}
void spacer_test()
{
    string shape_name = "spacer.ps";
    unique_ptr<Shape> shape = make_unique<Spacer>(50, 40);
    shape->draw("11_"+shape_name, 300, 300);
}
void multiple_test()
{
	unique_ptr<Shape> rectangle;
    unique_ptr<Shape> spacer;
    unique_ptr<Shape> circle;
    vector<unique_ptr<Shape>> pass(3);
    
    rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
    pass[0]=(move(rectangle));
    pass[1]=(move(spacer));
    pass[2]=(move(circle));
    unique_ptr<Shape> layered = make_unique<Layered>(pass);
	layered->draw("12_layered.ps", 300, 300);

	rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
    pass[0]=(move(rectangle));
    pass[1]=(move(spacer));
    pass[2]=(move(circle));
    unique_ptr<Shape> vertical = make_unique<Vertical>(pass);
    vertical->draw("13_vertical.ps", 300, 300);

	rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
    pass[0]=(move(rectangle));
    pass[1]=(move(spacer));
    pass[2]=(move(circle));
	unique_ptr<Shape> horizontal = make_unique<Horizontal>(pass);
	horizontal->draw("14_horizontal.ps", 300, 300);

    pass[0]=(move(vertical));
    pass[1]=(move(layered));
    pass[2]=(move(horizontal));
    unique_ptr<Shape> big1 = make_unique<Horizontal>(pass);
    big1->draw("15_horizontal_of_multiple.ps", 300, 300);

    rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
    pass[0]=(move(rectangle));
    pass[1]=(move(spacer));
    pass[2]=(move(circle));
    layered = make_unique<Layered>(pass);

	rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
    pass[0]=(move(rectangle));
    pass[1]=(move(spacer));
    pass[2]=(move(circle));
    vertical = make_unique<Vertical>(pass);

	rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
    pass[0]=(move(rectangle));
    pass[1]=(move(spacer));
    pass[2]=(move(circle));
	horizontal = make_unique<Horizontal>(pass);

    pass[0]=(move(vertical));
    pass[1]=(move(layered));
    pass[2]=(move(horizontal));
    unique_ptr<Shape> big2 = make_unique<Vertical>(pass);
    big2->draw("16_vertical_of_multiple.ps", 300, 300);

    rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
    pass[0]=(move(rectangle));
    pass[1]=(move(spacer));
    pass[2]=(move(circle));
    layered = make_unique<Layered>(pass);

	rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
    pass[0]=(move(rectangle));
    pass[1]=(move(spacer));
    pass[2]=(move(circle));
    vertical = make_unique<Vertical>(pass);

	rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
    pass[0]=(move(rectangle));
    pass[1]=(move(spacer));
    pass[2]=(move(circle));
	horizontal = make_unique<Horizontal>(pass);

    pass[0]=(move(vertical));
    pass[1]=(move(layered));
    pass[2]=(move(horizontal));
    unique_ptr<Shape> big3 = make_unique<Layered>(pass);
    big3->draw("17_layered_of_multiple.ps", 300, 300);

    rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
    pass[0]=(move(rectangle));
    pass[1]=(move(spacer));
    pass[2]=(move(circle));
    layered = make_unique<Layered>(pass);

	rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
    pass[0]=(move(rectangle));
    pass[1]=(move(spacer));
    pass[2]=(move(circle));
    vertical = make_unique<Vertical>(pass);

	rectangle = make_unique<Rectangle>(50, 40);
    spacer = make_unique<Spacer>(50, 40);
    circle = make_unique<Circle>(50);
    pass[0]=(move(rectangle));
    pass[1]=(move(spacer));
    pass[2]=(move(circle));
	horizontal = make_unique<Horizontal>(pass);
    unique_ptr<Shape> rotation = make_unique<Rotation>(move(layered), 90);
    pass[0]=(move(rotation));
    unique_ptr<Shape> scaled = make_unique<Scaled>(move(horizontal), 2, 1);
    pass[1]=(move(scaled));
    scaled = make_unique<Rotation>(move(vertical), 90);
    rotation = make_unique<Scaled>(move(scaled), .5, .5);
    pass[2]=(move(rotation));
    unique_ptr<Shape> big4 = make_unique<Vertical>(pass);
    big4->draw("18_vertical_of_decorated_multiple.ps", 300, 300);
}

int main()
{
    rectangle_test();
    circle_test();
    spacer_test();
	multiple_test();
    return 0;
}
