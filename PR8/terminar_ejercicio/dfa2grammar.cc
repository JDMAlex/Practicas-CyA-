// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Autor: Alexandro Dorta Mirena
// Correo: alu0101802961@ull.edu.es

#include "dfa2grammar.h"

void informacion_de_uso() {
  std::cout << "Programa de conversion de DFA a Gramatica Regular." << std::endl;
  std::cout << "Uso: ./dfa2grammar input.dfa output.gra" << std::endl;
}

// ALFABETO
Alfabeto::Alfabeto(const std::set<char>& simbolos_alfabeto) : simbolos_alfabeto_(simbolos_alfabeto) {}

std::set<char> Alfabeto::GetAlfabeto() const {
  return simbolos_alfabeto_;
}

bool Alfabeto::EsDelAlfabeto(char simbolo_entrada) const {
  return simbolos_alfabeto_.count(simbolo_entrada) > 0;
}

void Alfabeto::InsertarSimbolo(char simbolo_entrada) {
  simbolos_alfabeto_.insert(simbolo_entrada);
}

// ESTADO
Estado::Estado(const std::map<char, int>& transiciones, bool aceptacion, int numero_estado, int numero_transiciones) 
    : transiciones_(transiciones), aceptacion_(aceptacion), numero_estado_(numero_estado), numero_transiciones_(numero_transiciones) {}

std::map<char, int> Estado::GetTransiciones() const {
  return transiciones_;
}

bool Estado::GetEsAceptacion() const {
  return aceptacion_;
}

int Estado::GetNumeroEstado() const {
  return numero_estado_;
}

int Estado::GetNumeroTransiciones() const {
  return numero_transiciones_;
}

// GRAMATICA
Gramatica::Gramatica(const std::set<char>& terminales,
                     const std::set<std::string>& no_terminales,
                     const std::string& arranque,
                     const std::vector<Produccion>& producciones)
    : terminales_(terminales),
      no_terminales_(no_terminales),
      arranque_(arranque),
      producciones_(producciones) {}

void Gramatica::EscribirGramatica(const std::string& nombre_fichero) const {
  std::ofstream fichero(nombre_fichero);
  if (!fichero.is_open()) {
    std::cerr << "Error: no se pudo crear/abrir el fichero " << nombre_fichero << std::endl;
    return;
  }

  // 1. Simbolos terminales
  fichero << terminales_.size() << "\n";
  for (char t : terminales_) {
    fichero << t << "\n";
  }

  // 2. Simbolos no terminales
  fichero << no_terminales_.size() << "\n";
  for (const auto& nt : no_terminales_) {
    fichero << nt << "\n";
  }

  // 3. Simbolo de arranque
  fichero << arranque_ << "\n";

  // 4. Producciones
  fichero << producciones_.size() << "\n";
  for (const auto& prod : producciones_) {
    fichero << prod.origen << " -> " << prod.destino << "\n";
  }
}

// DFA
DFA::DFA(const std::string& nombre_fichero_dfa) {
  LeerDFA(nombre_fichero_dfa);
}

DFA::DFA(const Alfabeto& alfabeto, const std::vector<Estado>& estados, int estado_inicial) 
    : alfabeto_(alfabeto), estados_(estados), estado_inicial_(estado_inicial) {}

Alfabeto DFA::GetAlfabeto() const {
  return alfabeto_;
}

std::vector<Estado> DFA::GetEstados() const {
  return estados_;
}

int DFA::GetInicial() const {
  return estado_inicial_;
}

void DFA::LeerDFA(const std::string& DFA_a_leer) {
  std::ifstream DFA_abierto(DFA_a_leer);
  if (!DFA_abierto.is_open()) {
    std::cerr << "Error: no se pudo abrir el fichero " << DFA_a_leer << std::endl;
    return;
  }

  std::string linea_fichero;
  int posicion = 0;
  char simbolo;

  while (std::getline(DFA_abierto, linea_fichero)) {
    if (linea_fichero.empty()) continue;
    ++posicion;

    if (posicion == 1) {
      std::stringstream ss(linea_fichero);
      while (ss >> simbolo) {
        alfabeto_.InsertarSimbolo(simbolo);
      }
    } else if (posicion == 2) {
      estados_.reserve(std::stoi(linea_fichero));
    } else if (posicion == 3) {
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
      while (ss >> simbolo_transicion >> estado_transitar) {
        transiciones[simbolo_transicion] = estado_transitar;
      }
      
      Estado estado(transiciones, es_aceptacion, nombre_estado, numero_transiciones);
      estados_.push_back(estado);
    }
  }
}

Gramatica DFA::ConvertToGrammar() const {
  std::set<char> terminales = alfabeto_.GetAlfabeto();
  std::set<std::string> no_terminales;
  std::vector<Produccion> producciones;

  // Funcion auxiliar para formatear nombre de no terminal (ej: q0 -> Q0 o S)
  auto NombreNoTerminal = [](int id_estado) -> std::string {
    return "Q" + std::to_string(id_estado);
  };

  std::string simbolo_arranque = NombreNoTerminal(estado_inicial_);

  for (const auto& estado : estados_) {
    std::string origen = NombreNoTerminal(estado.GetNumeroEstado());
    no_terminales.insert(origen);

    // Reglas A -> aB para cada transicion delta(A, a) = B
    for (const auto& transicion : estado.GetTransiciones()) {
      char simbolo = transicion.first;
      int destino_id = transicion.second;
      std::string destino = std::string(1, simbolo) + NombreNoTerminal(destino_id);

      producciones.push_back({origen, destino});
    }

    // Regla A -> & si el estado es de aceptacion
    if (estado.GetEsAceptacion()) {
      producciones.push_back({origen, "&"});
    }
  }

  return Gramatica(terminales, no_terminales, simbolo_arranque, producciones);
}