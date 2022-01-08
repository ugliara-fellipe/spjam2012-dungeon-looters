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
#include "spider.h"
#include "window.h"
#include "map.h"
#include <allegro5/allegro_primitives.h>

ALLEGRO_BITMAP *Spider::spider = 0;
ALLEGRO_SAMPLE *Spider::sound = 0;

Spider::Spider() {
    life = 20;
    power = 15;
    speed = 320;
	maxSpeed = speed;
    weakness = ROGUE;
    width = 48;
    height = 48;
	gold = 2;
}

Spider::~Spider() {
}

void Spider::render(double edt) {
    if (!spider) {
        spider = al_load_bitmap("resources/graphics/spider.png");
    }

    Window *window = Window::getInstance();
    Vector2D windowPos = window->getWindowPos(position);

    al_draw_tinted_scaled_bitmap(spider, al_map_rgb(255, 255, 255),
                                 0, 0, width, height,
                                 windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	double t = immunity / 0.5;
	if (t > 0.0) {
		al_draw_tinted_scaled_bitmap(spider, al_map_rgba_f(1.0, 1.0, 1.0, t),
		                             0, height, width, height,
		                             windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	}
	
	renderWeakness();	
}

ParticleSystem *Spider::getDeathParticles() {
    Particle *particle = new Particle(6, 32, 32, 0.050, 1.0, 0.0, 1.0);
    ParticleSystem *particleSystem = new ParticleSystem(particle, RADIAL_ACCEL_OUT, position, 100, 0, 0.3);
	
	return particleSystem;
}

void Spider::playSound() {
	if (!sound) {
		sound = al_load_sample("resources/sound/spider.wav");
	}

	al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}


