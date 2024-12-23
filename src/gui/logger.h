#ifndef LOGGER_H
#define LOGGER_H

#include "iostream"
#include "gui_object.h"
using namespace std;

class Logger: public GUIObject{
    public: 
        Logger(
            int x,
            int y,
            int width,
            int height,
            sf::Color aBackgroundColor,
            sf::Color aFontColor,
            sf::Font aFont,
            int aTextSize
        );     
        ~Logger();

        void setMessage(string text);

        // Protocolo GUI Object
        void drawOnTarget(sf::RenderWindow* target);
        void mouseOverIt(){}
        void mouseNotOverIt(){}
        void mousePressed(AppGui* app){};

    private:
        sf::Color bgColor;
        sf::Color fontColor;
        sf::Font font;      

        sf::RectangleShape* box;
        sf::Text* text_view;
};

#endif