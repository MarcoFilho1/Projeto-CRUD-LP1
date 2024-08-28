#include <assert.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "GerenciamentoOlimpiadas.h"

GerenciamentoOlimpiadas::GerenciamentoOlimpiadas() {
  /*
  Contrutor padr�o -> Ser� utilizado na inicializa��o do programa,
  a �nica inst�ncia dessa classe dever� ser inicializada sem os dados armazenados,
  para ent�o serem 'settados' todos os seus dados com "setOlimpiadas", m�todo esse que
  � chamado no momento de leitura dos dados das olimp�adas, seja do arquivo, seja diretamente 
  do terminal
  */
  this->DatadeInicio = Data();
  this->Cidade = "";
  this->DataFinal = Data();
  this->mascote = "";
}

void GerenciamentoOlimpiadas::setOlimpiada(Data DatadeInicio, std::string Cidade, Data DataFinal, std::string mascote) {
  /*
    M�todo para atribuir os dados das olimp�adas na inst�ncia da classe, � chamado ap�s
    a leitura de dados, ou do arquivo ou do terminal
  */
  this->DatadeInicio = DatadeInicio;
  this->Cidade = Cidade;
  this->DataFinal = DataFinal;
  this->mascote = mascote;
}

void GerenciamentoOlimpiadas::AdicionarPessoa(Pessoa *p) {
  /*
    Esse m�todo � respons�vel por acrescentar um ponteiro de Pessoa ao vector "gerenciamento"
    Esse m�todo � chamado diversas vezes por outros m�todos, tendo em vista que ele � m�todo respons�vel por inserir Pessoas no vector (intera��o direta), sendo a chave do CREATE do sistema 
  */
  gerenciamento.push_back(p);
}

void GerenciamentoOlimpiadas::lerArquivoOlimpiadas() {
  /*
    Esse m�todo � respons�vel por fazer a leitura dos dados das Olimpiadas, que filtra,
    de acordo com o �xito da abertura do arquivo .txt, "dadosOlimpiadas", se os dados devem
    ser lidos do pr�prio .txt, caso esse exista, ou do terminal.

    -> Utiliza do setter da classe
    
    Execu��o ideal:
      -> Primeira execu��o:
        Os dados devem ser lidos do terminal e salvos no .txt para as pr�ximas execu��es
      -> As sucessivas execu��es:
        Os dados devem ser lidos diretamente do arquivo, podendo ser consultado pelo usu�rio 
        utilizando da op��o 6 do menu

    OBS.: Para altera��o dos dados, o usu�rio dever� apagar o .txt do ambiente em que o 
    programa est� sendo executado
  */
  std::fstream arqOlimpiada;
  arqOlimpiada.open("dadosOlimpiadas.txt", std::ios_base::in);

  if (arqOlimpiada.is_open()) {
    int diaAux, mesAux, anoAux;
    std::string Cidade, mascote;

    arqOlimpiada >> diaAux >> mesAux >> anoAux;
    Data dataInicioAux(diaAux, mesAux, anoAux);
    arqOlimpiada.ignore();

    getline(arqOlimpiada, Cidade);
    arqOlimpiada >> diaAux >> mesAux >> anoAux;

    Data dataFinalAux(diaAux, mesAux, anoAux);
    arqOlimpiada.ignore();

    getline(arqOlimpiada, mascote);

    setOlimpiada(dataInicioAux, Cidade, dataFinalAux, mascote);
    arqOlimpiada.close();

  } else {
    arqOlimpiada.close();
    int diaAux, mesAux, anoAux, anoFinal;

    std::string Cidade, mascote;
    std::cout << "Digite a cidade sede " << std::endl;
    std::cout << "\n-> ";
    getline(std::cin, Cidade);
    std::cout << "\n";

    std::cout << "Digite o ano das olimpiadas de " << Cidade << std::endl;
    std::cout << "\n-> ";
    std::cin >> anoAux;
    std::cout << "\n";

    std::cout << "Digite o mes de " << anoAux << " que comecam as olimpiadas de " << Cidade << std::endl;
    std::cout << "\n-> ";
    std::cin >> mesAux;
    std::cout << "\n";

    std::cout << "Digite dia do mes de " << mesAux << "/" << anoAux << " que comecam as olimpiadas de " << Cidade << std::endl;
    std::cout << "\n-> ";
    std::cin >> diaAux;
    std::cout << "\n";

    Data dataInicioAux(diaAux, mesAux, anoAux);

    std::cout << "Digite o ano que acabam as olimpiadas de " << Cidade << std::endl;
    std::cout << "\n-> ";
    std::cin >> anoFinal;
    std::cout << "\n";

    std::cout << "Digite o mes de " << anoAux << " que acabam as olimpiadas de " << Cidade << std::endl;
    std::cout << "\n-> ";
    std::cin >> mesAux;
    std::cout << "\n";

    std::cout << "Digite dia do mes de " << mesAux << "/" << anoAux << " que acabam as olimpiadas de " << Cidade << std::endl;
    std::cout << "\n-> ";
    std::cin >> diaAux;
    std::cout << "\n";

    Data dataFinalAux(diaAux, mesAux, anoFinal);

    std::cout << "Digite o nome do mascote das olimpiadas de " << Cidade << " " << anoAux << std::endl;
    std::cout << "\n-> ";
    std::cin.ignore();
    getline(std::cin, mascote);
    std::cout << "\n";

    setOlimpiada(dataInicioAux, Cidade, dataFinalAux, mascote);

    // Comeca a escrever no arquivo as informacoes sobre a olimpiada
    // O usuario so consegue "criar" outra olimpiada se apagar o arquivo olimpiada.txt
    // Isso deve ser documentado no README
    arqOlimpiada.open("dadosOlimpiadas.txt", std::ios_base::out);

    // Salvando a data inicial
    arqOlimpiada << dataInicioAux.getDia() << std::endl;
    arqOlimpiada << dataInicioAux.getMes() << std::endl;
    arqOlimpiada << dataInicioAux.getAno() << std::endl;

    // Salvando a cidade
    arqOlimpiada << Cidade << std::endl;

    // Salvando a data final
    arqOlimpiada << dataFinalAux.getDia() << std::endl;
    arqOlimpiada << dataFinalAux.getMes() << std::endl;
    arqOlimpiada << dataFinalAux.getAno() << std::endl;

    // Salvando mascote
    arqOlimpiada << mascote << std::endl;

    arqOlimpiada.close();
  }
};

