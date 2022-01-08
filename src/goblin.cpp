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
#include "goblin.h"
#include "window.h"
#include "map.h"
#include <allegro5/allegro_primitives.h>

ALLEGRO_BITMAP *Goblin::goblin = 0;
ALLEGRO_SAMPLE *Goblin::sound = 0;

Goblin::Goblin() {
    life = 30;
    power = 10;
    speed = 320;
	maxSpeed = speed;	
    weakness = ROGUE;
    width = 48;
    height = 48;
	gold = 3;
}

Goblin::~Goblin() {
}

void Goblin::render(double edt) {
    if (!goblin) {
        goblin = al_load_bitmap("resources/graphics/goblin.png");
    }

    Window *window = Window::getInstance();
    Vector2D windowPos = window->getWindowPos(position);

    al_draw_tinted_scaled_bitmap(goblin, al_map_rgb(255, 255, 255),
                                 0, 0, width, height,
                                 windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	double t = immunity / 0.5;
	if (t > 0.0) {
		al_draw_tinted_scaled_bitmap(goblin, al_map_rgba_f(1.0, 1.0, 1.0, t),
		                             0, height, width, height,
		                             windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	}
	
	renderWeakness();	
}

ParticleSystem *Goblin::getDeathParticles() {
    Particle *particle = new Particle(7, 32, 32, 0.050, 1.0, 0.0, 1.0);
    ParticleSystem *particleSystem = new ParticleSystem(particle, RADIAL_ACCEL_OUT, position, 100, 0, 0.3);
	
	return particleSystem;
}

void Goblin::playSound() {
	if (!sound) {
		sound = al_load_sample("resources/sound/goblin.wav");
	}

	al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

