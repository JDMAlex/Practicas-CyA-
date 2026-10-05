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

#ifndef P04_HTML_ANALYZER
#define P04_HTML_ANALYZER

#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <vector>

class Etiqueta;
class Atributo;

class DocumentoHTML{
  public:
    //Getter
    std::vector<Etiqueta> GetEtiquetas();
    //Metodos
    void LeerFichero(std::string fichero_entrada);
    void ExtraerEtiqueta(const std::string& linea, int num_linea);

  private:
    std::vector<Etiqueta> Etiquetas_;

};


class Etiqueta{
  public:
    //Constructor
    Etiqueta();
    Etiqueta(std::string etiqueta, int linea);
    //Getter
    std::string GetEtiqueta();
    int GetLinea();
    Atributo GetAtributo();

    private:
    std::string etiqueta_;
    int linea_;
    Atributo atributo_;
};

class Atributo{
  public:
  //constructor
  Atributo();
  Atributo(int numero_atributo, std::string nombre_atributo);
  //Getter
  std::string GetNombreAtributo();
  int GetNumeroAtributo();

  private:
  int numero_atributo_;
  std::string nombre_atributo_;
};

class Comentario{
  public:

  private:
};


void InformacionHelp();





#endif 