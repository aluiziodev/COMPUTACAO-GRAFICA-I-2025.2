#ifndef PLANO_H
#define PLANO_H

#include <bits/stdc++.h>
#include "EstruturasGeo.h"
#include "Janela.h"

using namespace std;


typedef struct Plano{
    Ponto P0;
    Vect N;
    int m;
    RGB K_d, K_e, K_a;

    Plano(Ponto P0, Vect N){
        this->P0 = P0;
        this->N = N;
        this->K_d = RGB(0.0, 0.0, 0.0);
        this->K_e = RGB(0.0, 0.0, 0.0);
        this->K_a = RGB(0.0, 0.0, 0.0);
        m = 0;
    }
    
    bool IntersectaPlano(Ponto &O, Vt &D, double &t){
        double denom = N.ProdEsc(D);
        // Se o denominador for próximo de 0, o raio é paralelo ao plano
        if (fabs(denom) < 1e-6) return false;

        Vt w = O - P0;

        t = -(N.ProdEsc(w)) / denom;
        
        // Interseção só é válida se estiver à frente da origem do raio
        if (t > 0){
            return true;
        }
        else return false;
        
    }



}pln;

#endif

