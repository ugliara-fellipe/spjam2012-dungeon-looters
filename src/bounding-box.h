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
#ifndef _BOUNDING_BOX_H
#define _BOUNDING_BOX_H

#include "vector2d.h"

class BoundingBox {
    private:
        Vector2D upperLeft;
        Vector2D lowerRight;
    
    public:
        BoundingBox();
        BoundingBox(Vector2D a, Vector2D b);
        BoundingBox(int x, int y, int width, int height);
        ~BoundingBox();
        
        double getMinX();
        double getMaxX();
        double getMinY();
        double getMaxY();
        bool intersects(BoundingBox box);
};

#endif
