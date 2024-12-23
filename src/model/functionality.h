// Parent functionality class
#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include "defines.h"

class AppGui;

using namespace std;
namespace fs = filesystem;

enum class Status {
    RUNNABLE,
    INVALID_INPUT,
    PROCESSING,
    COMPLETED
};

class Functionality {
      public:
            Functionality(AppGui* anApp, fs::path aSourceFolder, fs::path aDestinyFolder);
            virtual ~Functionality() = default; 
            virtual void execute() = 0; 

      protected:
            fs::path sourceFolder;
            fs::path destinyFolder;
            AppGui* app;
            Status status;
};

#endif
