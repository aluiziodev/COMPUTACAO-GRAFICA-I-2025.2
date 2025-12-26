#ifndef LUZ_H
#define LUZ_H

#include "Vetores.h"
#include "Janela.h"

typedef struct Luz{
   
    const RGB intensidade;
    const RGB ambiente;

    Luz(const RGB &I, const RGB &A) : intensidade(I), ambiente(A) {}

    virtual RGB ilumina(const Ponto P, Vt &N, Ponto pI, const Ponto &O, RGB kdif, RGB kesp, RGB ka, int m) const = 0;

    virtual ~Luz() {}
} Luz;

#endif