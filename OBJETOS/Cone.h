#ifndef CONE_H
#define CONE_H


#include <bits/stdc++.h>


#include "EstruturasGeo.h"
#include "Janela.h"
#include "Plano.h"

using namespace std;


typedef struct Cone{
    double r;
    double hCone;
    Ponto Cbase;
    Vt dCone;
    RGB kdif;
    RGB kesp;
    RGB kamb;
    int m;

    Cone(double raio, double alt, Ponto centro, Vect d){
        r = raio;
        Cbase = centro;
        hCone = alt;
        dCone = d; dCone.normaliza();
        kdif = {0, 0, 0};
        kesp = {0, 0, 0};
        kamb = {0, 0, 0};
        m = 0;
    }

    bool IntersectaCone(Ponto &O, Vt &D, double &t) {
        
        double k = r / hCone;
        k = k * k;
        
        Vt co = O - Cbase;
        double dv = D.ProdEsc(dCone);
        double cov = co.ProdEsc(dCone);

        double a = D.ProdEsc(D) - (1 + k) * dv * dv;
        double b = 2 * (co.ProdEsc(D) - (1 + k) * dv * cov);
        double c = co.ProdEsc(co) - (1 + k) * cov * cov;

        double delta = b*b - 4*a*c;
        if (delta < 0) return false;

        double t1 = (-b - sqrt(delta)) / (2*a);
        double t2 = (-b + sqrt(delta)) / (2*a);

        
        if (t1 <= 1e-6 && t2 <= 1e-6) return false;
        else if (t1 > 1e-6 && t2 <= 1e-6) t = t1;
        else if (t1 <= 1e-6 && t2 > 1e-6) t = t2;
        else t = min(t1, t2);

        Ponto P = Ponto(O.x + t*D.x, O.y + t*D.y, O.z + t*D.z);
        double h = (P - Cbase).ProdEsc(dCone);

        if (h < 0 || h > hCone) return false;

        
        return true;
    }

    bool intersectaBaseCone(Ponto &O, Vt &D, double &t){
        Plano p = Plano(Cbase, dCone);
        if(p.IntersectaPlano(O, D, t)){
            Ponto pI= Ponto(O.x + t*D.x,O.y + t*D.y, O.z + t*D.z);
            Vt v = pI - Cbase;
            double dist = v.ProdEsc(v);
            if(dist<= r*r){
                return true;
            }
        }
        return false;
    }

    bool coneBloqueia(Ponto &PI, Ponto &PF){
        Vt l = PF - PI;
        double dist = sqrt(l.ProdEsc(l));
        Vt D = {l.x / dist, l.y /dist, l.z / dist};
        
        double t_s;
        Ponto O = {PI.x + D.x*(1e-4), PI.y + D.y*(1e-4), PI.z + D.z*(1e-4)};
        if(IntersectaCone(O, D, t_s)){
            if(t_s > 0 && t_s < dist - 1e-6) return true;
        }
        return false;
    }




}cn;


#endif