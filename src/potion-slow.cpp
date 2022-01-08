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
#include "potion-slow.h"
#include "window.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

ALLEGRO_SAMPLE *PotionSlow::sound = 0;

PotionSlow::PotionSlow():Item(POTION_SLOW) {
}

PotionSlow::~PotionSlow() {
}

void PotionSlow::render(double edt) {
	if (!Item::items) {
		Item::items = al_load_bitmap("resources/graphics/items.png");
	}

	Window *window = Window::getInstance();
	Vector2D windowPos = window->getWindowPos(position);

	al_draw_tinted_scaled_bitmap(Item::items, al_map_rgb(255, 255, 255),
	                             0, 0, width, height,
	                             windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
}

void PotionSlow::action( Map *map, std::vector<Entity *> entities, Player **player, Player* eu) {
	Player* use;
	if(eu == player[0]) {
		use = player[1];
	} else {
		use = player[0];
	}
	target = use;

	use->speed -= 10;
}

ParticleSystem *PotionSlow::getUseParticles() {
	Particle *particle = new Particle(16, 32, 32, 0.03, 1.0, 0.0, 0.4);
	ParticleSystem *particleSystem = new ParticleSystem(particle, DOWN_BRAKE, target, 160, 100, 0.3);
	
	return particleSystem;
}

void PotionSlow::playUseSound() {
	if (!sound) {
		sound = al_load_sample("resources/sound/slow.wav");
	}

	al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}
