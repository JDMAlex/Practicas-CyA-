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

void informacion_de_uso(){
  std::cout << "caca" << std::endl;
}

//ALFABETO
Alfabeto::Alfabeto(const std::set<char>& simbolos_alfabeto) : simbolos_alfabeto_(simbolos_alfabeto) {}
std::set<char> Alfabeto::GetAlfabeto() const{
  return simbolos_alfabeto_;
}
bool Alfabeto::EsDelAlfabeto(char simbolo_entrada){
  for(const auto& simbolo_itera : simbolos_alfabeto_){
    if (simbolo_entrada != simbolo_itera){
      return false;
    }
  }
  return true;
}

void Alfabeto::InsertarSimbolo(char simbolo_entrada){
  simbolos_alfabeto_.insert(simbolo_entrada);
}

//ESTADO
Estado::Estado(const std::map<char, int>& transiciones, bool aceptacion, int numero_estado, int numero_transiciones) : transiciones_(transiciones), aceptacion_(aceptacion), numero_estado_(numero_estado), numero_transiciones_(numero_transiciones) {}
std::map<char, int> Estado::GetTransiciones() const{
  return transiciones_;
}
bool Estado::GetEsAceptacion() const{
  return aceptacion_;
}
int Estado::GetNumeroEstado() const{
  return numero_estado_;
}

int Estado::GetNumeroTransiciones() const{
  return numero_transiciones_;
}



//DFA
DFA::DFA(const Alfabeto& alfabeto, const std::vector<Estado>& estados, int estado_inicial) : alfabeto_(alfabeto), estados_(estados), estado_inicial_(estado_inicial) {}
Alfabeto DFA::GetAlfabeto() const{
  return alfabeto_;
}
std::vector<Estado> DFA::GetEstados() const{
  return estados_;
}
int DFA::GetInicial() const{
  return estado_inicial_;
}

void DFA::LeerDFA(const std::string& DFA_a_leer) {
  std::ifstream DFA_abierto(DFA_a_leer);
  if(!DFA_abierto.is_open()){
    std::cerr << "fichero no abierto " << std::endl;
    return;
  }
  std::string linea_fichero;
  int posicion = 0;
  char simbolo;
  std::string informacion_estado;

  while(std::getline(DFA_abierto, linea_fichero) ){
    ++posicion;
    if(posicion == 1){
      std::stringstream ss(linea_fichero);
      while(ss >> simbolo){
        alfabeto_.InsertarSimbolo(simbolo);
      }
    } else if(posicion == 2){
      estados_.resize(std::stoi(linea_fichero));
    } else if(posicion == 3){
      estado_inicial_ = std::stoi(linea_fichero);
    } else {
      std::stringstream ss(linea_fichero);
      std::map<char, int> transiciones;
      char simbolo_transicion;
      int estado_transitar;

      bool es_aceptacion;
      int nombre_estado;
      int numero_transiciones;
      ss >> nombre_estado >> es_aceptacion >> numero_transiciones;
      while(ss >> simbolo_transicion >> estado_transitar){
        transiciones[simbolo_transicion] = estado_transitar;
      }
      Estado estado(transiciones, es_aceptacion, nombre_estado, numero_transiciones);
      estados_.push_back(estado);
    }
  }


}

