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
#include "particle-system.h"
#include "particle.h"
#include "entity.h"

ParticleSystem::ParticleSystem(Particle *particle, GeneratorType type, Vector2D anchor, double speed, double accel, double lifetime) {
	this->particle = particle;
	this->type = type;
	time = 0;
	interval = 0;
	this->lifetime = lifetime;
	this->anchor = anchor;
	this->entity = 0;
	this->speed = speed;
	this->accel = accel;
}

ParticleSystem::ParticleSystem(Particle *particle, GeneratorType type, Entity *entity, double speed, double accel, double lifetime) {
	this->particle = particle;
	this->type = type;
	time = 0;
	interval = 0;
	this->lifetime = lifetime;
	this->anchor = Vector2D(entity->position);
	this->entity = entity;
	this->speed = speed;
	this->accel = accel;
}

ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::update(double dt) {
	time += dt;
	interval += dt;
	if (interval > particle->interval && time < lifetime) {
		interval -= particle->interval;
		Particle *newParticle = particle->clone();
		if (type == RADIAL_ACCEL_OUT) {
			Vector2D direction = Vector2D((rand() % 100) - 50, (rand() % 100) - 50);
			direction = direction.normalize();

			if (entity) {
				newParticle->anchor = Vector2D(entity->position);
			} else {
				newParticle->anchor = anchor;
			}
			newParticle->pos = newParticle->anchor;
			newParticle->vel = direction.mult(speed);
			newParticle->acc = direction.mult(accel);
			newParticle->rotation = 2.5;
		} else if (type == RADIAL_ACCEL_IN) {
			Vector2D direction = Vector2D((rand() % 100) - 50, (rand() % 100) - 50);
			direction = direction.normalize();

			if (entity) {
				newParticle->anchor = Vector2D(entity->position);
			} else {
				newParticle->anchor = anchor;
			}
			newParticle->pos = newParticle->anchor;
			newParticle->pos = newParticle->pos.add(direction.mult(64.0));
			direction = direction.mult(-1.0);
			newParticle->vel = direction.mult(speed);
			newParticle->acc = direction.mult(accel);
			newParticle->rotation = 2.5;
		} else if (type == UP_CONSTANT) {
			Vector2D direction = Vector2D(0, -1);
			Vector2D randPos = Vector2D((rand() % 40) - 20, (rand() % 40) - 20);

			if (entity) {
				newParticle->anchor = Vector2D(entity->position);
			} else {
				newParticle->anchor = anchor;
			}
			newParticle->pos = newParticle->anchor.add(randPos);
			newParticle->vel = direction.mult(speed);
			newParticle->acc = direction.mult(accel);
			newParticle->rotation = 2.5;
		}  else if (type == UP_ACCEL) {
			Vector2D direction = Vector2D(0, -1);
			Vector2D randPos = Vector2D((rand() % 40) - 20, (rand() % 40) - 20);

			if (entity) {
				newParticle->anchor = Vector2D(entity->position);
			} else {
				newParticle->anchor = anchor;
			}
			newParticle->pos = newParticle->anchor.add(randPos);
			newParticle->vel = direction.mult(speed);
			newParticle->acc = direction.mult(accel);
			newParticle->rotation = 0.0;
			newParticle->radians = 0.0;			
		}  else if (type == DOWN_BRAKE) {
			Vector2D direction = Vector2D(0, 1);
			Vector2D randPos = Vector2D((rand() % 40) - 20, (rand() % 40) - 20);

			if (entity) {
				newParticle->anchor = Vector2D(entity->position);
			} else {
				newParticle->anchor = anchor;
			}
			newParticle->pos = newParticle->anchor.add(randPos);
			newParticle->pos = newParticle->pos.add(Vector2D(0, -32));			
			newParticle->vel = direction.mult(speed);
			newParticle->acc = direction.mult(accel);
			newParticle->rotation = 0.0;
			newParticle->radians = 0.0;
		}
		particles.push_back(newParticle);
	}
	if (time > lifetime) {
		time = lifetime;
	}

	std::vector<Particle *>::iterator it = particles.begin();
	while (it != particles.end()) {
		Particle *uParticle = (*it);
		if (uParticle->isDead()) {
			it = particles.erase(it);
		} else {
			uParticle->update(dt);
			it++;
		}
	}
}

void ParticleSystem::render(double dt) {
	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i]->render(dt);
	}
}

bool ParticleSystem::isDead() {
	return (time >= lifetime) && particles.empty();
}
