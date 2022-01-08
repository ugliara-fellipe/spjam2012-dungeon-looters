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
#ifndef POTIONHASTE_H
#define POTIONHASTE_H

#include "item.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

class PotionHaste : public Item
{
public:
	static ALLEGRO_SAMPLE *sound;

	PotionHaste();
	~PotionHaste();

	void render(double edt);
	void action(Map *map, std::vector<Entity *> entities, Player **player, Player* eu);
	ParticleSystem *getUseParticles();	
	void playUseSound();
};

#endif // POTIONHASTE_H
