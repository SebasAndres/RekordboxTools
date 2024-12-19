#include "app.h"

std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    string ltrim = (start == std::string::npos) ? "" : s.substr(start);
    size_t end = ltrim.find_last_not_of(" \t\n\r\f\v");
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

void AppGui::load_background_image(){
    background_texture.loadFromFile("assets/img/studio.png");
    background_sprite.setTexture(background_texture);
    background_sprite.setScale(
        static_cast<float>(window_width) / background_texture.getSize().x,
        static_cast<float>(window_height) / background_texture.getSize().y
    );
}

void AppGui::initialize_text_boxs(){
    src_text_box = designer->DesignTextBox("Source folder", true);
    dst_text_box = designer->DesignTextBox("Destiny folder", false);

    this->keyboard_owner = src_text_box;

    gui_objects.push_back(src_text_box);
    gui_objects.push_back(dst_text_box);
}

void AppGui::initialize_buttons(){
    Button* extract_button = designer->DesignButton(
        "Extract",
        [](AppGui* app) {
            std::string src = trim(app->src_folder_text());
            std::string dst = trim(app->dst_folder_text());
            Extractor* extractor = new Extractor(app, src, dst);
            extractor->execute();          
        }
    );
    Button* classify_button = designer->DesignButton(
        "Classify",
        [](AppGui* app){
            std::string src = trim(app->src_folder_text());
            std::string dst = trim(app->dst_folder_text());
            ClassifierWrapper* classifier = new ClassifierWrapper(app, src, dst);
            classifier->execute();          
        }
    );

    gui_objects.push_back(extract_button);
    gui_objects.push_back(classify_button);
}

AppGui::AppGui(int aWindowWidth, int aWindowHeight, string aTitle){
    this->window_width = aWindowWidth;
    this->window_height = aWindowHeight;
    this->title = aTitle;
    this->window = new sf::RenderWindow(sf::VideoMode(aWindowWidth, aWindowHeight), aTitle, sf::Style::Close);   
    this->window->setPosition(sf::Vector2i(100, 100));
    this->designer = new Designer(aWindowWidth, aWindowHeight);
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

std::string AppGui::src_folder_text(){
    return this->src_text_box->getContent();    
}

std::string AppGui::dst_folder_text(){
    return this->dst_text_box->getContent();    
}