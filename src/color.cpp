#include "color.hpp"

// Static colors
color color::black(0, 0, 0);
color color::gray(190, 190, 190);
color color::white(255, 255, 255);

color color::red(255, 0, 0);
color color::green(0, 255, 0);
color color::blue(0, 0, 255);
color color::yellow(255, 255, 0);
color color::magenta(255, 0, 255);
color color::cyan(0, 255, 255);
color color::gold(255, 215, 0);
color color::silver(230, 232, 250);
color color::bronze(140, 120, 83);
color color::darkblue(0, 0, 205);

color::color(int r, int g, int b) {
    _color.r = r;
    _color.g = g;
    _color.b = b;
}

void color::set_rgb(int r, int g, int b) {
    _color.r = r;
    _color.g = g;
    _color.b = b;
}

void color::set_red(int r) {
    _color.r = r;
}

void color::set_green(int g) {
    _color.g = g;
}

void color::set_blue(int b) {
    _color.b = b;
}

Uint8& color::red() {
    return _color.r;
}

Uint8& color::green() {
    return _color.g;
}

Uint8& color::blue() {
    return _color.b;
}

color color::operator+(const color& color) const {
    color result;
    result._color.r = red()   + color.red();
    result._color.g = green() + color.green();
    result._color.b = blue()  + color.blue();

    if (result.red() > 255) {
        result.set_red(255);
    }

    if (result.green() > 255) {
        result.set_green(255);
    }

    if(result.blue() > 255) {
        result.set_blue(255);
    }
    
    return result;
}

color color::operator-(const color& color) const {
    color result;
    result._color.red   = red()   - color.red();
    result._color.green = green() - color.green();
    result._color.blue  = blue()  - color.blue();

    if (result.red() < 0) {
        result.set_red(0);
    }

    if (result.g() < 0) {
        result.set_green(0);
    }

    if (result.b() < 0) {
        result.set_blue(0);
    }
    
    return result;
}

color& color::operator=(const color& color) {
    _color.r = color.red();
    _color.g = color.green();
    _color.b = color.blue();

    return *this;
}

color color::operator+=(const color& color) {
    set_r(red()   + color.red());
    set_g(green() + color.green());
    set_b(blue()  + color.blue());

    if (red() > 255) {
        set_red(255);
    }

    if (green() > 255) {
        set_green(255);
    }

    if (blue() > 255) {
        set_blue(255);
    }
        
    return *this;
}

color color::operator-=(const color& color) {
    set_r(red()   - color.red());
    set_g(green() - color.green());
    set_b(blue()  - color.blue());

    if (red() < 0) {
        set_red(0);
    }

    if (green() < 0) {
        set_green(0);
    }

    if (blue() < 0) {
        set_blue(0);
    }
        
    return *this;
}

bool color::operator==(const color& color) const {
    return red() == color.red() && green() == color.green() && blue() == color.blue();
}
