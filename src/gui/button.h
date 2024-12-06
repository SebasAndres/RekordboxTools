#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <algorithm> 
#include <SFML/Graphics.hpp>
#include "gui_object.h"

class Button : public GUIObject {
    public: 
        Button(int width, int height, int x, int y, sf::Color color, std::string fontPath, std::string text, void (*onClickFunc)());
        ~Button();

        void drawOnTarget(sf::RenderWindow* window) override;
        void mouseOverIt() override;
        void mouseNotOverIt() override;
        void mousePressed() override;

    private:
        sf::RectangleShape* box;
        sf::Text* btText;
        sf::Color bgColor;
        sf::Color fgColor;
        sf::Font font;

        void (*onClick)(); 
};

#endif // BUTTON_H