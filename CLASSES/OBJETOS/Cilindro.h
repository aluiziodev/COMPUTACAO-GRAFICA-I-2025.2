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

        Ponto pI = Pt(O.x + D.x*t, O.y + D.y*t,O.z + D.z*t);
        double h = (pI - Cbase).ProdEsc(dCil);
        if(h<0 || h>hCil) return false;


        return true;

    }

    RGB pinta(Ponto &O, Ponto &P,Ponto &pF, RGB &iF, RGB &iA){
        Vt D = P -O; D.normaliza();
        Ponto pI= Ponto(O.x + t*D.x,O.y + t*D.y, O.z + t*D.z);

        Vt aux = pI - Cbase;
        Vt n = Vt(aux.x - (aux.ProdEsc(dCil)*dCil.x), 
                  aux.y - (aux.ProdEsc(dCil)*dCil.y), 
                  aux.z - (aux.ProdEsc(dCil)*dCil.z));
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