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
#include "game-over-screen.h"
#include "fadein.h"
#include "fadeout.h"
#include "window.h"

namespace Game {
    
GameOverScreen::GameOverScreen() {
    jumpToGame = false;                 
    
    entryTransition = 0;
    exitTransition = 0;
    title = 0;
    curTransition = 0;    
    
    font = 0;
}

GameOverScreen::~GameOverScreen() {
                          
}

void GameOverScreen::start(Engine * engine) {
    jumpToGame = false;                 
    entryTransition = new Fadein(al_map_rgb(0, 0, 0), 1.0);
    exitTransition = new Fadeout(al_map_rgb(0, 0, 0), 1.0);
    curTransition = entryTransition;    
}

void GameOverScreen::stop(Engine * engine) {

}

void GameOverScreen::handleEvents(Engine * engine ,ALLEGRO_EVENT *event) {
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

void GameOverScreen::update(Engine *engine, double dts) {
    if (jumpToGame && curTransition) {
        if (curTransition->isFinished()) {
            engine->jumpScreen(0);
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

void GameOverScreen::render(Engine *engine, double edt) {
    if (!title) {
        title = al_load_bitmap("resources/graphics/gameover.png");        
    }
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(title, 0, 0, 0);
    
	if (!font) {
		font = al_load_ttf_font("resources/fonts/segoepr.ttf", 50, 0);
	}
    
	char timeStr[8];
	sprintf(timeStr, "%d", (int) engine->gold);
	al_draw_text(font, al_map_rgb(255, 255, 255), Window::getInstance()->getWidth() / 2, Window::getInstance()->getHeight() / 2, ALLEGRO_ALIGN_CENTRE, timeStr);
    
    if (curTransition) {
        curTransition->render(edt);
    }
}

void GameOverScreen::flipStateBuffer() {
     
}

}

