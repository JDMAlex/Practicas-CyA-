#include " p06_DFA_simulator.h"


//ALFABETO
Alfabeto::Alfabeto(const std::set<char>& simbolos) : simbolos_(simbolos) {}
std::set<char> Alfabeto::GetAlfabeto() const {
  return simbolos_;
}
void Alfabeto::InsertarSimbolo(char simbolo) {
  simbolos_.insert(simbolo);
}

bool Alfabeto::PerteneceAlfabeto(char simbolo_verificar) const{
  for (const auto& simbolo_alfabeto : simbolos_){
    if(simbolo_verificar == simbolo_alfabeto ){
      return true;
    } 
  }
  return false;
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
char Transicion::GetSimbolo(){
  return simbolo_;
}
std::string Transicion::GetEstadoSiguiente(){
  return estado_siguiente_;
}


