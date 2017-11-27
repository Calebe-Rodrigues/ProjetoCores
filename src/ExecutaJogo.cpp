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
int ExecutaJogo::geraCor(){
    int oNumero;
    srand(time(NULL));
    oNumero = rand()%6;
    ACor.setCor(oNumero);

    return oNumero;
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

    Mat exibeCor;
    Mat imgOriginal;
    Mat outputImg;

    bool bSuccess;
    int ultimaCor, novaCor; //Vari�veis para evitar a repeti��o de cores.
    ultimaCor = 6; // Um valor fora da escala de cores.

    while (true){
        novaCor = geraCor();

        if (novaCor == ultimaCor) continue;

        std::cout << "---- " << ACor.getCor() << "! ----\n\n";
        exibeCor = imread(ACor.getCor(), 1);

        namedWindow("Cor", CV_WINDOW_FREERATIO);
        imshow("Cor", exibeCor);


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

                cvDestroyAllWindows();

                ultimaCor = novaCor;
                break;
            }
            if (waitKey(30) == 27){ //Se 'esc' for pressionado quebra o loop
                std::cout << "esc key is pressed by user\nPartida encerrada.\n" << std::endl;
                cvDestroyAllWindows();

                // EXIBINDO A PONTUA��O E VERIFICANDO SE � MAIOR QUE O RECORDE

                std::cout << "Voce marcou " << scoreAtual << " pontos!!\n\n";

                std::ifstream inpontos;

                inpontos.open("highscore.txt");

                if (!inpontos.is_open()){
                    std::cout << "Erro ao salvar a pontuacao!\n";
                    inpontos.close();
                    return;
                }

                int maiorPont;

                inpontos >> maiorPont;
                inpontos.close();

                if (scoreAtual > maiorPont){
                    std::cout << "NOVO RECORDE!!\n\n";
                    std::ofstream outpontos;

                    outpontos.open("highscore.txt");

                    if (!outpontos.is_open()){
                        std::cout << "Erro ao salvar a pontuacao!\n";
                        outpontos.close();
                        return;
                    }

                    outpontos << scoreAtual << std::endl << nomeJogador;

                    outpontos.close();

                }

                scoreAtual = 0;

                return;
            }
        }
    }
}
