#ifndef EXECUTAJOGO_H
#define EXECUTAJOGO_H

#include <iostream>
#include "Cor.h"
#include <string>
#include <stdlib.h> // necess�rio p/ as fun��es rand() e srand()
#include <time.h>   // necess�rio p/ fun��o time()
#include <unistd.h>
#include <fstream>

class ExecutaJogo
{
    public:
        ExecutaJogo();
        virtual ~ExecutaJogo();

        Cor *getACor(){return &ACor;}

        std::string getNome(){return nomeJogador;}
        void setNome();

        int getScore(){return scoreAtual;}
        void umPonto(int mult);

        int geraCor();

        void execJogo();

    protected:
    private:
        std::string nomeJogador;
        int scoreAtual;
        Cor ACor;
};

#endif // EXECUTAJOGO_H
