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
#include "particle.h"
#include "window.h"

ALLEGRO_BITMAP *Particle::particles = 0;

Particle::Particle(int id, int width, int height, double interval, double startOpacity, double endOpacity, double lifetime) {
    this->id = id;
    this->width = width;
    this->height = height;
    this->anchor = anchor;
    this->interval = interval;
    this->pos = anchor;
    this->vel = vel;
    this->acc = acc;
	this->rotation = 0.0;
	this->radians = (((double)(rand() % 360)) / 360.0) * 6.28;
    this->startOpacity = startOpacity;
    this->endOpacity = endOpacity;
    this->lifetime = lifetime;
    this->time = 0;
}

Particle::~Particle() {

}

void Particle::update(double dt) {
    vel = vel.add(acc.mult(dt));
    pos = pos.add(vel.mult(dt));
    time += dt;
    if (time > lifetime) {
        time = lifetime;
    }
	radians += rotation * dt;
}

void Particle::render(double dt) {
    if (!particles) {
        particles = al_load_bitmap("resources/graphics/particles.png");
    }

    Window *window = Window::getInstance();
    Vector2D windowPos = window->getWindowPos(pos);

    double t = time / lifetime;
    double opacity = (1 - t) * startOpacity + t * endOpacity;
    ALLEGRO_COLOR color = al_map_rgba(255, 255, 255, (opacity * 255));

        al_draw_tinted_scaled_rotated_bitmap_region(particles, 0, id * height, width, height, color,
                width / 2, height / 2,
                windowPos.getX(), windowPos.getY(), 2.0, 2.0, radians, 0);
}

bool Particle::isDead() {
    return (time >= lifetime);
}

Particle *Particle::clone() {
    Particle *particle = new Particle(id, width, height, interval, startOpacity, endOpacity, lifetime);
    return particle;
}



