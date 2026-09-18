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

#ifndef P02_STRINGS_H
#define P02_STRINGS_H

#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>

class Cadena{
  public:
    //Constructor
    Cadena() = default;
    //Getter
    std::set<std::string> GetCadena() const;
    //Metodo
    void LeerFichero(std::string fichero_entrada);
    void Alfabeto();

    //sobrecarga operador
    friend std::ostream& operator<<(std::ostream& os, const Cadena& cadena);
  private:
    std::set<std::string> cadena_;
};




void MostrarInformacion();



#endif