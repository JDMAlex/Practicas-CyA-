
#include "p06_DFA_simulator.h"

int main(int argc, char* argv[]){
    if(argc == 1){
    std::cerr << "Modo de empleo: " << argv[0] << " input.dfa, input.txt" << std::endl;
    std::cerr << "Pruebe " << argv[0] << " --help para mas informacion." << std::endl;
    return 1;
  }
  if(argc == 2){
    std::string help = argv[1];
    if(help == "--help"){
      InformacionHelp();
      return 0;
    }
  } 
  std::string dfa_entrada = argv[1];
  std::string cadena_entrada = argv[2];
  DFA dfa;
  dfa.LeerDFA(dfa_entrada);
  dfa.LeerCadena(cadena_entrada);

  return 0;
}