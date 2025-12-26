#ifndef LUZPONTUAL_H
#define LUZPONTUAL_H

#include "luz.h"

using namespace std;

struct LuzPontual : Luz {
    Ponto posicao;

    LuzPontual(RGB I, RGB A, Ponto pos) :  Luz(I, A), posicao(pos) {}

    RGB ilumina(const Ponto P, Vt &N, Ponto pI, const Ponto &O, RGB kdif, RGB kesp, RGB ka, int m) const override{
        Vt D = P - O; D.normaliza();

        Vt L = posicao - pI; L.normaliza();
        Vt V = Vt(-D.x, -D.y, -D.z); V.normaliza();

        double nL = N.ProdEsc(L);

        Vt r = Vt(2*nL*N.x - L.x, 2*nL*N.y - L.y, 2*nL*N.z - L.z); r.normaliza();

        RGB I = intensidade;

        //Calculando o difuso
        RGB I_d = kdif.arroba(I);
        double d = max(nL, 0.0);
        I_d.r = (I_d.r*d);
        I_d.g = (I_d.g*d);
        I_d.b = (I_d.b*d);

        //Calculando a especular
        RGB I_e = kesp.arroba(I); 
        double vR = max(V.ProdEsc(r), 0.0);
        double e = pow(vR, m);
        I_e.r = (I_e.r * e);
        I_e.g = (I_e.g * e);
        I_e.b = (I_e.b * e);

        RGB amb = ambiente;
        RGB I_a = ka.arroba(amb);

        double R = (I_d.r+I_e.r+I_a.r);
        double G = (I_d.g+I_e.g+I_a.g);
        double B = (I_d.b+I_e.b+I_a.b);

        return RGB(double( min(1.0, R)), double( min(1.0, G)), double(min(1.0, B)));
    }
};

#endif