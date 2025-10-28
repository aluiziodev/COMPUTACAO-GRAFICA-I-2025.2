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



    // PROPRIEDADES LUZ
    RGB I_F = {0.7, 0.7, 0.7}; 
    RGB I_A = {0.3,0.3,0.3};
    Ponto P_F(0, 60, -30);




    for(int g = 0; g<nLin; g++){
        for(int c = 0; c<nCol; c++){
            double x = -wJanela/2 + Dx/2 + c*Dx;
            double y = hJanela/2 - Dy/2 - g*Dy;
            Ponto P = Ponto(x, y , -dJanela);
            Vect D = P-Olho; D.normaliza();
            double t;

            if(esfera.IntersectaEsfera(Olho, D, t)){ // ESFERA
                
                Ponto pI= Ponto(Olho.x + t*D.x,Olho.y + t*D.y, Olho.z + t*D.z);

                Vect n = pI - esfera.Cesf; n.normaliza();

                Vect l = P_F - pI; l.normaliza();
                Vect v = {-D.x, -D.y, -D.z}; v.normaliza();
                Vect r = Vect(2*n.ProdEsc(l)*n.x - l.x, 2*n.ProdEsc(l)*n.y - l.y, 2*n.ProdEsc(l)*n.z - l.z);
                r.normaliza();

                RGB I_d = esfera.kdif.arroba(I_F);
                double nL = n.ProdEsc(l);
                double d = max(nL, 0.0);
                I_d.r = (I_d.r*d);
                I_d.g = (I_d.g*d);
                I_d.b = (I_d.b*d);

                RGB I_e = esfera.kesp.arroba(I_F);
                double vR = max(v.ProdEsc(r), 0.0);
                double e = pow(vR, esfera.m);
                I_e.r = (I_e.r * e);
                I_e.g = (I_e.g * e);
                I_e.b = (I_e.b * e);

                RGB I_a = esfera.kamb.arroba(I_A);
                int R = 255*(I_d.r+I_e.r+I_a.r);
                int G = 255*(I_d.g+I_e.g+I_a.g);
                int B = 255*(I_d.b+I_e.b+I_a.b);
                
                canvas.janela[g*nCol+c] = {double(min(255, R)), 
                                            double( min(255, G)), 
                                            double(min(255, B))};
                
            }
        }
        
    }

    canvas.GeraImg("tarefa2.ppm");

    return 0;

}




