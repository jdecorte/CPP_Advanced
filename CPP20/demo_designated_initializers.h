#pragma once
#include <iostream>
using namespace std;

struct Point {
    int x;
    int y;
    int z;
};

void demo_designated_initializers()
{
    // Using designated initializers to initialize a Point struct
    Point p1 = {.x = 1, .y = 2, .z = 3};
    Point p2 = {.y = 5, .z = 10}; // x will be default-initialized to 0, out-of-order initialization is non-standard

    std::cout << "Point p1: (" << p1.x << ", " << p1.y << ", " << p1.z << ")\n";
    std::cout << "Point p2: (" << p2.x << ", " << p2.y << ", " << p2.z << ")\n";
}