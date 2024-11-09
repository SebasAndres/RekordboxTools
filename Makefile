# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lstdc++fs  # Necesario para <filesystem> en algunas implementaciones
TARGET = copyFiles

# Regla para compilar el objetivo final
$(TARGET): main.o
	$(CXX) main.o -o $(TARGET) $(LDFLAGS)

# Regla para compilar el archivo fuente
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Regla para limpiar los archivos generados
clean:
	rm -f *.o $(TARGET)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)
