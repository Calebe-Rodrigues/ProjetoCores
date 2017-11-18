#include "ExecutaJogo.h"

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
    std::cout << "\nInsira o seu nome (sem espacos): ";
    std::cin >> nomeJogador;
}

//Gera um numero aleat�rio de 0 a 2 e passa como parametro de setCor(int)
void ExecutaJogo::geraCor(){
    srand(time(NULL));
    ACor.setCor(rand()%3);
}

void ExecutaJogo::execJogo(){
    std::cout << "-------------- Que o jogo comece!!! --------------\n\nMostre o cartao com a cor pedida!\n";
    std::cout << "(aperte 'ESC' para sair):\n\n";

    VideoCapture cap(0); //Captura a imagem da camera pad�o

    if ( !cap.isOpened() )  // Se n�o conseguir, fecha o programa
    {
         std::cout << "Nao foi possivel abrir a camera\n";
         return;
    }

    Mat imgOriginal;
    Mat outputImg;

    bool bSuccess;

    while (true){
        geraCor();
        std::cout << "---- " << ACor.getCor() << "! ----\n\n";

        sleep(1);

        while(true){
            bSuccess = cap.read(imgOriginal);

            if(!bSuccess){
                std::cout << "Nao foi possivel ler o frame" << std::endl;
                break;
            }

            inRange(imgOriginal, ACor.getMin(), ACor.getMax(),outputImg);

            //morphological opening (remove small objects from the foreground)
            erode(outputImg, outputImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
            dilate( outputImg, outputImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

            //morphological closing (fill small holes in the foreground)
            dilate( outputImg, outputImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
            erode(outputImg, outputImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

            imshow("Original", imgOriginal); //show the original image
            //imshow("Output", outputImg);

            //std::cout << countNonZero(outputImg) << "   ";

            if (countNonZero(outputImg) >= 40000){  //40000 � o valor que representa o valor minimo da carta
                std::cout << "Bom Trabalho!!\n\n";
                umPonto();

                break;
            }
            if (waitKey(30) == 27){ //Se 'esc' for pressionado quebra o loop
                std::cout << "esc key is pressed by user\nPartida encerrada.\n" << std::endl;
                cvDestroyAllWindows();
                /*
                    SALVAR A PONTUA�AO E O NOME DO JOGADOR EM UM ARQUIVO
                    AQUI
                */

                return;
            }
        }
    }
}
