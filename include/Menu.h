#ifndef MENU_H
#define MENU_H

#include "ExecutaJogo.h"


class Menu
{
    public:
        Menu();
        virtual ~Menu();

        void exibirScore();
        void abrirMenu();

    protected:

    private:
        ExecutaJogo jogo;
};

#endif // MENU_H
