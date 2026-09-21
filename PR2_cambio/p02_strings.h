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

#ifndef P02_CAMBIO_STRINGS_H
#define P02_CAMBIO_STRINGS_H

#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>

class Lenguaje;

class Alfabeto;

class Cadena{
  public:
    //constructor
    Cadena() = default;
    Cadena(const std::string& cadena);
    //Getter
    std::string GetCadena() const;
    //Metodos
    int LongitudCadena();
    Cadena InversaCadena();
    Lenguaje Prefijo();
    Lenguaje Sufijo();
    bool Validacion(Alfabeto alfabeto);
    friend std::istream& operator>>(std::istream& is, Cadena& cadena);
    friend std::ostream& operator<<(std::ostream& os, const Cadena& cadena);

  private:
  std::string cadena_;
};

class Alfabeto{
  public:
    //constructor
    Alfabeto() = default;
    //Getter
    std::set<char> GetAlfabeto();
    //Metodo
    bool Pertenece_alfabeto(Cadena cadena);
    friend std::istream& operator>>(std::istream& is, Alfabeto& alfabeto);
    friend std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto);

  private:
  std::set<char> alfabeto_;
};


class Lenguaje{
  public:
    //constructor
    Lenguaje() = default;
    //Getter
    std::set<std::string> GetLenguaje();
    //Metodos
    void InsertarCadena(const Cadena& cadena);
    friend std::ostream& operator<<(std::ostream& os, const Lenguaje& lenguaje);

  private:
  std::set<std::string> lenguaje_;
};



void MostrarInformacion();


#endif