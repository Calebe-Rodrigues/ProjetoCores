#include "Menu.h"
#include <stdio.h>

Menu::Menu()
{
    jogo = ExecutaJogo();
}

Menu::~Menu()
{
    //dtor
}

void Menu::exibirScores(){;} //LER ARQUIVOS COM OS NOMES E AS PONTUA��ES

void Menu::abrirMenu(){
    printf("---- Menu ----\n\n"
           "1 - Play\n"
           "2 - Definir nome do jogador\n"
           "3 - Exibir Pontuacoes\n"
           "4 - Calibrar cores (recomendado antes de jogar)\n"
           "5 - Sair");
    int i;

    std::cin >> i;

    switch(i){
    case 1:
        jogo.execJogo();
        abrirMenu();
        break;

    case 2:
        jogo.setNome();
        abrirMenu();
        break;

    case 3:
        exibirScores();
        abrirMenu();
        break;

    case 4:
        jogo.getACor().CalibrarCor();
        abrirMenu();
        break;

    case 5:
        std::cout << "Obrigado por jogar!! (ou abrir e fechar o jogo no caso)";
        break;

    }
}
