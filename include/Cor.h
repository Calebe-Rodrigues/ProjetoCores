#ifndef COR_H
#define COR_H

#include "opencv2/highgui/highgui.hpp"
#include "imgproc/imgproc.hpp"

using namespace cv;

class Cor
{
    public:
        Cor();
        virtual ~Cor();

        char getCor(){return cor;}
        void setCor(char essaCor);

        Scalar getMin(){return Scalar(Bmin,Gmin,Rmin);}
        Scalar getMax(){return Scalar(Bmax,Gmax,Rmax);}

        void CalibrarCor();


    protected:
        //Os valores da cor de fato:
        int Bmin, Bmax;
        int Gmin, Gmax;
        int Rmin, Rmax;

        //Variaveis usadas para calibrar os limites:

        int BBmin, BBmax; //Para a cor Azul
        int BGmin, BGmax;
        int BRmin, BRmax;

        int GBmin, GBmax; //Para a cor Verde
        int GGmin, GGmax;
        int GRmin, GRmax;

        int RBmin, RBmax; //Para a cor Vermelha
        int RGmin, RGmax;
        int RRmin, RRmax;


        char cor; // A letra representando a cor:

    private:
};

#endif // COR_H
