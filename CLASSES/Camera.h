#ifndef CAMERA_H
#define CAMERA_H

#include "Vetores.h"



typedef struct Camera{
    Ponto posicao;
    Vt U; //direita
    Vt V; //cima
    Vt W; //frente
    double d;
    double xmin;
    double xmax;
    double ymin;
    double ymax;

    Camera(double wJan, double hjan, Ponto posicao = Ponto(0,0,0), 
            Vt U = Vt(1,0,0), Vt V = Vt(0,1,0), Vt W = Vt(0,0,-1),
            double fovY = 60){
        this->posicao = posicao;
        this->d = 0.3; //Vamos deixar essa distancia por padrão 
        this->U = U;
        this->V = V;
        this->W = W;
        double h = d * tan(fovY * M_PI /360);
        double aspc = wJan/hjan;
        this->xmin = - h * aspc;
        this->xmax = h * aspc;
        this->ymin = -h;
        this->ymax = h;
    }
    
    void zoomIn(double z){
        d = min( 15.0 ,  d*z);
    }

    void zoomOut(double z){
        d = max(0.01, d/z);
    }


    void girarDireitaEsquerda(double angulo){
        double rad = angulo * M_PI / 180.0;
        double c = cos(rad);
        double s = sin(rad);

        Vt U = this->U;
        Vt W = this->W;

        this->U = U*c + W*s;
        this->W = W*c - U*s;
        
        this->U.normaliza();
        this->V.normaliza();
        this->W.normaliza();
    }

    void girarCimaBaixo(double angulo){
        double rad = angulo * M_PI /180.0;
        double c = cos(rad);
        double s = sin(rad);

        Vt V = this->V;
        Vt W = this->W;

        this->V = V*c - W*s;
        this->W = W*c + V*s;

        this->U.normaliza();
        this->V.normaliza();
        this->W.normaliza();
    }

    void girarRolamento( double angulo){
        double rad = angulo * M_PI /180.0;
        double c = cos(rad);
        double s = sin(rad);

        Vt U = this->U;
        Vt V = this->V;

        this->U = U*c - V*s;
        this->V = U*s + V*c;

        this->U.normaliza();
        this->V.normaliza();
        this->W.normaliza();

    }


    void LookAt( Ponto Alvo, Vt up = Vt(0,1,0)){
        this->W = Alvo - this->posicao;
        this->W.normaliza();

        if(abs(this->W.ProdEsc(up)) >0.999)
            up = Vt(0,0,1);
        
        this->U = this->W.prodVet(up);
        this->U.normaliza();

        this->V = this->U.prodVet(this->W);
        
    }

}Cam;

#endif