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
#ifndef _MAZE_GENERATOR_
#define _MAZE_GENERATOR_

#define XSIZE 64
#define YSIZE 64

#define TILESIZE 64

#define ATTEMPT_FEATURES 4000

#define WALL  0
#define FLOOR 1
#define DOOR  2

class MazeGenerator {
public:
    MazeGenerator();
    ~MazeGenerator();

	int maze[XSIZE][YSIZE];
	bool once;

	void generateMaze(void);
	void Blur(int x1, int y1, int x2, int y2);
	int negpo(void);
	int random(int num);
	bool CanAdd(int x1, int y1, int x2, int y2);
	bool IsWall(int x, int y, int &dx, int &dy);
	void Fill(int x1, int y1, int x2, int y2, int val);
};

#endif
