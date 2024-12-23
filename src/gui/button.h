#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <functional> 
#include <algorithm> 
#include <thread>
#include <SFML/Graphics.hpp>
#include "gui_object.h"

using namespace std;

class AppGui; // Declaracion para evitar imports circulares

class Button : public GUIObject {
    public: 
        Button(
            int width,
            int height,
            int x,
            int y,
            sf::Color color,
            sf::Font aFont,
            string text,
            function<void(AppGui*)> onClickFunc);
        ~Button();

        void drawOnTarget(sf::RenderWindow* window) override;
        void mouseOverIt() override;
        void mouseNotOverIt() override;
        void mousePressed(AppGui* app) override;

    private:
        sf::RectangleShape* box;
        sf::Text* text_view;

        sf::Color bgColor;
        sf::Color fgColor;
        sf::Font font;

        std::function<void(AppGui*)> onClick; 
};

#endif // BUTTON_H