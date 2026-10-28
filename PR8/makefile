## Universidad de La Laguna
## Escuela Superior de Ingenieria y Tecnologia
## Grado en Ingenieria Informatica
## Asignatura: Computabilidad y Algoritmia
## Curso: 2º
## Practica 1: Contenedores asociativos
## Autor: Alexandro Jesus Dorta Mirena
## Correo: alu0101802961@ull.edu.es
## Fecha: 
## Archivo makefile: 


# Variables de configuración
CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET =  dfa2grammar
OBJS =  dfa2grammar_main.o  dfa2grammar.o

# Regla principal
$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
# Reglas para compilar cada archivo objeto
dfa2grammar_main.o:  dfa2grammar_main.cc  dfa2grammar.h
	$(CXX) $(CXXFLAGS) -c  dfa2grammar_main.cc
dfa2grammar.o:  dfa2grammar.cc  dfa2grammar.h
	$(CXX) $(CXXFLAGS) -c  dfa2grammar.cc
# Regla para limpiar archivos temporales
clean:
	rm -f $(TARGET) $(OBJS)
# Declara objetivos que no son archivos físicos
.PHONY: clean