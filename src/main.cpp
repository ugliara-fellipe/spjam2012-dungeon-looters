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
#include "title-screen.h"
#include "info-screen.h"
#include "game-screen.h"
#include "game-over-screen.h"

// Alex Campos - A3 Studios
// Ronaldo Rodrigues da Silva

using namespace Game;

int main(int argc, char **argv) {
    Engine *engine = new Engine();
    Screen *titleScreen = new TitleScreen();
	Screen *infoScreen = new InfoScreen();
    Screen *gameScreen = new GameScreen();
    Screen *gameOverScreen = new GameOverScreen();

    engine->addScreen(0, titleScreen);
    engine->addScreen(1, infoScreen);	
    engine->addScreen(2, gameScreen);
    engine->addScreen(3, gameOverScreen);
    engine->run();

    return 0;
}
