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
#include "game-screen.h"
#include "warrior.h"
#include "rogue.h"
#include "mage.h"
#include "window.h"
#include "spider.h"
#include "construct.h"
#include "minotaur.h"
#include "ghost.h"
#include "witch.h"
#include "bat.h"
#include "zombie.h"
#include "medusa.h"
#include "goblin.h"
#include "potion-change.h"
#include "potion.h"
#include "gold.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "boots.h"
#include "item.h"
#include "potion.h"
#include "potion-change.h"
#include "potion-haste.h"
#include "potion-slow.h"
#include "sword.h"
#include "amulet.h"
#include "potion-poison.h"

namespace Game {

GameScreen::GameScreen() {
	font = 0;
	smallFont = 0;
	playerHud = 0;
	darkness = 0;
}

GameScreen::~GameScreen() {

}

int GameScreen::numRand(int minF, int maxF) {
	int interval = maxF - minF + 1;
	return (minF + int(interval * (double)rand() /((double)RAND_MAX + 1.0)) );
}

void GameScreen::selectPlayers() {
	int p1 = numRand(0,2);
	int p2 = p1;
	while(p1 == p2) {
		p2 = numRand(0,2);
	}
	switch(p1) {
	case MAGE:
		player[0] = new Mage();
		break;
	case WARRIOR:
		player[0] = new Warrior();
		break;
	case ROGUE:
		player[0] = new Rogue();
		break;
	}

	switch(p2) {
	case MAGE:
		player[1] = new Mage();
		break;
	case WARRIOR:
		player[1] = new Warrior();
		break;
	case ROGUE:
		player[1] = new Rogue();
		break;
	}

	map->positionInside(player[0]);
	player[1]->position = player[0]->position;

	entities.push_back(player[0]);
	entities.push_back(player[1]);
}

void GameScreen::selectMonsters(void) {
	int monsterIndice;

	for(int i = 0; i < 40; i++) {
		Entity* moster;
		monsterIndice = numRand(0,8);
		switch(monsterIndice) {
		case SPIDER:
			moster = new Spider();
			break;
		case BAT:
			moster = new Bat();
			break;
		case MINOTAUR:
			moster = new Minotaur();
			break;
		case CONSTRUCT:
			moster = new Construct();
			break;
		case WITCH:
			moster = new Witch();
			break;
		case ZOMBIE:
			moster = new Zombie();
			break;
		case MEDUSA:
			moster = new Medusa();
			break;
		case GOBLIN:
			moster = new Goblin();
			break;
		case GHOST:
			moster = new Ghost();
			break;
		default:
			moster = new Spider();
			break;
		}

		map->positionInside(moster);
		entities.push_back(moster);
	}
}

void GameScreen::selectItems(void) {
	int itemIndice;

	for(int i = 0; i < 40; i++) {
		Entity* item;
		itemIndice = numRand(1,9);
		switch(itemIndice) {

		case POTION_LIFE:
			item = new PotionLife();
			break;
		case POTION_POISON:
			item = new PotionPoison();
			break;
		case POTION_SLOW:
			item = new PotionSlow();
			break;
		case POTION_HASTE:
			item = new PotionHaste();
			break;
		case POTION_SWAP:
			item = new PotionChange();
			break;
		case BOOTS_OF_SPEED:
			item = new Boots();
			break;
		case AMULET:
			item = new Amulet();
			break;
		case HELMET:
			item = new Sword();
			break;
		case GOLD:
			item = new Gold();
			break;
		default:
			item = new Boots();
			break;
		}

		map->positionInside(item);
		entities.push_back(item);
	}

	for(int i = 0; i < 100; i++) {
		Entity* item;
		item = new Gold();
		map->positionInside(item);
		entities.push_back(item);
	}
}


void GameScreen::start(Engine * engine) {
	map = new Map();

	entities.clear();
	particleSystems.clear();

	selectPlayers();
	selectMonsters();
	selectItems();

	remainingTime = 60.0;
	font = 0;
	al_play_sample(engine->music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

	if (!playerHud) {
		playerHud = al_load_bitmap("resources/graphics/playerhud.png");
	}

	if (!darkness) {
		darkness = al_load_bitmap("resources/graphics/darkness.png");
	}
}

void GameScreen::stop(Engine * engine) {
	al_stop_samples();
}

void GameScreen::handleEvents(Engine * engine ,ALLEGRO_EVENT *event) {
	if(event->type == ALLEGRO_EVENT_KEY_DOWN) {
		switch(event->keyboard.keycode) {
		case ALLEGRO_KEY_UP:
			player[1]->inputEvent(UP_PRESS, map, entities,player);
			break;

		case ALLEGRO_KEY_DOWN:
			player[1]->inputEvent(DOWN_PRESS, map, entities,player);
			break;

		case ALLEGRO_KEY_LEFT:
			player[1]->inputEvent(LEFT_PRESS, map, entities,player);
			break;

		case ALLEGRO_KEY_RIGHT:
			player[1]->inputEvent(RIGHT_PRESS, map, entities,player);
			break;

		case ALLEGRO_KEY_I:
			player[1]->inputEvent(BUT1_PRESS, map, entities,player);
			break;

		case ALLEGRO_KEY_O:
			player[1]->inputEvent(BUT2_PRESS, map, entities,player);
			if (player[1]->usedItem) {
				ParticleSystem *particleSystem = player[1]->usedItem->getUseParticles();
				if (particleSystem) {
					particleSystems.push_back(particleSystem);
				}
				player[1]->usedItem = 0;
			}
			break;

		case ALLEGRO_KEY_P:
			player[1]->inputEvent(BUT3_PRESS, map, entities,player);
			if (player[1]->usedItem) {
				ParticleSystem *particleSystem = player[1]->usedItem->getUseParticles();
				if (particleSystem) {
					particleSystems.push_back(particleSystem);
				}
				player[1]->usedItem = 0;
			}
			break;

		case ALLEGRO_KEY_T:
			player[0]->inputEvent(BUT2_PRESS, map, entities,player);
			if (player[0]->usedItem) {
				ParticleSystem *particleSystem = player[0]->usedItem->getUseParticles();
				if (particleSystem) {
					particleSystems.push_back(particleSystem);
				}
				player[0]->usedItem = 0;
			}
			break;

		case ALLEGRO_KEY_Y:
			player[0]->inputEvent(BUT3_PRESS, map, entities,player);
			if (player[0]->usedItem) {
				ParticleSystem *particleSystem = player[0]->usedItem->getUseParticles();
				if (particleSystem) {
					particleSystems.push_back(particleSystem);
				}
				player[0]->usedItem = 0;
			}
			break;

		case ALLEGRO_KEY_W:
			player[0]->inputEvent(UP_PRESS, map, entities,player);
			break;

		case ALLEGRO_KEY_S:
			player[0]->inputEvent(DOWN_PRESS, map, entities,player);
			break;

		case ALLEGRO_KEY_A:
			player[0]->inputEvent(LEFT_PRESS, map, entities,player);
			break;

		case ALLEGRO_KEY_D:
			player[0]->inputEvent(RIGHT_PRESS, map, entities,player);
			break;

		case ALLEGRO_KEY_R:
			player[0]->inputEvent(BUT1_PRESS, map, entities,player);
			break;
		}
	} else if(event->type == ALLEGRO_EVENT_KEY_UP) {
		switch(event->keyboard.keycode) {
		case ALLEGRO_KEY_UP:
			player[1]->inputEvent(UP_RELEASE, map, entities,player);
			break;

		case ALLEGRO_KEY_DOWN:
			player[1]->inputEvent(DOWN_RELEASE, map, entities,player);
			break;

		case ALLEGRO_KEY_LEFT:
			player[1]->inputEvent(LEFT_RELEASE, map, entities,player);
			break;

		case ALLEGRO_KEY_RIGHT:
			player[1]->inputEvent(RIGHT_RELEASE, map, entities,player);
			break;

		case ALLEGRO_KEY_W:
			player[0]->inputEvent(UP_RELEASE, map, entities,player);
			break;

		case ALLEGRO_KEY_S:
			player[0]->inputEvent(DOWN_RELEASE, map, entities,player);
			break;

		case ALLEGRO_KEY_A:
			player[0]->inputEvent(LEFT_RELEASE, map, entities,player);
			break;

		case ALLEGRO_KEY_D:
			player[0]->inputEvent(RIGHT_RELEASE, map, entities,player);
			break;

		case ALLEGRO_KEY_ESCAPE:
			engine->endGame = true;
			break;
		}
	}
}

void GameScreen::update(Engine *engine, double dts) {
	std::vector<Entity *> entitiesToAdd;

	std::vector<Entity *>::iterator it = entities.begin();
	while (it != entities.end()) {
		Entity *entity = (*it);
		if (entity->isDead()) {
			ParticleSystem *partSys = entity->getDeathParticles();
			if (partSys) {
				particleSystems.push_back(partSys);
			}
			it = entities.erase(it);
		} else {
			entity->update(dts, map, entities);

			if (player[0] == entity) {
				if (player[0]->projectile) {
					entitiesToAdd.push_back(player[0]->projectile);
					player[0]->projectile = 0;
				}
			} else if (player[1] == entity) {
				if (player[1]->projectile) {
					entitiesToAdd.push_back(player[1]->projectile);
					player[1]->projectile = 0;
				}
			}

			it++;
		}
	}

	Vector2D windowCenter = Vector2D((player[0]->position.getX() + player[1]->position.getX()) / 2,
	                                 (player[0]->position.getY() + player[1]->position.getY()) / 2);
	Window *window = Window::getInstance();
	window->windowPos = windowCenter;

	std::vector<ParticleSystem *>::iterator itp = particleSystems.begin();
	while (itp != particleSystems.end()) {
		ParticleSystem *particleSystem = (*itp);
		if (particleSystem->isDead()) {
			itp = particleSystems.erase(itp);
		} else {
			particleSystem->update(dts);
			itp++;
		}
	}

	for (unsigned int i = 0; i < entitiesToAdd.size(); i++) {
		entities.push_back((entitiesToAdd[i]));
	}

	remainingTime -= dts;
	if (remainingTime < 0.0) {
		remainingTime = 0.0;
	}

	if (remainingTime <= 0.0 || player[0]->life <= 0.0 || player[1]->life <= 0.0) {
		engine->gold = player[0]->gold + player[1]->gold;
		engine->jumpScreen(3);
	}
}

void GameScreen::render(Engine *engine, double edt) {
	al_clear_to_color(al_map_rgb(0,0,0));
	map->render();
	for (unsigned int i = 0; i < entities.size(); i++) {
		entities[i]->render(edt);
	}
	for (unsigned int i = 0; i < particleSystems.size(); i++) {
		particleSystems[i]->render(edt);
	}

	if (!font) {
		font = al_load_ttf_font("resources/fonts/segoepr.ttf", 50, 0);
	}

	if (!smallFont) {
		smallFont = al_load_ttf_font("resources/fonts/segoepr.ttf", 16, 0);
	}

	al_draw_tinted_scaled_bitmap(darkness, al_map_rgb(255, 255, 255),
	                             0, 0, 640, 360,
	                             0, 0, 1280, 720, 0);

	char timeStr[8];
	sprintf(timeStr, "%d", (int) remainingTime);
	al_draw_text(font, al_map_rgb(255, 255, 255), Window::getInstance()->getWidth() / 2, 20, ALLEGRO_ALIGN_CENTRE, timeStr);

	drawPlayerHud();
}

void GameScreen::drawPlayerHud() {
	char gold1Str[8];
	sprintf(gold1Str, "%d", (int) player[0]->gold);
	al_draw_text(smallFont, al_map_rgb(255, 255, 255), 20 + 25, 20 + 96, ALLEGRO_ALIGN_CENTRE, gold1Str);

	al_draw_text(smallFont, al_map_rgb(255, 255, 255), 20 + 56, 20, ALLEGRO_ALIGN_LEFT, player[0]->getName().c_str());

	int whitebarWidth = ((double) player[0]->lifeBar / (double) player[0]->maxLife) * 116.0;
	int redbarWidth = ((double) player[0]->life / (double) player[0]->maxLife) * 116.0;

	al_draw_filled_rectangle(20 + 58, 20 + 26, 20 + 58 + whitebarWidth, 20 + 26 + 16, al_map_rgb(255, 255, 255));
	al_draw_filled_rectangle(20 + 58, 20 + 26, 20 + 58 + redbarWidth, 20 + 26 + 16, al_map_rgb(255, 0, 0));

	int slotX = 80;
	int slotY = 76;
	for (int i = 0; i < player[0]->maxSlots; i++) {
		if (player[0]->items[i]) {
			player[0]->items[i]->renderScreen(slotX + i * 64, slotY);
		}
	}

	if (player[0]->maxSlots == 2) {
		al_draw_tinted_scaled_bitmap(playerHud, al_map_rgb(255, 255, 255),
		                             0, 0, 184, 120,
		                             20, 20, 184, 120, 0);
	} else {
		al_draw_tinted_scaled_bitmap(playerHud, al_map_rgb(255, 255, 255),
		                             0, 120, 184, 120,
		                             20, 20, 184, 120, 0);
	}
	player[0]->renderScreen(20, 20);

	char gold2Str[8];
	sprintf(gold2Str, "%d", (int) player[1]->gold);
	al_draw_text(smallFont, al_map_rgb(255, 255, 255), 1280 - 20 - 25, 20 + 96, ALLEGRO_ALIGN_CENTRE, gold2Str);

	al_draw_text(smallFont, al_map_rgb(255, 255, 255), 1280 - 20 - 56, 20, ALLEGRO_ALIGN_RIGHT, player[1]->getName().c_str());

	whitebarWidth = ((double) player[1]->lifeBar / (double) player[1]->maxLife) * 116.0;
	redbarWidth = ((double) player[1]->life / (double) player[1]->maxLife) * 116.0;

	al_draw_filled_rectangle(1280 - 20 - 58 - whitebarWidth, 20 + 26, 1280 - 20 - 58, 20 + 26 + 16, al_map_rgb(255, 255, 255));
	al_draw_filled_rectangle(1280 - 20 - 58 - redbarWidth, 20 + 26, 1280 - 20 - 58, 20 + 26 + 16, al_map_rgb(255, 0, 0));

	slotX = 174;
	slotY = 76;
	for (int i = 0; i < player[1]->maxSlots; i++) {
		if (player[1]->items[i]) {
			player[1]->items[i]->renderScreen(1280 - 20 - slotX + i * 64, slotY);
		}
	}

	if (player[1]->maxSlots == 2) {
		al_draw_tinted_scaled_bitmap(playerHud, al_map_rgb(255, 255, 255),
		                             184, 0, 184, 120,
		                             1280 - 184 - 20, 20, 184, 120, 0);
	} else {
		al_draw_tinted_scaled_bitmap(playerHud, al_map_rgb(255, 255, 255),
		                             184, 120, 184, 120,
		                             1280 - 184 - 20, 20, 184, 120, 0);
	}
	player[1]->renderScreen(1280 - 20 - 48, 20);
}
}
