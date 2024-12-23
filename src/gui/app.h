#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cctype> 
#include "string.h"

#include "../model/extractor.h"
#include "../model/classifier_wrapper.h"

#include "button.h"
#include "text_box.h"
#include "designer.h"

using namespace std;

class AppGui {
    public:
        AppGui(int width, int height, string aTitle);
        ~AppGui();

        void handle_events();
        void render();
        bool is_open();

        void set_keyboard_ownership_to(TextBox* aTextbox);
        void next_keyboard_owner();       
        std::string get_source_folder();
        std::string get_destiny_folder();

        void notify(string aMessage);

        void check_and_execute(function<void()> aClosure);
        bool able_to_run_functionality;

    private:
        int window_width;
        int window_height;
        string title;
        sf::RenderWindow* window;

        Designer* designer;
        vector<GUIObject*> gui_objects;

        int idx_current_keyboard_owner;
        TextBox* keyboard_owner;
        vector<TextBox*> keyboard_handlers;

        TextBox* source_text_box;
        TextBox* destiny_text_box;

        sf::Texture background_texture;
        sf::Sprite background_sprite;      

        Logger* gui_logger;

        // Handlers
        void handle_text_entered(sf::Event anEvent);
        void handle_mouse_movement(int x, int y);
        void handle_mouse_pressed(sf::Event::MouseButtonEvent aMouseButton);

        // VISUAL
        void load_background_image();
        void initialize_buttons();
        void initialize_text_boxs();
        void initialize_gui_logger();
};
#endif