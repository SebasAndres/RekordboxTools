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
    if (!buttonFont.loadFromFile("gui/fonts/Roboto/Roboto-Regular.ttf"))
        std::cerr << "Error: No se pudo cargar la fuente." << std::endl;

    // TEXTBOXS
    this->textboxWidth = aWidth/2.2;
    this->textboxHeight = 30;
    this->nextTextboxHorizontalPosition = this->dx_center(textboxWidth);
    this->nextTextboxVerticalPosition = aHeight * 0.40;
    this->textboxVerticalPadding = textboxHeight/3.5;
    this->textboxFontPath = "gui/fonts/Roboto/Roboto-Regular.ttf";
    if (!textboxFont.loadFromFile(textboxFontPath))
        std::cerr << "Error: No se pudo cargar la fuente." << std::endl;
}

int Designer::dx_center(int anObjWidth){ return (this->window_width-anObjWidth)/2; }

Logger* Designer::DesignGuiLogger(){
    Logger* res = new Logger(
        0.05*window_width,
        10,
        this->window_width*0.9,
        30,
        sf::Color::Black,
        sf::Color::Green,
        this->textboxFont,
        14
    );
    return res;
}

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