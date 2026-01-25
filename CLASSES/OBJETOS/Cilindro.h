#ifndef CILINDRO_H
#define CILINDRO_H

#include <bits/stdc++.h>
#include "../../CLASSES/Janela.h"
#include "../../CLASSES/Vetores.h"
#include "../../CLASSES/Objeto.h"
#include "Plano.h"


using namespace std;


struct Cilindro : Objeto{
    double r;
    double hCil;
    Ponto Cbase;
    Vt dCil;
    bool temBase;
    bool temTampa;

    Cilindro(int id, double raio, double alt, Ponto centro, Vt d){
        this->id = id;
        r = raio;
        Cbase = centro;
        hCil = alt;
        dCil = d; dCil.normaliza();
        kdif = {0, 0, 0};
        kesp = {0, 0, 0};
        kamb = {0, 0, 0};
        m = 0;
        usaText = false;
        temBase = true;
        temTampa = true;
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
        Vt D = P-O; D.normaliza();
        double tBase = 1e9;
        bool hitBase = false;
        if(temBase){
            Plano p = Plano(Cbase, dCil);
            if(p.intersecta(O, P)){
                Ponto pI = O.pontoIntersecao(p.t, D);
                Vt v = pI - Cbase;
                double dist = v.ProdEsc(v);
                if(dist<= r*r){
                    tBase = p.t;
                    hitBase = true;
                }
            }
        }
        double tTampa = 1e9;
        bool hitTampa = false;
        if(temTampa){
            Ponto cTampa = Cbase+(dCil*hCil);
            Plano p2 = Plano(cTampa, dCil);
            if(p2.intersecta(O, P)){
                Ponto pI = O.pontoIntersecao(p2.t, D);
                Vt v = pI - cTampa;
                double dist = v.ProdEsc(v);
                if(dist<= r*r){
                    tTampa = p2.t;
                    hitTampa = true;
                    
                }
            }
        }
        double tCasca = 1e9;
        bool hitCasca = true;
        Vt d = O - Cbase;
        Vt dr = Vt(D.x - (D.ProdEsc(dCil)*dCil.x), D.y - (dCil.y*D.ProdEsc(dCil)), D.z - (dCil.z*D.ProdEsc(dCil)));
        Vt w = Vt(d.x - (dCil.x*d.ProdEsc(dCil)), d.y - (dCil.y*d.ProdEsc(dCil)), d.z - (dCil.z*d.ProdEsc(dCil)));

        double a = dr.ProdEsc(dr);
        double b = 2*w.ProdEsc(dr);
        double c = w.ProdEsc(w) - r*r;

        double dlt = b*b - (4*a*c);
        if(dlt<0) hitCasca = false;

        double t1 = (-b - sqrt(dlt))/(2*a);
        double t2 = (-b + sqrt(dlt))/(2*a);

        
        if(t1<= 1e-6 && t2<=1e-6) hitCasca = false;
        else if(t1>1e-6 && t2<=1e-6) tCasca = t1;
        else if(t1<=1e-6 && t2>1e-6) tCasca = t2;
        else tCasca = min(t1, t2);

        Ponto pI= O.pontoIntersecao(tCasca, D);
        double h = (pI - Cbase).ProdEsc(dCil);
        if(h<0 || h>hCil) hitCasca = false;

        if(hitBase || hitCasca || hitTampa){ 
            t = min(tCasca, min(tBase, tTampa));
            return true;
        }

        return false;

    }

    RGB pintaTextura(const Luz &L, Ponto &O, Ponto &P){
        return pinta(L, O, P);
    }

    void aplicaTransformacao(Matriz &T) override{
        Cbase = T * Cbase;
        dCil = T * dCil;
        dCil.normaliza();
        double s = sqrt(
            T(0,0)*T(0,0) + 
            T(1,0)*T(1,0) +
            T(2,0)*T(2,0)
        );

        r    *= s;
        hCil *= s;
    }


};


#endif