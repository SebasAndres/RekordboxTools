#include "trainer.h"

Trainer::Trainer(fs::path src, fs::path dst) : Functionality(src, dst) { }

vector<float> Trainer::extractFeatures(fs::path filePath){
      return ;
}

void Trainer::execute(){
     
      // Armado del dataset TRACK_ID | VECTOR | CLASSIFICATION      
      vector<TrackMetadata> dataset;
      for(const auto& classificationTypeFolder: fs::directory_iterator(this->src)){
            string classification = (string)classificationTypeFolder.path().filename();
            for(const auto& audioFile: fs::directory_iterator(classificationTypeFolder)){
                  if (audioFile.path().extension() != ".mp3" && audioFile.path().extension() != ".wav") continue;
                  string track_id = audioFile.path().filename();
                  vector<float> features = extractFeatures(audioFile.path());
                  dataset.push_back({ track_id, features, classification });
            }
      }

      // Armar, entrenar y guardar el modelo
      string command = "python3 train.py -dataset " + (string)this->src + " -results " + (string)this->dst; 
      int result = system(command.c_str());
      if(result) {
            throw::runtime_error("Hubo un error al ejecutar el script Python.");
      }
}
