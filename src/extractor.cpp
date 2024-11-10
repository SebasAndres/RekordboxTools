#include "extractor.h"

// Inicializacion de la funcionalidad
Extractor::Extractor(fs::path src, fs::path dst) : Functionality(src, dst) {

      // Inicialización de los atributos específicos de Extractor
      this->notCopiedFiles = new fs::path[MAX_FILES];
      this->notCopiedCounter = 0;
      this->copiedCounter = 0;
}

// Devuelve el destino del archivo a copiar dado el 
fs::path Extractor::getDestinyName(fs::path copied_file){ 
      return this->dst / copied_file.filename();
}

// Valida si es uno de los formatos aceptados
uint8_t Extractor::isAllowedExtension(const string& extension){ 
      for(string ext: ALLOWED_EXTENSIONS)
            if (ext==extension){ return 1; }
      return 0;
}

// Actualiza la flag con los registros no copiados
void Extractor::registerNotCopiedFile(const fs::path& not_copied_file){
      notCopiedFiles[notCopiedCounter] = not_copied_file;
      notCopiedCounter++;
}

// Vamos a realizar una copia al momento de leer la carpeta CONTENTS
// por cada subcarpeta obtener y copiar los archivos terminados en .mp3 o .wav 
void Extractor::execute(){

      uint8_t earlyStop = 0;

      cout << endl;
      cout << "Copiando archivos." << endl;
      for (const auto& artistFolder: fs::directory_iterator(this->src)){          // contents/artists
            for (const auto& sourceDownloadFolder: fs::directory_iterator(artistFolder)){       // contents/artists/source
                  for (const auto& file: fs::directory_iterator(sourceDownloadFolder)){         // contents/artists/source/file

                        fs::path srcTrackPath = file.path();
                        string trackExtension = srcTrackPath.extension();

                        // irregular file or invalid extension
                        if (!(file.is_regular_file()) | !(isAllowedExtension(trackExtension))) { 
                              registerNotCopiedFile(srcTrackPath);
                              continue;
                        }  

                        // copy file
                        fs::path dstTrackPath = getDestinyName(srcTrackPath);
                        try{
                              fs::copy(srcTrackPath, dstTrackPath, fs::copy_options::overwrite_existing);
                              cout << "(*) ["<< copiedCounter << "] Copiado exitosamente " << srcTrackPath << endl;
                              copiedCounter++;
                              if (copiedCounter >= MAX_FILES) { earlyStop = 1; break; }
                        }
                        catch(const fs::filesystem_error& e){
                              cout << e.what() << endl;
                              registerNotCopiedFile(srcTrackPath);
                        };
                  }
                  if (copiedCounter >= MAX_FILES) { break; } 
            }
            if (copiedCounter >= MAX_FILES) { break; }
      }

      if(notCopiedCounter > 0){
            cout << endl;
            cout << "No se copiaron " << notCopiedCounter << " archivos" << endl;
            for(uint32_t j=0; j<notCopiedCounter; j++)
                  cout << "(*) No se copió: " << notCopiedFiles[j] << endl;
      }

      if(earlyStop){
            cout << endl;
            cout << "El programa se terminó por early stop despues de " << MAX_FILES << " archivos copiados." << endl;
      }

      delete[] notCopiedFiles;
}
