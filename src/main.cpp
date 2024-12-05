#include <iostream>
#include <filesystem>

// model
#include "model/functionality.h"
#include "model/extractor.h"
#include "model/classifier_wrapper.h"

// GUI
#include <SFML/Graphics.hpp>

using namespace std;
namespace fs = filesystem;

int main(void){     

      // Main windows
      sf::RenderWindow window(sf::VideoMode(800, 600), "Rekordbox Tool \U0001F60A");

      // Render window loop
      while (window.isOpen()) {

            // Handle events & update
            sf::Event event;
            while (window.pollEvent(event)) {
                  if (event.type == sf::Event::Closed)
                  window.close();
            }

            // Render again
            window.clear(sf::Color::White);
            window.display();
      }

      return 0;      
}