void GerenciamentoOlimpiadas::lerArquivoPessoas() {
  /*
    Esse m�todo � respons�vel pela leitura do .txt "dadosPessoas", que dever� armazenar todas 
    as pessoas da �ltima execu��o (respeitando a decis�o do usu�rio de inserir, alterar, e remover)
    Para articular a leitura de acordo com a subclasse de pessoa, o c�digo dever� ler na seguinte ordem:
      - 1 . Tipo
      - 2 . Dia da data de nascimento
      - 3 . M�s da data de nascimento
      - 4 . Ano da data de nascimento
      - 5 . Nome
      - 6 . C�digo
      - 7 . Nacionalidade
      - 8 . Medalha     ||  Modalidade          ||  StatusVip
      - 9 . Modalidade  ||  Equipe Responsavel  ||

    OBS.: Na primeira execu��o do c�digo, o arquivo n�o dever� existir, tendo isso em vista, o mesmo n�o ser� lido e o m�todo retorna

    -> Respons�vel por iniciar �ndices do vector "gerenciamento", ou seja, iniciando ponteiros de Pessoa com os construtores das subclasses (realizando polimorfismo)
    -> Tamb�m chama o m�todo de inserir Pessoas no vector (AdicionarPessoa())
  */

  // ->> METODO COM PROBLEMA

  std::fstream arquivo;
  arquivo.open("dadosPessoas.txt", std::ios_base::in);
  if (!arquivo.is_open()) // Retorna caso o arquivo n�o seja aberto
    return;

  // Ler pessoa por pessoa do arquivo
  // Alocando ao vector de pessoas da superclasse
  
  // Declara��o de vari�veis auxiliares para receberem os valores salvos
  int tipoPessoa, diaAux, mesAux, anoAux;
  std::string pessoaNome, pessoaCodigo, pessoaNac;
  int idadeAux;

  while(arquivo >> tipoPessoa >> diaAux >> mesAux >> anoAux) {
    arquivo.ignore();
    Data dataAux = Data(diaAux, mesAux, anoAux);

    std::getline(arquivo, pessoaNome);
    std::getline(arquivo, pessoaCodigo);
    std::getline(arquivo, pessoaNac);
    arquivo >> idadeAux;

    if (tipoPessoa == 1) { // Atleta

      int auxMedalha;
      std::string auxMod;
      arquivo >> auxMedalha;
      arquivo.ignore();
      std::getline(arquivo, auxMod);
      Pessoa *pessoaAux = new Atleta(dataAux, pessoaNome, pessoaCodigo, pessoaNac, idadeAux, tipoPessoa, auxMedalha, auxMod);
      // Instanciando um atleta a partir dos dados do arquivo em PessoaAux

      // Alocando pessoa auxiliar no vector
      AdicionarPessoa(pessoaAux);

    } else if (tipoPessoa == 2) { // Membro da Comissao

      std::string auxMod, auxEquipResp;
      arquivo.ignore();
      std::getline(arquivo, auxMod);
      std::getline(arquivo, auxEquipResp);
      Pessoa *pessoaAux = new Comissao(dataAux, pessoaNome, pessoaCodigo, pessoaNac, idadeAux, tipoPessoa, auxMod, auxEquipResp);

      // Instanciando um membro da comissao a partir dos dados do arquivo em PessoaAux

      // Alocando pessoa auxiliar no vector
      AdicionarPessoa(pessoaAux);

    } else if (tipoPessoa == 3) { // Torcedor

      arquivo.ignore();
      int bitStatusVip;
      arquivo >> bitStatusVip;
      bool auxStatusVip = (bitStatusVip == 1) ? true : false;
      Pessoa *pessoaAux = new Torcedor(dataAux, pessoaNome, pessoaCodigo, pessoaNac, idadeAux, tipoPessoa, auxStatusVip);

      // Instanciando um torcedor a partir dos dados do arquivo em PessoaAux

      // Alocando pessoa auxiliar no vector
      AdicionarPessoa(pessoaAux);
    }
  };

  arquivo.close();
};

