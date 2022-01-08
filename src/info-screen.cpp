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
#include "info-screen.h"
#include "fadein.h"
#include "fadeout.h"

namespace Game {

InfoScreen::InfoScreen() {
    jumpToGame = false;

    entryTransition = 0;
    exitTransition = 0;
    info = 0;
    curTransition = 0;
}

InfoScreen::~InfoScreen() {

}

void InfoScreen::start(Engine * engine) {
    jumpToGame = false;
    entryTransition = new Fadein(al_map_rgb(0, 0, 0), 1.0);
    exitTransition = new Fadeout(al_map_rgb(0, 0, 0), 1.0);
    curTransition = entryTransition;
}

void InfoScreen::stop(Engine * engine) {

}

void InfoScreen::handleEvents(Engine * engine ,ALLEGRO_EVENT *event) {
    if (!curTransition) {
        if(event->type == ALLEGRO_EVENT_KEY_DOWN) {
            
        } else if (event->type == ALLEGRO_EVENT_KEY_UP) {
            switch (event->keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    engine->endGame = true;
                    break;
                    
                default:
                    jumpToGame = true;
                    curTransition = exitTransition;
                    break;
            }
        }
    }
}

void InfoScreen::update(Engine *engine, double dts) {
    if (jumpToGame && curTransition) {
        if (curTransition->isFinished()) {
            engine->jumpScreen(2);
        } else {
            curTransition->update(dts);            
        }
    } else {
        if (curTransition) {
            curTransition->update(dts);
            if (curTransition->isFinished()) {
                curTransition = 0;
            }
        }
    }
}

void InfoScreen::render(Engine *engine, double edt) {
    if (!info) {
        info = al_load_bitmap("resources/graphics/instructions.png");
    }
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(info, 0, 0, 0);
    if (curTransition) {
        curTransition->render(edt);
    }
}

void InfoScreen::flipStateBuffer() {

}

}
