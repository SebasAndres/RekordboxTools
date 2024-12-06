#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "gui_object.h"
#include <algorithm> 

class Button : public GUIObject {
    public: 
        Button(int width, int height, int x, int y, sf::Color color, void (*onClickFunc)());
        
        void mouseOverIt() override;
        void mouseNotOverIt() override;
        void mousePressed() override;

    private:
        sf::Color bgColor;
        void (*onClick)(); 
};

#endif // BUTTON_H