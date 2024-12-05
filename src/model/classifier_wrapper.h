#ifndef CLASSIFIER_WRAPPER_H
#define CLASSIFIER_WRAPPER_H

#include <filesystem>
#include "functionality.h"
#include <vector>
#include <cstdlib> // 
#include <stdexcept>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

class ClassifierWrapper : public Functionality {
    public:
        ClassifierWrapper(fs::path src, fs::path dst);
        void execute() override; 

        string strategy;
        vector<int (ClassifierWrapper::*)()> pipeline;

    private:
        int extractFeaturesFromTracks();
        int classifyTracksByFeatures();
        int copyFilesBasedOnClassificationResults();
        int deleteTemporalFilesCreated();
};

#endif 