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
#include "player.h"
#include "map.h"
#include "warrior.h"
#include "item.h"
#include "potion.h"
#include "potion-change.h"
#include "potion-haste.h"
#include "potion-slow.h"
#include "sword.h"
#include "amulet.h"
#include "potion-poison.h"
#include "boots.h"
#include "monster.h"
#include "window.h"

ALLEGRO_SAMPLE *Player::missSound = 0;
ALLEGRO_SAMPLE *Player::hurtSound = 0;
ALLEGRO_SAMPLE *Player::swordSound = 0;
ALLEGRO_SAMPLE *Player::daggerSound = 0;
ALLEGRO_SAMPLE *Player::fireballSound = 0;

Player::Player() {
	width = 48;
	height = 48;
	orientation = FACING_UP;
	attackCooldown = 0.0;
	projectile = 0;
	for (int i = 0; i < 6; i++) {
		slots[i] = EMPTY;
		items[i] = 0;
	}
	maxSlots = 1;
	type = PLAYER;
	immunity = 0.0;
	flags = 0;
	gold = 0;
	usedItem = 0;

	keyz[KEY_UP] = false;
	keyz[KEY_DOWN] = false;
	keyz[KEY_LEFT] = false;
	keyz[KEY_RIGHT] = false;
}

Player::~Player() {

}

void Player::inputEvent(InputEvent event, Map *map, std::vector<Entity *> entities,  Player **player) {
	switch(event) {
	case UP_PRESS:
		if (!keyz[KEY_UP]) {
			keyz[KEY_UP] = true;
			velocity = velocity.add(Vector2D(0, -1));
		}
		break;

	case UP_RELEASE:
		if (keyz[KEY_UP]) {
			keyz[KEY_UP] = false;
			velocity = velocity.add(Vector2D(0, 1));
		}
		break;

	case DOWN_PRESS:
		if (!keyz[KEY_DOWN]) {
			keyz[KEY_DOWN] = true;
			velocity = velocity.add(Vector2D(0, 1));
		}
		break;

	case DOWN_RELEASE:
		if (keyz[KEY_DOWN]) {
			keyz[KEY_DOWN] = false;
			velocity = velocity.add(Vector2D(0, -1));
		}
		break;

	case LEFT_PRESS:
		if (!keyz[KEY_LEFT]) {
			keyz[KEY_LEFT] = true;
			velocity = velocity.add(Vector2D(-1, 0));
		}
		break;

	case LEFT_RELEASE:
		if (keyz[KEY_LEFT]) {
			keyz[KEY_LEFT] = false;
			velocity = velocity.add(Vector2D(1, 0));
		}
		break;

	case RIGHT_PRESS:
		if (!keyz[KEY_RIGHT]) {
			keyz[KEY_RIGHT] = true;
			velocity = velocity.add(Vector2D(1, 0));
		}
		break;

	case RIGHT_RELEASE:
		if (keyz[KEY_RIGHT]) {
			keyz[KEY_RIGHT] = false;
			velocity = velocity.add(Vector2D(-1, 0));
		}
		break;

	case BUT1_PRESS:
		if (attackCooldown <= 0.0) {
			prepareAttack();
		}
		break;

	case BUT1_RELEASE:
		break;

	case BUT2_PRESS:
		if(this->slots[0] != EMPTY) {
			Item *it;
			switch(this->slots[0]) {
			case POTION_LIFE:
				it = new PotionLife();
				break;
			case POTION_POISON:
				it = new PotionPoison();
				break;
			case POTION_SLOW:
				it = new PotionSlow();
				break;
			case POTION_HASTE:
				it = new PotionHaste();
				break;
			case POTION_SWAP:
				it = new PotionChange();
				break;
			case BOOTS_OF_SPEED:
				it = new Boots();
				break;
			case AMULET:
				it = new Amulet();
				break;
			case HELMET:
				it = new Sword();
				break;
			}
			it->action(map,entities,player,this);
			this->slots[0] = EMPTY;
			this->items[0] = 0;
			usedItem = it;
			usedItem->playUseSound();
		}
		break;

	case BUT2_RELEASE:
		break;

	case BUT3_PRESS:
		if(maxSlots > 1) {
			if(this->slots[1] != EMPTY) {
				Item *it;
				switch(this->slots[1]) {
				case POTION_LIFE:
					it = new PotionLife();
					break;
				case POTION_POISON:
					it = new PotionPoison();
					break;
				case POTION_SLOW:
					it = new PotionSlow();
					break;
				case POTION_HASTE:
					it = new PotionHaste();
					break;
				case POTION_SWAP:
					it = new PotionChange();
					break;
				case BOOTS_OF_SPEED:
					it = new Boots();
					break;
				case AMULET:
					it = new Amulet();
					break;
				case HELMET:
					it = new Sword();
					break;
				}
				it->action(map,entities,player,this);
				this->slots[1] = EMPTY;
				this->items[1] = 0;
				usedItem = it;
				usedItem->playUseSound();
			}

		}
		break;

	case BUT3_RELEASE:
		break;

	case BUT4_PRESS:
		break;

	case BUT4_RELEASE:
		break;

	case BUT5_PRESS:
		break;

	case BUT5_RELEASE:
		break;

	case BUT6_PRESS:
		break;

	case BUT6_RELEASE:
		break;
	}

	if (keyz[KEY_UP] && !keyz[KEY_DOWN] && !keyz[KEY_LEFT] && !keyz[KEY_RIGHT]) {
		orientation = FACING_UP;
	}
	if (!keyz[KEY_UP] && keyz[KEY_DOWN] && !keyz[KEY_LEFT] && !keyz[KEY_RIGHT]) {
		orientation = FACING_DOWN;
	}
	if (!keyz[KEY_UP] && !keyz[KEY_DOWN] && keyz[KEY_LEFT] && !keyz[KEY_RIGHT]) {
		orientation = FACING_LEFT;
		flags = 0;
	}
	if (!keyz[KEY_UP] && !keyz[KEY_DOWN] && !keyz[KEY_LEFT] && keyz[KEY_RIGHT]) {
		orientation = FACING_RIGHT;
		flags = ALLEGRO_FLIP_HORIZONTAL;
	}
}

