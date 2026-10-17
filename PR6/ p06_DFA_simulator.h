
#ifndef P06_DFA_SIMULATOR
#define P06_DFA_SIMULATOR

#include<iostream>
#include<set>
#include<string>

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
    char GetSimbolo();
    std::string GetEstadoSiguiente();


  private:
    char simbolo_;
    std::string estado_siguiente_;
};


#endif