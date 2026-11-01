/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 8: Gramática Regular a partir de un DFA
 * 
 * @file dfa2grammar.h
 * @author Alexandro Dorta Mirena (alu0101802961@ull.edu.es)
 * @date 16/10/2026
 * @brief Declaración de las clases Alfabeto, Estado, DFA y Gramatica.
 */

#ifndef DFA2GRAMMAR_H
#define DFA2GRAMMAR_H

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Muestra el mensaje de ayuda de uso del programa.
 */
void informacion_de_uso();

/**
 * @class Alfabeto
 * @brief Clase que representa el alfabeto de símbolos de un autómata o gramática.
 */
class Alfabeto {
 public:
  Alfabeto() = default;
  
  /**
   * @brief Constructor con un conjunto inicial de símbolos.
   * @param simbolos_alfabeto Conjunto de caracteres pertenecientes al alfabeto.
   */
  explicit Alfabeto(const std::set<char>& simbolos_alfabeto);

  /**
   * @brief Obtiene el conjunto de símbolos del alfabeto.
   * @return std::set<char> Conjunto de caracteres del alfabeto.
   */
  std::set<char> GetAlfabeto() const;

  /**
   * @brief Comprueba si un símbolo pertenece al alfabeto.
   * @param simbolo_entrada Carácter a comprobar.
   * @return true si pertenece, false en caso contrario.
   */
  bool EsDelAlfabeto(char simbolo_entrada) const;

  /**
   * @brief Inserta un nuevo símbolo en el alfabeto.
   * @param simbolo_entrada Carácter a añadir.
   */
  void InsertarSimbolo(char simbolo_entrada);

 private:
  /// Conjunto de símbolos únicos que conforman el alfabeto.
  std::set<char> simbolos_alfabeto_;
};

/**
 * @class Estado
 * @brief Clase que representa un estado individual dentro de un autómata finito.
 */
class Estado {
 public:
  Estado() = default;

  /**
   * @brief Constructor parametrizado de un Estado.
   * @param transiciones Mapa de símbolos a IDs de estado destino.
   * @param aceptacion Indica si el estado es final/aceptación.
   * @param numero_estado Identificador numérico del estado.
   * @param numero_transiciones Cantidad de transiciones salientes del estado.
   */
  Estado(const std::map<char, int>& transiciones, bool aceptacion, int numero_estado, int numero_transiciones);

  /**
   * @brief Obtiene el mapa de transiciones del estado.
   * @return std::map<char, int> Transiciones (símbolo -> estado destino).
   */
  std::map<char, int> GetTransiciones() const;

  /**
   * @brief Indica si el estado es de aceptación.
   * @return true si es final, false si no lo es.
   */
  bool GetEsAceptacion() const;

  /**
   * @brief Obtiene el identificador numérico del estado.
   * @return int Identificador del estado.
   */
  int GetNumeroEstado() const;

  /**
   * @brief Obtiene el número de transiciones registradas en el estado.
   * @return int Número de transiciones.
   */
  int GetNumeroTransiciones() const;

 private:
  /// Mapa que relaciona cada símbolo con el ID del estado destino.
  std::map<char, int> transiciones_;
  /// Booleano que marca si el estado es final (true) o no (false).
  bool aceptacion_{false};
  /// Identificador entero del estado.
  int numero_estado_{0};
  /// Cantidad total de transiciones definidas para este estado.
  int numero_transiciones_{0};
};

/**
 * @struct Produccion
 * @brief Representa una regla de producción A -> alpha en la gramática.
 */
struct Produccion {
  /// Símbolo no terminal de origen.
  std::string origen;
  /// Cadena formada por símbolos terminales y/o no terminales de destino.
  std::string destino;
};

/**
 * @class Gramatica
 * @brief Clase que representa una Gramática Regular G = (Sigma, V, S, P).
 */
class Gramatica {
 public:
  Gramatica() = default;

  /**
   * @brief Constructor completo de una Gramática.
   * @param terminales Conjunto de símbolos terminales.
   * @param no_terminales Conjunto de símbolos no terminales.
   * @param arranque Símbolo de arranque o inicial.
   * @param producciones Lista de reglas de producción.
   */
  Gramatica(const std::set<char>& terminales,
            const std::set<std::string>& no_terminales,
            const std::string& arranque,
            const std::vector<Produccion>& producciones);

  /**
   * @brief Escribe la especificación de la gramática en un fichero plano .gra.
   * @param nombre_fichero Ruta del fichero de salida.
   */
  void EscribirGramatica(const std::string& nombre_fichero) const;

 private:
  /// Conjunto de símbolos terminales de la gramática.
  std::set<char> terminales_;
  /// Conjunto de símbolos no terminales de la gramática.
  std::set<std::string> no_terminales_;
  /// Símbolo inicial/arranque de la gramática.
  std::string arranque_;
  /// Vector con todas las reglas de producción.
  std::vector<Produccion> producciones_;
};

/**
 * @class DFA
 * @brief Clase que representa un Autómata Finito Determinista (DFA).
 */
class DFA {
 public:
  DFA() = default;

  /**
   * @brief Constructor que lee el autómata desde un fichero .dfa.
   * @param nombre_fichero_dfa Ruta del archivo con la especificación del DFA.
   */
  explicit DFA(const std::string& nombre_fichero_dfa);

  /**
   * @brief Constructor parametrizado de un DFA.
   * @param alfabeto Alfabeto del autómata.
   * @param estados Lista de estados del autómata.
   * @param estado_inicial ID del estado inicial.
   */
  DFA(const Alfabeto& alfabeto, const std::vector<Estado>& estados, int estado_inicial);
  
  /**
   * @brief Obtiene el alfabeto del DFA.
   * @return Alfabeto del autómata.
   */
  Alfabeto GetAlfabeto() const;

  /**
   * @brief Obtiene la lista de estados del DFA.
   * @return std::vector<Estado> Vector de estados.
   */
  std::vector<Estado> GetEstados() const;

  /**
   * @brief Obtiene el identificador del estado inicial.
   * @return int ID del estado inicial.
   */
  int GetInicial() const;

  /**
   * @brief Lee la especificación del autómata desde un fichero .dfa.
   * @param DFA_a_leer Ruta del archivo .dfa.
   */
  void LeerDFA(const std::string& DFA_a_leer);

  /**
   * @brief Convierte el autómata en una Gramática Regular equivalente.
   * @return Gramatica Objeto generado con la definición formal.
   */
  Gramatica ConvertToGrammar() const;

 private:
  /// Alfabeto del autómata finito determinista.
  Alfabeto alfabeto_;
  /// Colección de estados que componen el autómata.
  std::vector<Estado> estados_;
  /// Identificador numérico del estado inicial del autómata.
  int estado_inicial_{0};
};

#endif