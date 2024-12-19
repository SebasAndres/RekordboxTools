#include "designer.h"

Designer::Designer(int aWidth, int aHeight){

    this->window_width = aWidth;
    this->window_height = aHeight;    

    // BUTTONS
    this->buttonWidth = aWidth/3;
    this->buttonHeight = aHeight/7;
    this->nextButtonHorizontalPosition = this->dx_center(buttonWidth);
    this->nextButtonVerticalPosition = aHeight * 0.6;
    this->buttonVerticalPadding = buttonHeight/4;
    this->buttonFont = "gui/fonts/Roboto/Roboto-Regular.ttf";

    // TEXTBOXS
    this->textboxWidth = aWidth/3;
    this->textboxHeight = 30;
    this->nextTextboxHorizontalPosition = this->dx_center(textboxWidth);
    this->nextTextboxVerticalPosition = aHeight * 0.40;
    this->textboxVerticalPadding = textboxHeight/3.5;
    this->textboxFont = "gui/fonts/Roboto/Roboto-Regular.ttf";
}

int Designer::dx_center(int anObjWidth){ return (this->window_width-anObjWidth)/2; }

TextBox* Designer::DesignTextBox(string aText, bool aKeyboardOwnership){
    TextBox* res =  new TextBox(
        textboxWidth,
        textboxHeight,
        nextTextboxHorizontalPosition,
        nextTextboxVerticalPosition,
        textboxFont,
        aText,
        aKeyboardOwnership
    );
    nextTextboxVerticalPosition += textboxHeight + textboxVerticalPadding;
    return res;
}

Button* Designer::DesignButton(string aText, function<void(AppGui*)> aFunction){
    Button* res = new Button(
        buttonWidth,
        buttonHeight,
        nextButtonHorizontalPosition,
        nextButtonVerticalPosition,
        sf::Color::Blue,
        buttonFont,
        aText,
        aFunction
    );
    nextButtonVerticalPosition += buttonHeight + buttonVerticalPadding;
    return res;
}