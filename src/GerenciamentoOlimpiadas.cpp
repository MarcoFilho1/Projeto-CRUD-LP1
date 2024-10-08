#include "../headers/GerenciamentoOlimpiadas.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
// #include <typeinfo>
#include <unistd.h>
#include <vector>

/*
  -Corpo dos m�todos de GerenciamentoOlimpiadas-

  GerenciamentoOlimpiadas � a principal classe do sistema, possuindo os atributos:

    Data dataInicio
    std::string Cidade
    Data dataFinal
    vector<Pessoa*> gerenciamento
    vector<Pessoa*> filtroPessoasIndice
    std::string Mascote

  -> Essa classe possui m�todos principais e auxiliares, sendo eles comentados em seu corpo com a sua utilidade e funcionamento
  -> Possui m�todos que interagem com os arquivos .txt e com o usu�rio

  -> Alguns m�todos principais s�o privados, pois s�o chamados a partir do menu(), que � um m�todo p�blico
  -> Apenas 4 m�todos s�o p�blicos:
    void iniciarOlimpiada();   -> Inicia todo o processamento dos dados salvos em .txt
    int menu();                -> Imprimir o menu que interage com o usu�rio
    void salvarArquivo();      -> Respons�vel por salvar o arquivo periodicamente
    GerenciamentoOlimpiadas(); -> Construtor

*/

/*
  COMENT�RIO DESTAQUE - VALIDA��O DE ENTRADAS DO TIPO INTEIRO

  -> Para a verifica��o da entrada de inteiros foi utilizado o seguinte c�digo:

  while (1) {                                                               // loop infinito
    std::cin >> VARI�VEL TIPO INT;                                          // entrada do usu�rio
    if (std::cin.fail() || std::cin.peek() != '\n') {                       // verifica erro ou entrada incompleta
        std::cin.clear();                                                   // limpa o estado de erro
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpa buffer de entrada
        std::cout << "\nDigite um n�mero v�lido! \n\n-> ";                  // mensagem de erro
    } else {
        break;                                                              // entrada v�lida, sai do loop
    }
  }

  -> std::cin.fail() -> Verifica se a opera��o de entrada falhou. Isso ocorre se o valor inserido n�o puder ser convertido corretamente para o tipo inteiro (por exemplo, se o usu�rio inserir letras em vez de um n�mero).

  -> std::cin.peek() != '\n' -> olha o pr�ximo caractere no buffer de entrada sem remov�-lo. Se o pr�ximo caractere n�o for uma nova linha (\n), significa que h� algo mais na entrada que n�o foi consumido, indicando que a entrada era inv�lida ou incompleta.

  -> std::cin.clear() -> Em caso de uma entrada n�o v�lida, limpa o estado de erro da entrada para permitir que novas opera��es de entrada sejam realizadas. Sem isso, std::cin ficaria em estado de erro e nenhuma nova leitura poderia ser realizada.

  -> std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  -> Esta linha ignora (descarta - a partir do .ignore()) o restante da linha de entrada at� encontrar um caractere de nova linha (\n), ou at� atingir um n�mero m�ximo de caracteres (determinado por std::numeric_limits<std::streamsize>::max())
  -> Basicamente, isso limpa qualquer entrada residual que possa estar no buffer, garantindo que na pr�xima itera��o do loop a entrada esteja limpa para uma nova tentativa.

  -> Se a entrada foi bem-sucedida (ou seja, n�o houve falha e o buffer de entrada est� limpo), o else � executado, interrompendo o loop com a instru��o break.
  Isso significa que o loop s� ser� interrompido quando o usu�rio inserir um valor num�rico v�lido seguido de uma nova linha.
*/

GerenciamentoOlimpiadas::GerenciamentoOlimpiadas() {
  /*
    Construtor padr�o -> Ser� utilizado na inicializa��o do programa,
    a �nica inst�ncia dessa classe dever� ser inicializada sem os dados armazenados,
    para ent�o serem 'setados' todos os seus dados com "setOlimpiadas", m�todo esse que
    � chamado no momento de leitura dos dados das olimp�adas, seja do arquivo, seja diretamente
    do terminal
  */
  this->dataInicio = Data();
  this->cidade = "";
  this->dataFinal = Data();
  this->mascote = "";
}

