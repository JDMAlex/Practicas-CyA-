
#include "p06_DFA_simulator.h"

/**
 * @file p06_DFA_simulator_main.cc
 * @brief Programa principal del simulador de DFAs.
 *
 * Uso: ./p06_DFA_simulator input.dfa input.txt
 *
 * @author Alexandro Jesus Dorta Mirena
 * @date 2026-10-20
 */

/**
 * @brief Punto de entrada: valida los argumentos, carga el DFA y simula
 *        las cadenas del fichero de entrada.
 * @param argc Número de argumentos.
 * @param argv Argumentos: fichero .dfa y fichero .txt (o --help).
 * @return 0 si todo es correcto, 1 si el uso es incorrecto, 2 si el DFA es inválido.
 */
int main(int argc, char* argv[]){
  if(argc == 2 && std::string(argv[1]) == "--help"){
    InformacionHelp();
    return 0;
  }
  if(argc != 3){
    std::cerr << "Modo de empleo: " << argv[0] << " input.dfa input.txt" << std::endl;
    std::cerr << "Pruebe '" << argv[0] << " --help' para mas informacion." << std::endl;
    return 1;
  }
  DFA dfa;
  if(!dfa.LeerDFA(argv[1])){
    return 2;
  }
  dfa.LeerCadena(argv[2]);
  return 0;
}