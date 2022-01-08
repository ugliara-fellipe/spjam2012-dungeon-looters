/*
Dungeon Looters - SPJAM 2012
Copyright (C) 2012  Fellipe Augusto Ugliara, Jeferson Rodrigues da Silva

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "vector2d.h"
#include <cmath>

Vector2D::Vector2D() {
    this->x = 0.0;
    this->y = 0.0;
}

Vector2D::Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2D::Vector2D(Vector2D src, Vector2D dest) {
    this->x = dest.getX() - src.getX();
    this->y = dest.getY() - src.getY();
}

Vector2D::~Vector2D() {

}

void Vector2D::setX(double x) {
    this->x = x;
}

double Vector2D::getX() {
    return x;
}

void Vector2D::setY(double y) {
    this->y = y;
}

double Vector2D::getY() {
    return y;
}

Vector2D Vector2D::add(Vector2D vector) {
	Vector2D vectorNovo;
    vectorNovo.setX(this->x + vector.getX());
    vectorNovo.setY(this->y + vector.getY());

    return vectorNovo;
}

Vector2D Vector2D::mult(double scalar) {
    Vector2D vector;
    vector.setX(this->x * scalar);
    vector.setY(this->y * scalar);

    return vector;
}

double Vector2D::distanceTo(Vector2D vector) {
    double sqrdDeltaX = (this->x - vector.getX()) * (this->x - vector.getX());
    double sqrdDeltaY = (this->y - vector.getY()) * (this->y - vector.getY());
    double distance = sqrt(sqrdDeltaX + sqrdDeltaY);

    return distance;
}

Vector2D Vector2D::normalize() {
    Vector2D normalizedVector;
    double length = distanceTo(Vector2D());
    if (length > 1.0e-5) {
        normalizedVector = Vector2D(this->x / length, this->y / length);
    }
    return normalizedVector;
}

bool Vector2D::equals(Vector2D &vector) {
    bool result = false;

    if (std::fabs(getX() - vector.getX()) < 1.0e-5 &&
            std::fabs(getY() - vector.getY()) < 1.0e-5) {
        result = true;
    }

    return result;
}
