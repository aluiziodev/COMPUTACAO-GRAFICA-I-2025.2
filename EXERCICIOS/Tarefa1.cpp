#include <bits/stdc++.h>
#include "../OBJETOS/Esfera.h"
#include "../OBJETOS/Janela.h"
#include "../OBJETOS/EstruturasGeo.h"

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

    Ponto Olho = Ponto(0, 0, 0);



    // PROPRIEDADES ESFERA
    Esfera esfera(40, Ponto(0, 0, -100));
    esfera.kdif = {0.7, 0.2, 0.2};
    esfera.kesp = {0.7, 0.2, 0.2};
    esfera.kamb = {0.7, 0.2, 0.2};
    esfera.m = 10;



    for(int l = 0; l<nLin; l++){
        for(int c = 0; c<nCol; c++){
            double x = -wJanela/2 + Dx/2 + c*Dx;
            double y = hJanela/2 - Dy/2 - l*Dy;
            Ponto P = Ponto(x, y , -dJanela);
            Vect D = P-Olho; double t;
           

            if(esfera.IntersectaEsfera(Olho, D, t)){
                canvas.janela[l*nCol +c] = {255, 0, 0};
            }
            
        }
        
    }

    canvas.GeraImg("tarefa1.ppm");

    return 0;

}