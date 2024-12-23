#ifndef DESIGNER_H
#define DESIGNER_H

#include <iostream>
#include "string"

#include "text_box.h"
#include "button.h"
#include "logger.h"

using namespace std;

class Designer {
    public: 
        Designer(int aWindowWidth, int aWindowHeight);

        TextBox* DesignTextBox(string aText, bool aKeyboardOwnershipStatus);
        Button* DesignButton(string aText,  function<void(AppGui*)> aFunction);
        Logger* DesignGuiLogger();

    private:
        int window_width;
        int window_height;

        int dx_center(int anObjWidth);

        // BUTTONS
        int buttonWidth;
        int buttonHeight;
        int nextButtonHorizontalPosition;
        int buttonVerticalPadding;
        sf::Font buttonFont;
        int nextButtonVerticalPosition;

        // TEXTBOXS
        int textboxWidth;
        int textboxHeight;
        int nextTextboxHorizontalPosition;
        int textboxVerticalPadding;
        string textboxFontPath;
        sf::Font textboxFont;
        int nextTextboxVerticalPosition;
};

#endif