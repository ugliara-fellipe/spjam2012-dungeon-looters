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
#include "item.h"
#include "window.h"

ALLEGRO_BITMAP *Item::items = 0;
ALLEGRO_SAMPLE *Item::sound = 0;

Item::Item(int typeItem) {
	this->typeItem = typeItem;
	this->type = ITEM;
	this->remove = false;
	width = 48;
	height = 48;
	orientation = FACING_UP;
	flags = 0;
	target = 0;
}

Item::~Item() {
}

void Item::collisionWith(Entity *entity) {
	if(entity->type == PLAYER && !this->remove) {
		for(int i = 0; i < ((Player*)entity)->maxSlots; i++) {
			Player *p = ((Player*)entity);
			if(p->slots[i] == EMPTY) {
				((Player*)entity)->slots[i] = typeItem;
				((Player*)entity)->items[i] = this;
				this->remove = true;

				if (!sound) {
					sound = al_load_sample("resources/sound/loot.wav");
				}

				al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

				break;
			}
		}
	}
}

void Item::update(double dt, Map *map, std::vector<Entity *> entities) {
	Entity *entity = hasEntityCollision(entities);
	if (entity) {
		collisionWith(entity);
	}
}

bool Item::isDead() {
	return remove;
}

void Item::renderScreen(int x, int y) {
	if (!Item::items) {
		Item::items = al_load_bitmap("resources/graphics/items.png");
	}

	Window *window = Window::getInstance();
	Vector2D windowPos = window->getWindowPos(position);

	al_draw_tinted_scaled_bitmap(Item::items, al_map_rgb(255, 255, 255),
	                             typeItem * width, 0, width, height,
	                             x, y, width, height, flags);
}

ParticleSystem *Item::getDeathParticles() {
	return 0;
}

ParticleSystem *Item::getUseParticles() {
	return 0;
}

void Item::playUseSound() {
	
}
