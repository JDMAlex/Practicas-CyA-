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

void informacion_de_uso();

class Alfabeto {
  public:
  Alfabeto() = default;
  Alfabeto(std::set<char> alfabeto);
  std::set<char> GetAlfabeto();
  bool EsDelAlfabeto(char simbolo);

  private:
    std::set<char> alfabeto_;
};

class Transicion {
  public:


  private:
  

};

class Estado {
  public:


  private:
  Transicion transiciones_;
  bool aceptacion_;
  int numero_estado_;

};

class DFA {
  public:
  DFA() = default;
  DFA();
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