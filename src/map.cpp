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
#include "map.h"
#include "maze-generator.h"
#include "window.h"
#include "bounding-box.h"

ALLEGRO_BITMAP *Map::tileset = 0;

Map::Map() {
    MazeGenerator mazeGen;
    mazeGen.generateMaze();
    for (int y = 0; y < MAX_MAP_HEIGHT; y++) {
        for (int x = 0; x < MAX_MAP_WIDTH; x++) {
            tiles[y][x] = mazeGen.maze[y][x];
        }
    }

    Window *window = Window::getInstance();
    window->windowPos = Vector2D(window->getWidth() / 2,
                                 window->getHeight() / 2
                                );
								
	int r = rand() % 128;
	int g = rand() % 128;
	int b = rand() % 128;
	color = al_map_rgb(96 + r, 96 + g, 96 + b);
}

Map::~Map() {

}

void Map::render() {
    if (!tileset) {
        tileset = al_load_bitmap("resources/graphics/tileset.png");
    }


    Window *window = Window::getInstance();
    BoundingBox bounds = window->getBounds();
    int sx = (bounds.getMinX() / TILESET_WIDTH) - 1;
    int sy = (bounds.getMinY() / TILESET_HEIGHT) - 1;
    int ex = (bounds.getMaxX() / TILESET_WIDTH) + 1;
    int ey = (bounds.getMaxY() / TILESET_HEIGHT) + 1;

    for (int y = sy; y <= ey; y++) {
        for (int x = sx; x <= ex; x++) {
            if (x < 0 || x >= MAX_MAP_WIDTH || y < 0 || y >= MAX_MAP_HEIGHT) {
                continue;
            }
            Vector2D tilePos = window->getWindowPos(Vector2D(x * TILESET_WIDTH, y * TILESET_HEIGHT));
            al_draw_tinted_scaled_bitmap(tileset, color,
                                         0, tiles[y][x] * TILESET_HEIGHT, TILESET_WIDTH, TILESET_HEIGHT,
                                         tilePos.getX(), tilePos.getY(), TILESET_WIDTH, TILESET_HEIGHT, 0);
        }
    }
}

void Map::positionInside(Entity *entity)
{
	int interval = 63 - 0 + 1;
	int ppx = (0 + int(interval * (double)rand() /((double)RAND_MAX + 1.0)) );
	int ppy = (0 + int(interval * (double)rand() /((double)RAND_MAX + 1.0)) );

	while(tiles[ppy][ppx] != FLOOR) {
		ppx = (0 + int(interval * (double)rand() /((double)RAND_MAX + 1.0)) );
		ppy = (0 + int(interval * (double)rand() /((double)RAND_MAX + 1.0)) );
	}

	entity->position = Vector2D(ppx * TILESET_WIDTH + TILESET_WIDTH / 2,
	                            ppy * TILESET_HEIGHT + TILESET_HEIGHT / 2);
}
