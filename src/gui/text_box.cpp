#include "text_box.h"
#include "app.h"

TextBox::TextBox(
    int width,
    int height,
    int x,
    int y,
    std::string fontPath,
    std::string placeholder,
    bool is_keyboard_owner){

    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;

    this->placeholder = placeholder;
    this->is_keyboard_owner = is_keyboard_owner;

    this->written = false;

    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error: No se pudo cargar la fuente." << std::endl;
    }

    box = new sf::RectangleShape(sf::Vector2f(width, height));
    box->setPosition(x, y);
    box->setFillColor(sf::Color::White);

    text_view = new sf::Text();
    text_view->setFont(font);
    text_view->setString(placeholder);
    text_view->setCharacterSize(20);
    text_view->setPosition(x + 10, y + 3); 

    text_view->setFillColor(sf::Color(128,128,128));
    content = "";
}

TextBox::~TextBox() {
    delete box;
    delete text_view;
}

void TextBox::drawOnTarget(sf::RenderWindow* aWindow){
    aWindow->draw(*box);    
    aWindow->draw(*text_view);
}

void TextBox::mouseOverIt() {
};

void TextBox::mouseNotOverIt(){
};

void TextBox::mousePressed(AppGui* app){
    setAsKeyboardOwner();
    app->set_keyboard_ownership_to(this);
};

void TextBox::setAsKeyboardOwner(){
    this->content = "";
    text_view->setString(content);
}

void TextBox::removeKeyboardOwnership(){
    this->is_keyboard_owner = false;
}

void TextBox::receiveKeyboardInput(sf::Event event){
    if (event.text.unicode == 8) {
        if (content.length() > 0){ content.pop_back(); }
        if (content.length() == 0){ clearTextBox(); return; }
    }
    else if (event.text.unicode == 13) {
        std::cout << "Texto ingresado: " << content << std::endl;
    } 
    else if (event.text.unicode < 128) {
        content += static_cast<char>(event.text.unicode);
        text_view->setFillColor(sf::Color::Black);
    }
    text_view->setString(content);
}

void TextBox::clearTextBox(){
    text_view->setString(placeholder);
    text_view->setFillColor(sf::Color(128,128,128));   
}

std::string TextBox::getContent(){
    return content;
}