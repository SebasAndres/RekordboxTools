#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <iostream>
#include <algorithm> 
#include <SFML/Graphics.hpp>
#include "gui_object.h"

class AppGui; // Declaracion para evitar imports circulares

class TextBox : public GUIObject {
    public: 
        TextBox(int width, int height, int x, int y, std::string fontPath, std::string placeholder, bool is_keyboard_owner);
        ~TextBox();

        void drawOnTarget(sf::RenderWindow* window) override;
        void mouseOverIt() override;
        void mouseNotOverIt() override;
        void mousePressed(AppGui* app) override;

        void setAsKeyboardOwner();
        void removeKeyboardOwnership();
        void receiveKeyboardInput(sf::Event event);

        std::string getContent();
        std::string getContentTrim();

    private:
        sf::RectangleShape* box;
        sf::Text* text_view;
        sf::Color bgColor;
        sf::Color fgColor;
        sf::Font font;

        std::string placeholder;
        std::string content;

        bool is_keyboard_owner;
        bool written;

        void clearTextBox();
};

#endif // BUTTON_H