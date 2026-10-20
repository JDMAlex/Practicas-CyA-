/**
 * @file p06_DFA_simulator.h
 * @brief Declaración de las clases que modelan un DFA y su simulación.
 * @author Alexandro
 * @date 2026-10-20
 *
 * Práctica 6 de Computabilidad y Algoritmia (Grado en Ingeniería Informática,
 * Universidad de La Laguna).
 */

#ifndef P06_DFA_SIMULATOR
#define P06_DFA_SIMULATOR

#include<iostream>
#include<set>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include <sstream>

/**
 * @brief Imprime por pantalla la ayuda del programa (opción --help),
 *        incluyendo el formato de los ficheros .dfa y .txt.
 */
void InformacionHelp();

/**
 * @class Alfabeto
 * @brief Conjunto de símbolos que acepta como entrada un DFA.
 */
class Alfabeto {
  public:
    /// @brief Construye un alfabeto vacío.
    Alfabeto() = default;
    /**
     * @brief Construye un alfabeto a partir de un conjunto de símbolos.
     * @param simbolos Símbolos que formarán el alfabeto.
     */
    Alfabeto(const std::set<char>& simbolos);
    /// @return Conjunto de símbolos del alfabeto.
    std::set<char> GetAlfabeto() const;
    /**
     * @brief Inserta un símbolo en el alfabeto (si ya existe, no hace nada).
     * @param simbolo Símbolo a insertar.
     */
    void InsertarSimbolo(char simbolo);
    /**
     * @brief Comprueba si un símbolo pertenece al alfabeto.
     * @param simbolo_verificar Símbolo a comprobar.
     * @return true si el símbolo pertenece al alfabeto, false en caso contrario.
     */
    bool PerteneceAlfabeto(char simbolo_verificar) const; 
  private:
    std::set<char> simbolos_; ///< Símbolos que componen el alfabeto.
};
/**
 * @class Transicion
 * @brief Arco del diagrama de transiciones: un símbolo de entrada y el
 *        estado al que se llega al consumirlo.
 */
class Transicion {
  public:
    /// @brief Construye una transición vacía.
    Transicion() = default;
    /**
     * @brief Construye una transición.
     * @param simbolo Símbolo de entrada que la activa.
     * @param estado_siguiente Nombre del estado destino.
     */
    Transicion(char simbolo, const std::string& estado_siguiente);
    /// @return Símbolo de entrada que activa la transición.
    char GetSimbolo() const;
    /// @return Nombre del estado destino de la transición.
    std::string GetEstadoSiguiente() const;


  private:
    char simbolo_;  ///< Símbolo de entrada que provoca la transición.
    std::string estado_siguiente_;  ///< Nombre del estado al que se transita.
};

/**
 * @class Estado
 * @brief Estado de un DFA, con su carácter de aceptación y sus transiciones
 *        salientes.
 */
class Estado {
  public:
    /// @brief Construye un estado vacío.
    Estado() = default;
    /**
     * @brief Construye un estado.
     * @param nombre_estado Identificador del estado.
     * @param es_aceptacion true si es un estado de aceptación.
     * @param transiciones Transiciones que parten de este estado.
     */
    Estado(std::string nombre_estado_, bool es_aceptacion, const std::vector<Transicion>& transiciones);
    /// @return Identificador del estado.
    std::string GetNombreEstado() const;
    /// @return true si el estado es de aceptación.
    bool GetEsAceptacion() const;
    /// @return Transiciones salientes del estado.
    std::vector<Transicion> GetTransiciones() const;
    /**
     * @brief Calcula el estado destino para un símbolo de entrada.
     * @param simbolo Símbolo leído.
     * @return Nombre del estado destino, o "&" si no existe transición
     *         con ese símbolo.
     */
    std::string GetSiguienteEstado(char simbolo) const;
  private:
    std::string nombre_estado_;              ///< Identificador único del estado.
    bool es_aceptacion_;                     ///< Indica si es un estado final (de aceptación).
    std::vector<Transicion> transiciones_;   ///< Transiciones salientes del estado.
};

/**
 * @class DFA
 * @brief Autómata Finito Determinista capaz de cargarse desde un fichero
 *        .dfa y de simular cadenas de entrada.
 */
class DFA {
  public:
    /// @brief Construye un DFA vacío, a rellenar con LeerDFA().
    DFA() = default;
    /**
     * @brief Construye un DFA a partir de sus componentes.
     * @param alfabeto Alfabeto de entrada.
     * @param estado_inicial Estado de arranque.
     * @param conjunto_estados Todos los estados, indexados por nombre.
     */
    DFA(const Alfabeto& alfabeto, const Estado& estado_inicial, const std::map<std::string, Estado>& conjunto_estados);
    /// @return Alfabeto del autómata.
    Alfabeto GetAlfabeto() const;
    /// @return Estado inicial del autómata.
    Estado GetEstadoInicial() const;
    /// @return Conjunto de estados indexados por nombre.
    std::map<std::string, Estado> GetEstados() const;
    /**
     * @brief Carga y valida la especificación de un DFA desde un fichero .dfa.
     *
     * Las líneas vacías o que empiezan por "//" se ignoran. Notifica por
     * std::cerr los errores de definición: estado inicial inexistente,
     * número de estados incoherente, símbolos fuera del alfabeto,
     * transiciones a estados inexistentes o autómata incompleto.
     *
     * @param input_DFA Ruta del fichero .dfa.
     * @return true si el DFA se ha creado correctamente, false si hubo error.
     */
    bool LeerDFA(const std::string& input_DFA);
    /**
     * @brief Simula el autómata sobre una cadena e imprime la traza
     *        (estado actual, entrada, nuevo estado) y el veredicto.
     * @param cadena Cadena a procesar; "&" representa la cadena vacía.
     */
    void SimularCadena(const std::string& cadena) const;
    /**
     * @brief Indica si una línea del fichero .dfa debe ignorarse.
     * @param linea Línea leída del fichero.
     * @return true si está vacía o empieza por "//".
     */
    bool EsComentario(const std::string& linea) const;

    /**
     * @brief Lee un fichero de cadenas (una por línea) y simula cada una.
     * @param input_cadena Ruta del fichero .txt con las cadenas.
     */
    void LeerCadena(const std::string& input_cadena) const;

  private:
    Alfabeto alfabeto_;                                 ///< Alfabeto de entrada del autómata.
    Estado estado_inicial_;                             ///< Estado en el que arranca la simulación.
    std::map<std::string, Estado> conjunto_estados_;    ///< Todos los estados, indexados por nombre.
};


#endif