void GerenciamentoOlimpiadas::iniciarOlimpiada() {
  /*
    Esse m�todo � respons�vel por chamar os m�todos respons�veis pelo funcionamento sequencial
    das execu��es do programa, sendo os mesmos respons�veis pelo READ do sistema.
  */

  lerArquivoOlimpiadas();
  lerArquivoPessoas();
}

int GerenciamentoOlimpiadas::lerDadosPessoa() {
  /*
    Esse m�todo � respons�vel por ler diretamente do terminal todos os dados de uma determinada Pessoa
    que o usu�rio desejar inserir, ele vai iniciar um ponteiro de Pessoa com as informa��es utilizando
    o construtor da subclasse escolhida pelo usu�rio (tipo) e ao final do m�todo ir� chamar o m�todo
    de adicionar a pessoa no vector "gerenciamento"
    
    -> A partir desse m�todo possu�mos o  CREATE do sistema
  */
  Pessoa *pessoaAux;
  std::string nome, codigo, nacionalidade;
  int dia, mes, ano, idade, tipoPessoa;

  std::cin.ignore();
  std::cout << "Digite o nome da pessoa a ser adicionada" << "\n-> ";
  std::getline(std::cin, nome);
  std::cout << "\n";

  std::cout << "Digite o dia do nascimento de " << nome << "\n-> ";
  std::cin >> dia;
  std::cout << "\n";
  std::cout << "Digite o mes do nascimento de " << nome << "\n-> ";
  std::cin >> mes;
  std::cout << "\n";
  std::cout << "Digite o ano do nascimento de " << nome << "\n-> ";
  std::cin >> ano;
  std::cout << "\n";
  Data dataNasc(dia, mes, ano);

  std::cout << "Digite o codigo de " << nome << "\n-> ";
  std::cin >> codigo;
  std::cout << "\n";
  std::cin.ignore();

  std::cout << "Digite a nacionalidade de " << nome << "\n-> ";
  std::getline(std::cin, nacionalidade);
  std::cout << "\n";

  std::cout << "Digite a idade de " << nome << "\n-> ";
  std::cin >> idade;
  std::cout << "\n";

  std::cout << "Digite o tipo" << std::endl;
  std::cout << "-> 1 Atleta\t-> 2 Membro da comissao\n-> 3 Torcedor\t-> 4 Cancelar operacao\n-> ";
  std::cin >> tipoPessoa;
  std::cout << "\n";

  if (tipoPessoa == 1) {

    std::cin.ignore();
    int medalha;
    std::string modalidade;
    std::cout << "Digite a modalidade do atleta\n-> ";
    std::getline(std::cin, modalidade);
    std::cout << "\n";
    std::cout << "Digite a colocacao de " << nome << " em " << modalidade << "\n-> ";
    std::cin >> medalha;
    std::cout << "\n";

    pessoaAux = new Atleta(dataNasc, nome, codigo, nacionalidade, idade, tipoPessoa, medalha, modalidade);

  } else if (tipoPessoa == 2) {

    std::cin.ignore();
    std::string modalidade, equipeResponsavel;
    std::cout << "Digite a modalidade de atuacao do membro da comissao:\n-> ";
    std::getline(std::cin, modalidade);
    std::cout << "\n";
    std::cout << "Dentro de " << modalidade << ", digite a equipe de atuacao de " << nome << "\n-> ";
    std::getline(std::cin, equipeResponsavel);
    std::cout << "\n";

    pessoaAux = new Comissao(dataNasc, nome, codigo, nacionalidade, idade, tipoPessoa, modalidade, equipeResponsavel);

  } else if (tipoPessoa == 3) {

    std::cin.ignore();
    bool vipBool;
    std::string vip;
    std::cout << "O torcedor " << nome << " possui acesso vip? (Sim/Nao)\n-> ";
    std::getline(std::cin, vip);
    std::cout << "\n";

    if ((vip.find("s") != -1) || (vip.find("S") != -1) ||
        (vip.find("y") != -1) || (vip.find("y") != -1))
      vipBool = true;
    else
      vipBool = false;

    pessoaAux = new Torcedor(dataNasc, nome, codigo, nacionalidade, idade, tipoPessoa, vipBool);
  } else {
    // delete pessoaAux;
  }
  AdicionarPessoa(pessoaAux);
  // delete pessoaAux;
  return 0;
}

