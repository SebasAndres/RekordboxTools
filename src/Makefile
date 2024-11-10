SOURCES = main.cpp extractor.cpp functionality.cpp trainer.cpp # Define los archivos fuente
OBJECTS = $(SOURCES:.cpp=.o) # Define los archivos objeto
CXX = g++ # Define el compilador
CXXFLAGS = -std=c++17 -Wall -Wextra -g # Define las banderas de compilación
TARGET = main # Define el nombre del ejecutable

# Regla para compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Regla para compilar los archivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJECTS) $(TARGET)

run:
	./$(TARGET)