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
#include "title-screen.h"
#include "fadein.h"
#include "fadeout.h"
#include "window.h"

namespace Game {

TitleScreen::TitleScreen() {
    jumpToGame = false;

    entryTransition = 0;
    exitTransition = 0;
    title = 0;
    credits = 0;
    font = 0;
    curTransition = 0;
    
    player1Ready = false;
    player2Ready = false;
}

TitleScreen::~TitleScreen() {

}

void TitleScreen::start(Engine * engine) {
    jumpToGame = false;
    entryTransition = new Fadein(al_map_rgb(0, 0, 0), 1.0);
    exitTransition = new Fadeout(al_map_rgb(0, 0, 0), 1.0);
    curTransition = entryTransition;
    player1Ready = false;
    player2Ready = false;
}

void TitleScreen::stop(Engine * engine) {

}

void TitleScreen::handleEvents(Engine * engine ,ALLEGRO_EVENT *event) {
    if (!curTransition) {
        if(event->type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event->keyboard.keycode) {
            case ALLEGRO_KEY_1:
                player1Ready = true;
                break;

            case ALLEGRO_KEY_2:
                player2Ready = true;
                break;
            }

        } else if (event->type == ALLEGRO_EVENT_KEY_UP) {
            switch (event->keyboard.keycode) {
            case ALLEGRO_KEY_1:
                player1Ready = false;
                break;

            case ALLEGRO_KEY_2:
                player2Ready = false;
                break;

            case ALLEGRO_KEY_ESCAPE:
                engine->endGame = true;
                break;
            }
        }
    }
}

void TitleScreen::update(Engine *engine, double dts) {
    if (player1Ready && player2Ready) {
        jumpToGame = true;
        curTransition = exitTransition;
    }

    if (jumpToGame && curTransition) {
        if (curTransition->isFinished()) {
            engine->jumpScreen(1);
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

void TitleScreen::render(Engine *engine, double edt) {
    if (!title) {
        title = al_load_bitmap("resources/graphics/title.png");
        credits = al_load_bitmap("resources/graphics/credits.png");
    }
    if (!font) {
		font = al_load_ttf_font("resources/fonts/segoepr.ttf", 50, 0);
	}
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(title, 0, 0, 0);
    al_draw_bitmap(credits, 0, Window::getInstance()->getHeight() - (al_get_bitmap_height(credits) + 20), 0);
    
    char timeStr[50];
	sprintf(timeStr, "Player 1 and Player 2");

    char timeStr2[50];
	sprintf(timeStr2, "press start together to begin");

	al_draw_text(font, al_map_rgb(255, 255, 255), (Window::getInstance()->getWidth() / 2), Window::getInstance()->getHeight() - 160, ALLEGRO_ALIGN_CENTRE, timeStr);
    al_draw_text(font, al_map_rgb(255, 255, 255), (Window::getInstance()->getWidth() / 2), Window::getInstance()->getHeight() - 100, ALLEGRO_ALIGN_CENTRE, timeStr2);

    if (curTransition) {
        curTransition->render(edt);
    }
}

void TitleScreen::flipStateBuffer() {

}

}
