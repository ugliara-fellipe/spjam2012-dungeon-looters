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
#ifndef GOBLIN_H
#define GOBLIN_H

#include "monster.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

class Goblin : public Monster {
public:
	static ALLEGRO_BITMAP *goblin;
	static ALLEGRO_SAMPLE *sound;

	Goblin();
	~Goblin();

	void render(double edt);
	ParticleSystem *getDeathParticles();
	void playSound();
};

#endif // GOBLIN_H
