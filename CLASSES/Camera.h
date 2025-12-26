#include "Vetores.h"

typedef struct Camera{
    Ponto posicao;
    Vt U; //direita
    Vt V; //cima
    Vt W; //frente

    Camera(Ponto posicao = Ponto(0,0,0), Vt U = Vt(1,0,0), Vt V = Vt(0,1,0), Vt W = Vt(0,0,-1)){
        this->posicao = posicao;
        this->U = U;
        this->V = V;
        this->W = W;
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

    // ESSE AQUI USA O VETOR UP MOSTRADO NA AULA, MAS ESTAMOS USANDO O V DA PROPRIA CAMERA
    // void LookAt(Camera &cam, Ponto Alvo, Vt up){
    //     cam.W = Alvo - cam.posicao;
    //     cam.W.normaliza();

    //     cam.U = cam.W.prodVet(up);
    //     cam.U.normaliza();

    //     cam.V = cam.U.prodVet(cam.W);
        
    // }

    void LookAt( Ponto Alvo){
        this->W = Alvo - this->posicao;
        this->W.normaliza();

        this->U = this->W.prodVet(this->V);
        this->U.normaliza();

        this->V = this->U.prodVet(this->W);
        
    }

}Cam;