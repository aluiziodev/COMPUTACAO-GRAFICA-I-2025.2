#ifndef ESFERA_H
#define ESFERA_H


#include <bits/stdc++.h>
#include "EstruturasGeo.h"
#include "Janela.h"


using namespace std;

typedef struct Esfera{
    double r;
    Ponto Cesf;
    RGB kdif;
    RGB kesp;
    RGB kamb;
    int m;
    Esfera(double raio, Ponto centro){
        r = raio;
        Cesf = centro;
        kdif = {0, 0, 0};
        kesp = {0, 0, 0};
        kamb = {0, 0, 0};
        m = 0;
    }

    bool IntersectaEsfera(Ponto &O, Vt &D, double &t){
        Vt OrCe = O - Cesf;
        double a = D.ProdEsc(D);
        double b = 2 * OrCe.ProdEsc(D);
        double c = OrCe.ProdEsc(OrCe) - (r*r);
        double Dlt = (b*b) - (4*a*c);
        if(Dlt<0) return false;
        
        double x1 = (-b + sqrt(Dlt))/ (2*a);
        double x2 = (-b - sqrt(Dlt))/ (2*a);

        
        if(x1 > 0 && x2 > 0){
            if(x1>x2) t = x2;
            else t = x1;
        }
        else if(x1 > 0) t = x1;
        else if(x2 > 0) t = x2;

        else return false;

        
        return true;
    }
    bool esferaBloqueia(Ponto &PI, Ponto &PF){
        Vt l = PF - PI;
        double dist = sqrt(l.ProdEsc(l));
        Vt D = {l.x / dist, l.y /dist, l.z/dist}; 
        double t_s;
        Ponto O = {PI.x + D.x*(1e-4), PI.y + D.y*(1e-4), PI.z + D.z*(1e-4)};
        if(IntersectaEsfera(O, D, t_s)){
            if(t_s > 0 && t_s < dist - 1e-6) return true;
        }
        return false;
    }



}Esf;

#endif