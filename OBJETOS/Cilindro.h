#ifndef CILINDRO_H
#define CILINDRO_H

#include <bits/stdc++.h>

#include "EstruturasGeo.h"
#include "Janela.h"

using namespace std;


typedef struct Cilindro{
    double r;
    double hCil;
    Ponto Cbase;
    Vt dCil;
    RGB kdif;
    RGB kesp;
    RGB kamb;
    int m;

    Cilindro(double raio, double alt, Ponto centro, Vt d){
        r = raio;
        Cbase = centro;
        hCil = alt;
        dCil = d; dCil.normaliza();
        kdif = {0, 0, 0};
        kesp = {0, 0, 0};
        kamb = {0, 0, 0};
        m = 0;
    }

    bool IntersectaCilindro(Ponto &O, Vt &D, double &t){
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

        Ponto P = Ponto(O.x + (D.x*t),O.y + (D.y*t), O.z + (D.z*t));
        double h = (P - Cbase).ProdEsc(dCil);
        if(h<0 || h>hCil) return false;


        return true;

    }

    bool cilindroBloqueia(Ponto &PI, Ponto &PF){
        Vt l = PF - PI;
        double dist = sqrt(l.ProdEsc(l));
        Vt D = {l.x / dist, l.y /dist, l.z/dist}; 
        
        double t_s;
        Ponto O = {PI.x + D.x*(1e-4), PI.y + D.y*(1e-4), PI.z + D.z*(1e-4)};
        if(IntersectaCilindro(O, D, t_s)){
            if(t_s > 0 && t_s < dist - 1e-6) return true;
        }
        return false;
    }



}Cil;


#endif