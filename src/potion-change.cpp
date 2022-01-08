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
#include "potion-change.h"
#include "item.h"
#include "window.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

PotionChange::PotionChange():Item(POTION_SWAP) {
}

PotionChange::~PotionChange() {
}

void PotionChange::render(double edt) {
	if (!Item::items) {
		Item::items = al_load_bitmap("resources/graphics/items.png");
	}

	Window *window = Window::getInstance();
	Vector2D windowPos = window->getWindowPos(position);

	al_draw_tinted_scaled_bitmap(Item::items, al_map_rgb(255, 255, 255),
	                             0, 0, width, height,
	                             windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
}

void PotionChange::action( Map *map, std::vector<Entity *> entities, Player **player, Player* eu) {
	bool keyz[4];
	Vector2D velocity;

	velocity = Vector2D(player[0]->velocity);
	keyz[KEY_UP] = player[0]->keyz[KEY_UP];
	keyz[KEY_DOWN] = player[0]->keyz[KEY_DOWN];
	keyz[KEY_LEFT] = player[0]->keyz[KEY_LEFT];
	keyz[KEY_RIGHT] = player[0]->keyz[KEY_RIGHT];	
	player[0]->velocity = player[1]->velocity;
	player[0]->keyz[KEY_UP] = player[1]->keyz[KEY_UP];
	player[0]->keyz[KEY_DOWN] = player[1]->keyz[KEY_DOWN];
	player[0]->keyz[KEY_LEFT] = player[1]->keyz[KEY_LEFT];
	player[0]->keyz[KEY_RIGHT] = player[1]->keyz[KEY_RIGHT];	
	player[1]->velocity = velocity;
	player[1]->keyz[KEY_UP] = keyz[KEY_UP];
	player[1]->keyz[KEY_DOWN] = keyz[KEY_DOWN];
	player[1]->keyz[KEY_LEFT] = keyz[KEY_LEFT];
	player[1]->keyz[KEY_RIGHT] = keyz[KEY_RIGHT];	
	
	Player *p = player[0];
	player[0]=player[1];
	player[1] = p;
}
