SOURCES = main.cpp model/extractor.cpp model/functionality.cpp model/classifier_wrapper.cpp gui/app.cpp gui/button.cpp gui/gui_object.cpp gui/text_box.cpp

OBJECTS = $(SOURCES:.cpp=.o) # Define los archivos objeto

CXX = g++ # Define el compilador
CXXFLAGS = -std=c++17 -Wall -Wextra -g # Define las banderas de compilación

TARGET = main # Define el nombre del ejecutable

# JSON
JSON_CFLAGS = -I./include

# SFML
SFML_CFLAGS = $(shell pkg-config --cflags sfml-all)  
SFML_LIBS = $(shell pkg-config --libs sfml-all)

# Regla para compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(SFML_LIBS) -o $(TARGET)

# Regla para compilar los archivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(JSON_CFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJECTS) $(TARGET)

run:
	./$(TARGET)
