// Functionality >> Extractor
#ifndef EXTRACTOR_H
#define EXTRACTOR_H

// internal
#include "functionality.h"
#include <unordered_set>

class Extractor : public Functionality {
      public:             
            Extractor(fs::path src, fs::path dst);
            void execute() override; 
            uint8_t isAllowedExtension(const string& extension);

      private:
            unordered_set<fs::path> copiedFiles;
            uint32_t copiedCounter;
            fs::path* notCopiedFiles;
            uint32_t notCopiedCounter;
            
            fs::path getDestinyName(fs::path file2copy);
            void registerNotCopiedFile(const fs::path& not_copied_file);
};

#endif 