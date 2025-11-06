#ifndef OBJETO_H
#define OBJETO_H

#include <bits/stdc++.h>
#include "Janela.h"
#include "Vetores.h"

struct Objeto{
    RGB kdif, kesp, kamb;
    int m;
    double t;
    bool usaText;
    unsigned char* text;
    int textW, textH, textC;


    virtual bool intersecta(Ponto &O, Ponto &D) = 0;
    virtual RGB pintaTextura(Ponto &O, Ponto &P, Ponto &pf,RGB &I_F,RGB &I_A) = 0;
    virtual Vect normal(Ponto &pI) = 0;

    void colocaText(unsigned char* text, int &w, int &h, int &c){
        usaText = true;
        this->text = text;
        textW = w;
        textH = h;
        textC = c;
    }

    RGB pinta(Ponto &O, Ponto &P,Ponto &pF, RGB &iF, RGB &iA){
        Vt D = P -O; D.normaliza();
        Ponto pI= Ponto(O.x + t*D.x, O.y + t*D.y, O.z + t*D.z);
        Vt n = normal(pI);
        if(n.ProdEsc(D)>0.0) n = Vt(-n.x,-n.y,-n.z);
        Vect l = pF- pI; l.normaliza();
        Vect v = Vt(-D.x, -D.y, -D.z); v.normaliza();
        double nL = n.ProdEsc(l);
        Vect r = Vect(2*nL*n.x - l.x, 2*nL*n.y - l.y, 2*nL*n.z - l.z);
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

bool shadowRay(Ponto &pI, Ponto &pF, Objeto *atual, vector<Objeto *> &cena){
    Vt l = pF - pI;
    double dist = sqrt(l.ProdEsc(l));
    if(dist<=0.0) return false;
    l.normaliza();
    double eps = 1e-5;

    Ponto pL = pI.pontoInterseçao(dist, l);
    Vt n = atual->normal(pI);
    if(n.ProdEsc(l)>0.0) n = Vt(-n.x, -n.y, -n.z); 
    Ponto Desloc = pI.pontoInterseçao(eps, n);
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