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
#include "mage.h"
#include "window.h"
#include "fireball.h"
#include "map.h"
#include <allegro5/allegro_primitives.h>

ALLEGRO_BITMAP *Mage::mage = 0;

Mage::Mage() {
    life = 100;
	lifeBar = life;
    power = 40;
    speed = 300;
	maxLife = life;

    attackTime = 0.0;
    isAttacking = false;
    
    playerType = MAGE;    
}

Mage::~Mage() {

}

std::string Mage::getName() {
	return "Mage";
}

void Mage::collisionWith(Entity *entity) {

}

void Mage::render(double edt) {
    if (!mage) {
        mage = al_load_bitmap("resources/graphics/mage.png");
    }

    Window *window = Window::getInstance();
    Vector2D windowPos = window->getWindowPos(position);
    
    al_draw_tinted_scaled_bitmap(mage, al_map_rgb(255, 255, 255),
                                 0, 0, width, height,
                                 windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	double t = immunity;
	if (t > 0.0) {
		al_draw_tinted_scaled_bitmap(mage, al_map_rgba_f(1.0, 1.0, 1.0, t),
		                             0, height, width, height,
		                             windowPos.getX() - width / 2, windowPos.getY() - height / 2, width, height, flags);
	}
	
	renderWeakness();
}

void Mage::renderScreen(int x, int y) {
    if (!mage) {
        mage = al_load_bitmap("resources/graphics/mage.png");
    }

    al_draw_tinted_scaled_bitmap(mage, al_map_rgb(255, 255, 255),
                                 0, 0, width, height,
                                 x, y, width, height, 0);
}

void Mage::prepareAttack() {
    attackCooldown = FIREBALL_COOLDOWN;
    projectile = new Fireball(this, orientation, power);
	
	if (!Player::fireballSound) {
		Player::fireballSound = al_load_sample("resources/sound/fireball.wav");
	}

	al_play_sample(Player::fireballSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}
