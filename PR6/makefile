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
TARGET =  p06_DFA_simulator
OBJS =  p06_DFA_simulator_main.o  p06_DFA_simulator.o

# Regla principal
$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
# Reglas para compilar cada archivo objeto
p04_html_analyzer_main.o:  p06_DFA_simulator_main.cc  p06_DFA_simulator.h
	$(CXX) $(CXXFLAGS) -c  p06_DFA_simulator_main.cc
p04_html_analyzer.o:  p06_DFA_simulator.cc  p06_DFA_simulator.h
	$(CXX) $(CXXFLAGS) -c  p06_DFA_simulator.cc
# Regla para limpiar archivos temporales
clean:
	rm -f $(TARGET) $(OBJS)
# Declara objetivos que no son archivos físicos
.PHONY: clean