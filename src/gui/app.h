#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../model/extractor.h"

#include "button.h"
#include "text_box.h"

using namespace std;

class AppGui {
    public:
        AppGui(int width, int height, string title);
        ~AppGui();

        void handle_events();
        void render();
        bool is_open();

        void set_keyboard_ownership_to(TextBox* textbox);

    private:
        int window_width;
        int window_height;
        string title;
        sf::Color background_color;
        sf::RenderWindow* window;
        vector<GUIObject*> gui_objects;
        
        TextBox* src_text_box;
        TextBox* dst_text_box;

        TextBox* keyboard_owner;

        // Handlers
        void handle_text_entered(sf::Event event);
        void handle_mouse_movement(int x, int y);
        void handle_mouse_pressed(sf::Event::MouseButtonEvent button);

        // VISUAL
        void initialize_buttons();
        void initialize_text_boxs();
};
#endif