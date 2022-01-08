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
#ifndef MAP_H
#define MAP_H

#include "vector2d.h"
#include "player.h"
#include <allegro5/allegro.h>

const int MAX_MAP_WIDTH = 64;
const int MAX_MAP_HEIGHT = 64;

const int TILESET_WIDTH = 64;
const int TILESET_HEIGHT = 64;

enum TileType { WALL, FLOOR };

class Map {
public:
    static ALLEGRO_BITMAP *tileset;
    int tiles[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];
	ALLEGRO_COLOR color;

    Map();
    ~Map();

    void render();
    void positionInside(Entity *entity);
};

#endif // MAP_H
