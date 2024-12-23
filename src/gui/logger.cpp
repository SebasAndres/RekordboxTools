#include "logger.h"

Logger::Logger(
    int x,
    int y,
    int width,
    int height,
    sf::Color aBackgroundColor,
    sf::Color aFontColor,
    sf::Font aFont,
    int textSize){

    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;

    this->bgColor = aBackgroundColor;
    this->fontColor = aFontColor;    
    this->font = aFont;

    this->box = new sf::RectangleShape(sf::Vector2f(width, height));
    this->box->setPosition(x, y);
    this->box->setFillColor(aBackgroundColor);

    this->text_view = new sf::Text();
    this->text_view->setFont(font);
    this->text_view->setCharacterSize(textSize);
    this->text_view->setPosition(x + 5, y + 3); 
    this->text_view->setFillColor(aFontColor);
}

Logger::~Logger(){
    delete box;
    delete text_view;   
}

void Logger::setMessage(string aText){
    this->text_view->setString(aText);
}

void Logger::drawOnTarget(sf::RenderWindow* aTarget){
    aTarget->draw(*box);    
    aTarget->draw(*text_view);
}