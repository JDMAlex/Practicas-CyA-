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

class Atributo{
  public:
  //constructor
  Atributo();
  Atributo(std::string nombre_atributo , std::string valor_atributo);
  //Getter
  std::string GetNombreAtributo();
  std::string GetValorAtributo();
  private:
  std::string nombre_atributo_;
  std::string valor_atributo_;
};

class Etiqueta{
  public:
    //Constructor
    Etiqueta();
    Etiqueta(std::string etiqueta, int linea, std::vector<Atributo> atributos);
    //Getter
    std::string GetEtiqueta();
    int GetLinea();
    std::vector<Atributo> GetAtributo();

    private:
    std::string etiqueta_;
    int linea_;
    std::vector<Atributo> atributos_;
};

class DocumentoHTML{
  public:
    //Getter
    std::vector<Etiqueta> GetEtiquetas();
    //Metodos
    void LeerFichero(std::string fichero_entrada);
    void ExtraerEtiqueta(const std::string& linea, int num_linea);
    std::vector<Atributo> ExtraerAtributo(const std::string& linea);

  private:
    std::vector<Etiqueta> Etiquetas_;

};


class Comentario{
  public:

  private:
};


void InformacionHelp();





#endif 