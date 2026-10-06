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

int main(int argc, char* argv[]){
  if(argc == 1){
    std::cerr << "Modo de empleo: " << argv[0] << " pagina . html esquema . txt" << std::endl;
    std::cerr << "Pruebe " << argv[0] << " --help para mas informacion." << std::endl;
    return 1;
  }
  if(argc == 2){
    std::string help = argv[1];
    if(help == "--help"){
      InformacionHelp();
      return 0;
    }
  }
  if(argc < 3){
    std::cerr << "faltan argumentos" << std::endl;
    return 1;
  }
  std::string fichero_entrada = argv[1];
  std::string fichero_salida = argv[2];
  DocumentoHTML Documento_html;
  Documento_html.LeerFichero(fichero_entrada);
  Documento_html.LeerComentarios(fichero_entrada);
  Documento_html.EscribirFichero(fichero_salida, fichero_entrada);

  return 0;
}