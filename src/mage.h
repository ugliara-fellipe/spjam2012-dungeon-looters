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
#ifndef MAGE_H
#define MAGE_H

#include "player.h"
#include <allegro5/allegro.h>

const double FIREBALL_COOLDOWN = 0.5;

class Mage : public Player {
public:
    static ALLEGRO_BITMAP *mage;
    double attackTime;

    Mage();
    ~Mage();
    
	std::string getName();
    void collisionWith(Entity *entity);
    void render(double edt);
    void prepareAttack();
	void renderScreen(int x, int y);
};

#endif // MAGE_H
