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

#include "p04_html_analyzer.h"



void InformacionHelp(){
    std::cout << "hola" << std::endl;
    return;
}


//CLASE DOCUMENTOHTML
std::vector<Etiqueta> DocumentoHTML::GetEtiquetas(){
  return Etiquetas_;
}
void DocumentoHTML::LeerFichero(std::string fichero_entrada){
  std::ifstream fichero_abierto(fichero_entrada);
  if(!fichero_abierto.is_open()){
    std::cerr << "fichero no se ha abierto" << std::endl;
    return;
  }
  int num_linea = 0;
  std::string linea;
  while(std::getline(fichero_abierto, linea)){
    ++num_linea;
    ExtraerEtiqueta(linea, num_linea);
  
  }
}

void DocumentoHTML::ExtraerEtiqueta(const std::string& linea, int num_linea){
  std::regex expresion_regular(R"(<(/?)(html|head|title|body|h1|p|a|img)\b[^>]*>)");

  auto palabra_inicio = std::sregex_iterator(linea.begin(), linea.end(), expresion_regular);
  auto palabra_final = std::sregex_iterator();
  
  for(std::sregex_iterator i = palabra_inicio; i != palabra_final; ++i){
    std::smatch coincidencia = *i;
    bool es_cierre = !coincidencia[1].str().empty();
    std::string etiqueta_nombre = coincidencia[2];
    if(es_cierre == true){
      std::string coincidencia1 = "/";
      etiqueta_nombre = coincidencia1 + etiqueta_nombre;
      std::vector<Atributo> vacio;
      Etiqueta Etiqueta_extraida(etiqueta_nombre, num_linea, vacio);
      Etiquetas_.push_back(Etiqueta_extraida);
    } else {
      std::vector<Atributo> atributos_extraidos = ExtraerAtributo(linea);
      Etiqueta Etiqueta_extraida(etiqueta_nombre, num_linea, atributos_extraidos);
      Etiquetas_.push_back(Etiqueta_extraida);
    }
  }
}

std::vector<Atributo> DocumentoHTML::ExtraerAtributo(const std::string& linea){
  std::regex expresion_regular(R"regex(\b([\w-]+)="([^"]*)")regex");
  auto palabra_inicio = std::sregex_iterator(linea.begin(), linea.end(), expresion_regular);
  auto palabra_final = std::sregex_iterator();
  std::vector<Atributo> Atributos_de_etiqueta;

  for(std::sregex_iterator i = palabra_inicio; i != palabra_final; ++i){
    std::smatch coincidencia = *i;
    std::string nombre_atributo = coincidencia[1];
    std::string valor_atributo = coincidencia[2];
    Atributo Atributo_etiqueta(nombre_atributo, valor_atributo);
    Atributos_de_etiqueta.push_back(Atributo_etiqueta);
  }

  return Atributos_de_etiqueta;
}


//CLASE ETIQUETA
Etiqueta::Etiqueta() : etiqueta_(" "), linea_(0), atributos_{} {}
Etiqueta::Etiqueta(std::string etiqueta, int linea, std::vector<Atributo> atributos) : etiqueta_(etiqueta), linea_(linea), atributos_(atributos) {}
std::string Etiqueta::GetEtiqueta(){
  return etiqueta_;
}
int Etiqueta::GetLinea(){
  return linea_;
}
std::vector<Atributo> Etiqueta::GetAtributo(){
  return atributos_;
}

//CLASE ATRIBUTO
Atributo::Atributo() : nombre_atributo_(" "), valor_atributo_(" ") {}
Atributo::Atributo(std::string nombre_atributo, std::string valor_atributo) : nombre_atributo_(nombre_atributo), valor_atributo_(valor_atributo) {}
std::string Atributo::GetNombreAtributo(){
  return nombre_atributo_;
}
std::string Atributo::GetValorAtributo(){
  return valor_atributo_;
}