void GerenciamentoOlimpiadas::exibirTodos() {
  /*
    Esse m�todo � respons�vel por exibir no terminal todos os �ndices do vector "gerenciamento" de maneira otimizada, imprimindo o valor ordinal do elemento no vector, o tipo da Pessoa (de qual subclasse � uma inst�ncia), seguido do nome. Ex.:

    1o - Atleta : Michael Phelps 
    2o - Comissao : Bernardo Rocha
  */
    if(gerenciamento.size() == 0){
      std::cout << "N�o h� pessoas registradas" << std::endl;
      return;
    } else {
      std::cout << "Pessoas registradas:" << std::endl;
      int contador = 1;
      for (int i = 0; i < gerenciamento.size(); i++) {
          std::cout << contador;
          contador++;
          if(gerenciamento[i]->getTipo() == 1)
            std::cout << "o - Atleta\t";
          if(gerenciamento[i]->getTipo() == 2)
            std::cout << "o - Comissao\t";
          if(gerenciamento[i]->getTipo() == 3)
            std::cout << "o - Torcedor\t";
          std::cout << " : " << gerenciamento[i]->getNome() << std::endl;
        }
    }
}

Pessoa *GerenciamentoOlimpiadas::buscar() {
  /*
    Esse m�todo � respons�vel por realizar a busca por determinada Pessoa no vector, chamando primeiramente o m�todo de exibi��o dos �ndices (exibirTodos()) e ap�s isso tratando da escolha do usu�rio a partir do nome (que dever� coincidir com um dos nomes exibidos no terminal)
    -> Esse m�todo retorna a Pessoa encontrada (que � um ponteiro), retorno esse que deve ser tratado na chamada
    -> Esse m�todo � chamado nos m�todos de exibir (exibir com detalhe apenas uma Pessoa), alterar e remover
  */
  int count = 0;
  exibirTodos();

  std::cout << "\n\nEscolha o nome\n-> ";
  std::string nome;
  std::cin >> std::ws;
  getline(std::cin, nome);
  std::cout << "\n";
  int contador = 0, indice;

  // Testar quantas pessoas tem com o nome digitado
  for (int i = 0; i < gerenciamento.size(); i++) {
    if (gerenciamento[i]->getNome().find(nome) != -1) {
      contador++;
      indice = i;
    }
  }

  // No caso do nome ser incompat�vel com pelo menos um dos nomes no vector, o retorno ser� 
  // um nullptr (ponteiro vazio), esse retorno dever� ser tratado no local de chamada
  if(contador == 0) {
    std::cout << "Pessoa nao encontrada!" << std::endl;
    return nullptr;
  }

  if(contador == 1) 
    return gerenciamento[indice];

  int indiceEscolha;
  for (int i = 0; i < gerenciamento.size(); i++) {
      if(gerenciamento[i]->getNome().find(nome) != -1){

        std::cout << i;

        if(gerenciamento[i]->getTipo() == 1)
          std::cout << " - Atleta\t";

        if(gerenciamento[i]->getTipo() == 2)
          std::cout << " - Comissao\t";

        if(gerenciamento[i]->getTipo() == 3)
          std::cout << " - Torcedor\t";

        std::cout << gerenciamento[i]->getNome() << std::endl;
      }
    }
    
  std::cout << "Escolha o �ndice" << std::endl;
  std::cout << "\n-> ";
  std::cin >> indiceEscolha;
  std::cout << "\n";
  if(indiceEscolha < gerenciamento.size()) {
    return gerenciamento[indiceEscolha];
  } else {
    std::cout << "�ndice inv�lido" << std::endl;
    return nullptr;
  }
}