Entity *Player::handleCollisions(std::vector<Entity *> entities) {
	Entity *result = 0;
	BoundingBox box = BoundingBox(position.getX() - width / 2,
	                              position.getY() - height / 2,
	                              width, height);

	// colisão com entidades
	for (unsigned int i = 0; i < entities.size(); i++) {
		BoundingBox entityBox = BoundingBox(entities[i]->position.getX() - entities[i]->width / 2,
		                                    entities[i]->position.getY() - entities[i]->height / 2,
		                                    entities[i]->width, entities[i]->height);
		if (box.intersects(entityBox)) {
			collisionWith(entities[i]);
		}
	}

	return result;
}

BoundingBox Player::hasMapCollision(Map *map) {
	BoundingBox result = BoundingBox(0, 0, 0, 0);
	BoundingBox box = BoundingBox(position.getX() - width / 4,
	                              position.getY() - height / 4,
	                              width / 2, height / 2);

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

void Player::update(double dts, Map *map, std::vector<Entity *> entities) {
	lifeBar -= 50.0 * dts;
	if (lifeBar < life) {
		lifeBar = life;
	}

	immunity -= dts;
	if (immunity <= 0.0) {
		immunity = 0.0;
	}

	Vector2D vel = Vector2D(velocity);
	vel = vel.mult(speed * dts);

	Vector2D curPos = position;
	position = position.add(Vector2D(vel.getX(), 0));
	BoundingBox box = hasMapCollision(map);
	if (box.getMaxX() - box.getMinX() > 0) {
		if (vel.getX() > 0) {
			int dx = (position.getX() + width / 4) - box.getMinX();
			position.setX(position.getX() - dx - 1);
		} else if (vel.getX() < 0) {
			int dx = box.getMaxX() - (position.getX() - width / 4);
			position.setX(position.getX() + dx + 1);
		}
	}
	curPos = position;
	position = position.add(Vector2D(0, vel.getY()));
	box = hasMapCollision(map);
	if (box.getMaxY() - box.getMinY() > 0) {
		if (vel.getY() > 0) {
			int dy = (position.getY() + height / 4) - box.getMinY();
			position.setY(position.getY() - dy - 1);
		} else if (vel.getY() < 0) {
			int dy = box.getMaxY() - (position.getY() - height / 4);
			position.setY(position.getY() + dy + 1);
		}
	}

	handleCollisions(entities);

	if (attackCooldown > 0.0) {
		attackCooldown -= dts;
		if (attackCooldown <= 0.0) {
			attackCooldown = 0.0;
		}
	}
}

void Player::renderWeakness() {
	if (!Monster::weaknessImg) {
		Monster::weaknessImg = al_load_bitmap("resources/graphics/weakness.png");
	}

	Window *window = Window::getInstance();
	Vector2D windowPos = window->getWindowPos(position);

	al_draw_tinted_scaled_bitmap(Monster::weaknessImg, al_map_rgba_f(1.0, 1.0, 1.0, 1.0),
	                             playerType * 16, 0, 16, 16,
	                             windowPos.getX() - 8, windowPos.getY() - height, 16, 16, 0);
}

void Player::playMissSound() {
	if (!missSound) {
		missSound = al_load_sample("resources/sound/miss.wav");
	}

	al_play_sample(missSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void Player::playHurtSound() {
	if (!hurtSound) {
		hurtSound = al_load_sample("resources/sound/hurt.wav");
	}

	al_play_sample(hurtSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}
