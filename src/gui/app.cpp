#include "app.h"

int computeButtonWidth(int window_width, int window_height){
    return window_width/3;
}

int computeButtonHeight(int window_width, int window_height){
    return window_height/7;
}

int dx_CENTER(int window_width, int guiObject_width){
    return (window_width-guiObject_width)/2;
}

void AppGui::initialize_text_boxs(){
    src_text_box = new TextBox(200,30,200,200,"gui/fonts/Roboto/Roboto-Regular.ttf","Source folder", true);
    dst_text_box = new TextBox(200,30,200,240,"gui/fonts/Roboto/Roboto-Regular.ttf","Destiny folder", false);

    this->keyboard_owner = src_text_box;

    gui_objects.push_back(src_text_box);
    gui_objects.push_back(dst_text_box);
}

void AppGui::initialize_buttons(){
    int BUTTON_WIDTH = computeButtonWidth(window_width, window_height);
    int dx_BUTTON = dx_CENTER(window_width, BUTTON_WIDTH);
    int BUTTON_HEIGHT = computeButtonHeight(window_width, window_height);
    int y0_BUTTON_POSITION = window_height * 0.6;
    int pady_BUTTONS = BUTTON_HEIGHT/4;

    Button* extract_button = new Button(
                    BUTTON_WIDTH, // width
                    BUTTON_HEIGHT, // height 
                    dx_BUTTON,  // x
                    y0_BUTTON_POSITION,  // y
                    sf::Color::Blue,
                    "gui/fonts/Roboto/Roboto-Regular.ttf",
                    "Extract",
                    [srcTextBox=src_text_box, dstTextBox=dst_text_box]() {
                        cout << "> extrayendo" << endl;
                        string src = srcTextBox->getContent();
                        string dst = dstTextBox->getContent();
                        Extractor* extractor = new Extractor(src, dst);
                        extractor->execute();          
                    }
                );

    Button* classify_button = new Button(
                    BUTTON_WIDTH, // width
                    BUTTON_HEIGHT, // height 
                    dx_BUTTON,  // x
                    y0_BUTTON_POSITION+BUTTON_HEIGHT+pady_BUTTONS,  // y
                    sf::Color::Blue,
                    "gui/fonts/Roboto/Roboto-Regular.ttf",
                    "Classify",
                    []() {
                        cout << "> clasificando" << endl;
                    }
                );

    gui_objects.push_back(extract_button);
    gui_objects.push_back(classify_button);
}

AppGui::AppGui(int width, int height, string title){

    this->window_width = width;
    this->window_height = height;
    this->title = title;
    this->background_color = sf::Color::Black; 
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Close);   
   
    initialize_text_boxs();
    initialize_buttons();
}

AppGui::~AppGui() {
    delete window; 
    for (auto obj : gui_objects) {
        delete obj; 
    }
}

void AppGui::set_keyboard_ownership_to(TextBox* textBox){
    this->keyboard_owner->removeKeyboardOwnership();
    this->keyboard_owner = textBox;
}

void AppGui::handle_text_entered(sf::Event event){
    this->keyboard_owner->receiveKeyboardInput(event);
}

void AppGui::handle_mouse_movement(int x, int y){
    // Por cada objeto de la APP ver si está sobre él y reaccionar
    for(GUIObject* obj: this->gui_objects){
        if (obj->includesPoint(x,y)) { obj->mouseOverIt(); }
        else { obj->mouseNotOverIt(); }
    }
}

void AppGui::handle_mouse_pressed(sf::Event::MouseButtonEvent button){
    for(GUIObject* obj: this->gui_objects){
        if (obj->includesPoint(button.x,button.y)) { obj->mousePressed(this); }
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
        obj->drawOnTarget(this->window);
    }
    window->display();
}

bool AppGui::is_open(){
    return window->isOpen();
}