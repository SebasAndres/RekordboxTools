// MiClase.h
#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

class Functionality {
      public:
            Functionality(fs::path src, fs::path dst);
            virtual ~Functionality() = default; // Destructor virtual
            virtual void execute() = 0; // Método puramente virtual  
            
      protected:
            fs::path src;
            fs::path dst;
};

#endif
