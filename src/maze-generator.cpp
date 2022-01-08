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
#include "maze-generator.h"
#include <cstdlib>
#include <ctime>

using namespace std;

MazeGenerator::MazeGenerator()
{
	srand(time(0));
	once = false;
}

MazeGenerator::~MazeGenerator()
{

}

void MazeGenerator::generateMaze(void)
{
	for(int x = 0; x < XSIZE; x++) {
		for(int y = 0; y < YSIZE; y++) {
			maze[x][y] = WALL;
		}
	}

	int x;
	int y;
	int sx;
	int sy;
	int px;
	int py;
	int dx;
	int dy;

	//Create initial room

	Fill(47,47,53,53,FLOOR);

	for(int i = 0; i < ATTEMPT_FEATURES; i++) {
		for(;;) {
			//find insertion point
			x = random(XSIZE);
			y = random(YSIZE);
			if(IsWall(x,y,dx,dy)) break;
		}

		sx = random(3)+3;
		sy = random(3)+3;

		//make corridor

		if(random(10) < 5) {
			if(random(2) == 0) {
				sx = 1;
				sy *= 2;
			} else {
				sy = 1;
				sx *= 2;
			}
		}

		if(dx == 0) {
			px = x-(sx/2);
			if(dy > 0) {
				py = y +dy;
			} else {
				py = y - sy ;
			}
		} else {
			py = y-(sy/2);
			if(dx > 0) {
				px = x+dx ;
			} else {
				px = x - sx ;
			}
		}


		if(CanAdd(px-1,py-1,px+sx+1,py+sy+1) == true) {
			maze[x][y] = FLOOR;
//			if(random(10) == 2) maze[x][y] = DOOR;
			Fill(px,py,px+sx,py+sy, FLOOR);
			//	if(sx > 1 && sy > 1) Blur(px-2,py-2,px+sx+2,py+sy+2);
		}

	}

	for(int x = 0; x < XSIZE; x++) {
		for(int y = 0; y < YSIZE; y++) {
			if(x == 0 || y == 0 || x == XSIZE - 1 || y == YSIZE - 1) {
				maze[x][y] = WALL;
			}
		}
	}
}


void MazeGenerator::Fill(int x1, int y1, int x2, int y2, int val)
{
	for(int x = x1; x < x2; x++) {
		for(int y = y1; y < y2; y++) {
			maze[x][y] = val;
		}
	}

}

bool MazeGenerator::IsWall(int x, int y, int &dx, int &dy)
{
	int spaces = 0;

	if(maze[x][y] != WALL) return false;

	if(x <= 0 || x >= XSIZE) return false;
	if(y <= 0 || y >= YSIZE) return false;

	if(maze[x+1][y] == FLOOR) dx = -1, dy = 0, spaces++;
	if(maze[x-1][y] == FLOOR) dx = 1, dy = 0,spaces++;
	if(maze[x][y+1] == FLOOR) dx = 0, dy = -1,spaces++;
	if(maze[x][y-1] == FLOOR) dx = 0, dy = 1,spaces++;

	if(spaces == 1) return true;
	return false;

}

bool MazeGenerator::CanAdd(int x1, int y1, int x2, int y2)
{
	for(int x = x1; x < x2; x++) {
		for(int y = y1; y < y2; y++) {
			if(x <= 0 || x >= XSIZE) return false;
			if(y <= 0 || y >= YSIZE) return false;

			if(maze[x][y] != WALL) return false;
		}
	}

	return true;
}

int MazeGenerator::random(int num)
{
	return int(rand()%num);

}

int MazeGenerator::negpo(void)
{
	if(random(2) == 0) {
		return -1;
	} else {
		return 1;
	}
}

void MazeGenerator::Blur(int x1, int y1, int x2, int y2)
{
	int c,x,y;
	for(int i = 0; i < 30; i++) {
		x = random(x2-x1)+x1;
		y = random(y2-y1)+y1;

		if(IsWall(x,y,c,c) == true) maze[x][y] = FLOOR;
	}

	return;
}
