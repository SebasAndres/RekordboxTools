#include "functionality.h"

Functionality::Functionality(fs::path src, fs::path dst){
      // Validamos si existen las carpetas
      if (!(fs::exists(src))) { throw::invalid_argument("Detalle | No existe la carpeta de origen"); return; } 
      if (!(fs::exists(dst))) { throw::invalid_argument("Detalle | No existe la carpeta de destino"); return; } 

      // Inicializamos los atributos
      this->src = src;
      this->dst = dst;
}