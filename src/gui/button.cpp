#include "button.h"

bool isLightColored(sf::Color aColor){
    float brightness = 0.299f * aColor.r + 0.587f * aColor.g + 0.114f * aColor.b;
    return brightness > 128.0f;
}

Button::Button(int width, int height, int x, int y, sf::Color bgColor, std::string fontPath, std::string text, void (*onClickFunc)()) 
    : onClick(onClickFunc), bgColor(bgColor) {

    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;

    box = new sf::RectangleShape(sf::Vector2f(width, height));
    box->setPosition(x, y);
    box->setFillColor(bgColor);

    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error: No se pudo cargar la fuente ../fonts/Roboto-Black.ttf" << std::endl;
        // Manejar el error de carga de la fuente aquí
    }

    btText = new sf::Text();
    btText->setFont(font);
    btText->setString(text);
    btText->setCharacterSize(24);

    if (isLightColored(this->bgColor)){
        fgColor = sf::Color::Black;
    }
    else {
        fgColor = sf::Color::White;        
    }

    btText->setFillColor(fgColor); 
    btText->setPosition(x + 10, y + 10); 
}

Button::~Button() {
    delete box;
    delete btText;
}

void Button::drawOnTarget(sf::RenderWindow* aWindow){
    aWindow->draw(*box);    
    aWindow->draw(*btText);
}

void Button::mouseOverIt(){
    sf::Color coloredBg = bgColor;
    coloredBg.a = std::max(coloredBg.a - 50, 0);
    sf::Color coloredFg = sf::Color::White;
    if (isLightColored(coloredBg)){
        coloredFg = sf::Color::Black;
    }
    box->setFillColor(coloredBg);
    btText->setFillColor(coloredFg);
}

void Button::mouseNotOverIt(){
    box->setFillColor(bgColor);
    btText->setFillColor(fgColor);
}

void Button::mousePressed(){
    onClick();
}