#ifndef CLASSIFIER_WRAPPER_H
#define CLASSIFIER_WRAPPER_H

#include <filesystem>
#include <vector>
#include <cstdlib> 
#include <stdexcept>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

// internal
#include "functionality.h"

class AppGui; 

class ClassifierWrapper : public Functionality {
    public:
        ClassifierWrapper(AppGui* anApp, fs::path aSourceFolder, fs::path aDestinyFolder);
        void execute() override; 

        std::string strategy;

    private:
        int extractFeaturesFromTracks();
        int classifyTracksByFeatures();
        int copyFilesBasedOnClassificationResults();
        int deleteTemporalFilesCreated();

        void executePipeline();
        void loadClassificationResults(json& anObject);

        std::vector<int (ClassifierWrapper::*)()> pipeline;
};

#endif 