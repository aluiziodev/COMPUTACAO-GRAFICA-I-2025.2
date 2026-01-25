#ifndef CAMERA_H
#define CAMERA_H

#include "../UTILS/Vetores.h"



typedef struct Camera{
    Ponto posicao;
    Vt U; //direita
    Vt V; //cima
    Vt W; //frente
    float d;
    float xmin;
    float xmax;
    float ymin;
    float ymax;

    Camera(float wJan, float hjan, Ponto posicao = Ponto(0,0,0), 
            Vt U = Vt(1,0,0), Vt V = Vt(0,1,0), Vt W = Vt(0,0,-1),
            float fovY = 60){
        this->posicao = posicao;
        this->d = 0.3; //Vamos deixar essa distancia por padrão 
        this->U = U;
        this->V = V;
        this->W = W;
        float h = d * tan(fovY * M_PI /360);
        float aspc = wJan/hjan;
        this->xmin = - h * aspc;
        this->xmax = h * aspc;
        this->ymin = -h;
        this->ymax = h;
    }
    
    void zoomIn(float z){
        d =  d*z;
    }

    void zoomOut(float z){
        d =  d/z;
    }


    void girarDireitaEsquerda(float angulo){
        float rad = angulo * M_PI / 180.0;
        float c = cos(rad);
        float s = sin(rad);

        Vt U = this->U;
        Vt W = this->W;

        this->U = U*c + W*s;
        this->W = W*c - U*s;
        
        this->U.normaliza();
        this->V.normaliza();
        this->W.normaliza();
    }

    void girarCimaBaixo(float angulo){
        float rad = angulo * M_PI /180.0;
        float c = cos(rad);
        float s = sin(rad);

        Vt V = this->V;
        Vt W = this->W;

        this->V = V*c - W*s;
        this->W = W*c + V*s;

        this->U.normaliza();
        this->V.normaliza();
        this->W.normaliza();
    }

    void girarRolamento( float angulo){
        float rad = angulo * M_PI /180.0;
        float c = cos(rad);
        float s = sin(rad);

        Vt U = this->U;
        Vt V = this->V;

        this->U = U*c - V*s;
        this->V = U*s + V*c;

        this->U.normaliza();
        this->V.normaliza();
        this->W.normaliza();

    }


    void LookAt( Ponto Alvo, Vt up = Vt(0,1,0)){
        this->W = this->posicao - Alvo;
        this->W.normaliza();

        if(abs(this->W.ProdEsc(up)) >0.999)
            up = Vt(0,0,1);
        
        this->U = W.prodVet(up);
        this->U.normaliza();

       this->V = U.prodVet(W);
        
    }

}Cam;

#endif