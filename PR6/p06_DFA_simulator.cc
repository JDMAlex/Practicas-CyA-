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
void DFA::LeerDFA(const std::string& input_DFA){
  std::ifstream leer_DFA(input_DFA);
  if(!leer_DFA.is_open()){
    std::cerr << "no se abrio el DFA de forma correcta" << std::endl;
    return;
  }

  std::string linea_leida;
  int numero_linea_principal;



  while(std::getline(leer_DFA, linea_leida)){
    if(EsComentario(linea_leida)){
      continue;
    } 
    ++numero_linea_principal;

    if(numero_linea_principal == 1){
      std::stringstream ss(linea_leida);
      char alfabeto;
      while(ss >> alfabeto){
        alfabeto_.InsertarSimbolo(alfabeto);
      }
    } else if(numero_linea_principal == 2){
        std::stringstream ss(linea_leida);
        int numero_estados = 0;
        ss >> numero_estados;
    } else if(numero_linea_principal == 3){
        std::stringstream ss(linea_leida);
        std::string estado_inicial;
        ss >> estado_inicial;
    } else {
      std::stringstream ss(linea_leida);
      std::string estado_actual;
      bool es_aceptacion;
      while(ss >> estado_actual >> es_aceptacion){
        std::vector<Transicion> transiciones;
        char simbolo_transicion;
        std::string estado_siguiente;
        while(ss >> simbolo_transicion >> estado_siguiente){
          Transicion transicion(simbolo_transicion, estado_siguiente );
          transiciones.push_back(transicion);
        }
        Estado nuevo_estado(estado_actual, es_aceptacion, transiciones);
      }
      
    }
  }
}
bool DFA::SimularCadena(const std::string& cadena) const {

}

bool DFA::EsComentario(const std::string& linea) const {
  if(linea.empty()){
    return true;
  }
  if(linea.substr(0,2) == "//" && linea.size() >= 2){
    return true;
  }
  return false;
}