void GerenciamentoOlimpiadas::gerarRelatorio() {
  /*
    -> Esse m�todo � respons�vel por imprimir no terminal as informa��es gerais das Olimp�adas, sendo elas:
      - Cidade e ano
      - Data de Inicio
      - Data Final
      - Nome do Mascote

    -> E � respons�vel tamb�m por imprimir no terminal as informa��es das Pessoas que est�o cadastradas no sistema, sendo esses dados brutos e comparativos. Caso n�o haja Pessoas cadastradas, ele ir� imprimir e retornar
  */
  std::cout << "\n";
  std::cout << "Olimpiadas de " << Cidade << " " << DatadeInicio.getAno() << std::endl;
  std::cout << "Data de Inicio: ";
  DatadeInicio.exibir();
  std::cout << "Data Final: ";
  DataFinal.exibir();
  std::cout << "Mascote dos jogos: " << mascote << "\n\n";


  int countTotal = 0, countTorcedor = 0, countComissao = 0, countAtleta = 0;

  // Conta pessoas e os tipos
  for (auto p : gerenciamento) {
    if (p->getTipo() == 1)
      countAtleta++;
    else if (p->getTipo() == 2)
      countComissao++;
    else if (p->getTipo() == 3)
      countTorcedor++;
    countTotal++;
  }

  if (countTotal == 0) {
    // Caso o vector seja vazio, ele imprime esse fato e retorna
    std::cout << "Nao ha pessoas cadastradas" << std::endl;
    return;
  } else {
    // Imprime os dados brutos e comparativos das Pessoas
    float porcAtleta = 100 * (float)countAtleta / (float)countTotal;
    float porcComissao = 100 * (float)countComissao / (float)countTotal;
    float porcTorcedor = 100 * (float)countTorcedor / (float)countTotal;

    std::cout << "Quantidade total de pessoas: " << countTotal << std::endl;
    std::cout << "Quantidade total de Atletas: " << countAtleta << " (" << porcAtleta << "%)" << std::endl;
    std::cout << "Quantidade total de Membros da Comissao: " << countComissao << " (" << porcComissao << "%)" << std::endl;
    std::cout << "Quantidade total de Torcedores: " << countTorcedor << " (" << porcTorcedor << "%)" << std::endl;
  }
}

