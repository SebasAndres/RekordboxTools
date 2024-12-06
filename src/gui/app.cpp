#include "app.h"

AppGui::AppGui(int width, int height, string title){

    this->width = width;
    this->height = height;
    this->title = title;
    this->background_color = sf::Color::Black; 
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), title);   
	
    sf::Font font;
    font.loadFromFile("fonts/Roboto-Black.ttf");
	inputText = "";

    Button* extract_button = new Button(
                                200, // width
                                100, // height 
                                50,  // x
                                50,  // y
                                sf::Color::White,
                                []() {
                                    cout << "hola" << endl;
                                }
                            );

    Button* bt2 = new Button(
                                200, // width
                                100, // height 
                                400,  // x
                                50,  // y
                                sf::Color::Green,
                                []() {
                                    cout << "hola" << endl;
                                }
                            );

    gui_objects.push_back(extract_button);
    gui_objects.push_back(bt2);
}

void AppGui::handle_text_entered(sf::Event event){
        if (event.text.unicode == 8 && this->inputText.length() > 0) {
        inputText.pop_back();
    } 
    else if (event.text.unicode == 13) {
        std::cout << "Texto ingresado: " << inputText << std::endl;
    } 
    else if (event.text.unicode < 128) {
        inputText += static_cast<char>(event.text.unicode);
    }
}

void AppGui::handle_mouse_movement(int x, int y){
    // Por cada objeto de la APP ver si está sobre el y reaccionar
    for(GUIObject* obj: this->gui_objects){
        if (obj->includesPoint(x,y)) { obj->mouseOverIt(); }
        else { obj->mouseNotOverIt(); }
    }
}

void AppGui::handle_mouse_pressed(sf::Event::MouseButtonEvent button){
    for(GUIObject* obj: this->gui_objects){
        if (obj->includesPoint(button.x,button.y)) { obj->mousePressed(); }
    }
}

void AppGui::handle_events(){

    sf::Event event;	
    while (this->window->pollEvent(event)) {
		switch (event.type) {
 
            case sf::Event::Closed: 
                this->window->close();
                break;

            case sf::Event::TextEntered:
                handle_text_entered(event);
                break;

            case sf::Event::MouseMoved: 
                handle_mouse_movement(event.mouseMove.x, event.mouseMove.y);
                break;

            case sf::Event::MouseButtonPressed: 
                handle_mouse_pressed(event.mouseButton);
                break;
		}
    }
}

void AppGui::render(){
    window->clear();
    for(GUIObject* obj: gui_objects){
        window->draw(obj->getDrawable());
    }
    window->display();
}

bool AppGui::is_open(){
    return window->isOpen();
}