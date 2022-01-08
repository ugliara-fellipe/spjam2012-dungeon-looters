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
#include "bounding-box.h"
#include <algorithm>

BoundingBox::BoundingBox() {
    
}

BoundingBox::BoundingBox(Vector2D a, Vector2D b) {
    upperLeft.setX(std::min(a.getX(), b.getX()));
    upperLeft.setY(std::min(a.getY(), b.getY()));
    lowerRight.setX(std::max(a.getX(), b.getX()));
    lowerRight.setY(std::max(a.getY(), b.getY()));
}

BoundingBox::BoundingBox(int x, int y, int width, int height) {
    upperLeft.setX(x);
    upperLeft.setY(y);
    lowerRight.setX(x + width);
    lowerRight.setY(y + height);
}

BoundingBox::~BoundingBox() {
    
}

double BoundingBox::getMinX() {
    return upperLeft.getX();
}

double BoundingBox::getMaxX() {
    return lowerRight.getX();
}

double BoundingBox::getMinY() {
    return upperLeft.getY();
}

double BoundingBox::getMaxY() {
    return lowerRight.getY();
}
    
bool BoundingBox::intersects(BoundingBox box) {
    bool intersects = true;
    
    if (getMaxX() <= box.getMinX() || 
        getMinX() >= box.getMaxX() || 
        getMaxY() <= box.getMinY() || 
        getMinY() >= box.getMaxY()) {
        intersects = false;
    }
        
    return intersects;
}
