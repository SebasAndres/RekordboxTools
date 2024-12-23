#include "button.h"
#include "app.h"

bool isLightColored(sf::Color aColor){
    float brightness = 0.299f * aColor.r + 0.587f * aColor.g + 0.114f * aColor.b;
    return brightness > 128.0f;
}

Button::Button(
    int width,
    int height,
    int x,
    int y,
    sf::Color bgColor,
    sf::Font aFont,
    string text,
    function<void(AppGui*)> onClickFunc)      
    : onClick(onClickFunc), bgColor(bgColor) {

    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    this->font = aFont;

    box = new sf::RectangleShape(sf::Vector2f(width, height));
    box->setPosition(x, y);
    box->setFillColor(bgColor);

    text_view = new sf::Text();
    text_view->setFont(this->font);
    text_view->setString(text);
    text_view->setCharacterSize(height/3.7);
    if (isLightColored(this->bgColor)){
        fgColor = sf::Color::Black;
    }
    else {
        fgColor = sf::Color::White;        
    }
    text_view->setFillColor(fgColor); 
    text_view->setPosition(x + 10, y + 10); 
}

Button::~Button() {
    delete box;
    delete text_view;
}

void Button::drawOnTarget(sf::RenderWindow* aWindow){
    aWindow->draw(*box);    
    aWindow->draw(*text_view);
}

void Button::mouseOverIt(){
    sf::Color coloredBg = bgColor;
    coloredBg.a = std::max(coloredBg.a - 50, 0);
    sf::Color coloredFg = sf::Color::White;
    if (isLightColored(coloredBg)){
        coloredFg = sf::Color::Black;
    }
    box->setFillColor(coloredBg);
    text_view->setFillColor(coloredFg);
}

void Button::mouseNotOverIt(){
    box->setFillColor(bgColor);
    text_view->setFillColor(fgColor);
}

void Button::mousePressed(AppGui* app){
    thread([this, app]() {
        this->onClick(app);
    }).detach();
}

