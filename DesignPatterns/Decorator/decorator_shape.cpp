#include <iostream>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

struct Shape
{
    virtual string str() const = 0;
};

struct Circle : Shape
{
    float radius;
    explicit Circle(const float radius) : radius{radius} {}
    void resize(float factor) { radius *= factor; }
    string str() const override
    {
        ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square : Shape
{
    float side;
    explicit Square(const float s) : side{s} {}
    void resize(float factor) { side *= factor; }
    string str() const override
    {
        ostringstream oss;
        oss << "A square of side " << side;
        return oss.str();
    }
}; 

struct ColoredShape : public Shape
{
    Shape& shape;
    string color;
    ColoredShape(Shape& shape, const string& color) : shape{shape}, color{color} {}
    string str() const override
    {
        ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
    void make_dark() 
    {
        if (!(color.substr(0,4) == "dark") )
            color.insert(0, "dark");
    }
};

struct TransparentShape : Shape
{
    Shape& shape;
    short transparency;
    TransparentShape(Shape& shape, const short transparency) : shape{shape}, transparency{transparency} {}
    string str() const override
    {
        ostringstream oss;
        oss << shape.str() << " has "
        << static_cast<float>(transparency) / 255.f*100.f
        << "% transparency";
        return oss.str();
    }
};

int main()
{
    Circle circle{5};
    cout << circle.str() << endl;

    ColoredShape red_circle{circle, "red"};
    cout << red_circle.str() << endl;

    red_circle.make_dark();
    cout << red_circle.str() << endl;
    
    TransparentShape half_transparent_red_circle{red_circle, 128};
    cout << half_transparent_red_circle.str() << endl;

    Square square{10};
    cout << square.str() << endl;

    ColoredShape red_square{square, "red"};
    cout << red_square.str() << endl;

    red_square.make_dark();
    cout << red_square.str() << endl;

    return 0;
}