int GerenciamentoOlimpiadas::alterarPessoa() {
  /*
    Esse m�todo � respons�vel por alterar as informa��es de uma determinada Pessoa que j� est� registrada,
    alterando o elemento do vector, sendo o m�todo de salvar o arquivo ao final da execu��o respons�vel por alterar no arquivo

    -> Primeiramente permite ao usu�rio selecionar o elemento do vector, utilizando do m�todo "buscar()"
    -> Ap�s o �xito em selecionar a Pessoa a ser alterada, o m�todo ir� ler qual propriedade, de acordo com o tipo, o usu�rio quer alterar
    -> Considerando as propriedades de Pessoa, que s�o comuns entre as subclassses, essas podem ser
    alterados diretamente sem precisar consultar o tipo

    OBS -> Esse m�todo n�o ir� interagir com o 

    -> Esse m�todo � respons�vel pelo EDIT do sistema

  */
  Pessoa *p = buscar();
  if(!p)
    return 1;
  int indice = 0;
  for (auto busca : gerenciamento) {
    if (busca->getCodigo() == p->getCodigo()) {
      break;
    }
    indice++;
  }
  if (indice > gerenciamento.size())
    return 1;

  int escolha;

  std::cout << "Digite o que sera alterado" << std::endl;
  std::cout << "-> 1 Data de Nascimento" << std::endl;
  std::cout << "-> 2 Nome" << std::endl;
  std::cout << "-> 3 Codigo" << std::endl;
  std::cout << "-> 4 Nacionalidade" << std::endl;
  std::cout << "-> 5 idade" << std::endl;

  if (p->getTipo() == 1) {
    std::cout << "-> 6 Medalha" << std::endl;
    std::cout << "-> 7 Modalidade" << std::endl;
    std::cout << "\n-> ";

  } else if (p->getTipo() == 2) {
    std::cout << "-> 6 Modalidade" << std::endl;
    std::cout << "-> 7 Equipe de atuacao" << std::endl;
    std::cout << "\n-> ";

  } else if (p->getTipo() == 3) {
    std::cout << "-> 6 Status VIP" << std::endl;
    std::cout << "\n-> ";
  }

  std::cin >> escolha;
  std::cout << "\n";

  switch (escolha) {
  case 1: {
    // Para alterar a data de nascimento
    int diaAux, mesAux, anoAux;
    std::cout << "Digite o dia da nova data de nascimento de " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::cin >> diaAux;
    std::cout << "\n";
    std::cout << "Digite o mes da nova data de nascimento de " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::cin >> mesAux;
    std::cout << "\n";
    std::cout << "Digite o ano da nova data de nascimento de " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::cin >> anoAux;
    std::cout << "\n";
    Data novaDataDeNascimento(diaAux, mesAux, anoAux);
    gerenciamento[indice]->setDataDeNascimento(novaDataDeNascimento);
    std::cout << "Nova data de nascimento de " << gerenciamento[indice]->getNome() << " definida com sucesso!" << std::endl;
    return 0;
  } break;
  case 2: {
    // Para alterar o nome
    std::cout << "Digite o novo nome para alterar " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::string novoNome;
    std::cin.ignore();
    getline(std::cin, novoNome);
    std::cout << "\n";
    gerenciamento[indice]->setNome(novoNome);
    std::cout << "Novo nome definido com sucesso!" << std::endl;
    return 0;
  } break;
  case 3: {
    // Para alterar o codigo
    std::cout << "Digite o novo codigo para " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::string novoCodigo;
    std::cin.ignore();
    getline(std::cin, novoCodigo);
    std::cout << "\n";
    gerenciamento[indice]->setCodigo(novoCodigo);
    std::cout << "Novo codigo de " << gerenciamento[indice]->getNome() << " definido com sucesso!" << std::endl;
    return 0;
  } break;
  case 4: {
    // Para alterar a nacionalidade
    std::cout << "Digite a nova nacionalidade para " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::string novaNacionalidade;
    std::cin.ignore();
    getline(std::cin, novaNacionalidade);
    std::cout << "\n";
    gerenciamento[indice]->setNacionalidade(novaNacionalidade);
    std::cout << "Nova nacionalidade de " << gerenciamento[indice]->getNome() << " definida com sucesso!" << std::endl;
    return 0;
  } break;
  case 5: {
    // Para alterar a idade
    std::cout << "Digite a nova idade para " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    int idade;
    std::cin >> idade;
    std::cout << "\n";
    gerenciamento[indice]->setIdade(idade);
    std::cout << "Nova idade de " << gerenciamento[indice]->getNome() << " definida com sucesso!" << std::endl;
    return 0;
  } break;
  default:
    return 0;
    break;
  }

  if (p->getTipo() == 1 && escolha == 6) {
    // alterar a medalha do atleta

    int medalha;
    std::cout << "Digite a nova colocacao de " << gerenciamento[indice]->getNome() << " em " << dynamic_cast<Atleta *>(gerenciamento[indice])->getModalidade() << std::endl;
    std::cout << "\n-> ";
    std::cin >> medalha;
    std::cout << "\n";
    dynamic_cast<Atleta *>(gerenciamento[indice])->setMedalha(medalha);
    std::cout << "Nova medalha de " << gerenciamento[indice]->getNome() << " definida com sucesso!" << std::endl;
    return 0;
  } else if (p->getTipo() == 2 && escolha == 7) {
    // alterar a modalidade do atleta

    std::cout << "Digite a nova modalidade para " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::string novaModalidade;
    std::cin.ignore();
    getline(std::cin, novaModalidade);
    std::cout << "\n";
    dynamic_cast<Atleta *>(gerenciamento[indice])->setModalidade(novaModalidade);
    std::cout << "Nova modalidade de " << gerenciamento[indice]->getNome() << " definida com sucesso!" << std::endl;
    return 0;
  }

  if (p->getTipo() == 2 && escolha == 6) {
    // alterar a modalidade do membro da comissao

    std::cout << "Digite a nova modalidade para " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::string novaModalidade;
    std::cin.ignore();
    getline(std::cin, novaModalidade);
    std::cout << "\n";
    dynamic_cast<Comissao *>(gerenciamento[indice])->setModalidade(novaModalidade);
    std::cout << "Nova modalidade de " << gerenciamento[indice]->getNome() << " definida com sucesso!" << std::endl;
    return 0;
  } else if (p->getTipo() == 2 && escolha == 7) {
    // alterar a equipe do membro da comissao

    std::cout << "Digite a nova equipe da comissao para " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::string novaEquipeResponsavel;
    std::cin.ignore();
    getline(std::cin, novaEquipeResponsavel);
    std::cout << "\n";
    dynamic_cast<Comissao *>(gerenciamento[indice])->setEquipeResponsavel(novaEquipeResponsavel);
    std::cout << "Nova equipe de " << gerenciamento[indice]->getNome() << " definida com sucesso!" << std::endl;
    return 0;
  }

  if (p->getTipo() == 3 && escolha == 6) {
    // alterar o statusVip do torcedor

    std::string vip;
    std::cout << "O torcedor " << gerenciamento[indice]->getNome();
    std::string retornoStatus = (dynamic_cast<Torcedor *>(gerenciamento[indice])->getStatusVIP()) ? " possui status VIP" : " nao possui status VIP";
    std::cout << retornoStatus;
    std::cout << "\nGostaria de alterar?\n\n->";
    std::getline(std::cin, vip);
    std::cout << "\n";

    if ((vip.find("s") != -1) || (vip.find("S") != -1) ||
        (vip.find("y") != -1) || (vip.find("y") != -1)) {
      dynamic_cast<Torcedor *>(gerenciamento[indice])->setStatus(!dynamic_cast<Torcedor *>(gerenciamento[indice])->getStatusVIP());
      std::cout << "Status VIP de " << gerenciamento[indice]->getNome() << " alterado com sucesso!" << std::endl;
      return 0;
    }
  };
}

