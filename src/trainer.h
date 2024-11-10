// Functionality >> Trainer
#ifndef TRAINER_H
#define TRAINER_H

// external
#include <vector>

// internal
#include "functionality.h"


struct TrackMetadata{
      string trackId;
      vector<float> vector;
      string classification;
};

class Trainer : public Functionality {
      public:             
            Trainer(fs::path src, fs::path dst);
            void execute() override; 

      private:
            vector<float> extractFeatures(fs::path filePath);
};

#endif 