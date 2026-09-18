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

//Funciones
void MostrarInformacion(){
  std::cout << std::endl;
}

//CLASE CADENA
std::string Cadena::GetCadena() const{
  return cadena_;
}

std::istream& operator>>(std::istream& is, Cadena& cadena){
  is >> cadena.cadena_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Cadena& cadena){
  os << cadena.GetCadena();
  return os;
}

//CLASE ALFABETO
std::istream& operator>>(std::istream& is, Alfabeto& alfabeto){
  std::string cadena;
  while(is >> cadena){
    for(size_t i = 0; i < cadena.size(); i++){
      alfabeto.alfabeto_.insert(cadena[i]);
    }
  }
  is.clear();
  return is;
}

std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto){
  os << "{";
  for(const auto& simbolo : alfabeto.alfabeto_){
    os << simbolo << ", ";
  }
  os << "}" << std::endl;
  return os;
}


