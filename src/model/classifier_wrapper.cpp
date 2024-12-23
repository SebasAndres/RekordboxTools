#include "classifier_wrapper.h"
#include "../gui/app.h"

ClassifierWrapper::ClassifierWrapper(AppGui* app, fs::path sourceFolder, fs::path destinyFolder) : Functionality(app, sourceFolder, destinyFolder) { 
    if (status != Status::RUNNABLE){
        app->notify("Inicializacion incorrecta de ClassifierWrapper");
        return;
    }
    strategy = "tempo";
    pipeline.push_back(&ClassifierWrapper::extractFeaturesFromTracks);
    pipeline.push_back(&ClassifierWrapper::classifyTracksByFeatures);
    pipeline.push_back(&ClassifierWrapper::copyFilesBasedOnClassificationResults);
    pipeline.push_back(&ClassifierWrapper::deleteTemporalFilesCreated);
}

bool executeCommand(string command){ return system(command.c_str()); }

int ClassifierWrapper::extractFeaturesFromTracks(){
    app->notify("Extrayendo features");
    return executeCommand("python3 ml/extractors/extractor_"+this->strategy+".py --src " + this->sourceFolder.string() + " --dst " + this->destinyFolder.string());
}

int ClassifierWrapper::classifyTracksByFeatures(){
    app->notify("Clasificando tracks");
    return executeCommand("python3 ml/classifiers/classifier_"+this->strategy+".py --src " + this->destinyFolder.string() + " --dst " + this->destinyFolder.string());
}

void ClassifierWrapper::loadClassificationResults(json& anObject){
    ifstream file(this->destinyFolder / "classification.json");
    if (!file.is_open()) { throw runtime_error("No se pudo abrir el archivo classification.json"); }
    file >> anObject;
}

int ClassifierWrapper::copyFilesBasedOnClassificationResults(){    
    app->notify("Copiando archivos clasificados");

    json classificationResults;
    loadClassificationResults(classificationResults);     
    for (auto& [category, files] : classificationResults.items()) {        

        fs::path categoryFolder = destinyFolder / category;
        if (!fs::exists(categoryFolder)) { fs::create_directories(categoryFolder); }    

        for (auto& file : files) {
            fs::path sourceTrack = sourceFolder / file;
            fs::path destinyTrack = categoryFolder / file;
            try{ 
                app->notify("Copying "+sourceTrack.filename().string()); 
                fs::copy(sourceTrack, destinyTrack, fs::copy_options::overwrite_existing);
            }
            catch(const fs::filesystem_error& e){ 
                app->notify(e.what()); 
            };
        }
    }
    return 0;
}

int ClassifierWrapper::deleteTemporalFilesCreated(){
    app->notify("Borrando archivos temporales");
    return executeCommand("rm "+this->destinyFolder.string()+"/features.csv") & executeCommand("rm "+this->destinyFolder.string()+"/classification.json");
}

void ClassifierWrapper::execute() {    
    if (status != Status::RUNNABLE){ return; }
    executePipeline();
}

void ClassifierWrapper::executePipeline(){
    for (auto func : pipeline) {
        int result = (this->*func)(); 
        if (result != 0) {
            throw std::runtime_error("Error al ejecutar una etapa del pipeline");
            break;
        }
    }
}

