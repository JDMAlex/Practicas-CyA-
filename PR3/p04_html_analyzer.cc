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

void DocumentoHTML::DescripcionPrograma(const std::string& linea){
  std::regex expresion_regular(R"regex(-- ([^^-]*)--)regex");
  std::smatch coincidencia;
  std::regex_search(linea, coincidencia, expresion_regular);
  Descripcion_programa_ = coincidencia[1].str();
}

void DocumentoHTML::EscribirFichero(std::string fichero_salida, std::string fichero_entrada){
  std::ofstream fichero_escribir(fichero_salida);
  if(!fichero_escribir.is_open()){
    std::cerr << "fichero no escrito" << std::endl;
    return;
  }

  fichero_escribir << "PROGRAM: " << fichero_entrada << std::endl;
  fichero_escribir << std::endl;

  fichero_escribir << "DESCRIPCION: " << std::endl;
  fichero_escribir << Descripcion_programa_ << std::endl;


  fichero_escribir << "STRUCTURE:" << std::endl;
  for(size_t i = 0; i < Etiquetas_.size(); ++i){ 
    if(Etiquetas_[i].GetEtiqueta() == "html" || Etiquetas_[i].GetEtiqueta() == "head" || Etiquetas_[i].GetEtiqueta() == "body"){
      std::string nombre_etiqueta = Etiquetas_[i].GetEtiqueta();
      Estructura estructura_etiqueta(true, nombre_etiqueta);
      Estructuras_.push_back(estructura_etiqueta);
    }
  }
  for(size_t i = 0; i < Estructuras_.size(); ++i){
    if(Estructuras_[i].GetEsta() == true){
      fichero_escribir << Estructuras_[i].GetNombreEstructura() << ": TRUE" << std::endl;
    } else {  
      fichero_escribir << Estructuras_[i].GetNombreEstructura() << ": FALSE" << std::endl;
    }
  }
  
  fichero_escribir << "TAGS:" << std::endl;
  for(size_t i = 0; i < Etiquetas_.size(); ++i){ 
    fichero_escribir << "[line " << Etiquetas_[i].GetLinea() << "] " << Etiquetas_[i].GetEtiqueta() << std::endl;
  }
  fichero_escribir << std::endl;

  fichero_escribir << "ATTRIBUTES :" << std::endl;
  for(size_t i = 0; i < Etiquetas_.size(); ++i){
    if(Etiquetas_[i].GetAtributo().empty() == false){
      fichero_escribir << "[line " << Etiquetas_[i].GetLinea() << "] " << Etiquetas_[i].GetEtiqueta() << std::endl;
      for(size_t j = 0; j < Etiquetas_[i].GetAtributo().size(); ++j){
      fichero_escribir << Etiquetas_[i].GetAtributo()[j].GetNombreAtributo() << " = " << "\"" <<Etiquetas_[i].GetAtributo()[j].GetValorAtributo() << "\"" << std::endl;
      }
      fichero_escribir << std::endl;
    }
  }



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

//CLASE ESTRUCTURA
Estructura::Estructura() : esta_(false), nombre_estructura_(" ") {}
Estructura::Estructura(bool esta, std::string nombre_estructura) : esta_(esta), nombre_estructura_(nombre_estructura) {}
bool Estructura::GetEsta(){
  return esta_;
}
std::string Estructura::GetNombreEstructura(){
  return nombre_estructura_;
}