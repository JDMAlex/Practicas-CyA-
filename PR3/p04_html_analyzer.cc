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
  std::cout << "Uso: ./p04_html_analyzer <entrada.html> <salida.txt>" << std::endl;
  std::cout << "  entrada.html : fichero HTML a analizar" << std::endl;
  std::cout << "  salida.txt   : fichero donde se escribe el resumen" << std::endl;
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
    DescripcionPrograma(linea);
  
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
  EscribirEstructuraExtra(fichero_escribir);
  
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
  EscribirComentarios(fichero_escribir);

}

static int ContarLineas(const std::string& texto, size_t hasta){
  int contador = 0;
  for(size_t i = 0; i < hasta && i < texto.size(); ++i){
    if(texto[i] == '\n') ++contador;
  }
  return contador;
}

void DocumentoHTML::LeerComentarios(std::string fichero_entrada){
  std::ifstream fichero_abierto(fichero_entrada);
  if(!fichero_abierto.is_open()){
    return;
  }
  std::string contenido, linea;
  while(std::getline(fichero_abierto, linea)){
    contenido += linea + "\n";
  }
  size_t fin_doctype = DetectarDoctype(contenido);
  ExtraerComentarios(contenido, fin_doctype);
}

size_t DocumentoHTML::DetectarDoctype(const std::string& contenido){
  std::regex expresion_regular(R"(<!DOCTYPE\s+html\s*>)", std::regex::icase);
  std::smatch coincidencia;
  if(std::regex_search(contenido, coincidencia, expresion_regular)){
    doctype_ = true;
    linea_doctype_ = ContarLineas(contenido, coincidencia.position(0)) + 1;
    return coincidencia.position(0) + coincidencia.length(0);
  }
  return std::string::npos;
}

void DocumentoHTML::ExtraerComentarios(const std::string& contenido, size_t fin_doctype){
  std::regex expresion_regular(R"(<!--([\s\S]*?)-->)");
  auto palabra_inicio = std::sregex_iterator(contenido.begin(), contenido.end(), expresion_regular);
  auto palabra_final = std::sregex_iterator();
  int comentarios_antes_doctype = 0;

  for(std::sregex_iterator i = palabra_inicio; i != palabra_final; ++i){
    std::smatch coincidencia = *i;
    size_t posicion = coincidencia.position(0);
    std::string texto = coincidencia.str(0);
    int linea_inicio = ContarLineas(contenido, posicion) + 1;
    int linea_fin = linea_inicio + ContarLineas(texto, texto.size());
    if(fin_doctype != std::string::npos && posicion < fin_doctype){
      ++comentarios_antes_doctype;
    }
    Comentarios_.push_back(Comentario(texto, linea_inicio, linea_fin));
  }

  // Descripcion: comentario inmediatamente despues del DOCTYPE
  if(fin_doctype != std::string::npos){
    std::string resto = contenido.substr(fin_doctype);
    std::regex expresion_descripcion(R"(^\s*<!--([\s\S]*?)-->)");
    std::smatch coincidencia;
    if(std::regex_search(resto, coincidencia, expresion_descripcion)){
      indice_descripcion_ = comentarios_antes_doctype;
      std::regex espacios(R"(^\s+|\s+$)");
      Descripcion_programa_ = std::regex_replace(coincidencia[1].str(), espacios, std::string(""));
    }
  }
}

bool DocumentoHTML::TieneEtiqueta(const std::string& nombre){
  for(size_t i = 0; i < Etiquetas_.size(); ++i){
    if(Etiquetas_[i].GetEtiqueta() == nombre) return true;
  }
  return false;
}

void DocumentoHTML::EscribirEstructuraExtra(std::ofstream& fichero){
  const std::vector<std::string> obligatorias = {"html", "head", "body"};
  for(size_t i = 0; i < obligatorias.size(); ++i){
    if(!TieneEtiqueta(obligatorias[i])){
      fichero << obligatorias[i] << ": FALSE" << std::endl;
    }
  }
  fichero << "DOCTYPE: " << (doctype_ ? "HTML5" : "FALSE") << std::endl;
  fichero << std::endl;
}

void DocumentoHTML::EscribirComentarios(std::ofstream& fichero){
  fichero << "COMMENTS :" << std::endl;
  for(size_t i = 0; i < Comentarios_.size(); ++i){
    int inicio = Comentarios_[i].GetLineaInicio();
    int fin = Comentarios_[i].GetLineaFin();
    fichero << "[Line " << inicio;
    if(fin != inicio) fichero << "-" << fin;
    fichero << "]";
    if(static_cast<int>(i) == indice_descripcion_) fichero << " DESCRIPTION";
    fichero << std::endl;
    fichero << Comentarios_[i].GetTexto() << std::endl;
    fichero << std::endl;
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

//CLASE COMENTARIO
Comentario::Comentario() : texto_(""), linea_inicio_(0), linea_fin_(0) {}
Comentario::Comentario(std::string texto, int linea_inicio, int linea_fin) : texto_(texto), linea_inicio_(linea_inicio), linea_fin_(linea_fin) {}
std::string Comentario::GetTexto(){
  return texto_;
}
int Comentario::GetLineaInicio(){
  return linea_inicio_;
}
int Comentario::GetLineaFin(){
  return linea_fin_;
}
