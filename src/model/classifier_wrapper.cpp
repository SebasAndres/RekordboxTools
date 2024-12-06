#include "classifier_wrapper.h"

ClassifierWrapper::ClassifierWrapper(fs::path src, fs::path dst) : Functionality(src, dst) { 
    strategy = "tempo";
    pipeline.push_back(&ClassifierWrapper::extractFeaturesFromTracks);
    pipeline.push_back(&ClassifierWrapper::classifyTracksByFeatures);
    pipeline.push_back(&ClassifierWrapper::copyFilesBasedOnClassificationResults);
    pipeline.push_back(&ClassifierWrapper::deleteTemporalFilesCreated);
}

bool executeCommand(string command){
    return system(command.c_str());
}

int ClassifierWrapper::extractFeaturesFromTracks(){
    return executeCommand("python3 ml/extractors/extractor_"+strategy+".py --src " + src.string() + " --dst " + dst.string());
}

int ClassifierWrapper::classifyTracksByFeatures(){
    return executeCommand("python3 ml/classifiers/classifier_"+strategy+".py --src " + dst.string() + " --dst " + dst.string());
}

void createDirectoryIfNotExists(const fs::path& path) {
    if (!fs::exists(path)) {
        fs::create_directories(path);
    }
}

int ClassifierWrapper::copyFilesBasedOnClassificationResults(){    
    ifstream file(dst / "classification.json");
    if (!file.is_open()) { throw runtime_error("No se pudo abrir el archivo classification.json"); }
    json classificationResults;
    file >> classificationResults;
    for (auto& [category, files] : classificationResults.items()) {
        cout << "> Guardando categoria " << category << "bpm" << endl;
        fs::path categoryPath = dst / category;
        createDirectoryIfNotExists(categoryPath);
        for (auto& file : files) {
            fs::path srcTrackPath = this->src / file;
            fs::path dstTrackPath = this->dst / category / file;
            try{ 
                fs::copy(srcTrackPath, dstTrackPath, fs::copy_options::overwrite_existing);
            }
            catch(const fs::filesystem_error& e){ 
                cout << e.what() << endl; 
            };
        }
    }
    return 0;
}

int ClassifierWrapper::deleteTemporalFilesCreated(){
    cout << "> Borrando archivos temporales. " << endl;
    return executeCommand("rm "+dst.string()+"/features.csv") & executeCommand("rm "+dst.string()+"/classification.json");
}

void ClassifierWrapper::execute() {    
    for (auto func : pipeline) {
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        int result = (this->*func)(); 
        if (result != 0) {
            throw std::runtime_error("Error al ejecutar una etapa del pipeline");
            break;
        }
    }
    cout << "----------------------------------------------------------------------------------------------------" << endl;
}
