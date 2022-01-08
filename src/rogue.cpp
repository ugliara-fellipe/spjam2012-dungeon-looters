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
#include "rogue.h"
#include "window.h"
#include "dagger.h"
#include "map.h"
#include <allegro5/allegro_primitives.h>

ALLEGRO_BITMAP *Rogue::rogue = 0;

Rogue::Rogue() {
    life = 80;
	lifeBar = life;
	maxLife = life;
    power = 20;
    speed = 330;

	maxSlots = 2;
    attackTime = 0.0;
    isAttacking = false;
        
    playerType = ROGUE;    
}

Rogue::~Rogue() {

}

std::string Rogue::getName() {
	return "Rogue";
}

void Rogue::collisionWith(Entity *entity) {

}

void Rogue::render(double edt) {
    if (!rogue) {
        rogue = al_load_bitmap("resources/graphics/rogue.png");
    }

    Window *window = Window::getInstance();
    Vector2D windowPos = window->getWindowPos(position);

    al_draw_tinted_scaled_bitmap(rogue, al_map_rgb(255, 255, 255),
                                 0, 0, width, height,
                                 windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	double t = immunity;
	if (t > 0.0) {
		al_draw_tinted_scaled_bitmap(rogue, al_map_rgba_f(1.0, 1.0, 1.0, t),
		                             0, height, width, height,
		                             windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	}
	
	renderWeakness();
}

void Rogue::renderScreen(int x, int y) {
    if (!rogue) {
        rogue = al_load_bitmap("resources/graphics/rogue.png");
    }

    al_draw_tinted_scaled_bitmap(rogue, al_map_rgb(255, 255, 255),
                                 0, 0, width, height,
                                 x, y, width, height, 0);
}

void Rogue::prepareAttack() {
    attackCooldown = DAGGER_COOLDOWN;
    projectile = new Dagger(this, orientation, power);

	if (!Player::daggerSound) {
		Player::daggerSound = al_load_sample("resources/sound/dagger.wav");
	}

	al_play_sample(Player::daggerSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}
