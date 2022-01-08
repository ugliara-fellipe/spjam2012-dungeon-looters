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
#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include "map.h"
#include <vector>
#include <allegro5/allegro_audio.h>

#define EMPTY			-1
#define CHEST           0
#define GOLD	     	1
#define AMULET			2
#define BOOTS_OF_SPEED	3
#define HELMET			4
#define POTION_LIFE 	5
#define POTION_POISON 	6
#define POTION_HASTE 	7
#define POTION_SLOW 	8
#define POTION_SWAP 	9


class Player;

class Item : public Entity {
public:
    static ALLEGRO_BITMAP *items;
	static ALLEGRO_SAMPLE *sound;	

    Item(int type);
    ~Item();
	
	int typeItem;
	bool remove;
	Entity *target;
	
	virtual void action( Map *map, std::vector<Entity *> entities, Player **player, Player* eu) = 0;
	void update(double dt, Map *map, std::vector<Entity *> entities);
	void collisionWith(Entity *entity);
    bool isDead();
	void renderScreen(int x, int y);
	virtual ParticleSystem *getDeathParticles();	
	virtual ParticleSystem *getUseParticles();
	virtual void playUseSound();
};

#endif // ITEM_H
