#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <iostream>
#include <algorithm> 
#include <SFML/Graphics.hpp>
#include "gui_object.h"

using namespace std;

class AppGui; // Declaracion para evitar imports circulares

class TextBox : public GUIObject {
    public: 
        TextBox(
            int aWidth,
            int aHeight,
            int x,
            int y,
            sf::Font aFont,
            std::string aPlaceholder,
            bool aKeyboardOwnershipStatus);
        ~TextBox();

        void drawOnTarget(sf::RenderWindow* aWindow) override;
        void mouseOverIt() override;
        void mouseNotOverIt() override;
        void mousePressed(AppGui* anApp) override;

        void setAsKeyboardOwner();
        void removeKeyboardOwnership();
        void receiveKeyboardInput(int aKeyUnicode);

        string getContent();
        string getContentTrim();

    private:
        sf::RectangleShape* box;
        sf::Text* text_view;
        sf::CircleShape* circle_ownership;
        sf::Color bgColor;
        sf::Color fgColor;
        sf::Font font;
        string placeholder;
        string content;
        bool is_keyboard_owner;
        bool written;
        int charsPerBox;
 
        string fitTextInBox(string& aText);
        void clearTextBox();
};

#endif // BUTTON_H