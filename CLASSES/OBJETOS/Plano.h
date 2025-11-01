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

    Plano(Ponto P0, Vect N){
        this->P0 = P0;
        this->N = N;
        this->kdif= RGB(0.0, 0.0, 0.0);
        this->kesp=  RGB(0.0, 0.0, 0.0);
        this->kamb = RGB(0.0, 0.0, 0.0);
        m = 0;
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

    RGB pinta(Ponto &O, Ponto &P,Ponto &pF, RGB &iF, RGB &iA){
        Vt D = P -O; D.normaliza();
        Vt n;
        if(D.ProdEsc(N)>0) n = Vt(-N.x, -N.y, -N.z);
        else n = N;
        n.normaliza();
        Ponto pI = Ponto(P0.x + t*D.x, P0.y + t*D.y, P0.z + t*D.z);
        Vect l = pF- pI; l.normaliza();
        Vect v = Vt(-D.x, -D.y, -D.z); v.normaliza();
        double nL = n.ProdEsc(l);
        Vect r = Vect(2*nL*n.x - l.x, 
                    2*nL*n.y - l.y,
                    2*nL*n.z - l.z);
        r.normaliza();

        RGB I_d = kdif.arroba(iF);
        double d = max(nL, 0.0);
        I_d.r = (I_d.r*d);
        I_d.g = (I_d.g*d);
        I_d.b = (I_d.b*d);

        RGB I_e = kesp.arroba(iF);
        double vR = max(v.ProdEsc(r), 0.0);
        double e = pow(vR, m);
        I_e.r = (I_e.r * e);
        I_e.g = (I_e.g * e);
        I_e.b = (I_e.b * e);

        RGB I_a = kamb.arroba(iA);

        double R = (I_d.r+I_e.r+I_a.r);
        double G = (I_d.g+I_e.g+I_a.g);
        double B = (I_d.b+I_e.b+I_a.b);

        return RGB(double(min(1.0, R)), double( min(1.0, G)), double(min(1.0, B)));

    }



};

#endif

