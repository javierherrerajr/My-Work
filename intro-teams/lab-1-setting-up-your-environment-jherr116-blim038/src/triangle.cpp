#include "../header/triangle.hpp"

void Triangle::set_base(int b) {
    base = b;
}

void Triangle::set_height(int h) {
    height = h;
}

double Triangle::area() {
    return base/2.0 * height; 
}