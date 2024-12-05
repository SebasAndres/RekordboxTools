#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

// internal
#include "model/functionality.h"
#include "model/extractor.h"
#include "model/classifier_wrapper.h"

using namespace std;

// Factory Method
Functionality* setUpFunctionality(string type){
      if (type=="extract"){
            cout << "* Source path: "; fs::path source; cin >> source;
            cout << "* Destiny path: "; fs::path destiny; cin >> destiny;
            return new Extractor(source, destiny);  
      }
      else if (type == "classify"){
            cout << "* Source path: "; fs::path source; cin >> source;
            cout << "* Destiny path: "; fs::path destiny; cin >> destiny;
            return new ClassifierWrapper(source, destiny);        
      }
      return nullptr; 
}

int main(void){      

      cout << "Functionality: ";
      string typeOfFunctionality; cin >> typeOfFunctionality;

      try{
            Functionality* functionality = setUpFunctionality(typeOfFunctionality);
            if (functionality == nullptr) { throw::runtime_error("Invalid functionality selected"); }
            functionality->execute();   
            delete functionality;
      }
      catch(const std::runtime_error& e){
            cout << endl;
            cout << "----------------------------------------------------------------------------------------------------" << endl;
            cout << "ERROR | No se ejecutó la funcionalidad" << endl;
            cout << e.what() << endl;
            cout << "----------------------------------------------------------------------------------------------------" << endl;
      }

      
}
