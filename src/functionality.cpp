#include "functionality.h"

Functionality::Functionality(fs::path src, fs::path dst){
      
      // valido si src y dst pasados son validos
      if (!(fs::exists(src))) { throw::invalid_argument("Detalle | No existe la carpeta de origen"); return; } 
      if (!(fs::exists(dst))) { throw::invalid_argument("Detalle | No existe la carpeta de destino"); return; } 

      // inicializo
      this->src = src;
      this->dst = dst;
}