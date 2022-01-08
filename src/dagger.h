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
#ifndef DAGGER_H
#define DAGGER_H

#include "entity.h"
#include "player.h"

class Dagger : public Entity {
public:
    Dagger(Player *player, Orientation orientation, int damage);
    ~Dagger();

    Player *player;
    Orientation orientation;
    double attackTime;
    int damage;
    double range;

    Vector2D vel;
    double speed;
    bool dead;

    void collisionWith(Entity *entity);
	BoundingBox hasMapCollision(Map *map);	
    void update(double dt, Map *map, std::vector<Entity *> entities);
    void render(double edt);
    bool isDead();
};

#endif // DAGGER_H
