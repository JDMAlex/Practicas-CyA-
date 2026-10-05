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
  std::regex etiqueta_regex(R"(<(/?)(html|head|title|body|h1|p|a|img)\b[^>]*>)");
  std::smatch coincidencia;

  while(std::regex_search(linea, coincidencia, etiqueta_regex)){
    bool es_cierre =  ! coincidencia[1].str().empty();
    std::string nombre_etiqueta = coincidencia[2].str();
    std::cout << "[numero linea= " << num_linea << "]"; 
    if(es_cierre == true){
      std::cout << "/" << nombre_etiqueta << std::endl;
    } else {
      std::cout << nombre_etiqueta << std::endl;
    }
    
  }
  
}

//CLASE ETIQUETA
Etiqueta::Etiqueta() : etiqueta_(" "), linea_(0) {}
Etiqueta::Etiqueta(std::string etiqueta, int linea) : etiqueta_(etiqueta), linea_(linea) {}
std::string Etiqueta::GetEtiqueta(){
  return etiqueta_;
}
int Etiqueta::GetLinea(){
  return linea_;
}
Atributo Etiqueta::GetAtributo(){
  return atributo_;
}

//CLASE ATRIBUTO
Atributo::Atributo() : numero_atributo_(0), nombre_atributo_(" ") {}
Atributo::Atributo(int numero_atributo, std::string nombre_atributo) : numero_atributo_(numero_atributo), nombre_atributo_(nombre_atributo) {}
std::string Atributo::GetNombreAtributo(){
  return nombre_atributo_;
}
int Atributo::GetNumeroAtributo(){
  return numero_atributo_;
}
