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
#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector2d.h"
#include <allegro5/allegro.h>

class Particle {
public:
    Particle(int id, int width, int height, double interval, double startOpacity, double endOpacity, double lifetime);
    ~Particle();
    
    static ALLEGRO_BITMAP *particles;

    int id;
    int width;
    int height;
    
    Vector2D anchor;
    double interval;

    Vector2D pos;
    Vector2D vel;
    Vector2D acc;
	double rotation;
	double radians;

    double startOpacity;
    double endOpacity;
    double lifetime;
    double time;

    void update(double dt);
    void render(double dt);
    bool isDead();
    Particle *clone();
};

#endif // PARTICLE_H
