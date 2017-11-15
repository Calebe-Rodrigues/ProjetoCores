#include "Cor.h"
#include <iostream>

using namespace cv;
using namespace std;

Cor::Cor()
{
    //Só definindo valores padrões iniciais para as cores
    BBmin = GGmin = RRmin = BGmax = BRmax = GBmax = GRmax = RBmax = RGmax = 100;

    BGmin = BRmin = GBmin = GRmin = RBmin = RGmin = 10;

    BBmax = GGmax = RRmax = 255;

}

Cor::~Cor()
{
    //dtor
}



void Cor::setCor(char essaCor){ //Entra com R G ou B no parametro para definir qual cor esse objeto representa
    cor = essaCor;

    if (essaCor == 'B'){
        Bmin = BBmin;
        Bmax = BBmax;

        Gmin = BGmin;
        Gmax = BGmax;

        Rmin = BRmin;
        Rmax = BRmax;
    }
    if (essaCor == 'G'){
        Bmin = GBmin;
        Bmax = GBmax;

        Gmin = GGmin;
        Gmax = GGmax;

        Rmin = GRmin;
        Rmax = GRmax;
    }
    if (essaCor == 'R'){
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

    // O for vai rodar 3 vezes uma pra cada cor
    for (int i=0; i<3; i++){
        if (i==0) cout << "Calibrando cor: Azul\nPressine 'enter' quando estiver calibrado.\n";
        if (i==1) cout << "Calibrando cor: Verde\nPressine 'enter' quando estiver calibrado.\n";
        if (i==2) cout << "Calibrando cor: Vermelho\nPressine 'enter' quando estiver calibrado.\n";

        VideoCapture cap(0); //Captura a imagem da camera padão
        if ( !cap.isOpened() )  // Se não conseguir, fecha o programa
        {
             cout << "Nao foi possivel abrir a camera" << endl;
             break;
        }

        namedWindow("Control", CV_WINDOW_AUTOSIZE); // Cria uma janela chamada"Control"

        cvCreateTrackbar("LowB", "Control", &LowB, 255);
        cvCreateTrackbar("HighB", "Control", &HighB, 255);

        cvCreateTrackbar("LowG", "Control", &LowG, 255);
        cvCreateTrackbar("HighG", "Control", &HighG, 255);

        cvCreateTrackbar("LowR", "Control", &LowR, 255);
        cvCreateTrackbar("HighR", "Control", &HighR, 255);

        while(true){
            Mat imgOriginal;

            bool bSuccess = cap.read(imgOriginal);

            if(!bSuccess){
                cout << "Nao foi possivel ler o frame do video" << endl;
                break;
            }

            Mat outputImg;

            inRange(imgOriginal, Scalar(LowB,LowG,LowR), Scalar(HighB,HighG,HighR),outputImg);

            //morphological opening (Remove pequenos objetos em primeiro plano)
            erode(outputImg, outputImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
            dilate( outputImg, outputImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

            //morphological closing (Preenche pequenos buracos em primeiro plano)
            dilate( outputImg, outputImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
            erode(outputImg, outputImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

            imshow("Output Image", outputImg); //Exibe a imagem de saida
            imshow("Original image", imgOriginal); //Exibe a imagem original

            if (waitKey(30) == 13) //espera que a tecla 'enter' seja pressionada por 30ms. Se 'enter' for pressionado quebra o loop
            {
                cout << "Cor calibrada" << endl;
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
}
