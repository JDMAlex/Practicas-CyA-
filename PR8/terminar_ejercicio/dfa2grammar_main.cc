/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 8: Gramática Regular a partir de un DFA
 * 
 * @file dfa2grammar_main.cc
 * @author Alexandro Dorta Mirena (alu0101802961@ull.edu.es)
 * @date 16/10/2026
 * @brief Programa principal (cliente) para convertir un DFA en una Gramática Regular.
 */

#include "dfa2grammar.h"

/**
 * @brief Punto de entrada principal del programa dfa2grammar.
 * @param argc Número de argumentos pasados por línea de comandos.
 * @param argv Vector de argumentos por línea de comandos.
 * @return int Retorna 0 si termina correctamente, o 1 en caso de error.
 */
int main(int argc, char* argv[]) {
  if (argc == 2 && std::string(argv[1]) == "--help") {
    informacion_de_uso();
    return 0;
  }
  
  if (argc != 3) {
    std::cerr << "Modo de empleo: " << argv[0] << " input.dfa output.gra\n";
    std::cerr << "Pruebe '" << argv[0] << " --help' para mas informacion.\n";
    return 1;
  }

  std::string dfa_input_filename = argv[1];
  std::string grammar_output_filename = argv[2];

  // 1. Cargar el autómata determinista
  DFA dfa(dfa_input_filename);

  // 2. Transformar autómata a gramática regular
  Gramatica gramatica = dfa.ConvertToGrammar();

  // 3. Volcar gramática generada en el fichero de salida .gra
  gramatica.EscribirGramatica(grammar_output_filename);

  std::cout << "Conversión completada con éxito en '" << grammar_output_filename << "'.\n";

  return 0;
}