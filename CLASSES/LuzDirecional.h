#ifndef LUZDIRECIONAL_H
#define LUZDIRECIONAL_H

#include "luz.h"

struct LuzDirecional : Luz {
    Vt dir;

    LuzDirecional(RGB I, Vt d) :  Luz(I), dir(d) {
        dir.normaliza();
    }

    double distanciaParaLuz(const Ponto &P) const override
    {
        (void) P; // P nao eh usado em luz direcional
        return 1e9; //"Infinito"
    }

    Vt direcaoLuz(const Ponto &P) const override
    {
        (void) P; // P nao eh usado em luz direcional
        return -dir;
    }

    RGB ilumina(const Ponto P, Vt &N, Ponto pI, const Ponto &O, RGB kdif, RGB kesp, int m) const override
    {
        (void) pI; // pI nao eh usado em luz direcional
        
        Vt D = P - O;
        D.normaliza();

        Vt L = -dir;
        L.normaliza();

        Vt V = -D;
        V.normaliza();



        double nL = max(N.ProdEsc(L), 0.0);

        Vt R = Vt(2*nL* (N.x - L.x), 2*nL* (N.y - L.y), 2*nL*(N.z - L.z)); R.normaliza();

        RGB I = intensidade;

        // Difusa
        RGB I_d = kdif.arroba(I);
        I_d.r *= nL;
        I_d.g *= nL;
        I_d.b *= nL;

        // Especular
        double vR = max(V.ProdEsc(R), 0.0);
        double e = pow(vR, m);

        RGB I_e = kesp.arroba(I);
        I_e.r *= e;
        I_e.g *= e;
        I_e.b *= e;

        // Soma final
        double Rf =  I_d.r + I_e.r;
        double Gf = I_d.g + I_e.g;
        double Bf = I_d.b + I_e.b;

        return RGB(
            min(1.0, Rf),
            min(1.0, Gf),
            min(1.0, Bf)
        );
    }
    
};

#endif