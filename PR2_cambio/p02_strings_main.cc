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

#include "p02_strings.h"

int main(int argc, char* argv[]){

  if(argc == 1){
    std::cerr << "Modo de empleo: " <<  argv[0] <<  " filein.txt fileout.txt opcode " << std::endl;
    std::cerr << "Prueba " << argv[0] << " --help para mas informacion " << std::endl;
    return 1;
  }

  std::string help = argv[1];
  if(argc == 2 && help == "--help"){
    MostrarInformacion();
    return 1;
  }

  if(argc == 4){
    int opcode = std::stoi(argv[3]);
    std::string entrada = argv[1];
    std::string salida = argv[2];
    Cadena cadena;
    Alfabeto alfabeto;
    Lenguaje lenguaje;


    //Leer fichero
    std::ifstream fichero_entrada(entrada);
    if(!fichero_entrada.is_open()){
      std::cerr << "fichero no abierto" << std::endl;
      return 1;
    }
    std::string linea;
    while(std::getline(fichero_entrada, linea)){
      std::stringstream ss(linea);
      if(ss >> cadena >> alfabeto){
        lenguaje.InsertarCadena(cadena);
      }
    }

    //escribir fichero
    std::ofstream fichero_salida(salida);
    if(!fichero_salida.is_open()){
      std::cerr << "fichero no escrito" << std::endl;
    }
    switch(opcode){
      case 1:

      break;

      default:
      break;
    }  
  }

  return 0;
}
