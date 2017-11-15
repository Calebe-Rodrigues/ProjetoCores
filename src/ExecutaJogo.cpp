#include "ExecutaJogo.h"

#define CARDMIN 10000 // VALOR QUE REPRESENTAM O TAMANHO MINIMO DA CARTA (ainda nao definido)
                      // SE A FUNÇÃO countNonZero() RETORNAR UM VALOR MAIOR OU IGUAL A CARDMIN
                      // SIGNIFICA QUE A CARTA ESTÁ NA CAMERA

ExecutaJogo::ExecutaJogo()
{
    nomeJogador = "JogadorAnonimo";
    ACor = Cor();
    scoreAtual = 0;
}

ExecutaJogo::~ExecutaJogo()
{
    //dtor
}

void ExecutaJogo::setNome(){
    std::cout << "Insira o seu nome: ";
    std::cin >> nomeJogador;
}

//Gera um numero aleatório de 0 a 2 e passa como parametro de setCor(int)
void ExecutaJogo::geraCor(){
    srand(time(NULL));
    ACor.setCor(rand()%3);
}

int ExecutaJogo::execJogo(){
    std::cout << "-------------- Que o jogo comece!!! --------------\n\nMostre o cartao com a cor pedida!\n";
    std::cout << "(aperte 'ESC' para sair):\n\n";

    VideoCapture cap(0); //Captura a imagem da camera padão

    if ( !cap.isOpened() )  // Se não conseguir, fecha o programa
    {
         std::cout << "Nao foi possivel abrir a camera\n";
         return -1;
    }

    Mat imgOriginal;
    Mat imgThresholded;

    while (true){
        geraCor();
        std::cout << "---- " << ACor.getCor() << "! ----\n\n";

        while(true){
            bool bSuccess = cap.read(imgOriginal);

            if(!bSuccess){
                std::cout << "Nao foi possivel ler o frame" << std::endl;
                break;
            }

            inRange(imgOriginal, ACor.getMin(), ACor.getMax(),imgThresholded);

            //morphological opening (remove small objects from the foreground)
            erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
            dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

            //morphological closing (fill small holes in the foreground)
            dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
            erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

            imshow("Original", imgOriginal); //show the original image

            if (countNonZero(imgThresholded) <= CARDMIN){ // !!!!!!! O VALOR DE CARDMIN AINDA PRECISA SER DEFINIDO E TESTADO !!!!!!!!!!!
                std::cout << "Bom Trabalho!!\n\n";
                umPonto();
                break;
            }
            if (waitKey(30) == 27){ //Se 'esc' for pressionado quebra o loop
                std::cout << "esc key is pressed by user\n Thanks for playing!" << std::endl;
                /*
                    SALVAR A PONTUAÇAO E O NOME DO JOGADOR EM UM ARQUIVO
                    AQUI
                */

                return 0;
            }
        }
    }
}
