#ifndef PLANO_H
#define PLANO_H

#include <bits/stdc++.h>
#include "../../CLASSES/Janela.h"
#include "../../CLASSES/Vetores.h"
#include "../../CLASSES/Objeto.h"

using namespace std;


struct Plano : Objeto{
    Ponto P0;
    Vect N;
    Vt ud;
    Vt vd;
    

    Plano(Ponto P0, Vect N){
        this->P0 = P0;
        this->N = N;
        this->kdif= RGB(0.0, 0.0, 0.0);
        this->kesp=  RGB(0.0, 0.0, 0.0);
        this->kamb = RGB(0.0, 0.0, 0.0);
        m = 0;
        usaText = false;
    }

    Vt normal(Ponto &/*pI*/){
        return N;
    }
    
    bool intersecta(Ponto &O, Ponto &P){
        Vt D = P - O; D.normaliza();
        double denom = N.ProdEsc(D);
        // Se o denominador for próximo de 0, o raio é paralelo ao plano
        if (fabs(denom) < 1e-6) return false;

        Vt w = O - P0;

        t = -(N.ProdEsc(w)) / denom;
        
        // Interseção só é válida se estiver à frente da origem do raio
        if (t > 1e-6){
            return true;
        }
        else return false;
        
    }

    RGB pintaTextura(Luz &L, Ponto &O, Ponto &P){
        Vt D = P - O; D.normaliza();
        Ponto pI = O.pontoIntersecao(t, D);
        Vt l = pI - P0;
        ud.normaliza();
        vd.normaliza();

        double u = l.ProdEsc(ud)/ ud.norma();
        double v = l.ProdEsc(vd)/ vd.norma();
        u = u - floor(u);
        v = v - floor(v);

        int tx = (int)(u * (textW - 1));
        int ty = (int)((1 - v) * (textH - 1));

        int idx = (ty * textW + tx) *  textC;
        double r = text[idx + 0] / 255.0;
        double g = text[idx + 1] / 255.0;
        double b = text[idx + 2] / 255.0;
        kdif = RGB(r, g, b);
        kesp = RGB(r, g, b);
        kamb = RGB(r, g, b);


        return pinta(L, O, P);
    }
    
    void aplicaTransformacao(Matriz &T) override{
        P0 = T * P0;
        
        Matriz R = T;
        R(0, 3) = 0;
        R(1, 3) = 0;
        R(2, 3) = 0;

        N = R * N;
        N.normaliza();
    }



};

#endif

