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
#include "entity.h"
#include "bounding-box.h"
#include "map.h"

BoundingBox Entity::hasMapCollision(Map *map) {
    BoundingBox result = BoundingBox(0, 0, 0, 0);
    BoundingBox box = BoundingBox(position.getX() - width / 2,
                                  position.getY() - height / 2,
                                  width, height);

    int tileX = position.getX() / TILESET_WIDTH;
    int tileY = position.getY() / TILESET_HEIGHT;

    // colisão com o mapa
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int x = tileX + dx;
            int y = tileY + dy;
            if (map->tiles[y][x] == WALL) {
                BoundingBox tileBox = BoundingBox(x * TILESET_WIDTH, y * TILESET_HEIGHT,
                                                  TILESET_WIDTH, TILESET_HEIGHT);
                if (box.intersects(tileBox)) {
                    result = tileBox;
                    return result;
                }
            }
        }
    }

    return result;
}

Entity *Entity::hasEntityCollision(std::vector<Entity *> entities) {
    Entity *result = 0;
    BoundingBox box = BoundingBox(position.getX() - width / 2,
                                  position.getY() - height / 2,
                                  width, height);

    // colisão com entidades
    if (!result) {
        for (unsigned int i = 0; i < entities.size(); i++) {
            BoundingBox entityBox = BoundingBox(entities[i]->position.getX() - entities[i]->width / 2,
                                                entities[i]->position.getY() - entities[i]->height / 2,
                                                entities[i]->width, entities[i]->height);
            if (box.intersects(entityBox)) {
                result = entities[i];
                break;
            }
        }
    }
    
    return result;
}

bool Entity::isDead() {
    return false;
}

ParticleSystem *Entity::getDeathParticles() {
	return 0;
}
