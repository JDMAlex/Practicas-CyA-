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

class Comentario{
  public:
    //Constructor
    Comentario();
    Comentario(std::string texto, int linea_inicio, int linea_fin);
    //Getter
    std::string GetTexto();
    int GetLineaInicio();
    int GetLineaFin();
  private:
    std::string texto_;
    int linea_inicio_;
    int linea_fin_;
};


class Estructura{
  public:
  //Constructor
  Estructura();
  Estructura(bool esta, std::string nombre_estructura);
  //Getter
  bool GetEsta();
  std::string GetNombreEstructura();

  private:
  bool esta_;
  std::string nombre_estructura_;
};


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
    void EscribirFichero(std::string fichero_salida, std::string fichero_entrada);
    //
    void LeerComentarios(std::string fichero_entrada);
    size_t DetectarDoctype(const std::string& contenido);
    void ExtraerComentarios(const std::string& contenido, size_t fin_doctype);
    bool TieneEtiqueta(const std::string& nombre);
    void EscribirEstructuraExtra(std::ofstream& fichero);
    void EscribirComentarios(std::ofstream& fichero);
    

  private:
    std::vector<Etiqueta> Etiquetas_;
    std::vector<Estructura> Estructuras_;
    std::string Descripcion_programa_;
    //
    std::vector<Comentario> Comentarios_;
    bool doctype_ = false;
    int linea_doctype_ = 0;
    int indice_descripcion_ = -1;
    

};

void InformacionHelp();





#endif 