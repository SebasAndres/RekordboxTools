#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

// internal
#include "functionality.h"
#include "extractor.h"
#include "trainer.h"

using namespace std;

// Factory Method
Functionality* setUpFunctionality(string type){
      if (type=="extract"){
            cout << "* Source path: "; fs::path source; cin >> source;
            cout << "* Destiny path: "; fs::path destiny; cin >> destiny;
            return new Extractor(source, destiny);  
      }
      else if (type == "train"){
            cout << "* Dataset path: "; fs::path source; cin >> source;
            cout << "* Results path: "; fs::path destiny; cin >> destiny;
            return new Trainer(source, destiny);
      } 
      else {
            cout << "* Algun dato que necesite: ";
            return NULL; // hacer algo
      }
      return NULL;          
}

int main(void){      

      cout << "Functionality: ";
      string typeOfFunctionality; cin >> typeOfFunctionality;

      try{
            Functionality* functionality = setUpFunctionality(typeOfFunctionality);
            if (functionality == NULL) { throw::runtime_error("Invalid functionality selected"); }
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
