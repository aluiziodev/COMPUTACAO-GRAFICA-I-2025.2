#include <bits/stdc++.h>

#include "../CLASSES/OBJETOS/Esfera.h"
#include "../CLASSES/Janela.h"
#include "../CLASSES/Vetores.h"
#include "../CLASSES/Objeto.h"
#include "../CLASSES/LuzPontual.h"
#include "../CLASSES/Camera.h"

using namespace std;

int main(){
    // PROPRIEDADES CANVAS
    double wJanela = 60;
    double hJanela = 60;
    double dJanela = 30;
    int nLin = 500;
    int nCol = 500;

    double Dx = wJanela/nCol;
    double Dy = hJanela/nLin;

    Canvas canvas(nLin, nCol);

    Camera Cam( wJanela, hJanela, Pt(0.0, 0.0, 0.0));




    // PROPRIEDADES ESFERA
    Esfera esfera(40, Ponto(0, 0, -100));
    esfera.kdif = {0.7, 0.2, 0.2};
    esfera.kesp = {0.7, 0.2, 0.2};
    esfera.kamb = {0.7, 0.2, 0.2};
    esfera.m = 10;



    // PROPRIEDADES LUZ
    LuzPontual luz(RGB(0.7, 0.7, 0.7),Pt(0, 60, -30));
    RGB I_A = {0.3,0.3,0.3};
    




    for(int g = 0; g<nLin; g++){
        for(int c = 0; c<nCol; c++){
            double x = -wJanela/2 + Dx/2 + c*Dx;
            double y = hJanela/2 - Dy/2 - g*Dy;
            Ponto P = Ponto(x, y , -dJanela);

            if(esfera.intersecta(Cam.posicao, P)){ // ESFERA
                RGB cor = esfera.kamb.arroba(I_A);
                cor += esfera.pinta(luz, Cam.posicao, P);
                canvas.janela[g*nCol+c] = cor;
            }
            
        }
        
    }

    canvas.GeraImg("tarefa2.ppm");

    return 0;

}




