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
#include "potion.h"
#include "window.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

ALLEGRO_SAMPLE *PotionLife::sound = 0;

PotionLife::PotionLife():Item(POTION_LIFE) {
}

PotionLife::~PotionLife() {
}

void PotionLife::render(double edt) {
	if (!Item::items) {
		Item::items = al_load_bitmap("resources/graphics/items.png");
	}

	Window *window = Window::getInstance();
	Vector2D windowPos = window->getWindowPos(position);

	al_draw_tinted_scaled_bitmap(Item::items, al_map_rgb(255, 255, 255),
	                             0, 0, width, height,
	                             windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
}

void PotionLife::action( Map *map, std::vector<Entity *> entities, Player **player, Player* eu) {
	Player* use;
	if(eu == player[0]) {
		use = player[1];
	} else {
		use = player[0];
	}
	target = use;

	if(use->life+ 10 <= use->maxLife) {
		use->life += 10;

	} else {
		use->life= use->maxLife;
	}
}

ParticleSystem *PotionLife::getUseParticles() {
	Particle *particle = new Particle(13, 32, 32, 0.015, 1.0, 0.3, 0.4);
	ParticleSystem *particleSystem = new ParticleSystem(particle, UP_CONSTANT, target, 160, 0, 0.2);
	
	return particleSystem;
}

void PotionLife::playUseSound() {
	if (!sound) {
		sound = al_load_sample("resources/sound/heal.wav");
	}

	al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}
