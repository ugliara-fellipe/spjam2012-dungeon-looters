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
#ifndef MONSTER_H
#define MONSTER_H

#include "entity.h"
#include "map.h"
#include "player.h"
#include "particle-system.h"
#include <vector>

#define STOP 0
#define MOVE 1
#define FOLLOW_PLAYER 2
#define ATTACK 3
#define CHARGE 4

#define SPIDER 0
#define BAT 1
#define MINOTAUR 2
#define CONSTRUCT 3
#define WITCH 4
#define ZOMBIE 5
#define MEDUSA 6
#define GOBLIN 7
#define GHOST 8
			
const int dxMoster[] = {-1,-1,-1,0,1,1,1,0};
const int dyMoster[] = {1,0,-1,-1,-1,0,1,1};

class Monster : public Entity
{
public:
    static ALLEGRO_BITMAP *weaknessImg;
	
	Monster();
	~Monster();

	int life;
	int power;
	int maxSpeed;
	int speed;
	int gold;
	Player* targetPlayer;
	
	int stepDx, stepDy;
	
	double distanceAlert;
	double distanceAttack;
	
	double slowDuration;
	
	double inercia;
    double immunity;
	
	PlayerType weakness;
	
	int state;
	
	void collisionWith(Entity *entity);
	void update(double dt, Map *map, std::vector<Entity *> entities);
	virtual void artificialIntelligence(double dt, Map *map, std::vector<Entity *> entities);
    bool isDead();
	void renderWeakness();
	virtual void playSound() = 0;
};

#endif // MONSTER_H
