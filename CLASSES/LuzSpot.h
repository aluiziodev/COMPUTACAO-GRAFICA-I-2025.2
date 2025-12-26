#ifndef LUZSPOT_H
#define LUZSPOT_H

#include "luz.h"

struct LuzSpot : Luz {
    Ponto posicao;
    Vt dir;
    double cutoff;

    LuzSpot(const RGB &I, const RGB &A, const Vt &d, double ang, const Ponto &pos) 
        : Luz(I, A), posicao(pos), dir(d)  {
        dir.normaliza();
        cutoff = cos(ang * M_PI / 180.0);
    }

    RGB ilumina(const Ponto P, Vt &N, Ponto pI, const Ponto &O, RGB kdif, RGB kesp, RGB ka, int m) const override{
        Vt D = P - O; D.normaliza();

        Vt L = posicao - pI; L.normaliza();
        Vt V = Vt(-D.x, -D.y, -D.z); V.normaliza();

        double spotEffect = (-L).ProdEsc(dir);

        RGB amb = ambiente;
        RGB I_a = ka.arroba(amb);

        if(spotEffect < cutoff){
            return I_a;
        }

        double nL = N.ProdEsc(L);

        Vt r = Vt(2*nL* (N.x - L.x), 2*nL* (N.y - L.y), 2*nL*(N.z - L.z)); r.normaliza();

        RGB I = intensidade;

        //Calculando o difuso
        RGB I_d = kdif.arroba(I);
        double d = max(nL, 0.0);
        I_d.r = (I_d.r*d*spotEffect);
        I_d.g = (I_d.g*d*spotEffect);
        I_d.b = (I_d.b*d*spotEffect);

        //Calculando a especular
        RGB I_e = kesp.arroba(I); 
        double vR = max(V.ProdEsc(r), 0.0);
        double e = pow(vR, m);
        I_e.r = (I_e.r * e * spotEffect);
        I_e.g = (I_e.g * e * spotEffect);
        I_e.b = (I_e.b * e * spotEffect);

        
        double R = (I_d.r+I_e.r+I_a.r);
        double G = (I_d.g+I_e.g+I_a.g);
        double B = (I_d.b+I_e.b+I_a.b);

        return RGB(double( min(1.0, R)), double( min(1.0, G)), double(min(1.0, B)));
    }

    void apontarPara(const Ponto &P){
        Vt L = posicao - P; 
        L.normaliza();
        this->dir = -L;
    }
};

#endif