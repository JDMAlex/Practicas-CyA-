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

void MostrarInformacion(){
  std::cout << "" << std::endl;
}

std::set<std::string> Cadena::GetCadena() const {
  return cadena_;
}

void Cadena::LeerFichero(std::string fichero_entrada){
  std::ifstream fichero_leer(fichero_entrada);
  if(!fichero_leer.is_open()){
    std::cerr << "fichero no abierto";
    return;
  }
  std::string linea;
  std::string cadena;
  while(std::getline(fichero_leer, linea)){
    std::stringstream ss(linea);
    while(ss >> cadena){
      cadena_.insert(cadena);
    }
  }
}

void Cadena::Alfabeto(){
  for(const auto& cadena : cadena_){
    for(size_t i = 0; i < cadena.size(); i++){
      if(cadena[i] >= 1 && cadena[i] <= 9){
      }
    }
  }
}

std::ostream& operator<<(std::ostream& os, const Cadena& cadena){
  os << cadena.GetCadena();
  return os;
}



