#ifndef TORCEDOR_H
#define TORCEDOR_H

#include <assert.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Pessoa.h"

class Torcedor : public Pessoa {
protected:
  bool statusVIP;

public:
  int tipo;
  Torcedor();
  Torcedor(Data DataDeNascimento, std::string Nome, std::string Codigo, std::string Nacionalidade, int idade, bool statusVIP);
  bool getStatusVIP();
  std::string getTipo();
  void setTorcedor(Data DataDeNascimento, std::string Nome, std::string Codigo, std::string Nacionalidade, int idade, bool statusVIP);
  void exibir();
};
#endif
