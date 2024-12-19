#include "text_box.h"
#include "app.h"

#define DELETE_KEY_UNICODE 8
#define ENTER_KEY_UNICODE 13

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

    if (!font.loadFromFile(fontPath))
        std::cerr << "Error: No se pudo cargar la fuente." << std::endl;

    int charSize = 20;

    box = new sf::RectangleShape(sf::Vector2f(width, height));
    box->setPosition(x, y);
    box->setFillColor(sf::Color::White);
    charsPerBox = width/charSize * 2;

    text_view = new sf::Text();
    text_view->setFont(font);
    text_view->setString(placeholder);
    text_view->setCharacterSize(charSize);
    text_view->setPosition(x + 5, y + 3); 
    text_view->setFillColor(sf::Color(128,128,128));

    circle_ownership = new sf::CircleShape(5);
    circle_ownership->setFillColor(sf::Color::Green);
    circle_ownership->setPosition(x - 15, y + height / 2 - 5); 

    content = "";
}

TextBox::~TextBox() {
    delete box;
    delete text_view;
    delete circle_ownership;
}

void TextBox::drawOnTarget(sf::RenderWindow* aWindow){
    aWindow->draw(*box);    
    aWindow->draw(*text_view);
    if (is_keyboard_owner)
        aWindow->draw(*circle_ownership);
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
    this->is_keyboard_owner = true;
}

void TextBox::removeKeyboardOwnership(){
    this->is_keyboard_owner = false;
}

std::string TextBox::fitTextInBox(string& aText){
    int textLength = aText.length();
    int firstDisplayedCharacter = aText.length()-charsPerBox;
    int begginAt = std::max(0, firstDisplayedCharacter);
    return aText.substr(begginAt, textLength);
}

void TextBox::receiveKeyboardInput(int aKeyUnicode){    
    if (aKeyUnicode == DELETE_KEY_UNICODE) {
        if (content.length() > 0){ 
            content.pop_back();
        }
        if (content.length() == 0){ clearTextBox(); return; }
    }    
    else {
        content += static_cast<char>(aKeyUnicode);
        text_view->setFillColor(sf::Color::Black);
    }

    string displayableContent = fitTextInBox(content);
    text_view->setString(displayableContent);
}

void TextBox::clearTextBox(){
    text_view->setString(placeholder);
    text_view->setFillColor(sf::Color(128,128,128));   
}

std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    string ltrim = (start == std::string::npos) ? "" : s.substr(start);
    size_t end = ltrim.find_last_not_of(" \t\n\r\f\v");
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string TextBox::getContent(){
    return content;
}

std::string TextBox::getContentTrim(){
    return trim(content);   
}