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
#include "ghost.h"
#include "window.h"
#include "map.h"
#include <allegro5/allegro_primitives.h>

ALLEGRO_BITMAP *Ghost::ghost = 0;
ALLEGRO_SAMPLE *Ghost::sound = 0;

Ghost::Ghost() {
    life = 60;
    power = 20;
    speed = 192;
	maxSpeed = speed;	
    weakness = ALL;
    width = 48;
    height = 48;
	gold = 2;
}

Ghost::~Ghost() {
}

BoundingBox Ghost::hasMapCollision(Map *map) {
    BoundingBox result = BoundingBox(0, 0, 0, 0);
    BoundingBox box = BoundingBox(position.getX() - width / 2,
                                  position.getY() - height / 2,
                                  width, height);

    int tileX = position.getX() / TILESET_WIDTH;
    int tileY = position.getY() / TILESET_HEIGHT;

    // colisão com o mapa
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int x = tileX + dx;
            int y = tileY + dy;
            if (x == TILESET_WIDTH - 1 || x == 0 || y == 0 || y == TILESET_HEIGHT - 1) {
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

void Ghost::render(double edt) {
    if (!ghost) {
        ghost = al_load_bitmap("resources/graphics/ghost.png");
    }

    Window *window = Window::getInstance();
    Vector2D windowPos = window->getWindowPos(position);

    al_draw_tinted_scaled_bitmap(ghost, al_map_rgb(255, 255, 255),
                                 0, 0, width, height,
                                 windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	double t = immunity / 0.5;
	if (t > 0.0) {
		al_draw_tinted_scaled_bitmap(ghost, al_map_rgba_f(1.0, 1.0, 1.0, t),
		                             0, height, width, height,
		                             windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	}
	
	renderWeakness();	
}

ParticleSystem *Ghost::getDeathParticles() {
    Particle *particle = new Particle(0, 32, 32, 0.050, 1.0, 0.0, 1.0);
    ParticleSystem *particleSystem = new ParticleSystem(particle, RADIAL_ACCEL_OUT, position, 100, -300, 0.5);
	
	return particleSystem;
}

void Ghost::playSound() {
	if (!sound) {
		sound = al_load_sample("resources/sound/ghost.wav");
	}

	al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}
