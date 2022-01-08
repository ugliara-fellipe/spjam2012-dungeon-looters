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
#ifndef _ENGINE_
#define _ENGINE_

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>

namespace Game {

class Screen;

class Engine {
public:
    static constexpr double FPS = 60.0; // Frame per second
    static constexpr double UPS = 60.0; // Update per second

    static constexpr int SCREEN_WIDTH = 720;
    static constexpr int SCREEN_HEIGHT = 720;

    static constexpr int SCREEN_SIZE = 30;
    Screen *screen[SCREEN_SIZE];
    int currentScreen;
    
    int gold;

    double delta_time;
    double draw_old_time;
    double update_old_time;

    bool endGame;

    ALLEGRO_THREAD *thread_update;
    ALLEGRO_MUTEX *mutex;

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timerUpdate;
	ALLEGRO_SAMPLE *music;

    Engine();
    ~Engine();

    void run();
    void loop();

    void addScreen(int index, Screen * screen);
    void jumpScreen(int index);

    static void *updateThread(ALLEGRO_THREAD *thr, void *arg);
};

}


#endif
