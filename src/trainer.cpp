#include "trainer.h"

Trainer::Trainer(fs::path src, fs::path dst) : Functionality(src, dst) {
      // por ahora nada 👀
}

void Trainer::execute(){
      string command = "python3 train.py -dataset " + (string)this->src + " -results " + (string)this->dst; 
      int result = system(command.c_str());
      if(result) {
            throw::runtime_error("Hubo un error al ejecutar el script Python.");
      }
}