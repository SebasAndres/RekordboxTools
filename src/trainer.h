// Functionality >> Trainer
#ifndef TRAINER_H
#define TRAINER_H

// external
#include <iostream>
#include <fstream>
#include <vector>
#include <essentia/essentia.h>
#include <essentia/algorithmfactory.h>
#include <essentia/scheduler/network.h>
#include <essentia/pool.h>

using namespace essentia;
using namespace essentia::standard;
using namespace std;

// internal
#include "functionality.h"

struct TrackMetadata{
      string trackId;
      float MFCCs;
      float chromaFeatures;
      float spectralCentroid;
      float tempo;
      string classification;
};

class Trainer : public Functionality {
      public:             
            Trainer(fs::path src, fs::path dst);
            ~Trainer();
            void execute() override; 

      private:
            AlgorithmFactory& factory;
            unique_ptr<Algorithm> mfcc;
            unique_ptr<Algorithm> chromaExtractor;
            unique_ptr<Algorithm> spectralCentroidExtractor;
            unique_ptr<Algorithm> tempoExtractor;
            TrackMetadata extractFeatures(fs::path filePath, string classification);
            void buildDataset(void);
};

#endif 