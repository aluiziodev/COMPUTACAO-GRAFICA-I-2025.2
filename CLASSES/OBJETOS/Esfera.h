#ifndef ESFERA_H
#define ESFERA_H


#include <bits/stdc++.h>
#include "../../CLASSES/Janela.h"
#include "../../CLASSES/Vetores.h"
#include "../../CLASSES/Objeto.h"

using namespace std;

struct Esfera : public Objeto{
    double r;
    Ponto Cesf;

    Esfera(double raio, Ponto centro){
        r = raio;
        Cesf = centro;
        kdif = {0, 0, 0};
        kesp = {0, 0, 0};
        kamb = {0, 0, 0};
        m = 0;
    }

    bool intersecta(Ponto &O, Ponto &P){
        Vt D = P - O; D.normaliza();
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
    RGB pinta(Ponto &O, Ponto &P,Ponto &pF, RGB &iF, RGB &iA){
        Vt D = P - O; D.normaliza();
        Ponto pI= Ponto(O.x + t*D.x,O.y + t*D.y, O.z + t*D.z);

        Vect n = pI - Cesf; 
        n.normaliza();

        Vect l = pF - pI; l.normaliza();
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

#endif