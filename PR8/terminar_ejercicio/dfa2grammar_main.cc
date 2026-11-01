// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Autor: Alexandro Dorta Mirena
// Correo: alu0101802961@ull.edu.es

#include "dfa2grammar.h"

int main(int argc, char* argv[]) {
  if (argc == 2 && std::string(argv[1]) == "--help") {
    informacion_de_uso();
    return 0;
  }
  
  if (argc != 3) {
    std::cerr << "Modo de empleo: " << argv[0] << " input.dfa output.gra" << std::endl;
    std::cerr << "Pruebe '" << argv[0] << " --help' para mas informacion." << std::endl;
    return 1;
  }

  std::string dfa_input_filename = argv[1];
  std::string grammar_output_filename = argv[2];

  // 1. Cargar el autómata desde el archivo
  DFA dfa(dfa_input_filename);

  // 2. Convertir DFA a Gramática Regular
  Gramatica gramatica = dfa.ConvertToGrammar();

  // 3. Escribir el fichero .gra de salida
  gramatica.EscribirGramatica(grammar_output_filename);

  std::cout << "Conversion completada con exito en '" << grammar_output_filename << "'." << std::endl;

  return 0;
}