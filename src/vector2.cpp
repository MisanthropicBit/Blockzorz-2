#include "vector2.hpp"
#include <cmath>

vector2::vector2() : x(0.f), y(0.f) {
}

vector2::vector2(float x, float y) : x(x), y(y) {
}

void vector2::set_angle(float angle) {
    float angle_radians = angle * DEGS_TO_RADS;

    x *= std::cos(angle_radians);
    y *= std::sin(angle_radians);
}

float vector2::angle() const {
    float result = std::atan2(y, x);

    if (result < 0.f) {
        result += 360.f;
    }

    if (result > 0.f) {
        result -= 360.f;
    }

    return result;
}

float vector2::length() const {
    return x * x + y * y;
}

bool vector2::is_zero() const {
    return x == 0 && y == 0;
}

void vector2::zero() {
    x = 0;
    y = 0;
}

vector2 vector2::operator+(const vector2& v) {
    return vector2(x + v.x, y + v.y);
}

vector2 vector2::operator-(const vector2& v) {
    return vector2(x - v.x, y - v.y);
}

vector2 vector2::operator*(const vector2& v) {
    return vector2(x * v.x, y * v.y);
}

vector2 vector2::operator/(const vector2& v) {
    return vector2(x / v.x, y / v.y);
}

vector2& vector2::operator+=(const vector2& v) {
    x += v.x;
    y += v.y;

    return *this;
}

vector2& vector2::operator-=(const vector2& v) {
    x -= v.x;
    y -= v.y;

    return *this;
}

vector2& vector2::operator*=(const vector2& v) {
    x *= v.x;
    y *= v.y;

    return *this;
}

vector2& vector2::operator/=(const vector2& v) {
    x /= v.x;
    y /= v.y;

    return *this;
}

vector2 vector2::operator+(float f) {
    return vector2(x + f, y + f);
}

vector2 vector2::operator-(float f) {
    return vector2(x - f, y - f);
}

vector2 vector2::operator*(float f) {
    return vector2(x * f, y * f);
}

vector2 vector2::operator/(float f) {
    // Ignore division by zero
    return vector2(x / f, y / f);
}

vector2& vector2::operator+=(float f) {
    x += f;
    y += f;
}

vector2& vector2::operator-=(float f) {
    x -= f;
    y -= f;
}

vector2& vector2::operator*=(float f) {
    x *= f;
    y *= f;
}

vector2& vector2::operator/=(float f) {
    x /= f;
    y /= f;
}

bool vector2::operator==(const vector2& v) {
    return x == v.x && y == v.y;
}

bool vector2::operator!=(const vector2& v) {
    return !(*this == v)
}
