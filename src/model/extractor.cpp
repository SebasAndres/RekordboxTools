#include "extractor.h"
#include "../gui/app.h"

Extractor::Extractor(
      AppGui* anApp,
      fs::path aSourceFolder,
      fs::path aDestinyFolder) : Functionality(anApp, aSourceFolder, aDestinyFolder) {
      if (this->status != Status::RUNNABLE){
            this->app->notify("Inicializacion incorrecta de Extractor");
      }
}

uint8_t Extractor::isAllowedExtension(const string& extension){ 
      for(string ext: ALLOWED_EXTENSIONS)
            if (ext==extension){ return 1; }
      return 0;
}

void Extractor::registerNotCopiedFile(const fs::path& aFile){
      app->notify("No se copió "+aFile.filename().string());
}

void Extractor::execute(){       // contents/artists/source/file
      if (status != Status::RUNNABLE){ return; }
      try{
            for (const auto& artistFolder: fs::directory_iterator(sourceFolder)){                       
                  for (const auto& sourceDownloadFolder: fs::directory_iterator(artistFolder)){      
                        for (const auto& file: fs::directory_iterator(sourceDownloadFolder)){         
                              fs::path sourceTrack = file.path();              
                              // assertIsValidFile
                              if (!(file.is_regular_file()) | !(isAllowedExtension(sourceTrack.extension()))) { 
                                    registerNotCopiedFile(sourceTrack);
                                    continue;
                              }              
                              // assertAlreadyCopied
                              if (this->copiedFiles.find(sourceTrack.filename()) != this->copiedFiles.end()) { continue; } 
                              copyFile(sourceTrack);
                        }
                  }
            }      
            status = Status::COMPLETED;  
            this->app->notify("Extraction ended");     
      }
      catch(const fs::filesystem_error& e){
            this->app->notify("Extraction failed because of :\n"+std::string(e.what()).substr(0,100)+"...");
      }
}

void Extractor::copyFile(fs::path sourceTrack){
      fs::path destinyTrack = destinyFolder / sourceTrack.filename();
      try {
            fs::copy(sourceTrack, destinyTrack, fs::copy_options::overwrite_existing);
            this->copiedFiles.insert(sourceTrack.filename());
            app->notify(sourceTrack.filename().string() + " copiado. ");
      }
      catch(const fs::filesystem_error& e){
            app->notify("Error copiando "+sourceTrack.filename().string() + ": " + e.what());
            registerNotCopiedFile(sourceTrack);
      };
}