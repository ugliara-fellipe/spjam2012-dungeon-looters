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
#ifndef INFOSCREEN_H
#define INFOSCREEN_H

#include "game.h"
#include <allegro5/allegro.h>

class Environment;
class Transition;

namespace Game {

class InfoScreen : public Screen {
    private:
        ALLEGRO_BITMAP *info;
        enum MYKEYS {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
        bool jumpToGame;
        Transition *entryTransition;
        Transition *exitTransition;        
        Transition *curTransition;
      
    public:
        bool key[4];
             
        InfoScreen();
        ~InfoScreen();
             
        void start(Engine * engine);
        void stop(Engine * engine);

        void handleEvents(Engine * engine ,ALLEGRO_EVENT *event);
        void update(Engine * engine ,double dts);
        void render(Engine * engine ,double edt);
        void flipStateBuffer();
};

}
#endif // INFOSCREEN_H