void GerenciamentoOlimpiadas::removerPessoa() {
  /*
    Esse m�todo � respons�vel por remover o registro de uma Pessoa, tendo em vista que o arquivo s� ser� salvo ao final da execu��o, ele exclui diretamente do registro do vector "gerenciamento", deixando a altera��o no arquivo, caso j� tenha dados salvos dessa inst�ncia, por responsabilidade do m�todo de salvar o arquivo

    -> Primeiramente permite ao usu�rio selecionar o elemento do vector, utilizando do m�todo "buscar()"
    -> Ap�s o �xito em selecionar a Pessoa a ser removida, o m�todo ir� remover e comunicar no terminal se a opera��o foi bem sucedida

    -> Esse m�todo � respons�vel pelo DELETE do sistema
  */
  Pessoa *pessoaRemov = buscar();
  int indice = 0;
  if (pessoaRemov == nullptr) {
    std::cout << "Pessoa nao encontrada, logo, nao sera apagada" << std::endl;
    return;
  };
  for (auto p : gerenciamento) {
    if (p->getNome() == pessoaRemov->getNome())
      break;
    indice++;
  }
  gerenciamento.erase(gerenciamento.begin() + indice);
  std::cout << "Pessoa removida com sucesso!" << std::endl;
  // remover
}

