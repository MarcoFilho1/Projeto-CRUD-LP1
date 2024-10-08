#include "../headers/Pessoa.h"

/*
  -Corpo dos m�todos de Pessoa-

  Pessoa � uma superclasse, possuindo os atributos:
    Data DataDeNascimento
    std::string Nome
    std::string Codigo
    std::string Nacionalidade
    int idade
    int tipo

  -> Todos esses atributos s�o comuns entre suas subclasses e cada atributo possui getters e setters
  -> Pessoa tamb�m possui o m�todo exibir(), sendo este sobrescrito por cada subclasse, mas que utiliza esse m�todo como molde
*/

Pessoa::Pessoa() {
  this->DataDeNascimento = Data();
  this->Nome = "";
  this->Codigo = "";
  this->Nacionalidade = "";
  this->idade = 0;
  this->tipo = 0;
}

Pessoa::~Pessoa() {
}

Pessoa::Pessoa(Data DataDeNascimento, std::string Nome, std::string Codigo, std::string Nacionalidade, int idade, int tipo) {
  this->DataDeNascimento = DataDeNascimento;
  this->Nome = Nome;
  this->Codigo = Codigo;
  this->Nacionalidade = Nacionalidade;
  this->idade = idade;
  this->tipo = tipo;
};

Data Pessoa::getDataDeNascimento() {
  return this->DataDeNascimento;
};

std::string Pessoa::getNome() {
  return this->Nome;
};

std::string Pessoa::getCodigo() {
  return this->Codigo;
};

std::string Pessoa::getNacionalidade() {
  return this->Nacionalidade;
};

int Pessoa::getIdade() {
  return this->idade;
};

int Pessoa::getTipo() {
  return this->tipo;
};

void Pessoa::exibir() {
  std::cout << "Nome: " << this->Nome << std::endl;
  std::cout << "Data de Nascimento: ";
  this->DataDeNascimento.exibir();
  std::cout << "C�digo: " << this->Codigo << std::endl;
  std::cout << "Nacionalidade: " << this->Nacionalidade << std::endl;
  std::cout << "Idade: " << this->idade << std::endl;
}

void Pessoa::setDataDeNascimento(Data DataDeNascimento) {
  this->DataDeNascimento = DataDeNascimento;
};

void Pessoa::setNome(std::string Nome) {
  this->Nome = Nome;
};

void Pessoa::setCodigo(std::string Codigo) {
  this->Codigo = Codigo;
};

void Pessoa::setNacionalidade(std::string Nacionalidade) {
  this->Nacionalidade = Nacionalidade;
};

void Pessoa::setIdade(int idade) {
  this->idade = idade;
};