void GerenciamentoOlimpiadas::setOlimpiada(Data dataInicio, std::string cidade, Data dataFinal, std::string mascote) {
  /*
    M�todo para atribuir os dados das olimp�adas na inst�ncia da classe, � chamado ap�s
    a leitura de dados, ou do arquivo ou do terminal
  */
  this->dataInicio = dataInicio;
  this->cidade = cidade;
  this->dataFinal = dataFinal;
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
    /*
      Testa se o arquivo foi devidamente aberto
      -> Caso sim : Ir� ler as informa��es pelo arquivo
      -> Caso n�o : Ir� ler as informa��es pelo terminal
    */
    int diaAux, mesAux, anoAux;
    std::string cidade, mascote;

    arqOlimpiada >> diaAux >> mesAux >> anoAux;
    Data dataInicioAux(diaAux, mesAux, anoAux);
    arqOlimpiada.ignore();

    getline(arqOlimpiada, cidade);
    arqOlimpiada >> diaAux >> mesAux >> anoAux;

    Data dataFinalAux(diaAux, mesAux, anoAux);
    arqOlimpiada.ignore();

    getline(arqOlimpiada, mascote);

    setOlimpiada(dataInicioAux, cidade, dataFinalAux, mascote);
    arqOlimpiada.close();

  } else {
    arqOlimpiada.close();

    /*
      Imprime algumas coisas sobre o projeto na tela
      -> L� do usu�rio as informa��es sobre as olimp�adas, verificando sempre se a entrada � v�lida
      -> Grava no arquivo as informa��es que o usu�rio digitou
    */

    std::cout << "**********************************************\n";
    std::cout << "*                                            *\n";
    std::cout << "*     Bem-vindo ao nosso projeto de CRUD     *\n";
    std::cout << "*         com tema de Olimp�adas!            *\n";
    std::cout << "*                                            *\n";
    std::cout << "**********************************************\n\n\n";

    std::cout
        << "    \033[34m********         \033[30m*******         \033[31m********    \n"
        << "  \033[34m**        **    \033[30m***       ***    \033[31m**        **  \n"
        << " \033[34m*           **  \033[30m**           **  \033[31m**           * \n"
        << "\033[34m**            *  \033[30m*             *  \033[31m*            **\n"
        << "\033[34m*           \033[33m***\033[34m*\033[33m*\033[30m*\033[33m***        \033[32m****\033[30m*\033[32m****           \033[31m*\n"
        << " \033[34m**        \033[33m** \033[34m**  \033[30m**  \033[33m*     \033[32m* \033[30m**   \033[31m** \033[32m**       \033[31m**\n"
        << "  \033[34m**      \033[33m*  \033[34m**    \033[30m**  \033[33m*   \033[32m* \033[30m**     \033[31m**  \033[32m*     \033[31m** \n"
        << "   \033[34m*****\033[33m*\033[34m***        \033[30m**\033[33m**\033[30m*\033[32m**\033[30m**        \033[31m***\033[32m*\033[31m*****   \n"
        << "        \033[33m**            ** \033[32m**            **        \n"
        << "         \033[33m**           *   \033[32m*           **         \n"
        << "          \033[33m**        **     \033[32m**        **          \n"
        << "            \033[33m********         \033[32m********    \n\n";

    std::cout << "\033[0m" << "Desenvolvedores do projeto:\n";
    std::cout << "----------------------------------------------\n";
    std::cout << "* Eduardo Asfuri Carvalho                    * \n";
    std::cout << "* Lucas Henrique Vieira da Silva             * \n";
    std::cout << "* Marco Antonio de Vasconcelos Souza Filho   * \n";

    std::cout << "----------------------------------------------\n";
    std::cout << "Professor Respons�vel:\n";
    std::cout << "* Derzu Omaia                                *\n";
    std::cout << "----------------------------------------------\n\n";
    sleep(1);
    int diaAux, mesAux, anoAux, anoFinal;
    std::string cidade, mascote;
    std::cout << "Digite a cidade sede " << std::endl;
    std::cout << "\n-> ";
    getline(std::cin, cidade);
    std::cout << "\n";

    std::cout << "Digite o ano das olimp�adas de " << cidade << std::endl;
    std::cout << "\n-> ";
    while (1) {
      std::cin >> anoAux;
      if (std::cin.fail() || std::cin.peek() != '\n') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nDigite um n�mero v�lido! \n\n-> ";
      } else {
        break;
      }
    }
    std::cout << "\n";

    std::cout << "Digite o m�s de " << anoAux << " que come�am as olimp�adas de " << cidade << std::endl;
    std::cout << "\n-> ";
    while (1) {
      std::cin >> mesAux;
      if (std::cin.fail() || std::cin.peek() != '\n' || mesAux < 1 || mesAux > 12) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nDigite um n�mero v�lido! \n\n-> ";
      } else {
        break;
      }
    }
    std::cout << "\n";

    std::cout << "Digite dia do m�s de " << mesAux << "/" << anoAux << " que come�am as olimp�adas de " << cidade << std::endl;
    std::cout << "\n-> ";
    while (1) {
      std::cin >> diaAux;
      if (std::cin.fail() || std::cin.peek() != '\n') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nDigite um n�mero v�lido! \n\n-> ";
      } else {
        break;
      }
    }
    std::cout << "\n";

    Data dataInicioAux(diaAux, mesAux, anoAux);

    std::cout << "Digite o ano que acabam as olimp�adas de " << cidade << std::endl;
    std::cout << "\n-> ";
    while (1) {
      std::cin >> anoFinal;
      if (std::cin.fail() || std::cin.peek() != '\n' || anoFinal < anoAux) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nDigite um n�mero v�lido! \n\n-> ";
      } else {
        break;
      }
    }
    std::cout << "\n";

    std::cout << "Digite o m�s de " << anoFinal << " que acabam as olimp�adas de " << cidade << std::endl;
    std::cout << "\n-> ";
    while (1) {
      std::cin >> mesAux;
      if (std::cin.fail() || std::cin.peek() != '\n' || (anoFinal == anoAux && mesAux < dataInicioAux.getMes()) || mesAux > 12 || mesAux < 1) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nDigite um m�s v�lido! \n\n-> ";
      } else {
        break;
      }
    }
    std::cout << "\n";

    std::cout << "Digite dia do m�s de " << mesAux << "/" << anoFinal << " que acabam as olimp�adas de " << cidade << std::endl;
    std::cout << "\n-> ";
    while (1) {
      std::cin >> diaAux;
      if (std::cin.fail() || std::cin.peek() != '\n' || (anoFinal == anoAux && mesAux == dataInicioAux.getMes() && diaAux < dataInicioAux.getDia()) || diaAux < 1) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nDigite um n�mero v�lido! \n\n-> ";
      } else {
        break;
      }
    }
    std::cout << "\n";

    Data dataFinalAux(diaAux, mesAux, anoFinal);

    std::cout << "Digite o nome do mascote das olimp�adas de " << cidade << " " << anoAux << std::endl;
    std::cout << "\n-> ";
    std::cin.ignore();
    getline(std::cin, mascote);
    std::cout << "\n";

    setOlimpiada(dataInicioAux, cidade, dataFinalAux, mascote);

    // Come�a a escrever no arquivo as informa��es sobre a olimp�ada
    // O usu�rio so consegue "criar" outra olimp�ada se apagar o arquivo "olimpiada.txt"
    // Isso deve ser documentado no README
    arqOlimpiada.open("dadosOlimpiadas.txt", std::ios_base::out);

    // Salvando a data inicial
    arqOlimpiada << dataInicioAux.getDia() << std::endl;
    arqOlimpiada << dataInicioAux.getMes() << std::endl;
    arqOlimpiada << dataInicioAux.getAno() << std::endl;

    // Salvando a cidade
    arqOlimpiada << cidade << std::endl;

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
      - 9 . Modalidade  ||  Equipe Respons�vel  ||

    OBS.: Na primeira execu��o do c�digo, o arquivo n�o dever� existir, tendo isso em vista, o mesmo n�o ser� lido e o m�todo retorna

    -> Respons�vel por iniciar os �ndices do vector "gerenciamento", ou seja, iniciar os ponteiros de Pessoa com os construtores das subclasses (realizando polimorfismo)
    -> Tamb�m chama o m�todo de inserir Pessoas no vector (AdicionarPessoa())
  */

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

  while (arquivo >> tipoPessoa >> diaAux >> mesAux >> anoAux) {
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

    } else if (tipoPessoa == 2) { // Membro da Comiss�o

      std::string auxMod, auxEquipResp;
      arquivo.ignore();
      std::getline(arquivo, auxMod);
      std::getline(arquivo, auxEquipResp);
      Pessoa *pessoaAux = new Comissao(dataAux, pessoaNome, pessoaCodigo, pessoaNac, idadeAux, tipoPessoa, auxMod, auxEquipResp);

      // Instanciando um membro da comiss�o a partir dos dados do arquivo em PessoaAux

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

void GerenciamentoOlimpiadas::lerDadosPessoa() {
  /*
    Esse m�todo � respons�vel por ler diretamente do terminal todos os dados de uma determinada Pessoa
    que o usu�rio desejar inserir, ele vai iniciar um ponteiro de Pessoa com as informa��es utilizando
    o construtor da subclasse escolhida pelo usu�rio (tipo) e ao final do m�todo ir� chamar o m�todo
    de adicionar a pessoa no vector "gerenciamento"

    -> Esse m�todo l� os dados espec�ficos das subclasses, sendo a leitura filtrada pela escolha do usu�rio

    -> A partir desse m�todo possu�mos o CREATE do sistema
  */
  Pessoa *pessoaAux;
  std::string nome, codigo, nacionalidade;
  int dia, mes, ano, idade, tipoPessoa;

  std::cout << "\nDigite o nome da pessoa a ser adicionada" << "\n\n-> ";
  std::getline(std::cin, nome);
  std::cout << "\n";

  std::cout << "Digite o dia do nascimento de " << nome << "\n\n-> ";
  while (1) {
    std::cin >> dia;
    if (std::cin.fail() || std::cin.peek() != '\n') {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "\nDigite um n�mero v�lido! \n\n-> ";
    } else {
      break;
    }
  }
  std::cout << "\n";
  std::cout << "Digite o mes do nascimento de " << nome << "\n\n-> ";
  while (1) {
    std::cin >> mes;
    if (std::cin.fail() || std::cin.peek() != '\n') {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "\nDigite um n�mero v�lido! \n\n-> ";
    } else {
      break;
    }
  }
  std::cout << "\n";
  std::cout << "Digite o ano do nascimento de " << nome << "\n\n-> ";

  while (1) {
    std::cin >> ano;
    std::cout << "\n";
    if (std::cin.fail() || std::cin.peek() != '\n' || dataInicio.getAno() < ano) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Digite um ano v�lido! \n\n-> ";
    } else {
      break;
    }
  }

  idade = dataInicio.getAno() - ano;
  Data dataNasc(dia, mes, ano);

  std::cin.ignore();
  std::cout << "Digite o c�digo de " << nome << "\n\n-> ";
  getline(std::cin, codigo);
  std::cout << "\n";

  std::cout << "Digite a nacionalidade de " << nome << "\n\n-> ";
  std::getline(std::cin, nacionalidade);
  std::cout << "\n";

  std::cout << "Digite o tipo\n"
            << std::endl;
  std::cout << "-> \033[36m1\033[0m Atleta\t-> \033[36m2\033[0m Membro da comiss�o\n-> \033[36m3\033[0m Torcedor\t-> \033[36m4\033[0m Cancelar opera��o\n\n-> ";
  while (1) {
    std::cin >> tipoPessoa;
    std::cout << "\n";
    if (std::cin.fail() || std::cin.peek() != '\n') {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Digite um n�mero v�lido! \n\n-> ";
    } else {
      break;
    }
  }

  if (tipoPessoa == 1) {

    std::cin.ignore();
    int medalha;
    std::string modalidade;
    std::cout << "Digite a modalidade do atleta\n\n-> ";
    std::getline(std::cin, modalidade);
    std::cout << "\n";
    std::cout << "Digite a coloca��o de " << nome << " em " << modalidade << "\n\n-> ";

    while (1) {
      std::cin >> medalha;
      std::cout << "\n";
      if (std::cin.fail() || std::cin.peek() != '\n') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nDigite um n�mero v�lido! \n\n-> ";
      } else {
        break;
      }
    }
    pessoaAux = new Atleta(dataNasc, nome, codigo, nacionalidade, idade, tipoPessoa, medalha, modalidade);

  } else if (tipoPessoa == 2) {

    std::cin.ignore();
    std::string modalidade, equipeResponsavel;
    std::cout << "Digite a modalidade de atua��o do membro da comiss�o:\n\n-> ";
    std::getline(std::cin, modalidade);
    std::cout << "\n";
    std::cout << "Dentro de " << modalidade << ", digite a equipe de atua��o de " << nome << "\n\n-> ";
    std::getline(std::cin, equipeResponsavel);
    std::cout << "\n";

    pessoaAux = new Comissao(dataNasc, nome, codigo, nacionalidade, idade, tipoPessoa, modalidade, equipeResponsavel);

  } else if (tipoPessoa == 3) {

    std::cin.ignore();
    bool vipBool;
    std::string vip;
    std::cout << "O torcedor " << nome << " possui acesso vip? (Sim/N�o)\n\n-> ";
    std::getline(std::cin, vip);
    std::cout << "\n";

    if ((vip.find("s") != -1) || (vip.find("S") != -1) ||
        (vip.find("y") != -1) || (vip.find("y") != -1))
      vipBool = true;
    else
      vipBool = false;

    pessoaAux = new Torcedor(dataNasc, nome, codigo, nacionalidade, idade, tipoPessoa, vipBool);
  } else {
    std::cout << "Opera��o cancelada! \n";
    return;
  }
  AdicionarPessoa(pessoaAux);
  std::cout << "Pessoa \033[32mregistrada\033[0m com sucesso!" << std::endl;
  return;
}

