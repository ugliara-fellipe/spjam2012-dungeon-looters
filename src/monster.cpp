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
#include "monster.h"
#include "window.h"

ALLEGRO_BITMAP *Monster::weaknessImg = 0;

Monster::Monster() {
	distanceAlert = 200.0;
	distanceAttack = 36.0;
	inercia = 0;
	type = MONSTER;
	width = 48;
	height = 48;
	immunity = 0.0;
	flags = 0;
	slowDuration = 0.0;
}

Monster::~Monster() {
}

void Monster::collisionWith(Entity *entity) {
    if (entity->type == PLAYER) {
        Player *player = (Player *) entity;
        if (player->immunity <= 0.0) {
			player->playHurtSound();
            player->life -= power;
            if (player->life < 0.0) {
                player->life = 0.0;
            }
            player->immunity = 1.0;
        }
    }
}

void Monster::
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

void Monster::update(double dt, Map *map, std::vector<Entity *> entities) {
	immunity -= dt;
	if (immunity < 0.0) {
		immunity = 0.0;
	}

	speed = maxSpeed;
	if (slowDuration > 0.0) {
		slowDuration -= dt;
		if (slowDuration <= 0.0) {
			slowDuration = 0.0;
		}

		speed = 0.5 * maxSpeed;
	}

	artificialIntelligence(dt,map,entities);

	Entity *entity = hasEntityCollision(entities);
	if (entity) {
		collisionWith(entity);
	}
}

bool Monster::isDead() {
	return (life <= 0);
}

void Monster::renderWeakness() {
	if (!weaknessImg) {
		weaknessImg = al_load_bitmap("resources/graphics/weakness.png");
	}

	Window *window = Window::getInstance();
	Vector2D windowPos = window->getWindowPos(position);

	if (weakness == ALL) {
		al_draw_tinted_scaled_bitmap(weaknessImg, al_map_rgba_f(1.0, 1.0, 1.0, 1.0),
		                             0, 0, 48, 16,
		                             windowPos.getX() - 24, windowPos.getY() - height, 48, 16, 0);
	} else {
		al_draw_tinted_scaled_bitmap(weaknessImg, al_map_rgba_f(1.0, 1.0, 1.0, 1.0),
		                             weakness * 16, 0, 16, 16,
		                             windowPos.getX() - 8, windowPos.getY() - height, 16, 16, 0);
	}
}
