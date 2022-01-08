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
#include "fadeout.h"
#include "window.h"
#include <allegro5/allegro_primitives.h>

Fadeout::Fadeout(ALLEGRO_COLOR color, double duration) {
    this->color = color;
    totalDuration = duration;
    curDuration = 0.0;
}

Fadeout::~Fadeout() {
    
}

void Fadeout::update(double dt) {
    curDuration += dt;
    if (curDuration > totalDuration) {
        curDuration = totalDuration;
    }
}

void Fadeout::render(double edt) {
    double duration = curDuration + edt;
    if (duration > totalDuration) {
        duration = totalDuration;
    }
    
    double t = duration / totalDuration;
    unsigned char r, g, b;
    al_unmap_rgb(color, &r, &g, &b);
    ALLEGRO_COLOR fillColor = al_map_rgba(r, g, b, (unsigned char) (t * 255.0));
    al_draw_filled_rectangle(0, 0, Window::getInstance()->getWidth(), Window::getInstance()->getHeight(), fillColor);
}

bool Fadeout::isFinished() {
    return curDuration == totalDuration;
}
