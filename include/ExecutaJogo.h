#ifndef EXECUTAJOGO_H
#define EXECUTAJOGO_H

#include <iostream>
#include "cor.h"
#include <string>
#include <stdlib.h> // necessário p/ as funções rand() e srand()
#include <time.h>   // necessário p/ função time()

class ExecutaJogo
{
    public:
        ExecutaJogo();
        virtual ~ExecutaJogo();

        Cor getACor(){return ACor;}

        std::string getNome(){return nomeJogador;}
        void setNome();

        int getScore(){return scoreAtual;}
        void umPonto(){scoreAtual++;}

        void geraCor();

        int execJogo();

    protected:

    private:
        std::string nomeJogador;
        int scoreAtual;
        Cor ACor;
};

#endif // EXECUTAJOGO_H
