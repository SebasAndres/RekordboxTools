SOURCES = main.cpp model/extractor.cpp model/functionality.cpp model/classifier_wrapper.c # Define los archivos fuente
OBJECTS = $(SOURCES:.cpp=.o) # Define los archivos objeto
CXX = g++ # Define el compilador
CXXFLAGS = -std=c++17 -Wall -Wextra -g # Define las banderas de compilación
TARGET = main # Define el nombre del ejecutable

JSON_CFLAGS = -I./include

# Regla para compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(ESSENTIA_CFLAGS) $(ESSENTIA_LIBS) -o $(TARGET) $(OBJECTS)

# Regla para compilar los archivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(ESSENTIA_CFLAGS) $(JSON_CFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJECTS) $(TARGET)

run:
	./$(TARGET)
