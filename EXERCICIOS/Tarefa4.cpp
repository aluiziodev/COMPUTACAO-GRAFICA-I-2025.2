#include <bits/stdc++.h>

#include "../CLASSES/OBJETOS/Esfera.h"
#include "../CLASSES/OBJETOS/Cilindro.h"
#include "../CLASSES/OBJETOS/Cone.h"
#include "../CLASSES/OBJETOS/Plano.h"
#include "../CLASSES/Janela.h"
#include "../CLASSES/Vetores.h"
#include "../CLASSES/Objeto.h"

using namespace std;


int main(){

    // PROPRIEDADES CANVAS
    double wJanela = 0.6;
    double hJanela = 0.6;
    double dJanela = 0.3;
    int nLin = 500;
    int nCol = 500;

    double Dx = wJanela/nCol;
    double Dy = hJanela/nLin;

    Canvas canvas(nLin, nCol);

    Ponto Olho = Ponto(0.0, 0.0, 0.0);


     // PROPRIEDADES LUZ
    RGB I_F = {0.7, 0.7, 0.7}; 
    RGB I_A = {0.3,0.3,0.3};
    Ponto P_F(0.0, 0.6, -0.3);



    // PROPRIEDADES ESFERA
    Esfera esfera(0.4, Ponto(0.0, 0.0, -1.0));
    esfera.kdif = {0.7, 0.2, 0.2};
    esfera.kesp = {0.7, 0.2, 0.2};
    esfera.kamb = {0.7, 0.2, 0.2};
    esfera.m = 10;

    // PROPRIEDADES PLANOS
    Plano planoChao({0.0, -esfera.r, 0.0}, {0.0, 1.0, 0.0});
    planoChao.kdif = {0.2, 0.7, 0.2};
    planoChao.kamb = {0.2, 0.7, 0.2};
    planoChao.m = 1;

    Plano planoFundo({0.0, 0.0, -2.0}, {0.0, 0.0, 1.0});
    planoFundo.kdif = {0.3,0.3,0.7};
    planoFundo.kamb =  {0.3,0.3,0.7};
    planoFundo.m = 1;

    // PROPRIEDADES CILINDRO
    Cilindro cilindro(esfera.r/3.0, esfera.r*3.0, esfera.Cesf, Vt(-1/sqrt(3), 1/sqrt(3),-1/sqrt(3)));
    cilindro.kdif = {0.2,0.3,0.8};
    cilindro.kesp = {0.2,0.3,0.8};
    cilindro.kamb = {0.2,0.3,0.8};
    cilindro.m = 1;

    // PROPRIEDADES CONE
    Ponto cBaseCone = Ponto(
        cilindro.Cbase.x + cilindro.dCil.x * cilindro.hCil,
        cilindro.Cbase.y + cilindro.dCil.y * cilindro.hCil,
        cilindro.Cbase.z + cilindro.dCil.z * cilindro.hCil);
    Cone cone(1.5*esfera.r, (1.5*esfera.r)/3.0, cBaseCone, cilindro.dCil);
    cone.kdif = {0.8, 0.3, 0.2};
    cone.kesp = {0.8, 0.3, 0.2};
    cone.kamb = {0.8, 0.3, 0.2};
    cone.m = 1;

    
    vector<Objeto *> cena = {&esfera, &cilindro, &planoChao, &planoFundo, &cone};



    for(int g = 0; g<nLin; g++){
        for(int c = 0; c<nCol; c++){
            double x = -wJanela/2 + Dx/2 + c*Dx;
            double y = hJanela/2 - Dy/2 - g*Dy;
            Ponto P = Ponto(x, y , -dJanela);
            double tmin = -1.0;

            RGB cor;
            for(Objeto *obj : cena){
                if(obj->intersecta(Olho, P)){
                    if(obj->t>0 && (tmin<0 || obj->t<tmin)){
                        tmin = obj->t;
                        Vt D = P - Olho; D.normaliza();
                        Ponto pI= Olho.pontoInterseçao(obj->t, D);
                        if(shadowRay(pI, P_F, obj, cena)){
                            cor = obj->kamb.arroba(I_A);
                        }
                        else{
                            cor = obj->pinta(Olho, P, P_F, I_F, I_A);
                        }
                    }
                }
            }

            canvas.janela[g*nCol+c] = cor;
            

            
            
        }
        
    }

    canvas.GeraImg("tarefa4.ppm");

    cout << "concluido \n";

    return 0;

}