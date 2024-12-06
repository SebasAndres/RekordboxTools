#ifndef GUI_OBJECT_H
#define GUI_OBJECT_H

#include <iostream>
#include <SFML/Graphics.hpp>

class GUIObject{
    public:
        int width;
        int height;
        int x;
        int y;

        virtual void drawOnTarget(sf::RenderWindow* target) = 0;
        virtual void mouseOverIt() = 0;
        virtual void mouseNotOverIt() = 0; 
        virtual void mousePressed() = 0;
        virtual bool includesPoint(int x, int y) {
            return x >= this->x && x <= this->x + this->width &&
                y >= this->y && y <= this->y + this->height;
        }

};

#endif