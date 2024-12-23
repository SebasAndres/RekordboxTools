#include <iostream>
#include <filesystem>

// GUI
#include "gui/app.h"

using namespace std;
namespace fs = filesystem;

int main(void){     
      AppGui app = AppGui(600, 500, "Rekordbox Tools");
      while (app.is_open()) {
            app.handle_events();
            app.render();
      }
      return 0;      
}
