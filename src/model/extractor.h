// Functionality >> Extractor
#ifndef EXTRACTOR_H
#define EXTRACTOR_H

// internal
#include "functionality.h"
#include <unordered_set>

class AppGui; 

class Extractor : public Functionality {
      public:             
            Extractor(AppGui* anApp, fs::path aSourceFolder, fs::path aDestinyFolder);
            void execute() override; 
      
      private:                  
            void copyFile(fs::path aFileToCopy);
            void registerNotCopiedFile(const fs::path& aNotCopiedFile);
            uint8_t isAllowedExtension(const string& anExtension);

            unordered_set<fs::path> copiedFiles;      
};

#endif 