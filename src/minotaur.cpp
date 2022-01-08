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
#include "minotaur.h"
#include "window.h"
#include "map.h"
#include <allegro5/allegro_primitives.h>

ALLEGRO_BITMAP *Minotaur::minotaur = 0;
ALLEGRO_SAMPLE *Minotaur::sound = 0;

Minotaur::Minotaur() {
	life = 100;
	power = 25;
	speed = 192;
	maxSpeed = speed;
	weakness = WARRIOR;
	width = 48;
	height = 48;
	distanceAlert = 360.0;
	gold = 2;
}

Minotaur::~Minotaur() {
}

void Minotaur::render(double edt) {
	if (!minotaur) {
		minotaur = al_load_bitmap("resources/graphics/minotaur.png");
	}

	Window *window = Window::getInstance();
	Vector2D windowPos = window->getWindowPos(position);

	al_draw_tinted_scaled_bitmap(minotaur, al_map_rgb(255, 255, 255),
	                             0, 0, width, height,
	                             windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	double t = immunity / 0.5;
	if (t > 0.0) {
		al_draw_tinted_scaled_bitmap(minotaur, al_map_rgba_f(1.0, 1.0, 1.0, t),
		                             0, height, width, height,
		                             windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	}

	renderWeakness();
}

ParticleSystem *Minotaur::getDeathParticles() {
	Particle *particle = new Particle(1, 32, 32, 0.050, 1.0, 0.0, 1.0);
	ParticleSystem *particleSystem = new ParticleSystem(particle, RADIAL_ACCEL_OUT, position, 100, 0, 0.3);

	return particleSystem;
}

void Minotaur::
artificialIntelligence(double dt, Map *map, std::vector<Entity *> entities) {
	if(inercia <= 0) {
		int interval = 1 - 0 + 1;//MAX-MIN+1
		int numRand = 0 + int(interval * (double)rand() /((double)RAND_MAX + 1.0));
		state = numRand;
		inercia = 1.0;
		if(state == MOVE) {
			inercia = 2.0;
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

	for(unsigned int i = 0; i < entities.size(); i++) {
		if(entities[i]->type == PLAYER) {
			double distance = position.distanceTo(entities[i]->position) ;
			if(distance < distanceAlert && state != CHARGE) {
				targetPlayer = ((Player*)entities[i]);
				if (targetPlayer->position.getX() > position.getX() - width / 2 &&
				        targetPlayer->position.getX() < position.getX() + width / 2) {
					inercia = 2.0;
					state = CHARGE;

					if (position.getY() < targetPlayer->position.getY()) {
						chargeDirection = Vector2D(0, 1);
					} else {
						chargeDirection = Vector2D(0, -1);
					}
				} else if (targetPlayer->position.getY() > position.getY() - height / 2 &&
				           targetPlayer->position.getY() < position.getY() + height / 2) {
					inercia = 3.0;
					state = CHARGE;

					if (position.getX() < targetPlayer->position.getX()) {
						chargeDirection = Vector2D(1, 0);
					} else {
						chargeDirection = Vector2D(-1, 0);
					}
				}
			}
		}
	}

	Vector2D curPos;
	Vector2D move;
	BoundingBox box ;
	switch(state) {
	case STOP:
		inercia-=dt;
		break;

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

	case CHARGE:
		Vector2D move = chargeDirection.mult(maxSpeed * 1.75 * dt);

		position = position.add(Vector2D(move.getX(), 0));
		BoundingBox box2 = hasMapCollision(map);
		if (box2.getMaxX() - box2.getMinX() > 0) {
			if (move.getX() > 0) {
				int dx = (position.getX() + width / 2) - box2.getMinX();
				position.setX(position.getX() - dx - 1);
			} else {
				int dx = box2.getMaxX() - (position.getX() - width / 2);
				position.setX(position.getX() + dx + 1);
			}
		}
		curPos = position;
		position = position.add(Vector2D(0, move.getY()));
		box2 = hasMapCollision(map);
		if (box2.getMaxY() - box2.getMinY() > 0) {
			if (move.getY() > 0) {
				int dy = (position.getY() + height / 2) - box2.getMinY();
				position.setY(position.getY() - dy - 1);
			} else {
				int dy = box2.getMaxY() - (position.getY() - height / 2);
				position.setY(position.getY() + dy + 1);
			}
		}
		inercia-=dt;
		break;

	}
}

void Minotaur::playSound() {
	if (!sound) {
		sound = al_load_sample("resources/sound/minotaur.wav");
	}

	al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}
