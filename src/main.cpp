#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

// internal
#include "functionality.h"
#include "extractor.h"

using namespace std;

// Factory Method
Functionality* initializeFunctionality(uint8_t type, fs::path& source, fs::path& destiny){
      if (type)
            return new Extractor(source, destiny);  
      return NULL;          
}

int main(void){      

      cout << "Functionality: ";
      uint8_t f; cin >> f;

      try{
            cout << "* Source path: ";
            fs::path source; cin >> source;
            cout << "* Destiny path: ";
            fs::path destiny; cin >> destiny;

            Functionality* funct = initializeFunctionality(f, source, destiny);
            funct->execute();   
            delete funct;
      }
      catch(const std::invalid_argument& e){
            cout << endl;
            cout << "--------------------------------------------" << endl;
            cout << "ERROR | No se ejecutó la funcionalidad" << endl;
            cout << e.what() << endl;
            cout << "--------------------------------------------" << endl;
      }

      
}
