#ifndef OBJETO_H
#define OBJETO_H

#include <bits/stdc++.h>
#include "Janela.h"
#include "Vetores.h"

struct Objeto{
    RGB kdif, kesp, kamb;
    int m;
    double t;

    virtual bool intersecta(Ponto &O, Ponto &D) = 0;
    virtual RGB pinta( Ponto &O, Ponto &P, Ponto &pF, RGB &iF, RGB &iA) = 0;


};

bool shadowRay(Ponto &pI, Ponto &pF, Objeto *atual, vector<Objeto *> &cena){
    Vt l = pF - pI;
    double dist = sqrt(l.ProdEsc(l));
    if(dist<=0.0) return false;
    l.normaliza();
    double eps = 0.001;

    Ponto pL = Ponto(pI.x + l.x*dist, pI.y + l.y*dist, pI.z + l.z*dist);
    for(Objeto *obj : cena){
        if(obj != atual){
            if(obj->intersecta(pI, pL)){
                if(obj->t > eps && obj->t<dist) return true;
            }
        }
    }
    return false;
} 








#endif