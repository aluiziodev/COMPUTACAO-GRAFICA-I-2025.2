#ifndef OBJETO_H
#define OBJETO_H

#include <bits/stdc++.h>
#include "Janela.h"
#include "Vetores.h"
#include "Matriz.h"
#include "Luz.h"

struct Objeto{
    RGB kdif, kesp, kamb;
    int m;
    double t;
    bool usaText;
    unsigned char* text;
    int textW, textH, textC;
   

    virtual ~Objeto() {}

    virtual void aplicaTransformacao(Matriz &T) = 0;
    virtual bool intersecta(Ponto &O, Ponto &D) = 0;
    virtual RGB pintaTextura(Luz &l, Ponto &O, Ponto &P) = 0;
    virtual Vect normal(Ponto &pI) = 0;

    void colocaText(unsigned char* text, int &w, int &h, int &c){
        usaText = true;
        this->text = text;
        textW = w;
        textH = h;
        textC = c;
    }

    RGB pinta(Luz &luz, Ponto &O, Ponto &P){
        Vt D = P -O; D.normaliza();
        Ponto pI= Ponto(O.x + t*D.x, O.y + t*D.y, O.z + t*D.z);
        Vt N = normal(pI);
        if(N.ProdEsc(D)>0.0) N = Vt(-N.x,-N.y,-N.z);

        return luz.ilumina(P, N, pI, O, kdif, kesp, kamb, m);
    }


};

bool shadowRay(Ponto &pI, Ponto &pF, Objeto *atual, vector<Objeto *> &cena){
    Vt l = pF - pI;
    double dist = sqrt(l.ProdEsc(l));
    if(dist<=0.0) return false;
    l.normaliza();
    double eps = 1e-5;

    Ponto pL = pI.pontoIntersecao(dist, l);
    Vt n = atual->normal(pI);
    if(n.ProdEsc(l)>0.0) n = Vt(-n.x, -n.y, -n.z); 
    Ponto Desloc = pI.pontoIntersecao(eps, n);
    for(Objeto *obj : cena){
        if(obj != atual){
            if(obj->intersecta(Desloc, pL)){
                if(obj->t > eps && obj->t<dist) return true;
            }
        }
    }
    return false;
} 








#endif