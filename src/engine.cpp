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
#include "engine.h"
#include "game.h"
#include "window.h"

Game::Engine::Engine() {

	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
	}

	if (!al_install_audio()) {
		fprintf(stderr, "failed to initialize the audio!\n");
	}

	if (!al_init_acodec_addon()) {
		fprintf(stderr, "failed to initialize the audio codec addon!\n");
	}

	if (!al_reserve_samples(16)) {
		fprintf(stderr, "failed to reserve samples for audio!\n");
	}

	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
	}

	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
	}

	if(!al_init_image_addon()) {
		fprintf(stderr, "Failed to initialize al_init_image_addon!\n");
	}

	if(!al_init_primitives_addon()) {
		fprintf(stderr, "Failed to initialize al_init_primitives_addon!\n");
	}

	al_init_font_addon();
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "Failed to initialize al_init_primitives_addon!\n");
	}

	music = al_load_sample( "resources/music/music.ogg" );
	if (!music) {
		printf( "Audio clip sample not loaded!\n" );
	}
	// timerUpdate = al_create_timer(1.0 / this->UPS);
	//if(!timerUpdate) {
	//	fprintf(stderr, "failed to create timerUpdate!\n");
	//}

	this->event_queue = al_create_event_queue();
	if(!this->event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(this->display);
		al_destroy_timer(timerUpdate);
	}

//	al_register_event_source(this->event_queue, al_get_timer_event_source(this->timerUpdate));
	al_register_event_source(this->event_queue, al_get_mouse_event_source());
	al_register_event_source(this->event_queue, al_get_keyboard_event_source());

//    this->mutex = al_create_mutex();

	this->currentScreen = 0;
	this->endGame = false;
    this->gold = 0;

	al_set_new_bitmap_flags( ALLEGRO_NO_PREMULTIPLIED_ALPHA );
	al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
}

Game::Engine::~Engine() {
	al_uninstall_audio();

	al_destroy_thread(this->thread_update);

	al_destroy_timer(this->timerUpdate);
	al_destroy_display(this->display);
	al_destroy_event_queue(this->event_queue);
}

void Game::Engine::run() {
	draw_old_time = al_get_time();

	Window *window = Window::getInstance();
	window->setSize(1280, 720);
	display = al_create_display(window->getWidth(), window->getHeight());
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timerUpdate);
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));

	screen[currentScreen]->start(this);

	loop();

//    this->thread_update = al_create_thread(Game::Engine::updateThread, this);
//    al_start_thread(thread_update);

//    while(!this->endGame) {
//        double current_time = al_get_time();
//        delta_time = current_time - draw_old_time;
//        if (update_old_time < draw_old_time) {
//            delta_time = current_time - update_old_time;
//        }

//        al_lock_mutex(mutex);
//        screen[currentScreen]->flipStateBuffer();
//        al_unlock_mutex(mutex);

//        double start_render = al_get_time();

//        screen[currentScreen]->render(this, delta_time);
//        al_flip_display();
//        draw_old_time = al_get_time();

//        double end_render = al_get_time();

//        double rest_time = (1.0 / this->FPS - end_render + start_render)/5;
//        if (end_render - start_render < 1.0 / this->FPS && rest_time > 0){
//            al_rest(rest_time);
//        }
//    }
}

void Game::Engine::loop() {
	delta_time = 0.0;
	update_old_time = al_get_time();

	while(!this->endGame) {
		double current_time = al_get_time();
		delta_time += current_time - update_old_time;
		update_old_time = al_get_time();

		ALLEGRO_EVENT event;
		while (al_get_next_event(this->event_queue, &event)) {
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				this->endGame = true;
			} else {
				this->screen[this->currentScreen]->handleEvents(this, &event);
			}
		}

		while (delta_time >= (1.0 / this->UPS)) {
			delta_time -= 1.0 / this->UPS;
			this->screen[this->currentScreen]->update(this, 1.0 / this->UPS); // parametro em mili
			this->update_old_time = al_get_time();
		}

		screen[currentScreen]->render(this, delta_time);
		al_flip_display();
		al_rest(0.01);
	}
}

void Game::Engine::addScreen(int index, Screen * screen) {
	this->screen[index] = screen;
}

void Game::Engine::jumpScreen(int index) {
	this->screen[this->currentScreen]->stop(this);
	this->currentScreen = index;
	this->screen[index]->start(this);
}

//==============================================================================

void * Game::Engine::updateThread(ALLEGRO_THREAD *thr, void *arg) {
	Game::Engine * engine = (Game::Engine *)arg;

	al_start_timer(engine->timerUpdate);
	engine->update_old_time = al_get_time();

	while(!engine->endGame) {
		ALLEGRO_EVENT event;
		al_wait_for_event(engine->event_queue, &event);

		al_lock_mutex(engine->mutex);
		if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			engine->endGame = true;
		}
		if(event.type == ALLEGRO_EVENT_TIMER) {
			engine->screen[engine->currentScreen]->update(engine, 1.0 / engine->UPS); // parametro em mili
			engine->update_old_time = al_get_time();
		} else {
			engine->screen[engine->currentScreen]->handleEvents(engine, &event);
		}
		al_unlock_mutex(engine->mutex);
	}

	return 0;
}
