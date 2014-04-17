#include <memory>
using std::make_shared;
using std::shared_ptr;
#include <map>
using std::map;
#include <utility>
using std::make_pair;
using std::pair;
#include "ShapeClass.h"

map<shared_ptr<Shape>, string> shapes {
    make_pair<shared_ptr<Shape>, string>(make_shared<Rectangle>(50,40), "rectangle"),
    make_pair<shared_ptr<Shape>, string>(make_shared<Circle>(50), "circle"),
    make_pair<shared_ptr<Shape>, string>(make_shared<Spacer>(50, 40), "spacer")
};

void shape_test(const pair<shared_ptr<Shape>, string> & test_shape)
{
    shared_ptr<Shape> shape = test_shape.first;
    string shape_name = test_shape.second+".ps";

    shared_ptr<Shape> rotation =  make_shared<Rotation>(shape, 90);
    shared_ptr<Shape> scaled =    make_shared<Scaled>(shape, 2, 3);

    shape = make_shared<Rectangle>(50, 40);
    shape->draw(shape_name, 100, 100);

    shape = make_shared<Rectangle>(50, 40);
    rotation =  make_shared<Rotation>(shape, 90);
    rotation->draw("rotated_"+shape_name, 100, 100);

    shape = make_shared<Rectangle>(50, 40);
    scaled =    make_shared<Scaled>(shape, 2, 3);
    scaled->draw("scaled_"+shape_name, 300, 300);

    shape = make_shared<Rectangle>(50, 40);
    scaled =    make_shared<Scaled>(shape, 2, 3);
    rotation =  make_shared<Rotation>(scaled, 90);
    rotation->draw("scaled_rotated_"+shape_name, 300, 300);

    shape = make_shared<Rectangle>(50, 40);
    rotation =  make_shared<Rotation>(shape, 90);
    scaled =    make_shared<Scaled>(rotation, 2, 3);
    scaled->draw("rotated_scaled_"+shape_name, 300, 300);
}

int main()
{
    for(auto shape : shapes) {
        shape_test(shape);
    }
    return 0;
}
