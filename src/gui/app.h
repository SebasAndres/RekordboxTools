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
        std::string get_source_folder();
        std::string get_destiny_folder();

        bool ableToRun();
        void enableFunctionalities();
        void disableFunctionalities();

        void notify(string aMessage);

    private:
        int window_width;
        int window_height;
        string title;
        sf::RenderWindow* window;

        Designer* designer;
        vector<GUIObject*> gui_objects;

        TextBox* keyboard_owner;
        TextBox* source_text_box;
        TextBox* destiny_text_box;

        sf::Texture background_texture;
        sf::Sprite background_sprite;      

        bool able_to_run_functionality;

        // Handlers
        void handle_text_entered(sf::Event anEvent);
        void handle_mouse_movement(int x, int y);
        void handle_mouse_pressed(sf::Event::MouseButtonEvent aMouseButton);

        // VISUAL
        void load_background_image();
        void initialize_buttons();
        void initialize_text_boxs();
};
#endif