// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 2: Cadenas y lenguajes
// Autor: Alexandro Dorta Mirena
// Correo: alu0101802961@ull.edu.es
// Fecha: 16/09/2025
// Archivo cya-P02-strings.cc: programa cliente.
// Objetivo: 

#include "dfa2grammar.h"


int main(int argc, char* argv[]){

  if(argc == 2 && std::string(argv[1]) == "--help"){
    informacion_de_uso();
    return 0;
  }
  if(argc != 3){
    std::cerr << "Modo de empleo: " << argv[0] << " input.dfa output.gra" << std::endl;
    std::cerr << "Pruebe '" << argv[0] << " --help' para mas informacion." << std::endl;
    return 1;
  }

  std::string DFA_a_leer = argv[1];
  DFA dfa;
  dfa.LeerDFA(DFA_a_leer);
  std::string Gramatica_escribir = argv[2];


  


  return 0;
}