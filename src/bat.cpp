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
#include "bat.h"
#include "window.h"
#include "map.h"
#include <allegro5/allegro_primitives.h>

ALLEGRO_BITMAP *Bat::bat = 0;
ALLEGRO_SAMPLE *Bat::sound = 0;

Bat::Bat() {
	life = 10;
	power = 5;
	speed = 330;
	maxSpeed = speed;
	weakness = ALL;
	width = 48;
	height = 48;
	gold = 1;
}

Bat::~Bat() {
}

void Bat::render(double edt) {
	if (!bat) {
		bat = al_load_bitmap("resources/graphics/bat.png");
	}

	Window *window = Window::getInstance();
	Vector2D windowPos = window->getWindowPos(position);

	al_draw_tinted_scaled_bitmap(bat, al_map_rgb(255, 255, 255),
	                             0, 0, width, height,
	                             windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	double t = immunity / 0.5;
	if (t > 0.0) {
		al_draw_tinted_scaled_bitmap(bat, al_map_rgba_f(1.0, 1.0, 1.0, t),
		                             0, height, width, height,
		                             windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	}
	
	renderWeakness();
}

ParticleSystem *Bat::getDeathParticles() {
	Particle *particle = new Particle(5, 32, 32, 0.050, 1.0, 0.0, 1.0);
	ParticleSystem *particleSystem = new ParticleSystem(particle, RADIAL_ACCEL_OUT, position, 100, 0, 0.3);

	return particleSystem;
}

void Bat::
artificialIntelligence(double dt, Map *map, std::vector<Entity *> entities) {
	if(inercia <= 0) {
		int interval = 1 - 0 + 1;//MAX-MIN+1
		int numRand = 0 + int(interval * (double)rand() /((double)RAND_MAX + 1.0));
		state = MOVE;
		inercia = 1.0;
		if(state == MOVE) {
			inercia = 1.0;
			interval = 7 - 0 + 1;//MAX-MIN+1
			numRand = 0 + int(interval * (double)rand() /((double)RAND_MAX + 1.0));
			stepDx = dxMoster[numRand];
			numRand = 0 + int(interval * (double)rand() /((double)RAND_MAX + 1.0));
			stepDy = dyMoster[numRand];
			if (stepDx > 0) {
				flags = ALLEGRO_FLIP_HORIZONTAL;
			}
		}
	}

	Vector2D curPos;
	Vector2D move;
	BoundingBox box ;
	switch(state) {
	case MOVE:
		curPos = position;
		move = Vector2D(stepDx,stepDy);
		move = move.mult(speed * dt);
		position = position.add(Vector2D(move.getX(), 0));
		box = hasMapCollision(map);
		if (box.getMaxX() - box.getMinX() > 0) {
			if (move.getX() > 0) {
				int dx = (position.getX() + width / 2) - box.getMinX();
				position.setX(position.getX() - dx - 1);
			} else {
				int dx = box.getMaxX() - (position.getX() - width / 2);
				position.setX(position.getX() + dx + 1);
			}
		}
		curPos = position;
		position = position.add(Vector2D(0, move.getY()));
		box = hasMapCollision(map);
		if (box.getMaxY() - box.getMinY() > 0) {
			if (move.getY() > 0) {
				int dy = (position.getY() + height / 2) - box.getMinY();
				position.setY(position.getY() - dy - 1);
			} else {
				int dy = box.getMaxY() - (position.getY() - height / 2);
				position.setY(position.getY() + dy + 1);
			}
		}
		inercia-=dt;
		break;
	}
}

void Bat::playSound() {
	if (!sound) {
		sound = al_load_sample("resources/sound/bat.wav");
	}

	al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}
