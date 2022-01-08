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
#include "fadein.h"
#include "window.h"
#include <allegro5/allegro_primitives.h>

Fadein::Fadein(ALLEGRO_COLOR color, double duration) {
    this->color = color;
    totalDuration = duration;
    curDuration = 0.0;
}

Fadein::~Fadein() {
    
}

void Fadein::update(double dt) {
    curDuration += dt;
    if (curDuration > totalDuration) {
        curDuration = totalDuration;
    }
}

void Fadein::render(double edt) {
    double duration = curDuration + edt;
    if (duration > totalDuration) {
        duration = totalDuration;
    }
    
    double t = (1.0 - (duration / totalDuration)) * 255.0;
    unsigned char a = (unsigned char) t;
    unsigned char r, g, b;
    al_unmap_rgb(color, &r, &g, &b);
    ALLEGRO_COLOR fillColor = al_map_rgba(r, g, b, a);
    al_draw_filled_rectangle(0, 0, Window::getInstance()->getWidth(), Window::getInstance()->getHeight(), fillColor);
}

bool Fadein::isFinished() {
    return curDuration == totalDuration;
}



