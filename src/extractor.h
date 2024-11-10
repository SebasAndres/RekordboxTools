// extractor.h
#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

// internal
#include "defines.h"
#include "functionality.h"

class Extractor : public Functionality {
      public:             
            Extractor(fs::path src, fs::path dst);
            void execute() override; 
            uint8_t isAllowedExtension(const string& extension);

      private:
            fs::path* notCopiedFiles;
            uint32_t notCopiedCounter;
            uint32_t copiedCounter;

            fs::path getDestinyName(fs::path file2copy);
            void registerNotCopiedFile(const fs::path& not_copied_file);
};

#endif // EXTRACTOR_H