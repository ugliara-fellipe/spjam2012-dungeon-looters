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
#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "particle.h"
#include <vector>

class Entity;

enum GeneratorType {
	RADIAL_ACCEL_OUT,
	RADIAL_ACCEL_IN,	
	UP_CONSTANT,
	UP_ACCEL,
	DOWN_BRAKE
};

class ParticleSystem {
public:
    ParticleSystem(Particle *particle, GeneratorType type, Vector2D anchor, double speed, double accel, double lifetime);
    ParticleSystem(Particle *particle, GeneratorType type, Entity *entity, double speed, double accel, double lifetime);	
    ~ParticleSystem();

	GeneratorType type;
    double time;
    double lifetime;
    double interval;
	Entity *entity;
	Vector2D anchor;
	double speed;
	double accel;
    Particle *particle;
    std::vector<Particle *> particles;

    void update(double dt);
    void render(double dt);
    bool isDead();
};

#endif // PARTICLESYSTEM_H