void GerenciamentoOlimpiadas::exibirTodos() {
  /*
    Esse m�todo � respons�vel por exibir no terminal todos os �ndices do vector "gerenciamento" de maneira otimizada, imprimindo o valor ordinal do elemento no vector, o tipo da Pessoa (de qual subclasse � uma inst�ncia), seguido do nome. Ex.:

    1o - Atleta : Michael Phelps
    2o - Comissao : Bernardo Rocha
  */
  if (gerenciamento.size() == 0) {
    std::cout << "N�o h� pessoas registradas" << std::endl;
    return;
  } else {
    std::cout << "\nPessoas registradas:\n"
              << std::endl;
    int contador = 1;
    for (int i = 0; i < gerenciamento.size(); i++) {
      std::cout << "\033[36m" << contador << "�\033[0m";
      contador++;
      if (gerenciamento[i]->getTipo() == 1)
        std::cout << " - Atleta\t";
      if (gerenciamento[i]->getTipo() == 2)
        std::cout << " - Comiss�o\t";
      if (gerenciamento[i]->getTipo() == 3)
        std::cout << " - Torcedor\t";
      std::cout << " : " << gerenciamento[i]->getNome() << std::endl;
    }
  }
}
std::string paraMinusculo(const std::string &stringComMaiusculo) {
  std::string stringMinuscula = stringComMaiusculo;
  std::transform(stringMinuscula.begin(), stringMinuscula.end(), stringMinuscula.begin(), ::tolower);
  return stringMinuscula;
}

