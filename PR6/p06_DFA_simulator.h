
#ifndef P06_DFA_SIMULATOR
#define P06_DFA_SIMULATOR

#include<iostream>
#include<set>
#include<string>
#include<vector>
#include<fstream>

class Alfabeto {
  public:
    Alfabeto() = default;
    Alfabeto(const std::set<char>& simbolos);
    std::set<char> GetAlfabeto() const;
    void InsertarSimbolo(char simbolo);
    bool PerteneceAlfabeto(char simbolo_verificar) const;

  private:
    std::set<char> simbolos_;
};

class Transicion {
  public:
    Transicion() = default;
    Transicion(char simbolo, const std::string& estado_siguiente);
    char GetSimbolo() const;
    std::string GetEstadoSiguiente() const;


  private:
    char simbolo_;
    std::string estado_siguiente_;
};

class Estado {
  public:
    Estado() = default;
    Estado(std::string nombre_estado_, bool es_aceptacion, const std::vector<Transicion>& transiciones);
    std::string GetNombreEstado() const;
    bool GetEsAceptacion() const;
    std::vector<Transicion> GetTransiciones() const;
    std::string GetSiguienteEstado(char simbolo) const;
  private:
    std::string nombre_estado_;
    bool es_aceptacion_;
    std::vector<Transicion> transiciones_; 
};

class DFA {
  public:
    DFA() = default;
    DFA(const Alfabeto& alfabeto, const Estado& estado_inicial, const std::vector<Estado>& conjunto_estados);
    Alfabeto GetAlfabeto() const;
    Estado GetEstadoInicial() const;
    std::vector<Estado> GetEstados() const;
    void LeerDFA(const std::string& DFA);

  private:
    Alfabeto alfabeto_;
    Estado estado_inicial_;
    std::vector<Estado> conjunto_estados_;

};


#endif