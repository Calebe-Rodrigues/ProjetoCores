#ifndef COR_H
#define COR_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>

using namespace cv;

class Cor
{
    public:
        Cor();
        virtual ~Cor();

        std::string getCor(){return cor;}
        void setCor(int essaCor);

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


        std::string cor; // A cor:

    private:
};

#endif // COR_H