Pessoa *GerenciamentoOlimpiadas::buscar() {
  /*
    Esse m�todo � respons�vel por realizar a busca por determinada Pessoa no vector, chamando primeiramente o m�todo de exibi��o dos �ndices (exibirTodos()), ap�s isso, o usu�rio dever� digitar um nome que coincide com uma das pessoas registradas, podendo ser completamente coincidente ou parcialmente. Em caso do usu�rio digitar uma entrada que coincide parcialmente com mais de uma pessoa registrada, o usu�rio ser� apresentado a uma nova lista de �ndices v�lidos para as pessoas que coincidem parcialmente com o que ele digitou anteriormente

    -> Esse m�todo retorna a Pessoa encontrada (que � um ponteiro), retorno esse que deve ser tratado na chamada
    -> Esse m�todo � chamado nos m�todos de exibir (exibir com detalhe apenas uma Pessoa), alterar e remover
  */
  int count = 0;
  exibirTodos();
  std::cout << "\n\nEscolha o nome\n\n-> ";
  std::string nome;
  std::cin >> std::ws;
  getline(std::cin, nome);
  std::transform(nome.begin(), nome.end(), nome.begin(), ::tolower);
  std::cout << "\n";
  int contador = 0, indice;

  // Testar quantas pessoas tem com o nome digitado
  for (int i = 0; i < gerenciamento.size(); i++) {
    if (paraMinusculo(gerenciamento[i]->getNome()).find(nome) != -1) {
      contador++;

      indice = i;
    }
  }

  // No caso do nome ser incompat�vel com pelo menos um dos nomes no vector, o retorno ser�
  // um nullptr (ponteiro vazio), esse retorno dever� ser tratado no local de chamada
  if (contador == 0) {
    std::cout << "Pessoa n�o encontrada!" << std::endl;
    return nullptr;
  }

  if (contador == 1)
    return gerenciamento[indice];

  /* Quando ocorre de mais de uma pessoa possuir a mesma substring, essas pessoas ser�o
     adicionadas a um novo vector de Pessoas, onde ser� exibido o �ndice de cada uma e
     pedir ao usu�rio pra escolher de acordo com o �ndice.
     Detalhe --> O vector � apagado depois de cada intera��o, garantindo que n�o ter� um
     lixo de mem�ria de execu��es*/
  int indiceEscolha;
  // Imprimir a lista de pessoas que coincidem com o nome digitado pelo usu�rio
  // filtrando a partir das letras minusculas (normaliza��o) dos nomes utilizando o m�todo .find()
  for (int i = 0; i < gerenciamento.size(); i++) {

    if (paraMinusculo(gerenciamento[i]->getNome()).find(nome) != -1) {
      filtroPessoasIndice.push_back(gerenciamento[i]);
      std::cout << "\033[36m" << filtroPessoasIndice.size() - 1 << "\033[0m";

      if (gerenciamento[i]->getTipo() == 1)
        std::cout << " - Atleta\t";

      if (gerenciamento[i]->getTipo() == 2)
        std::cout << " - Comiss�o\t";

      if (gerenciamento[i]->getTipo() == 3)
        std::cout << " - Torcedor\t";

      std::cout << gerenciamento[i]->getNome() << std::endl;
    }
  }
  std::cout << "\n";
  std::cout << "Escolha o �ndice" << std::endl;
  std::cout << "\n-> ";
  while (1) {
    std::cin >> indiceEscolha;
    std::cout << "\n";
    if (std::cin.fail() || std::cin.peek() != '\n' || indiceEscolha < 0 || indiceEscolha >= filtroPessoasIndice.size()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Digite um n�mero v�lido! \n\n-> ";
    } else {
      break;
    }
  }
  Pessoa *retornoPessoa = filtroPessoasIndice[indiceEscolha];
  filtroPessoasIndice.clear();
  return retornoPessoa;
}

