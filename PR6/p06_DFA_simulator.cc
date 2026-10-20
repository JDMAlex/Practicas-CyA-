#include "p06_DFA_simulator.h"

/**
 * @file p06_DFA_simulator.cc
 * @brief Implementación de las clases Alfabeto, Transicion, Estado y DFA.
 * @author Alexandro Jesus Dorta Mirena
 * @date 2026-10-20
 */

void InformacionHelp(){
  std::cout << "Simulador de DFAs. Uso: ./p06_DFA_simulator input.dfa input.txt" << std::endl;
  std::cout << "Formato del fichero .dfa (las lineas que empiezan por // son comentarios):" << std::endl;
  std::cout << "  Linea 1: simbolos del alfabeto, sin espacios" << std::endl;
  std::cout << "  Linea 2: numero total de estados" << std::endl;
  std::cout << "  Linea 3: estado de arranque" << std::endl;
  std::cout << "  Resto:   una linea por estado: id, 1/0 (aceptacion), y pares simbolo destino" << std::endl;
  std::cout << "Fichero .txt: una cadena por linea; '&' representa la cadena vacia." << std::endl;
}

//ALFABETO
Alfabeto::Alfabeto(const std::set<char>& simbolos) : simbolos_(simbolos) {}
std::set<char> Alfabeto::GetAlfabeto() const {
  return simbolos_;
}
void Alfabeto::InsertarSimbolo(char simbolo) {
  simbolos_.insert(simbolo);
}

bool Alfabeto::PerteneceAlfabeto(const char simbolo_verificar) const{
  auto posicion_elemento = simbolos_.find(simbolo_verificar);
  if(posicion_elemento != simbolos_.end()){
    return true;
  } else {
    return false;
  }
}

//TRANSICIONES
Transicion::Transicion(char simbolo, const std::string& estado_siguiente) : simbolo_(simbolo), estado_siguiente_(estado_siguiente) {}
char Transicion::GetSimbolo() const {
  return simbolo_;
}
std::string Transicion::GetEstadoSiguiente()const {
  return estado_siguiente_;
}

//ESTADOS
Estado::Estado(std::string nombre_estado, bool es_aceptacion, const std::vector<Transicion>& transiciones) : nombre_estado_(nombre_estado), es_aceptacion_(es_aceptacion), transiciones_(transiciones) {}
std::string Estado::GetNombreEstado() const {
  return  nombre_estado_;
}
bool Estado::GetEsAceptacion() const {
  return es_aceptacion_;
}
std::vector<Transicion> Estado::GetTransiciones() const {
  return transiciones_;
}

std::string Estado::GetSiguienteEstado(char simbolo) const{
  for(size_t i = 0; i < transiciones_.size(); ++i){
    if(transiciones_[i].GetSimbolo() == simbolo){
      return transiciones_[i].GetEstadoSiguiente();
    }
  }
  return "&";
}

