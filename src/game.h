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
#ifndef _GAME_
#define _GAME_

#include "engine.h"
#include <stdio.h>
#include <allegro5/allegro.h>

namespace Game {

class Screen {
public:
    static const int BACK_BUFFER = 0;
    static const int FRONT_BUFFER = 1;

    virtual ~Screen() {};

    virtual void start(Engine * engine) = 0;
    virtual void stop(Engine * engine) = 0;

    virtual void handleEvents(Engine * engine ,ALLEGRO_EVENT *event) = 0;
    virtual void update(Engine * engine ,double deltaTimeSecond) = 0;
    virtual void render(Engine * engine ,double deltaTimeSecond) = 0;
};

}

#endif
