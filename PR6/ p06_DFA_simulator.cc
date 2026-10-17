#include "p06_DFA_simulator.h"

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
DFA::DFA(const Alfabeto& alfabeto, const Estado& estado_inicial, const std::vector<Estado>& conjunto_estados) : alfabeto_(alfabeto), estado_inicial_(estado_inicial), conjunto_estados_(conjunto_estados) {}
Alfabeto DFA::GetAlfabeto() const{
  return alfabeto_;
}
Estado DFA::GetEstadoInicial() const{
  return estado_inicial_;
}
std::vector<Estado> DFA::GetEstados() const{
  return conjunto_estados_;
}

void LeerDFA(const std::string& DFA){
  std::ifstream leer_DFA(DFA);
  if(!leer_DFA.is_open()){
    std::cerr << "no se abrio el DFA de forma correcta" << std::endl;
    return;
  }
  
}






