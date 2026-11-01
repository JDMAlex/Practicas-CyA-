// Universidad de La Laguna
// Escuela Superior de Ingenieria y Tecnologia
// Grado en Ingenieria Informatica
// Asignatura: Computabilidad y Algoritmia
// Autor: Alexandro Dorta Mirena
// Correo: alu0101802961@ull.edu.es

#ifndef DFA2GRAMMAR_H
#define DFA2GRAMMAR_H

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

void informacion_de_uso();

class Alfabeto {
 public:
  Alfabeto() = default;
  Alfabeto(const std::set<char>& simbolos_alfabeto);
  std::set<char> GetAlfabeto() const;
  bool EsDelAlfabeto(char simbolo_entrada) const;
  void InsertarSimbolo(char simbolo_entrada);

 private:
  std::set<char> simbolos_alfabeto_;
};

class Estado {
 public:
  Estado() = default;
  Estado(const std::map<char, int>& transiciones, bool aceptacion, int numero_estado, int numero_transiciones);
  std::map<char, int> GetTransiciones() const;
  bool GetEsAceptacion() const;
  int GetNumeroEstado() const;
  int GetNumeroTransiciones() const;

 private:
  std::map<char, int> transiciones_;
  bool aceptacion_;
  int numero_estado_;
  int numero_transiciones_;
};

// Estructura para representar una regla de produccion A -> alpha
struct Produccion {
  std::string origen;
  std::string destino;
};

class Gramatica {
 public:
  Gramatica() = default;
  Gramatica(const std::set<char>& terminales,
            const std::set<std::string>& no_terminales,
            const std::string& arranque,
            const std::vector<Produccion>& producciones);

  void EscribirGramatica(const std::string& nombre_fichero) const;

 private:
  std::set<char> terminales_;
  std::set<std::string> no_terminales_;
  std::string arranque_;
  std::vector<Produccion> producciones_;
};

class DFA {
 public:
  DFA() = default;
  explicit DFA(const std::string& nombre_fichero_dfa);
  DFA(const Alfabeto& alfabeto, const std::vector<Estado>& estados, int estado_inicial);
  
  Alfabeto GetAlfabeto() const;
  std::vector<Estado> GetEstados() const;
  int GetInicial() const;
  void LeerDFA(const std::string& DFA_a_leer);

  // Metodo de conversion solicitado en la practica
  Gramatica ConvertToGrammar() const;

 private:
  Alfabeto alfabeto_;
  std::vector<Estado> estados_;
  int estado_inicial_;
};

#endif