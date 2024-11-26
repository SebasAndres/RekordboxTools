#include "trainer.h"

Trainer::Trainer(fs::path src, fs::path dst) : Functionality(src, dst), factory(AlgorithmFactory::instance()) {
//     essentia::init();
//     mfcc = std::unique_ptr<Algorithm>(factory.create("MFCC"));
//     chromaExtractor = std::unique_ptr<Algorithm>(factory.create("Chromagram"));
//     spectralCentroidExtractor = std::unique_ptr<Algorithm>(factory.create("SpectralCentroidTime"));
//     tempoExtractor = std::unique_ptr<Algorithm>(factory.create("Tempo"));
}


Trainer::~Trainer(){
      // essentia::shutdown();
}

void Trainer::execute(){    
      // armado del dataset
      buildDataset();

      // Armar, entrenar y guardar el modelo
      // string command = "python3 train.py -dataset " + (string)this->src + " -results " + (string)this->dst; 
      // int result = system(command.c_str());
      // if(result)
      //       throw::runtime_error("Hubo un error al ejecutar el script Python.");
      // cout << "Dataset armado en " << this->dst << endl;
}

void Trainer::buildDataset(void){
      cout << endl;
      cout << "---------------------------------------------------------" << endl;
      cout << "Armando el dataset:" << endl;

      vector<TrackMetadata> dataset;
      for(const auto& classificationTypeFolder: fs::directory_iterator(this->src)){
            string classification = (string)classificationTypeFolder.path().filename();
            cout << "(*) Leyendo carpeta " << classification << endl;
            for(const auto& audioFile: fs::directory_iterator(classificationTypeFolder)){      
                  if (audioFile.path().extension() != ".mp3" && audioFile.path().extension() != ".wav") continue;                  
                  TrackMetadata features = extractFeatures(audioFile.path(), classification);
                  dataset.push_back( features );
            }
      }

      // guardado en un csv
      ofstream file((string)this->dst+"/dataset.csv");
      if (!file.is_open()) { throw::runtime_error("No se pudo abrir el archivo para escribir."); }
      file << "TrackId, MFCCs, chromaFeatures, spectralCentroid, tempo, classification, \n";
      for (const auto& track : dataset) {
            file << track.trackId << ",";
            file << track.MFCCs << ",";
            file << track.chromaFeatures << ",";
            file << track.spectralCentroid << ",";
            file << track.tempo << ",";
            file << track.classification;            
            file << "\n";  
      }
      file.close();
      cout << "Finalizado en " << (string)this->dst+"/dataset.csv" << endl;
      cout << "---------------------------------------------------------" << endl;
      cout << endl;
}

TrackMetadata Trainer::extractFeatures(fs::path filePath, string classification){    

    // Ruta del archivo de audio
    string audioFilePath = (string)filePath;

    // Crear una instancia de Pool para almacenar las características extraídas
    Pool pool;

    // Crear una fábrica de algoritmos
    AlgorithmFactory& factory = AlgorithmFactory::instance();

    // Cargar el archivo de audio
    std::vector<Real> audio;
    Algorithm* audioLoader = factory.create("MonoLoader", "filename", audioFilePath, "sampleRate", 44100);
    audioLoader->output("audio").set(audio);
    audioLoader->compute();

    // Calcular el BPM
    std::vector<Real> bpm;
    Algorithm* rhythmExtractor = factory.create("RhythmExtractor2013", "method", "multifeature");
    rhythmExtractor->input("signal").set(audio);
    rhythmExtractor->output("bpm").set(bpm);
    rhythmExtractor->compute();

    // Calcular el tono
    Real pitch;
    Real pitchConfidence;
    Algorithm* pitchYin = factory.create("PitchYinFFT", "frameSize", 2048, "sampleRate", 44100);
    pitchYin->input("signal").set(audio);
    pitchYin->output("pitch").set(pitch);
    pitchYin->output("pitchConfidence").set(pitchConfidence);
    pitchYin->compute();

    // Calcular el espectro
    std::vector<Real> spectrum;
    Algorithm* spectrumAlgorithm = factory.create("Spectrum", "frameSize", 2048);
    spectrumAlgorithm->input("frame").set(audio);
    spectrumAlgorithm->output("spectrum").set(spectrum);
    spectrumAlgorithm->compute();

    // Guardar las características en el pool
    pool.add("rhythm.bpm", bpm);
    pool.add("pitch.pitch", pitch);
    pool.add("pitch.confidence", pitchConfidence);
    pool.add("spectrum.spectrum", spectrum);

    // Mostrar los resultados
    std::cout << "BPM: " << bpm[0] << std::endl;
    std::cout << "Pitch: " << pitch << std::endl;
    std::cout << "Pitch Confidence: " << pitchConfidence << std::endl;

    // Liberar memoria
    delete audioLoader;
    delete rhythmExtractor;
    delete pitchYin;
    delete spectrumAlgorithm;

    return { "track_id", 0, pitch, 0, bpm[0], classification };
}

