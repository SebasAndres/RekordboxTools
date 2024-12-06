#ifndef GUI_OBJECT_H
#define GUI_OBJECT_H

#include <iostream>
#include <SFML/Graphics.hpp>

class AppGui; // Declaracion para evitar imports circulares

class GUIObject{
    public:
        int width;
        int height;
        int x;
        int y;

        virtual void drawOnTarget(sf::RenderWindow* target) = 0;
        virtual void mouseOverIt() = 0;
        virtual void mouseNotOverIt() = 0; 
        virtual void mousePressed(AppGui* app) = 0;
        virtual bool includesPoint(int x, int y) {
            return x >= this->x && x <= this->x + this->width &&
                y >= this->y && y <= this->y + this->height;
        }

};

#endif