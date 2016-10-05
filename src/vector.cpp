#include "vector.hpp"

vector::vector() {
    this->x = 0.f;
    this->y = 0.f;
}

vector::vector(float x, float y) {
    this->x = x;
    this->y = y;
}

void vector::set_angle(float angle) {
    float angle_radians = angle * DEGS_TO_RADS;

    x *= std::cos(angle_radians);
    y *= std::sin(angle_radians);
}

float vector::angle() const {
    float result = atan2(y, x);

    if (result < 0) {
        result += 360;
    }

    if (result > 0) {
        result -= 360;
    }

    return result;
}

float vector::length() const {
    return x * x + y * y;
}

bool vector::is_zero() {
    return x == 0 && y == 0;
}

void vector::zero() {
    x = 0;
    y = 0;
}

vector vector::operator+(const vector& v) {
    return vector(this->x + v.x, this->y + v.y);
}

vector vector::operator-(const vector& v) {
    return vector(this->x - v.x, this->y - v.y);
}

vector vector::operator*(const vector& v) {
    return vector(this->x * v.x, this->y * v.y);
}

vector vector::operator/(const vector& v) {
    return vector(this->x / v.x, this->y / v.y);
}

void vector::operator+=(const vector& v) {
    this->x += v.x;
    this->y += v.y;
}

void vector::operator-=(const vector& v) {
    this->x -= v.x;
    this->y -= v.y;
}

void vector::operator*=(const vector& v) {
    this->x *= v.x;
    this->y *= v.y;
}

void vector::operator/=(const vector& v) {
    this->x /= v.x;
    this->y /= v.y;
}

vector vector::operator+(float f) {
    return vector(this->x + f, this->y + f);
}

vector vector::operator-(float f) {
    return vector(this->x - f, this->y - f);
}

vector vector::operator* (float f) {
    return vector(this->x * f, this->y * f);
}

vector vector::operator/(float f) {
    return vector(this->x / f, this->y / f);
}

void vector::operator+=(float f) {
    this->x += f;
    this->y += f;
}

void vector::operator-=(float f) {
    this->x -= f;
    this->y -= f;
}

void vector::operator*=(float f) {
    this->x *= f;
    this->y *= f;
}

void vector::operator/=(float f) {
    this->x /= f;
    this->y /= f;
}

bool vector::operator==(const vector& v) {
    return this->x == v.x && this->y == v.y;
}

bool vector::operator!=(const vector& v) {
    return this->x != v.x || this->y != v.y;
}