void GerenciamentoOlimpiadas::gerarRelatorio() {
  /*
    -> Esse m�todo � respons�vel por imprimir no terminal as informa��es gerais das Olimp�adas, sendo elas:
      - cidade e ano
      - Data de Inicio
      - Data Final
      - Nome do Mascote

    -> E � respons�vel tamb�m por imprimir no terminal as informa��es das Pessoas que est�o cadastradas no sistema, sendo esses dados brutos e comparativos. Caso n�o haja Pessoas cadastradas, ele ir� imprimir e retornar
  */
  std::cout << "\n";
  std::cout << "Olimpiadas de \033[33m" << cidade << " " << dataInicio.getAno() << "\033[0m" << std::endl;
  std::cout << "Data de Inicio: \033[33m";
  dataInicio.exibir();
  std::cout << "\033[0mData Final: \033[33m";
  dataFinal.exibir();
  std::cout << "\033[0mMascote dos jogos: \033[33m" << mascote << "\n\n\033[0m";

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
    std::cout << "\033[0mN�o h� pessoas cadastradas\033[33m" << std::endl;
    return;
  } else {
    // Imprime os dados brutos e comparativos das Pessoas
    float porcAtleta = 100 * (float)countAtleta / (float)countTotal;
    float porcComissao = 100 * (float)countComissao / (float)countTotal;
    float porcTorcedor = 100 * (float)countTorcedor / (float)countTotal;

    std::cout << "Quantidade total de Pessoas: \033[33m" << countTotal << "\033[0m" << std::endl;
    std::cout << "Quantidade total de Atletas: \033[33m" << countAtleta << " (" << porcAtleta << "%)\033[0m" << std::endl;
    std::cout << "Quantidade total de Membros da Comiss�o: \033[33m" << countComissao << " (" << porcComissao << "%)\033[0m" << std::endl;
    std::cout << "Quantidade total de Torcedores: \033[33m" << countTorcedor << " (" << porcTorcedor << "%)\033[0m" << std::endl;
  }
}

