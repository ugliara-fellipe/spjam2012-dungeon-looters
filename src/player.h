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
#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <allegro5/allegro_audio.h>
#include <string>

class Item;

enum PlayerType {
    ALL = -1, WARRIOR = 0, MAGE = 1, ROGUE = 2
};

enum InputEvent {
    UP_PRESS, UP_RELEASE,  DOWN_PRESS, DOWN_RELEASE,
    LEFT_PRESS, LEFT_RELEASE, RIGHT_PRESS, RIGHT_RELEASE,
    BUT1_PRESS, BUT1_RELEASE, BUT2_PRESS, BUT2_RELEASE,
    BUT3_PRESS, BUT3_RELEASE, BUT4_PRESS, BUT4_RELEASE,
    BUT5_PRESS, BUT5_RELEASE, BUT6_PRESS, BUT6_RELEASE
};

enum {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

class Player : public Entity {
public:
	static ALLEGRO_SAMPLE *missSound;
	static ALLEGRO_SAMPLE *hurtSound;
	static ALLEGRO_SAMPLE *swordSound;
	static ALLEGRO_SAMPLE *daggerSound;
	static ALLEGRO_SAMPLE *fireballSound;

	Player();
	~Player();

	int life;
	double lifeBar;
	int power;
	int speed;
	int maxSlots;
	int slots[6];
	Item *items[6];
	int playerType;
	double immunity;
	bool keyz[4];
	int maxLife;
	int gold;

	Entity *projectile;
	Item *usedItem;

	bool isAttacking;
	double attackCooldown;

	virtual std::string getName() = 0;
	void inputEvent(InputEvent event, Map *map, std::vector<Entity *> entities,  Player **player);
	void update(double dts, Map *map, std::vector<Entity *> entities);
	virtual void prepareAttack() = 0;
	Entity *handleCollisions(std::vector<Entity *> entities);
	BoundingBox hasMapCollision(Map *map);
	void renderWeakness();
	virtual void renderScreen(int x, int y) = 0;
	void playMissSound();
	void playHurtSound();
};

#endif // PLAYER_H
