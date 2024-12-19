#include "functionality.h"
#include "../gui/app.h"

Functionality::Functionality(AppGui* anApp, fs::path aSourceFolder, fs::path aDestinyFolder){     
      if ((fs::exists(aSourceFolder)) && (fs::exists(aDestinyFolder))){
            this->sourceFolder = aSourceFolder;
            this->destinyFolder = aDestinyFolder;
            this->app = anApp;
            this->status = Status::RUNNABLE;
      }
      else {
            this->status=Status::INVALID_INPUT;
      }
}