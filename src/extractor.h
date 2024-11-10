// Functionality >> Extractor
#ifndef EXTRACTOR_H
#define EXTRACTOR_H

// internal
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

#endif 