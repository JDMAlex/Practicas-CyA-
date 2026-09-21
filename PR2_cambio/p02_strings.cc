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
Cadena::Cadena(const std::string& cadena) : cadena_(cadena) {}

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

int Cadena::LongitudCadena(){
  int longitud = cadena_.size();
  return longitud;
}

Cadena Cadena::InversaCadena(){
  if(cadena_ == "&"){
    return Cadena("&");
  }
  std::string cadena_inversa = cadena_;
  std::reverse(cadena_inversa.begin(), cadena_inversa.end());
  Cadena cadena_invertida(cadena_inversa);
  return cadena_invertida;
}

Lenguaje Cadena::Prefijo(){
  Lenguaje lenguaje;
  Cadena conjunto_con_cadena_vacia("&");
  if(cadena_ == "&"){
    return lenguaje;
  }
  std::string contenedor;
  lenguaje.InsertarCadena(conjunto_con_cadena_vacia);
  for(char simbolo : cadena_){
    contenedor.push_back(simbolo);
    Cadena cadena_contenedor(contenedor);
    lenguaje.InsertarCadena(cadena_contenedor);
  }
  return lenguaje;
}

Lenguaje Cadena::Sufijo(){
  Lenguaje lenguaje;
  Cadena conjunto_con_cadena_vacia("&");
  if(cadena_ == "&"){
    return lenguaje;
  }
  std::string contenedor;
  lenguaje.InsertarCadena(conjunto_con_cadena_vacia);
  for(int i = cadena_.size() - 1 ; i >= 0; i--){
    Cadena cadena_contenedor(cadena_.substr(i));
    lenguaje.InsertarCadena(cadena_contenedor);
  }
  return lenguaje;
}

bool Cadena::Validacion(Alfabeto alfabeto){
  return alfabeto.Pertenece_alfabeto(cadena_);
}



//CLASE ALFABETO
std::istream& operator>>(std::istream& is, Alfabeto& alfabeto){
  alfabeto.alfabeto_.clear();
  std::string cadena;
  if(is >> cadena){
    for(char simbolo : cadena){
      alfabeto.alfabeto_.insert(simbolo);
    }
  }
  return is;
}

std::set<char> Alfabeto::GetAlfabeto(){
  return alfabeto_;
}


std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto){
  os << "{";
  bool primero = true;
  for(const auto& simbolo : alfabeto.alfabeto_){
    if(!primero) os << ", ";
    os << simbolo;
    primero = false;
  }
  os << "}";
  return os;
}

bool Alfabeto::Pertenece_alfabeto(Cadena cadena){
  for(char simbolo : cadena.GetCadena()){
    if(alfabeto_.find(simbolo) == alfabeto_.end()){
      return false;
    }
  }
  return true;
}


//CLASE LENGUAJE
void Lenguaje::InsertarCadena(const Cadena& cadena){
  lenguaje_.insert(cadena.GetCadena());
}

std::set<std::string> Lenguaje::GetLenguaje(){
  return lenguaje_;
}


std::ostream& operator<<(std::ostream& os, const Lenguaje& lenguaje){
  os << "{";
  bool primero = true;
  for(const auto& cadena : lenguaje.lenguaje_){
    if(!primero) os << ", ";
    os << cadena;
    primero = false;
  }
  os << "}";
  return os;
}
