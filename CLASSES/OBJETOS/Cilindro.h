#ifndef CILINDRO_H
#define CILINDRO_H

#include <bits/stdc++.h>
#include "../../CLASSES/Janela.h"
#include "../../CLASSES/Vetores.h"
#include "../../CLASSES/Objeto.h"


using namespace std;


struct Cilindro : Objeto{
    double r;
    double hCil;
    Ponto Cbase;
    Vt dCil;

    Cilindro(double raio, double alt, Ponto centro, Vt d){
        r = raio;
        Cbase = centro;
        hCil = alt;
        dCil = d; dCil.normaliza();
        kdif = {0, 0, 0};
        kesp = {0, 0, 0};
        kamb = {0, 0, 0};
        m = 0;
        usaText = false;
    }

    Vt normal(Ponto &pI){
        Vt aux = pI - Cbase;
        Vt n = Vt(aux.x - (aux.ProdEsc(dCil)*dCil.x), 
                  aux.y - (aux.ProdEsc(dCil)*dCil.y), 
                  aux.z - (aux.ProdEsc(dCil)*dCil.z));
        n.normaliza();
        return n;
    }

    bool intersecta(Ponto &O, Ponto &P){
        Vt D = P -O; D.normaliza();
        Vt d = O - Cbase;
        Vt dr = Vt(D.x - (D.ProdEsc(dCil)*dCil.x), D.y - (dCil.y*D.ProdEsc(dCil)), D.z - (dCil.z*D.ProdEsc(dCil)));
        Vt w = Vt(d.x - (dCil.x*d.ProdEsc(dCil)), d.y - (dCil.y*d.ProdEsc(dCil)), d.z - (dCil.z*d.ProdEsc(dCil)));

        double a = dr.ProdEsc(dr);
        double b = 2*w.ProdEsc(dr);
        double c = w.ProdEsc(w) - r*r;

        double dlt = b*b - (4*a*c);
        if(dlt<0) return false;

        double t1 = (-b - sqrt(dlt))/(2*a);
        double t2 = (-b + sqrt(dlt))/(2*a);

        
        if(t1<= 1e-6 && t2<=1e-6) return false;
        else if(t1>1e-6 && t2<=1e-6) t = t1;
        else if(t1<=1e-6 && t2>1e-6) t = t2;
        else t = min(t1, t2);

        Ponto pI= O.pontoInterseçao(t, D);
        double h = (pI - Cbase).ProdEsc(dCil);
        if(h<0 || h>hCil) return false;


        return true;

    }

   

    RGB pintaTextura(Ponto &O, Ponto &P, Ponto &pf,RGB &iF,RGB &iA){
        return pinta(O, P, pf, iF, iA);
    }


};


#endif