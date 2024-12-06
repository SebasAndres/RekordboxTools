#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "button.h"

using namespace std;

class AppGui {
    public:
        AppGui(int width, int height, string title);
        ~AppGui();

        void handle_events();
        void render();
        bool is_open();

    private:
        int window_width;
        int window_height;
        string title;
        sf::Color background_color;
        sf::RenderWindow* window;
        
        vector<GUIObject*> gui_objects;
 
        string inputText; // to delete

        void handle_text_entered(sf::Event event);
        void handle_mouse_movement(int x, int y);
        void handle_mouse_pressed(sf::Event::MouseButtonEvent button);

        void initialize_buttons();
};
#endif