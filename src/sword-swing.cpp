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
#include "sword-swing.h"
#include "warrior.h"
#include "window.h"
#include "monster.h"
#include <cmath>

SwordSwing::SwordSwing(Player *player, Orientation orientation, int damage) {
	type = PROJECTILE;
	this->player = player;
	this->orientation = orientation;

	width = 48;
	height = 48;
	this->damage = damage;
	attackTime = 0.0;
}

SwordSwing::~SwordSwing() {

}

void SwordSwing::collisionWith(Entity *entity) {
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

void SwordSwing::update(double dt, Map *map, std::vector<Entity *> entities) {
	attackTime += dt;
	if (attackTime > SWING_DURATION) {
		attackTime = SWING_DURATION;
	}

	Vector2D swordPos = Vector2D(player->position);
	Vector2D direction;
	switch (orientation) {
	case FACING_UP:
		direction = Vector2D(0, -1);
		break;

	case FACING_LEFT:
		direction = Vector2D(-1, 0);
		break;

	case FACING_RIGHT:
		direction = Vector2D(1, 0);
		break;

	case FACING_DOWN:
		flags = ALLEGRO_FLIP_VERTICAL;
		direction = Vector2D(0, 1);
		break;
	}

	double t = attackTime / SWING_DURATION;
	double swingStart = 0.0;
	double swingEnd = 6.28;
	double radians = ((1 - t) * swingStart) + (t * swingEnd);

	Vector2D rotated = Vector2D(direction.getX() * cos(-radians) + direction.getY() * sin(-radians),
	                            -direction.getX() * sin(-radians) + direction.getY() * cos(-radians));
	rotated = rotated.mult(width);
	rotated = rotated.add(Vector2D(swordPos));

	BoundingBox box = BoundingBox(rotated.getX() - width / 2,
	                              rotated.getY() - height / 2,
	                              width, height);

	// colisão com entidades
	for (unsigned int i = 0; i < entities.size(); i++) {
		if (entities[i]->type == MONSTER) {
			BoundingBox entityBox = BoundingBox(entities[i]->position.getX() - entities[i]->width / 2,
			                                    entities[i]->position.getY() - entities[i]->height / 2,
			                                    entities[i]->width, entities[i]->height);
			if (box.intersects(entityBox)) {
				Entity *result = entities[i];
				collisionWith(result);
			}
		}
	}
}

void SwordSwing::render(double edt) {
	if (!Warrior::warrior) {
		Warrior::warrior = al_load_bitmap("resources/graphics/warrior.png");
	}

	double t = attackTime / SWING_DURATION;
	double swingStart = 0;
	double swingEnd = 6.28;
	double radians = ((1 - t) * swingStart) + (t * swingEnd);

	Window *window = Window::getInstance();
	Vector2D windowPos = window->getWindowPos(player->position);

	switch (orientation) {
	case FACING_UP:
		al_draw_tinted_scaled_rotated_bitmap_region(Warrior::warrior, width, 0, width, height, al_map_rgb(255, 255, 255),
		        width / 2, 3 * height / 2,
		        windowPos.getX(), windowPos.getY(), 1.0, 1.0, radians, 0);
		break;

	case FACING_LEFT:
		al_draw_tinted_scaled_rotated_bitmap_region(Warrior::warrior, width, height, width, height, al_map_rgb(255, 255, 255),
		        3 * width / 2, height / 2,
		        windowPos.getX(), windowPos.getY(), 1.0, 1.0, radians, 0);
		break;

	case FACING_RIGHT:
		al_draw_tinted_scaled_rotated_bitmap_region(Warrior::warrior, width, height, width, height, al_map_rgb(255, 255, 255),
		        - width / 2, height / 2,
		        windowPos.getX(), windowPos.getY(), 1.0, 1.0, radians, ALLEGRO_FLIP_HORIZONTAL);
		break;

	case FACING_DOWN:
		al_draw_tinted_scaled_rotated_bitmap_region(Warrior::warrior, width, 0, width, height, al_map_rgb(255, 255, 255),
		        width / 2, - height / 2,
		        windowPos.getX(), windowPos.getY(), 1.0, 1.0, radians, ALLEGRO_FLIP_VERTICAL);
		break;
	}
}

bool SwordSwing::isDead() {
	return (attackTime >= SWING_DURATION);
}