int GerenciamentoOlimpiadas::menu() {
  /*
    Esse m�todo � respons�vel pela principal exibi��o no terminal, mostrando ao usu�rio suas op��es de gerenciamento do registro das Pessoas.

    -> Respons�vel por dar n�vel de autonomia ao usu�rio, j� que, a partir desse m�todo, o pr�prio usu�rio ir� coordenar o fluxo da execu��o do programa

    -> Respons�vel por chamar os principais grandes m�todos a partir da escolha do usu�rio
  */
  std::cout << "\n\n";
  std::cout << "1. Inserir pessoa" << std::endl;
  std::cout << "2. Listar pessoas" << std::endl;
  std::cout << "3. Exibir pessoa" << std::endl;
  std::cout << "4. Alterar pessoa" << std::endl;
  std::cout << "5. Remover pessoa" << std::endl;
  std::cout << "6. Exibir Relatorio" << std::endl;
  std::cout << "7. Sair" << std::endl;

  std::cout << "\n-> ";

  int opcao;
  std::cin >> opcao;
  std::cout << "\n";
  
  switch (opcao) {
  case 1: {
    int erro = lerDadosPessoa();
    if (erro == 1)
      return 1;
    return 0;
  };
  case 2: {
    if(gerenciamento.size() == 0){
      std::cout << "N�o possui pessoas registradas" << std::endl;
      break;
    }
    exibirTodos();
    break;
    // listar
  };
  case 3: {
    if(gerenciamento.size() == 0){
      std::cout << "N�o possui pessoas registradas" << std::endl;
      return 0;
    }
    Pessoa *p = buscar();
    if(!p){
      return 0;
    };
    switch (p->getTipo()) {
      case 1:
        dynamic_cast<Atleta *>(p)->exibir();
        break;
      case 2:
        dynamic_cast<Comissao *>(p)->exibir();
        break;
      case 3:
        dynamic_cast<Torcedor *>(p)->exibir();
        break;
      }
    break;
  };
  case 4: {
    // alterar
    if(gerenciamento.size() == 0){
      std::cout << "N�o possui pessoas registradas" << std::endl;
      break;
    }
    int erro = alterarPessoa();
    if (erro == 1)
      return 1;
    return 0;
  };
  case 5: {
    if(gerenciamento.size() == 0){
      std::cout << "N�o possui pessoas registradas" << std::endl;
      break;
    }
    removerPessoa();
    return 0;
  };
  case 6: {
    gerarRelatorio();
    break;
  };
  case 7: {
    return 1;
    // sair
  };
  default:
    break;
  }
  return 0;
};

void GerenciamentoOlimpiadas::salvarArquivo() {
  /*
    Esse m�todo � respons�vel por salvar todos os dados do vector "gerenciamento" no arquivo "dadosPessoas.txt", salvando, em ordem, as Pessoas salvas no vector. O salvamento dos dados devem ser feitos na mesma ordem de que s�o lidos, que �:
      - 1 . Tipo
      - 2 . Dia da data de nascimento
      - 3 . M�s da data de nascimento
      - 4 . Ano da data de nascimento
      - 5 . Nome
      - 6 . C�digo
      - 7 . Nacionalidade
      - 8 . Medalha     ||  Modalidade          ||  StatusVip
      - 9 . Modalidade  ||  Equipe Responsavel  ||

    -> Esse m�todo � respons�vel por manter todos os dados da execu��o na mem�ria r�gida da m�quina, permitindo a execu��o sequencial do programa, tendo em vista que para os dados serem lidos, elem precisam ser salvos.

    -> Esse m�todo � chamado apenas no final da execu��o do programa, permitindo que as modifica��es s� sejam "carimbadas" ao final da execu��o
  */

  std::fstream arquivo;
  arquivo.open("dadosPessoas.txt", std::ios_base::out);

  if (!arquivo.is_open())
    std::cout << "Erro na abertura do arquivo para escrita!" << std::endl;

  for (auto pessoa : gerenciamento) {
    int tipoPessoa = pessoa->getTipo(), diaAux, mesAux, anoAux, idadeAux;

    arquivo << tipoPessoa << std::endl;
    arquivo << pessoa->getDataDeNascimento().getDia() << std::endl;
    arquivo << pessoa->getDataDeNascimento().getMes() << std::endl;
    arquivo << pessoa->getDataDeNascimento().getAno() << std::endl;
    arquivo << pessoa->getNome() << std::endl;
    arquivo << pessoa->getCodigo() << std::endl;
    arquivo << pessoa->getNacionalidade() << std::endl;
    arquivo << pessoa->getIdade() << std::endl;

    switch (tipoPessoa) {
    case 1:
      arquivo << dynamic_cast<Atleta *>(pessoa)->getMedalhaNum() << std::endl;
      arquivo << dynamic_cast<Atleta *>(pessoa)->getModalidade() << std::endl;
      break;
    
    case 2:
      arquivo << dynamic_cast<Comissao *>(pessoa)->getModalidade() << std::endl;
      arquivo << dynamic_cast<Comissao *>(pessoa)->getEquipe() << std::endl;
      break;

    case 3:
      if(arquivo << dynamic_cast<Torcedor *>(pessoa)->getStatusVIP())
        arquivo << 1 << std::endl;
      else
        arquivo << 0 << std::endl;
      break;
    default:
      break;
    }
  }
  
}