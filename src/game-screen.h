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
#ifndef _GAME_SCREEN_H
#define _GAME_SCREEN_H

#include "game.h"
#include "map.h"
#include "entity.h"
#include "player.h"
#include "particle-system.h"
#include <allegro5/allegro.h>
#include <vector>

namespace Game {

class GameScreen : public Screen {
private:
    std::vector<Entity *> entities;
    Map *map;
    Player *player[2];
    std::vector<ParticleSystem *> particleSystems;
	double remainingTime;
	ALLEGRO_FONT *font;
	ALLEGRO_FONT *smallFont;
	ALLEGRO_BITMAP *playerHud;
	ALLEGRO_BITMAP *darkness;	

public:
    GameScreen();
    ~GameScreen();

    void start(Engine * engine);
    void stop(Engine * engine);

    void handleEvents(Engine * engine ,ALLEGRO_EVENT *event);
    void update(Engine * engine ,double dts);
    void render(Engine * engine ,double edt);
	int numRand(int min, int max);
	void selectPlayers(void);
	void selectMonsters(void);
	void selectItems(void);
	void drawPlayerHud();
};

}

#endif
