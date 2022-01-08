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
#ifndef ENTITY_H
#define ENTITY_H

#include "vector2d.h"
#include "bounding-box.h"
#include "particle-system.h"
#include <vector>
#include <map>

class Map;

enum EntityType {
    PLAYER, MONSTER, ITEM, PROJECTILE
};

enum Orientation {
    FACING_UP, FACING_LEFT, FACING_RIGHT, FACING_DOWN
};

class Entity {
    public:
    virtual ~Entity() {};

    int type;
	Orientation orientation;
	int flags;
    Vector2D position;
    Vector2D velocity;
    int width;
    int height;
    virtual BoundingBox hasMapCollision(Map *map);
    Entity *hasEntityCollision(std::vector<Entity *> entities);
    virtual void collisionWith(Entity *entity) = 0; // devolve null se é uma colisão com mapa
    virtual void update(double dt, Map *map, std::vector<Entity *> entities) = 0;
    virtual void render(double edt) = 0;
    virtual bool isDead();
	virtual ParticleSystem *getDeathParticles();
};

#endif // ENTITY_H
