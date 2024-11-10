#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

// internal
#include "functionality.h"
#include "extractor.h"
#include "trainer.h"

using namespace std;

// Factory Method
Functionality* setUpFunctionality(string type, fs::path& source, fs::path& destiny){
      if (type=="extract")
            return new Extractor(source, destiny);  
      else if (type == "train")
            return new Trainer(source, destiny);
      return NULL;          
}

int main(void){      

      cout << "Functionality: ";
      string typeOfFunctionality; cin >> typeOfFunctionality;

      try{
            cout << "* Source path: ";
            fs::path source; cin >> source;
            cout << "* Destiny path: ";
            fs::path destiny; cin >> destiny;

            Functionality* functionality = setUpFunctionality(typeOfFunctionality, source, destiny);
            functionality->execute();   
            delete functionality;
      }
      catch(const std::invalid_argument& e){
            cout << endl;
            cout << "--------------------------------------------" << endl;
            cout << "ERROR | No se ejecutó la funcionalidad" << endl;
            cout << e.what() << endl;
            cout << "--------------------------------------------" << endl;
      }

      
}
