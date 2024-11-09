#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

// internal
#include "extractor.h"

using namespace std;

int main(void){      

      cout << "* Source path: ";
      fs::path source; cin >> source;
      cout << "* Destiny path: ";
      fs::path destiny; cin >> destiny;

      extractTracks(source, destiny);


}

