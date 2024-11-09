#include <iostream>
#include "extractor.h"

using namespace std;

// dst_folder ++ filename
fs::path getDestinyName(fs::path originalPath, fs::path destiny){ 
      return destiny / originalPath.filename();
}

// valida si es uno de los formatos aceptados
uint8_t isAllowedExtension(const string& extension){ 
      for(string ext: ALLOWED_EXTENSIONS){
            if (ext==extension)    
                  return 1;
      }
      return 0;
}

// actualiza la flag con los registros no copiados
void registerNotCopiedFile(fs::path* notCopied, uint32_t& count, const fs::path& path){
      notCopied[count] = path;
      count++;
}

// vamos a realizar una copia al momento de leer la carpeta CONTENTS
// por cada subcarpeta obtener y copiar los archivos terminados en .mp3 o .wav 
void extractTracks(fs::path& source, fs::path& destiny){

      if (!(fs::exists(source))) { cerr << "ERROR: No existe la carpeta de origen" << endl; return; } 
      if (!(fs::exists(destiny))) { cerr << "ERROR: No existe la carpeta de destino" << endl; return; } 

      fs::path* notCopiedFiles = new fs::path[MAX_FILES];
      uint32_t notCopiedCounter = 0;
      uint32_t copiedCounter = 0;
      uint8_t earlyStop = 0;

      cout << endl;
      cout << "Copiando archivos." << endl;
      for (const auto& artistFolder: fs::directory_iterator(source)){             // contents/artists
            for (const auto& sourceDownloadFolder: fs::directory_iterator(artistFolder)){       // contents/artists/source
                  for (const auto& file: fs::directory_iterator(sourceDownloadFolder)){         // contents/artists/source/file

                        fs::path srcTrackPath = file.path();
                        string trackExtension = srcTrackPath.extension();

                        // irregular file or invalid extension
                        if (!(file.is_regular_file()) | !(isAllowedExtension(trackExtension))) { 
                              registerNotCopiedFile(notCopiedFiles, notCopiedCounter, srcTrackPath);
                              continue;
                        }  

                        // copy file
                        fs::path dstTrackPath = getDestinyName(srcTrackPath, destiny);
                        try{
                              fs::copy(srcTrackPath, dstTrackPath, fs::copy_options::overwrite_existing);
                              cout << "(*) ["<< copiedCounter << "] Copiado exitosamente " << srcTrackPath << endl;
                              copiedCounter++;
                              if (copiedCounter >= MAX_FILES) { earlyStop = 1; break; }
                        }
                        catch(const fs::filesystem_error& e){
                              cout << e.what() << endl;
                              registerNotCopiedFile(notCopiedFiles, notCopiedCounter, srcTrackPath);
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