int GerenciamentoOlimpiadas::alterarPessoa() {
  /*
    Esse m�todo � respons�vel por alterar as informa��es de uma determinada Pessoa que j� est� registrada,
    alterando o elemento do vector, sendo o m�todo de salvar o arquivo ao final da execu��o respons�vel por alterar no arquivo

    -> Primeiramente permite ao usu�rio selecionar o elemento do vector, utilizando do m�todo "buscar()"
    -> Ap�s o �xito em selecionar a Pessoa a ser alterada (ele compara o c�digo e o nome para ter acesso ao �ndice do vector), o m�todo ir� ler qual propriedade, de acordo com o tipo, o usu�rio quer alterar
    -> Considerando as propriedades de Pessoa, que s�o comuns entre as subclasses, essas podem ser
    alterados diretamente sem precisar consultar o tipo

    OBS -> Esse m�todo n�o ir� interagir com o

    -> Esse m�todo � respons�vel pelo EDIT do sistema

  */

  Pessoa *p = buscar();
  if (p == nullptr) {
    return 0;
  };

  int indice = 0;

  for (auto busca : gerenciamento) {
    if (busca->getNome() == p->getNome() && busca->getCodigo() == p->getCodigo())
      break;

    indice++;
  }

  if (indice > gerenciamento.size())
    return 1;

  std::cout << "Digite o que ser� alterado" << std::endl;
  std::cout << "-> \033[36m1\033[0m Data de Nascimento" << std::endl;
  std::cout << "-> \033[36m2\033[0m Nome" << std::endl;
  std::cout << "-> \033[36m3\033[0m C�digo" << std::endl;
  std::cout << "-> \033[36m4\033[0m Nacionalidade" << std::endl;

  if (p->getTipo() == 1) {
    std::cout << "-> \033[36m5\033[0m Medalha" << std::endl;
    std::cout << "-> \033[36m6\033[0m Modalidade" << std::endl;

  } else if (p->getTipo() == 2) {
    std::cout << "-> \033[36m5\033[0m Modalidade" << std::endl;
    std::cout << "-> \033[36m6\033[0m Equipe de atua��o" << std::endl;

  } else if (p->getTipo() == 3) {
    std::cout << "-> \033[36m5\033[0m Status VIP" << std::endl;
  }

  std::cout << "-> \033[31mOutro\033[0m Cancelar opera��o\n\n-> ";
  std::cin >> std::ws;
  std::string strEscolha;
  getline(std::cin, strEscolha);

  if (strEscolha.size() > 1) {
    std::cout << "\nOpera��o cancelada" << std::endl;
    return 0;
  }

  const char *arrayEscolha = strEscolha.c_str();
  char escolha = arrayEscolha[0];

  switch (escolha) {
  case '1': {
    // Para alterar a data de nascimento
    int diaAux, mesAux, anoAux;
    std::cout << "Digite o dia da nova data de nascimento de " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    while (1) {
      std::cin >> diaAux;
      std::cout << "\n";
      if (std::cin.fail() || std::cin.peek() != '\n') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Digite um n�mero v�lido! \n\n-> ";
      } else {
        break;
      }
    }
    std::cout << "\n";
    std::cout << "Digite o m�s da nova data de nascimento de " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    while (1) {
      std::cin >> mesAux;
      std::cout << "\n";
      if (std::cin.fail() || std::cin.peek() != '\n') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Digite um n�mero v�lido! \n\n-> ";
      } else {
        break;
      }
    }
    std::cout << "\n";
    std::cout << "Digite o ano da nova data de nascimento de " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    while (1) {
      std::cin >> anoAux;
      std::cout << "\n";
      if (std::cin.fail() || std::cin.peek() != '\n') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Digite um n�mero v�lido! \n\n-> ";
      } else {
        break;
      }
    }
    std::cout << "\n";
    Data novaDataDeNascimento(diaAux, mesAux, anoAux);
    gerenciamento[indice]->setDataDeNascimento(novaDataDeNascimento);
    std::cout << "Nova data de nascimento de " << gerenciamento[indice]->getNome() << " \033[35mdefinida\033[0m com sucesso!" << std::endl;

    int idade = dataInicio.getAno() - anoAux;
    gerenciamento[indice]->setIdade(idade);
    std::cout << "Nova idade de " << gerenciamento[indice]->getNome() << " \033[35mdefinida\033[0m com sucesso!" << std::endl;
    return 0;
  } break;
  case '2': {
    // Para alterar o nome
    std::cout << "Digite o novo nome para alterar " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::string novoNome;
    std::cin.ignore();
    getline(std::cin, novoNome);
    std::cout << "\n";
    gerenciamento[indice]->setNome(novoNome);
    std::cout << "Novo nome \033[35mdefinido\033[0m com sucesso!" << std::endl;
    return 0;
  } break;
  case '3': {
    // Para alterar o codigo
    std::cout << "Digite o novo c�digo para " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::string novoCodigo;
    std::cin >> std::ws;
    getline(std::cin, novoCodigo);
    std::cout << "\n";
    gerenciamento[indice]->setCodigo(novoCodigo);
    std::cout << "Novo c�digo de " << gerenciamento[indice]->getNome() << " \033[35mdefinido\033[0m com sucesso!" << std::endl;
    return 0;
  } break;
  case '4': {
    // Para alterar a nacionalidade
    std::cout << "Digite a nova nacionalidade para " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::string novaNacionalidade;
    std::cin.ignore();
    getline(std::cin, novaNacionalidade);
    std::cout << "\n";
    gerenciamento[indice]->setNacionalidade(novaNacionalidade);
    std::cout << "Nova nacionalidade de " << gerenciamento[indice]->getNome() << " \033[35mdefinida\033[0m com sucesso!" << std::endl;
    return 0;
  } break;
  default:
    break;
  }

  if (p->getTipo() == 1 && escolha == '5') {
    // alterar a medalha do atleta

    int medalha;
    std::cout << "Digite a nova coloca��o de " << gerenciamento[indice]->getNome() << " em " << dynamic_cast<Atleta *>(gerenciamento[indice])->getModalidade() << std::endl;
    std::cout << "\n-> ";
    while (1) {
      std::cin >> medalha;
      std::cout << "\n";
      if (std::cin.fail() || std::cin.peek() != '\n') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Digite um n�mero v�lido! \n\n-> ";
      } else {
        break;
      }
    }
    dynamic_cast<Atleta *>(gerenciamento[indice])->setMedalha(medalha);
    std::cout << "Nova medalha de " << gerenciamento[indice]->getNome() << " \033[35mdefinida\033[0m com sucesso!" << std::endl;
    return 0;
  } else if (p->getTipo() == 1 && escolha == '6') {
    // alterar a modalidade do atleta

    std::cout << "Digite a nova modalidade para " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::string novaModalidade;
    std::cin >> std::ws;
    getline(std::cin, novaModalidade);
    std::cout << "\n";
    dynamic_cast<Atleta *>(gerenciamento[indice])->setModalidade(novaModalidade);
    std::cout << "Nova modalidade de " << gerenciamento[indice]->getNome() << " \033[35mdefinida\033[0m com sucesso!" << std::endl;
    return 0;
  }

  if (p->getTipo() == 2 && escolha == '5') {
    // alterar a modalidade do membro da comiss�o

    std::cout << "Digite a nova modalidade para " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::string novaModalidade;
    // std::cin.ignore();
    std::cin >> std::ws;
    getline(std::cin, novaModalidade);
    std::cout << "\n";
    dynamic_cast<Comissao *>(gerenciamento[indice])->setModalidade(novaModalidade);
    std::cout << "Nova modalidade de " << gerenciamento[indice]->getNome() << " \033[35mdefinida\033[0m com sucesso!" << std::endl;
    return 0;
  } else if (p->getTipo() == 2 && escolha == '6') {
    // alterar a equipe do membro da comiss�o

    std::cout << "Digite a nova equipe da comiss�o para " << gerenciamento[indice]->getNome() << std::endl;
    std::cout << "\n-> ";
    std::string novaEquipeResponsavel;
    std::cin >> std::ws;
    // std::cin.ignore();
    getline(std::cin, novaEquipeResponsavel);
    std::cout << "\n";
    dynamic_cast<Comissao *>(gerenciamento[indice])->setEquipeResponsavel(novaEquipeResponsavel);
    std::cout << "Nova equipe de " << gerenciamento[indice]->getNome() << " \033[35mdefinida\033[0m com sucesso!" << std::endl;
    return 0;
  }

  if (p->getTipo() == 3 && escolha == '5') {
    // alterar o statusVip do torcedor

    std::string vip;
    std::cout << "O torcedor " << gerenciamento[indice]->getNome();
    std::string retornoStatus = (dynamic_cast<Torcedor *>(gerenciamento[indice])->getStatusVIP()) ? " possui status VIP" : " n�o possui status VIP";
    std::cout << retornoStatus;
    std::cout << "\nGostaria de alterar?\n\n-> ";
    std::cin >> std::ws;
    std::getline(std::cin, vip);
    std::cout << "\n";

    if ((vip.find("s") != -1) || (vip.find("S") != -1) ||
        (vip.find("y") != -1) || (vip.find("y") != -1)) {
      dynamic_cast<Torcedor *>(gerenciamento[indice])->setStatusVIP(!dynamic_cast<Torcedor *>(gerenciamento[indice])->getStatusVIP());
      std::cout << "Status VIP de " << gerenciamento[indice]->getNome() << " \033[35malterado\033[0m com sucesso!" << std::endl;
      return 0;
    } else {
      std::cout << "N�o ser� alterado! \n";
      return 0;
    }
  };

  std::cout << "Opera��o cancelada! " << std::endl;
  return 0;
}

