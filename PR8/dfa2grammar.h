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

#ifndef DFA2GRAMMAR_H
#define DFA2GRAMMAR_H

#include<iostream>
#include<set>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include <sstream>

void informacion_de_uso();

class Alfabeto {
  public:
  Alfabeto() = default;
  Alfabeto(const std::set<char>& simbolos_alfabeto);
  std::set<char> GetAlfabeto() const;
  bool EsDelAlfabeto(char simbolo_entrada);
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

class DFA {
  public:
  DFA() = default;
  DFA(const Alfabeto& alfabeto, const std::vector<Estado>& estados, int estado_inicial);
  Alfabeto GetAlfabeto() const;
  std::vector<Estado> GetEstados() const;
  int GetInicial() const;
  void LeerDFA(const std::string& DFA_a_leer);

  private:
  Alfabeto alfabeto_;
  std::vector<Estado> estados_;
  int estado_inicial_;
  
};

class Gramatica {
  public:

  private:

};



#endif