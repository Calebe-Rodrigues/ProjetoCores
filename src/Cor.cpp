#include "Cor.h"
#include <iostream>

using namespace cv;
using namespace std;

Cor::Cor()
{
    //S� definindo valores padr�es iniciais para as cores
    BBmin = GGmin = RRmin = BGmax = BRmax = GBmax = GRmax = RBmax = RGmax = 100;

    BGmin = BRmin = GBmin = GRmin = RBmin = RGmin = 10;

    BBmax = GGmax = RRmax = 255;

}

Cor::~Cor()
{
    //dtor
}



void Cor::setCor(int essaCor){ //Entra com R G ou B no parametro para definir qual cor esse objeto representa
    //cout << "em setCor BBmin = " << BBmin<< endl;

    if (essaCor == 0){
        cor = "Azul";

        Bmin = BBmin;
        Bmax = BBmax;

        Gmin = BGmin;
        Gmax = BGmax;

        Rmin = BRmin;
        Rmax = BRmax;
    }
    if (essaCor == 1){
        cor = "Verde";

        Bmin = GBmin;
        Bmax = GBmax;

        Gmin = GGmin;
        Gmax = GGmax;

        Rmin = GRmin;
        Rmax = GRmax;
    }
    if (essaCor == 2){
        cor = "Vermelho";

        Bmin = RBmin;
        Bmax = RBmax;

        Gmin = RGmin;
        Gmax = RGmax;

        Rmin = RRmin;
        Rmax = RRmax;
    }
}

void Cor::CalibrarCor(){
    int LowB, HighB;
    int LowG, HighG;
    int LowR, HighR;

    LowB = LowG = LowR = 0;
    HighB = HighG = HighR = 255;

    VideoCapture cap(0); //Captura a imagem da camera pad�o
    if ( !cap.isOpened() )  // Se n�o conseguir, fecha o programa
    {
        cout << "Nao foi possivel abrir a camera" << endl;
        return;
    }

    namedWindow("Control", CV_WINDOW_AUTOSIZE); // Cria uma janela chamada"Control"

    cvCreateTrackbar("LowB", "Control", &LowB, 255);
    cvCreateTrackbar("HighB", "Control", &HighB, 255);

    cvCreateTrackbar("LowG", "Control", &LowG, 255);
    cvCreateTrackbar("HighG", "Control", &HighG, 255);

    cvCreateTrackbar("LowR", "Control", &LowR, 255);
    cvCreateTrackbar("HighR", "Control", &HighR, 255);

    //Criando as variaveis antes de come�ar a loop
    Mat imgOriginal;
    Mat outputImg;
    bool bSuccess;

    // O for vai rodar 3 vezes uma pra cada cor
    for (int i=0; i<3; i++){
        if (i==0) cout << "\nCalibrando cor: Azul\nPressine 'enter' quando estiver calibrado.\n";
        if (i==1) cout << "\nCalibrando cor: Verde\nPressine 'enter' quando estiver calibrado.\n";
        if (i==2) cout << "\nCalibrando cor: Vermelho\nPressine 'enter' quando estiver calibrado.\n";


        while(true){
            bSuccess = cap.read(imgOriginal);

            if(!bSuccess){
                cout << "Nao foi possivel ler o frame do video" << endl;
                break;
            }

            inRange(imgOriginal, Scalar(LowB,LowG,LowR), Scalar(HighB,HighG,HighR),outputImg);

            //morphological opening (Remove pequenos objetos em primeiro plano)
            erode(outputImg, outputImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
            dilate( outputImg, outputImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

            //morphological closing (Preenche pequenos buracos em primeiro plano)
            dilate( outputImg, outputImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
            erode(outputImg, outputImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

            imshow("Output Image", outputImg); //Exibe a imagem de saida
            imshow("Original image", imgOriginal); //Exibe a imagem original

            //cout << countNonZero(outputImg) << "   ";

            if (waitKey(30) == 13) //espera que a tecla 'enter' seja pressionada por 30ms. Se 'enter' for pressionado quebra o loop
            {
                cout << "Cor calibrada\n" << endl;
                break;
            }
        }

        // No primeiro loop salva os valores limites para a cor azul
        if (i==0){
            BBmin = LowB;
            BBmax = HighB;

            BGmin = LowG;
            BGmax = HighG;

            BRmin = LowR;
            BRmax = HighR;
        }

        // No segundo loop salva os valores para verde
        if (i==1){
            GBmin = LowB;
            GBmax = HighB;

            GGmin = LowG;
            GGmax = HighG;

            GRmin = LowR;
            GRmax = HighR;
        }

        // No terceiro para vermelho
        if (i==2){
            RBmin = LowB;
            RBmax = HighB;

            RGmin = LowG;
            RGmax = HighG;

            RRmin = LowR;
            RRmax = HighR;
        }
    }
    cvDestroyAllWindows();
}
