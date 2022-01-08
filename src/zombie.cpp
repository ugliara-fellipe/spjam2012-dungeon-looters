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
#include "zombie.h"
#include "window.h"
#include "map.h"
#include <allegro5/allegro_primitives.h>

ALLEGRO_BITMAP *Zombie::zombie = 0;
ALLEGRO_SAMPLE *Zombie::sound = 0;

Zombie::Zombie() {
	life = 60;
	power = 25;
	speed = 128;
	maxSpeed = speed;	
	weakness = ALL;
	width = 48;
	height = 48;
	gold = 1;
}

Zombie::~Zombie() {
}

void Zombie::render(double edt) {
	if (!zombie) {
		zombie = al_load_bitmap("resources/graphics/zombie.png");
	}

	Window *window = Window::getInstance();
	Vector2D windowPos = window->getWindowPos(position);

	al_draw_tinted_scaled_bitmap(zombie, al_map_rgb(255, 255, 255),
	                             0, 0, width, height,
	                             windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	double t = immunity / 0.5;
	if (t > 0.0) {
		al_draw_tinted_scaled_bitmap(zombie, al_map_rgba_f(1.0, 1.0, 1.0, t),
		                             0, height, width, height,
		                             windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	}
	
	renderWeakness();	
}

ParticleSystem *Zombie::getDeathParticles() {
	Particle *particle = new Particle(3, 32, 32, 0.050, 1.0, 0.0, 1.0);
	ParticleSystem *particleSystem = new ParticleSystem(particle, RADIAL_ACCEL_OUT, position, 100, 0, 0.3);

	return particleSystem;
}

void Zombie::
artificialIntelligence(double dt, Map *map, std::vector<Entity *> entities) {
	if(inercia <= 0) {
		int interval = 9 - 0 + 1;//MAX-MIN+1
		int numRand = 0 + int(interval * (double)rand() /((double)RAND_MAX + 1.0));
		state = STOP;
		if(numRand > 8 ) {
			state = MOVE;
		}
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

	for(unsigned int i = 0; i < entities.size(); i++) {
		if(entities[i]->type == PLAYER) {
			double distance = position.distanceTo(entities[i]->position) ;
			if(distance < distanceAlert) {

				inercia = 0;
				state = FOLLOW_PLAYER;
				targetPlayer = ((Player*)entities[i]);
				if(distance < distanceAttack) {
					state = ATTACK;
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

	case FOLLOW_PLAYER:
		Vector2D aux = position.mult(-1);
		Vector2D movTarget = targetPlayer->position.add(aux);
		movTarget = movTarget.normalize();
		movTarget = movTarget.mult(speed * dt);

		position = position.add(Vector2D(movTarget.getX(), 0));
		BoundingBox box2 = hasMapCollision(map);
		if (box2.getMaxX() - box2.getMinX() > 0) {
			if (movTarget.getX() > 0) {
				int dx = (position.getX() + width / 2) - box2.getMinX();
				position.setX(position.getX() - dx - 1);
			} else {
				int dx = box2.getMaxX() - (position.getX() - width / 2);
				position.setX(position.getX() + dx + 1);
			}
		}
		curPos = position;
		position = position.add(Vector2D(0, movTarget.getY()));
		box2 = hasMapCollision(map);
		if (box2.getMaxY() - box2.getMinY() > 0) {
			if (movTarget.getY() > 0) {
				int dy = (position.getY() + height / 2) - box2.getMinY();
				position.setY(position.getY() - dy - 1);
			} else {
				int dy = box2.getMaxY() - (position.getY() - height / 2);
				position.setY(position.getY() + dy + 1);
			}
		}
		break;

	}
}

void Zombie::playSound() {
	if (!sound) {
		sound = al_load_sample("resources/sound/zombie.wav");
	}

	al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}
