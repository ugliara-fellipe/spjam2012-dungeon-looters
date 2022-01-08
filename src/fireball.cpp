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
#include "fireball.h"
#include "mage.h"
#include "window.h"
#include "monster.h"
#include "particle-system.h"

Fireball::Fireball(Player *player, Orientation orientation, int damage) {
	type = PROJECTILE;
	this->player = player;
	this->orientation = orientation;
	this->position = player->position;
	this->damage = damage;

	width = 48;
	height = 48;

	switch (orientation) {
	case FACING_UP:
		vel = Vector2D(0, -1);
		position = position.add(Vector2D(0, -height / 2));
		break;
	case FACING_RIGHT:
		vel = Vector2D(1, 0);
		position = position.add(Vector2D(width / 2, 0));
		break;
	case FACING_DOWN:
		vel = Vector2D(0, 1);
		position = position.add(Vector2D(0, height / 2));
		break;
	case FACING_LEFT:
		vel = Vector2D(-1, 0);
		position = position.add(Vector2D(-width / 2, 0));
		break;
	}

	speed = 384.0;
	dead = false;
}

Fireball::~Fireball() {

}

void Fireball::collisionWith(Entity *entity) {
	if (entity->type == MONSTER) {
		Monster *monster = (Monster *)entity;
		monster->slowDuration = 1.0;
		if (monster->weakness == ALL || monster->weakness == player->playerType) {
			if (monster->immunity <= 0.0) {
				monster->playSound();
				monster->life -= damage;
				if (monster->life < 0.0) {
					monster->life = 0.0;
					player->gold += monster->gold;					
				}
				monster->immunity = 0.5;
			}
		} else {
			player->playMissSound();
		}
	}
}

void Fireball::update(double dt, Map *map, std::vector<Entity *> entities) {
	position = position.add(vel.mult(speed * dt));

	Entity *result = 0;
	BoundingBox box = BoundingBox(position.getX() - width / 4,
	                              position.getY() - height / 4,
	                              width / 2, height / 2);

	// colisão com entidades
	if (!result) {
		for (unsigned int i = 0; i < entities.size(); i++) {
			if (entities[i]->type == MONSTER) {
				BoundingBox entityBox = BoundingBox(entities[i]->position.getX() - entities[i]->width / 2,
				                                    entities[i]->position.getY() - entities[i]->height / 2,
				                                    entities[i]->width, entities[i]->height);
				if (box.intersects(entityBox)) {
					result = entities[i];
					dead = true;
					break;
				}
			}
		}
	}

	if (result) {
		collisionWith(result);
	} else {
		box = hasMapCollision(map);
		if (box.getMaxX() - box.getMinX() > 0 ||
		        box.getMaxY() - box.getMinY()) {
			dead = true;
		}
	}
}

BoundingBox Fireball::hasMapCollision(Map *map) {
	BoundingBox result = BoundingBox(0, 0, 0, 0);
	BoundingBox box = BoundingBox(position.getX() - width / 6,
	                              position.getY() - height / 6,
	                              width / 3, height / 3);

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

void Fireball::render(double edt) {
	if (!Mage::mage) {
		Mage::mage = al_load_bitmap("resources/graphics/warrior.png");
	}

	Window *window = Window::getInstance();
	Vector2D windowPos = window->getWindowPos(position);

	switch (orientation) {
	case FACING_UP:
		al_draw_tinted_scaled_rotated_bitmap_region(Mage::mage, width, 0, width, height, al_map_rgb(255, 255, 255),
		        width / 2, height / 2,
		        windowPos.getX(), windowPos.getY(), 1.0, 1.0, 0.0, 0);
		break;

	case FACING_RIGHT:
		al_draw_tinted_scaled_rotated_bitmap_region(Mage::mage, width, 0, width, height, al_map_rgb(255, 255, 255),
		        width / 2, height / 2,
		        windowPos.getX(), windowPos.getY(), 1.0, 1.0, 3.14 / 2.0, 0);
		break;

	case FACING_DOWN:
		al_draw_tinted_scaled_rotated_bitmap_region(Mage::mage, width, 0, width, height, al_map_rgb(255, 255, 255),
		        width / 2, height / 2,
		        windowPos.getX(), windowPos.getY(), 1.0, 1.0, 3.14, 0);
		break;

	case FACING_LEFT:
		al_draw_tinted_scaled_rotated_bitmap_region(Mage::mage, width, 0, width, height, al_map_rgb(255, 255, 255),
		        width / 2, height / 2,
		        windowPos.getX(), windowPos.getY(), 1.0, 1.0, 3.0 * 3.14 / 2.0, 0);
		break;
	}
}

bool Fireball::isDead() {
	return dead;
}
