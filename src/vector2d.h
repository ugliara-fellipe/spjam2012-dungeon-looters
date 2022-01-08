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
#ifndef _VECTOR2D_h
#define _VECTOR2D_h

class Vector2D {
private:
    double x, y;

public:
    Vector2D();
    Vector2D(double x, double y);
    Vector2D(Vector2D src, Vector2D dest);
    ~Vector2D();

    void setX(double x);
    double getX();
    void setY(double y);
    double getY();
    Vector2D add(Vector2D vector);
    Vector2D mult(double scalar);
    double distanceTo(Vector2D vector);
    Vector2D normalize();
    bool equals(Vector2D &vector);
};

#endif
