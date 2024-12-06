#include "button.h"

Button::Button(int width, int height, int x, int y, sf::Color color, void (*onClickFunc)()) 
    : onClick(onClickFunc) {

    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    
    this->bgColor = color;

    sf::RectangleShape* rect;
    rect = new sf::RectangleShape(sf::Vector2f(width, height));
    rect->setPosition(x, y);
    rect->setFillColor(color);

    shape = rect;
}

void Button::mouseOverIt(){
    sf::Color coloredBg = bgColor;
    coloredBg.b = std::max(coloredBg.b + 100, 255);

    sf::RectangleShape* rectShape = dynamic_cast<sf::RectangleShape*>(shape);
    if (rectShape) {
        rectShape->setFillColor(coloredBg);
    }
}

void Button::mouseNotOverIt(){
    sf::RectangleShape* rectShape = dynamic_cast<sf::RectangleShape*>(shape);
    if (rectShape) {
        rectShape->setFillColor(this->bgColor);
    }
}

void Button::mousePressed(){
    onClick();
}