#include "functionality.h"
#include "../gui/app.h"

Functionality::Functionality(AppGui* anApp, fs::path aSourceFolder, fs::path aDestinyFolder){     
      this->app = anApp;
      if ((fs::exists(aSourceFolder)) && (fs::exists(aDestinyFolder))){
            this->sourceFolder = aSourceFolder;
            this->destinyFolder = aDestinyFolder;
            this->status = Status::RUNNABLE;
      }
      else {
            this->status=Status::INVALID_INPUT;
            cout << aSourceFolder;
            cout << endl;
            cout << aDestinyFolder;
            cout << endl;
      }
}