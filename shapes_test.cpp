#include <memory>
using std::shared_ptr;
using std::make_shared;
#include <utility>
using std::move;
#include "ShapeClass.h"

void shape_test()
{
    shared_ptr<Shape> rectangle;
    shared_ptr<Shape> circle;
    shared_ptr<Shape> spacer;
    shared_ptr<Shape> rotation;
    shared_ptr<Shape> scaled;
    shared_ptr<Shape> layered;
    shared_ptr<Shape> vertical;
    shared_ptr<Shape> horizontal;
    vector<shared_ptr<Shape>> pass(3);

    rectangle = make_shared<Rectangle>(50, 40);
    rectangle->draw("01_rectangle.ps", 300, 300);
    rotation = make_shared<Rotation>(rectangle, 90);
    rotation->draw("02_rotated_rectangle.ps", 300, 300);
    scaled = make_shared<Scaled>(rectangle, .5, 2);
    scaled->draw("03_scaled_rectangle.ps", 300, 300);
    scaled = make_shared<Scaled>(rectangle, .5, 2);
    rotation = make_shared<Rotation>(scaled, 90);
    rotation->draw("04_scaled_rotated_rectangle.ps", 300, 300);
    rotation = make_shared<Rotation>(rectangle, 90);
    scaled = make_shared<Scaled>(rotation, .5, 2);
    scaled->draw("05_rotated_scaled_rectangle.ps", 300, 300);

    circle = make_shared<Circle>(50);
    rotation = make_shared<Rotation>(circle, 90);
    scaled = make_shared<Scaled>(circle, .5, 2);
    circle->draw("06_circle.ps", 300, 300);
    rotation = make_shared<Rotation>(circle, 90);
    rotation->draw("07_rotated_circle.ps", 300, 300);
    scaled = make_shared<Scaled>(circle, .5, 2);
    scaled->draw("08_scaled_circle.ps", 300, 300);
    scaled = make_shared<Scaled>(circle, .5, 2);
    rotation = make_shared<Rotation>(scaled, 90);
    rotation->draw("09_scaled_rotated_circle.ps", 300, 300);
    rotation = make_shared<Rotation>(circle, 90);
    scaled = make_shared<Scaled>(rotation, .5, 2);
    scaled->draw("10_rotated_scaled_circle.ps", 300, 300);

    spacer = make_shared<Spacer>(50, 40);
    spacer->draw("11_spacer.ps", 300, 300);

    pass[0]=(rectangle);
    pass[1]=(spacer);
    pass[2]=(circle);
    layered = make_shared<Layered>(pass);
    vertical = make_shared<Vertical>(pass);
    horizontal = make_shared<Horizontal>(pass);
	layered->draw("12_layered.ps", 300, 300);
    vertical->draw("13_vertical.ps", 300, 300);
	horizontal->draw("14_horizontal.ps", 300, 300);

    pass[0]=(layered);
    pass[1]=(vertical);
    pass[2]=(horizontal);
    layered = make_shared<Layered>(pass);
    vertical = make_shared<Vertical>(pass);
    horizontal = make_shared<Horizontal>(pass);
    horizontal->draw("15_horizontal_of_multiple.ps", 300, 300);
    vertical->draw("16_vertical_of_multiple.ps", 300, 300);
    layered->draw("17_layered_of_multiple.ps", 300, 300);

    rotation = make_shared<Rotation>(layered, 90);
    pass[0]=(rotation);
    scaled = make_shared<Scaled>(horizontal, 2, 1);
    pass[1]=(scaled);
    scaled = make_shared<Rotation>(vertical, 90);
    rotation = make_shared<Scaled>(scaled, .5, .5);
    pass[2]=(rotation);
    shared_ptr<Shape> multiple4 = make_shared<Vertical>(pass);
    multiple4->draw("18_vertical_of_decorated_multiple.ps", 300, 300);
}

int main()
{
    shape_test();
    return 0;
}
