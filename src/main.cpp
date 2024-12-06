#include <iostream>
#include <filesystem>

// model
#include "model/functionality.h"
#include "model/extractor.h"
#include "model/classifier_wrapper.h"

// GUI
#include "gui/app.h"

using namespace std;
namespace fs = filesystem;

int main(void){     
      AppGui app = AppGui(800, 600, "Rekordbox Tools");
      while (app.is_open()) {
            app.handle_events();
            app.render();
      }
      return 0;      
}
