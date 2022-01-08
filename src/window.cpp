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
#include "window.h"

Window *Window::instance = 0;

Window::Window() {

}

Window::~Window() {

}

Window *Window::getInstance() {
    if (!instance) {
        instance = new Window();
    }

    return instance;
}

void Window::setSize(int width, int height) {
    this->width = width;
    this->height = height;
}

int Window::getWidth() {
    return this->width;
}

int Window::getHeight() {
    return this->height;
}

BoundingBox Window::getBounds() {
    return BoundingBox(windowPos.getX() - width / 2,
                       windowPos.getY() - height / 2, width, height);
}

Vector2D Window::getWindowPos(Vector2D worldPos) {
    BoundingBox bounds = getBounds();
    Vector2D newPos = Vector2D(worldPos.getX() - bounds.getMinX(),
                               worldPos.getY() - bounds.getMinY());
    return newPos;
}