//DFA
DFA::DFA(const Alfabeto& alfabeto, const Estado& estado_inicial, const std::map<std::string, Estado>& conjunto_estados) : alfabeto_(alfabeto), estado_inicial_(estado_inicial), conjunto_estados_(conjunto_estados) {}
Alfabeto DFA::GetAlfabeto() const{
  return alfabeto_;
}
Estado DFA::GetEstadoInicial() const{
  return estado_inicial_;
}
std::map<std::string, Estado> DFA::GetEstados() const{
  return conjunto_estados_;
}
bool DFA::LeerDFA(const std::string& input_DFA){
  std::ifstream leer_DFA(input_DFA);
  if(!leer_DFA.is_open()){
    std::cerr << "no se abrio el DFA de forma correcta" << std::endl;
    return false;
  }
  std::string linea_leida;
  int numero_linea_principal = 0;
  std::string estado_inicial;
  int numero_estado = 0;

  while(std::getline(leer_DFA, linea_leida)){
    if(EsComentario(linea_leida)){
      continue;
    } 
    ++numero_linea_principal;
    std::stringstream ss(linea_leida);

    if(numero_linea_principal == 1){
      char simbolo;
      while(ss >> simbolo){
        alfabeto_.InsertarSimbolo(simbolo);
      }
    } else if(numero_linea_principal == 2) {
        if(!(ss >> numero_estado)){
          std::cerr << "Error: numero de estados invalido" << std::endl;
          return false;
        }
    } else if(numero_linea_principal == 3){
        ss >> estado_inicial;
    } else {
      std::string estado_actual;
      bool es_aceptacion;
      if(!(ss >> estado_actual >> es_aceptacion) || (es_aceptacion != 0 && es_aceptacion != 1)){
        std::cerr << "Error: linea de estado invalida: " << linea_leida << std::endl;
        return false;
      }
      if(conjunto_estados_.count(estado_actual)){
        std::cerr << "Error: estado repetido " << estado_actual << std::endl;
        return false; 
      }
      std::vector<Transicion> transiciones;
      char simbolo_transicion;
      std::string estado_siguiente;
      while(ss >> simbolo_transicion >> estado_siguiente){
        if(!alfabeto_.PerteneceAlfabeto(simbolo_transicion)){
          std::cerr << "Error: simbolo " << simbolo_transicion << " fuera del alfabeto" << std::endl;
          return false;
        }
        Transicion transicion(simbolo_transicion, estado_siguiente);
        transiciones.push_back(transicion);
      }
      conjunto_estados_[estado_actual] = Estado(estado_actual, es_aceptacion == 1, transiciones);
    }
  }
  if(conjunto_estados_.size() != numero_estado){
    std::cerr << "Error: el numero de estados no coincide con las lineas definidas" << std::endl;
    return false;
  }
  auto inicial = conjunto_estados_.find(estado_inicial);
  if(inicial == conjunto_estados_.end()) {
    std::cerr << "Error: el estado inicial " << estado_inicial << " no existe" << std::endl;
    return false;
  }
  estado_inicial_ = inicial->second;
  for(const auto& par : conjunto_estados_){
    const Estado& estado = par.second;
    if(estado.GetTransiciones().size() != alfabeto_.GetAlfabeto().size()){
      std::cerr << "Error: el estado " << par.first << " no tiene una transicion por simbolo" << std::endl;
      return false;
    }
    for(const Transicion& t : estado.GetTransiciones()){
      if(!conjunto_estados_.count(t.GetEstadoSiguiente())){
        std::cerr << "Error: transicion a estado inexistente " << t.GetEstadoSiguiente() << std::endl;
        return false;
      }
    }
  }
  return true;
}

void DFA::SimularCadena(const std::string& cadena) const {
  std::cout << "Cadena a procesar: " << cadena << std::endl;
  std::cout << "Estado actual\tEntrada\tSiguiente estado" << std::endl;
  Estado estado_actual = estado_inicial_;

  if(cadena != "&"){
    for(char simbolo : cadena){
      if(!alfabeto_.PerteneceAlfabeto(simbolo)){
        std::cout << "Error: el simbolo " << simbolo << " no pertenece al alfabeto." << std::endl;
        std::cout << "Cadena de entrada RECHAZADA." << std::endl << std::endl;
        return;
        }
      std::string siguiente = estado_actual.GetSiguienteEstado(simbolo);
      std::cout << estado_actual.GetNombreEstado() << "\t\t" << simbolo << "\t" << siguiente << std::endl;
      estado_actual = conjunto_estados_.at(siguiente);
    }
  }
  std::cout << std::endl << "Cadena de entrada " << (estado_actual.GetEsAceptacion() ? "ACEPTADA." : "RECHAZADA.") << std::endl;
}


bool DFA::EsComentario(const std::string& linea) const {
  if(linea.empty()){
    return true;
  }
  if( linea.size() >= 2 && linea.substr(0,2) == "//" ){
    return true;
  }
  return false;
}

void DFA::LeerCadena(const std::string& input_cadena)const {
  std::ifstream leer_cadena(input_cadena);
  if(!leer_cadena.is_open()){
    std::cerr << "cadena no leida" << std::endl;
    return;
  }
  std::string cadena;
  while(std::getline(leer_cadena, cadena)){
  if(cadena.empty()) continue;
  SimularCadena(cadena);
  }
}








