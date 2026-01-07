#ifndef LUZ_H
#define LUZ_H

#include "Vetores.h"
#include "Janela.h"

typedef struct Luz{
   
    RGB intensidade;
    RGB ambiente;

    Luz(const RGB &I) : intensidade(I) {}

    virtual RGB ilumina(const Ponto P, Vt &N, Ponto pI, const Ponto &O, RGB kdif, RGB kesp, int m) const = 0;

    virtual double distanciaParaLuz(const Ponto &P) const = 0;
    virtual Vt direcaoLuz(const Ponto &P) const = 0;
    
    virtual ~Luz() {}
} Luz;

#endif