void GerenciamentoOlimpiadas::removerPessoa() {
  /*
    Esse m�todo � respons�vel por remover o registro de uma Pessoa, tendo em vista que o arquivo s� ser� salvo ao final da execu��o, ele exclui diretamente do registro do vector "gerenciamento", deixando a altera��o no arquivo para o m�todo, caso j� tenha dados salvos dessa inst�ncia, por responsabilidade do m�todo de salvar o arquivo

    -> Primeiramente permite ao usu�rio selecionar o elemento do vector, utilizando do m�todo "buscar()"
    -> Ap�s o �xito em selecionar a Pessoa a ser removida, o m�todo ir� remover e comunicar no terminal se a opera��o foi bem sucedida

    -> Esse m�todo � respons�vel pelo DELETE do sistema
  */
  Pessoa *pessoaRemov = buscar();
  int indice = 0;
  if (pessoaRemov == nullptr) {
    std::cout << "Pessoa n�o encontrada, logo, n�o ser� apagada" << std::endl;
    sleep(1);
    return;
  };
  for (auto p : gerenciamento) {
    if (p->getNome() == pessoaRemov->getNome() && p->getCodigo() == pessoaRemov->getCodigo())
      break;
    indice++;
  }
  gerenciamento.erase(gerenciamento.begin() + indice);
  std::cout << "Pessoa \033[31mremovida\033[0m com sucesso!" << std::endl;
  // remover
}

