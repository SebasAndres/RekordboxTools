#include "app.h"

#define ESCAPE_KEY_UNICODE 9

template <typename T>
size_t indexOf(T* item, const vector<T*>& vec) {
    auto it = std::find(vec.begin(), vec.end(), item);
    if (it != vec.end()) {
        return std::distance(vec.begin(), it);
    } else {
        throw std::runtime_error("Item not found in vector");
    }
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
    source_text_box = designer->DesignTextBox("Source folder", true);
    destiny_text_box = designer->DesignTextBox("Destiny folder", false);
    this->keyboard_owner = source_text_box;
    gui_objects.push_back(source_text_box);
    gui_objects.push_back(destiny_text_box);
    keyboard_handlers.push_back(source_text_box);
    keyboard_handlers.push_back(destiny_text_box);
}

void AppGui::check_and_execute(function<void()> aFunction){
    if (this->able_to_run_functionality){
        this->able_to_run_functionality = false;
        aFunction();
        this->able_to_run_functionality = true;
    }
    else {
        this->notify("Estoy ocupado bro");
    }
}

void AppGui::initialize_buttons(){
    Button* extract_button = designer->DesignButton(
        "Extract",
        [](AppGui* app) {
            app->check_and_execute(
                [app](){
                    std::string src = app->get_source_folder();
                    std::string dst = app->get_destiny_folder();
                    Extractor* extractor = new Extractor(app, src, dst);
                    extractor->execute();      
                }
            );
        }
    );
    Button* classify_button = designer->DesignButton(
        "Classify",
        [](AppGui* app){
            app->check_and_execute(
                [app](){
                    std::string src = app->get_source_folder();
                    std::string dst = app->get_destiny_folder();
                    ClassifierWrapper* classifier = new ClassifierWrapper(app, src, dst);
                    classifier->execute();          
                }
            );
        }
    );
    gui_objects.push_back(extract_button);
    gui_objects.push_back(classify_button);
}

void AppGui::initialize_gui_logger(){
    this->gui_logger = designer->DesignGuiLogger();
    this->gui_logger->setMessage("🧪");
    gui_objects.push_back(gui_logger);
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
    initialize_gui_logger();
    this->able_to_run_functionality = true;
}

AppGui::~AppGui() {
    delete window; 
    delete designer;
    for (auto obj : gui_objects)
        delete obj; 
}

void AppGui::notify(string aMessage){
    cout << aMessage << endl;
    gui_logger->setMessage(aMessage);
}

void AppGui::set_keyboard_ownership_to(TextBox* aTextBox){
    this->keyboard_owner->removeKeyboardOwnership();
    aTextBox->setAsKeyboardOwner();
    this->keyboard_owner = aTextBox;
    this->idx_current_keyboard_owner = indexOf(aTextBox, keyboard_handlers);
}

void AppGui::next_keyboard_owner(){
    size_t next_owner_index = (idx_current_keyboard_owner + 1) % keyboard_handlers.size();
    TextBox* next_owner = keyboard_handlers[next_owner_index];
    set_keyboard_ownership_to(next_owner);
}

void AppGui::handle_text_entered(sf::Event event){
    int keyPressed = event.text.unicode;
    if (keyPressed == ESCAPE_KEY_UNICODE) { next_keyboard_owner(); }
    else { this->keyboard_owner->receiveKeyboardInput(keyPressed); }
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