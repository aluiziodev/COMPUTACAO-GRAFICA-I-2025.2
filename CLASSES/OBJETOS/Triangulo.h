#ifndef TRIANGULO_H
#define TRIANGULO_H

#include <bits/stdc++.h>
#include "../../CLASSES/Janela.h"
#include "../../CLASSES/Vetores.h"
#include "../../CLASSES/Objeto.h"

struct Triangulo : Objeto{
    Ponto P0;
    Ponto P1;
    Ponto P2;

    Triangulo(Ponto p1, Ponto p2, Ponto p0){
        P0 = p0;
        P1 = p1;
        P2 = p2;
        kdif = {0, 0, 0};
        kesp = {0, 0, 0};
        kamb = {0, 0, 0};
        m = 0;
        usaText = false;
    }

    Vt normal(Ponto &/*pI*/){
        Vt E1 = P1 - P0;
        Vt E2 = P2 - P0;
        Vt n = E1.prodVet(E2);
        n.normaliza();
        return n;
    }

    bool intersecta(Ponto &O, Ponto &P){
        Vt D = P -O; D.normaliza();
        Vt s = O - P0;
        Vt E1 = P1 - P0;
        Vt E2 = P2 - P0;
        Vt pv = D.prodVet(E2);
        double a = E1.ProdEsc(pv);
        if(fabs(a)<1e-6) return false;
        double c1 = s.ProdEsc(pv)/a;
        Vt qv = s.prodVet(E1);
        double c2 = D.ProdEsc(qv)/a;
        double c3 = 1.0 - c1 - c2;
        t = E2.ProdEsc(qv)/a;
        if(t>1e-6 && c1>=0 && c2>=0 && c3>=0) return true;
        return false;
    }


   RGB pintaTextura(Ponto &O, Ponto &P, Ponto &pf,RGB &iF,RGB &iA){
    return pinta(O, P, pf, iF, iA);
   }

   void aplicaTransformacao(Matriz &T) override{
        P0 = T * P0;
        P1 = T * P1;
        P2 = T * P2;
    }

};



#endif