int GerenciamentoOlimpiadas::menu() {
  /*
    Esse m�todo � respons�vel pela principal exibi��o no terminal, mostrando ao usu�rio suas op��es de gerenciamento do registro das Pessoas.

    -> Respons�vel por dar n�vel de autonomia ao usu�rio, j� que, a partir desse m�todo, o pr�prio usu�rio ir� coordenar o fluxo da execu��o do programa

    -> Respons�vel por chamar os principais grandes m�todos a partir da escolha do usu�rio
  */
  std::cout << "\n\n";
  std::cout << "\033[36m1\033[0m. Inserir pessoa" << std::endl;
  std::cout << "\033[36m2\033[0m. Listar pessoas" << std::endl;
  std::cout << "\033[36m3\033[0m. Exibir pessoa" << std::endl;
  std::cout << "\033[36m4\033[0m. Alterar pessoa" << std::endl;
  std::cout << "\033[36m5\033[0m. Remover pessoa" << std::endl;
  std::cout << "\033[36m6\033[0m. Exibir relat�rio" << std::endl;
  std::cout << "\033[36m7\033[0m. Sair" << std::endl;
  std::cout << "\n-> ";

  std::cin >> std::ws;
  std::string strOpcao;
  getline(std::cin, strOpcao);
  std::cout << "\n";

  if (strOpcao.size() > 1) {
    if (strOpcao == "7777777") {
      std::cout << "Querido programador:\nQuando eu escrevi este c�digo,\napenas eu e Deus sab�amos como\nele funcionava. Agora, apenas Deus sabe!" << std::endl;
      sleep(4);
      std::cout << "\nPortanto, se estiver tentando\nmelhorar este c�digo porque est� com bug...\ne com certeza est�, por favor, aumente este contador\ncomo um aviso para o pr�ximo programador:" << std::endl;
      sleep(4);
      std::cout << "\ntotal_de_horas_gastas_aqui: 79 horas" << std::endl;
      sleep(2);
      return 0;
    }
    std::cout << "Entrada inv�lida! " << std::endl;
    return 0;
  }

  const char *arrayOpcao = strOpcao.c_str();
  char opcao = arrayOpcao[0];

  switch (opcao) {
  case '1': {
    lerDadosPessoa();
    return 0;
  };
  case '2': {
    if (gerenciamento.size() == 0) {
      std::cout << "N�o possui pessoas registradas" << std::endl;
      sleep(1);
      break;
    }
    exibirTodos();
    sleep(1);
    break;
    // listar
  };
  case '3': {
    if (gerenciamento.size() == 0) {
      std::cout << "N�o possui pessoas registradas" << std::endl;
      return 0;
    }
    Pessoa *p = buscar();
    if (p == nullptr) {
      return 0;
    };
    switch (p->getTipo()) {
    case 1:
      dynamic_cast<Atleta *>(p)->exibir();
      sleep(1);
      break;
    case 2:
      dynamic_cast<Comissao *>(p)->exibir();
      sleep(1);
      break;
    case 3:
      dynamic_cast<Torcedor *>(p)->exibir();
      sleep(1);
      break;
    }
    break;
  };
  case '4': {
    // alterar
    if (gerenciamento.size() == 0) {
      std::cout << "N�o possui pessoas registradas" << std::endl;
      sleep(1);
      break;
    }
    int erro = alterarPessoa();
    return 0;
  };
  case '5': {
    if (gerenciamento.size() == 0) {
      std::cout << "N�o possui pessoas registradas" << std::endl;
      sleep(1);
      break;
    }
    removerPessoa();
    sleep(1);
    return 0;
  };
  case '6': {
    gerarRelatorio();
    sleep(1);
    break;
  };
  case '7': {
    return 1;
    // sair
  };
  default:
    std::cout << "Entrada inv�lida! " << std::endl;
    sleep(1);
    return 0;
    break;
  }
  return 0;
}

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
      arquivo << dynamic_cast<Comissao *>(pessoa)->getEquipeResponsavel() << std::endl;
      break;

    case 3:
      if (arquivo << dynamic_cast<Torcedor *>(pessoa)->getStatusVIP())
        arquivo << 1 << std::endl;
      else
        arquivo << 0 << std::endl;
      break;
    default:
      break;
    }
  }
}