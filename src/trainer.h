// Functionality >> Trainer
#ifndef TRAINER_H
#define TRAINER_H

// internal
#include "functionality.h"

class Trainer : public Functionality {
      public:             
            Trainer(fs::path src, fs::path dst);
            void execute() override; 

      private:
};

#endif 