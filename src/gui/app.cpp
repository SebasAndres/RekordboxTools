#include "app.h"

void AppGui::load_background_image(){
    background_texture.loadFromFile("assets/img/studio.png");
    background_sprite.setTexture(background_texture);
    background_sprite.setScale(
        static_cast<float>(window_width) / background_texture.getSize().x,
        static_cast<float>(window_height) / background_texture.getSize().y
    );
}

void AppGui::initialize_text_boxs(){
    source_text_box = designer->DesignTextBox("Source folder", true);
    destiny_text_box = designer->DesignTextBox("Destiny folder", false);
    this->keyboard_owner = source_text_box;
    gui_objects.push_back(source_text_box);
    gui_objects.push_back(destiny_text_box);
}

void AppGui::initialize_buttons(){
    Button* extract_button = designer->DesignButton(
        "Extract",
        [](AppGui* app) {
            if (app->ableToRun()){
                app->disableFunctionalities();
                std::string src = app->get_source_folder();
                std::string dst = app->get_destiny_folder();
                Extractor* extractor = new Extractor(app, src, dst);
                extractor->execute();      
                app->enableFunctionalities();    
            }
            else {
                app->notify("Estoy ocupado bro");
            }
        }
    );
    Button* classify_button = designer->DesignButton(
        "Classify",
        [](AppGui* app){
            if (app->ableToRun()){
                app->disableFunctionalities();
                std::string src = app->get_source_folder();
                std::string dst = app->get_destiny_folder();
                ClassifierWrapper* classifier = new ClassifierWrapper(app, src, dst);
                classifier->execute();          
                app->enableFunctionalities();    
            }
            else {
                app->notify("Estoy ocupado bro");
            }
        }
    );

    gui_objects.push_back(extract_button);
    gui_objects.push_back(classify_button);
}

void AppGui::enableFunctionalities(){
    this->able_to_run_functionality = true;
}

void AppGui::disableFunctionalities(){
    this->able_to_run_functionality = false;
}

bool AppGui::ableToRun(){
    return this->able_to_run_functionality;
}

AppGui::AppGui(int aWindowWidth, int aWindowHeight, string aTitle){
    this->window_width = aWindowWidth;
    this->window_height = aWindowHeight;
    this->title = aTitle;
    this->window = new sf::RenderWindow(sf::VideoMode(aWindowWidth, aWindowHeight), aTitle, sf::Style::Close);   
    this->window->setPosition(sf::Vector2i(100, 100));
    this->designer = new Designer(aWindowWidth, aWindowHeight);
    enableFunctionalities();
    load_background_image();
    initialize_text_boxs();
    initialize_buttons();
}

AppGui::~AppGui() {
    delete window; 
    delete designer;
    for (auto obj : gui_objects)
        delete obj; 
}

void AppGui::notify(string aMessage){
    cout << aMessage << endl;
}

void AppGui::set_keyboard_ownership_to(TextBox* textBox){
    this->keyboard_owner->removeKeyboardOwnership();
    this->keyboard_owner = textBox;
}

void AppGui::handle_text_entered(sf::Event event){
    this->keyboard_owner->receiveKeyboardInput(event);
}

void AppGui::handle_mouse_movement(int x, int y){
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
    window->draw(background_sprite);
    for(GUIObject* obj: gui_objects)
        obj->drawOnTarget(this->window);
    window->display();
}

bool AppGui::is_open(){
    return window->isOpen();
}

std::string AppGui::get_source_folder(){
    return this->source_text_box->getContentTrim();    
}

std::string AppGui::get_destiny_folder(){
    return this->destiny_text_box->getContentTrim();    
}