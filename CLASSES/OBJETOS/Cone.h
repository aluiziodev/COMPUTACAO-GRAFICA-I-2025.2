#ifndef CONE_H
#define CONE_H

#include <bits/stdc++.h>
#include "../../CLASSES/Janela.h"
#include "../../CLASSES/Vetores.h"
#include "../../CLASSES/Objeto.h"
#include "Plano.h"

using namespace std;


struct Cone : Objeto{
    double r;
    double hCone;
    Ponto Cbase;
    Vt dCone;

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

    bool intersecta(Ponto &O, Ponto &P) {
        Vt D = P-O; D.normaliza();
        Plano p = Plano(Cbase, dCone);
        if(p.intersecta(O, P)){
            Ponto pI= Ponto(O.x +p.t*D.x,O.y + p.t*D.y, O.z + p.t*D.z);
            Vt v = pI - Cbase;
            double dist = v.ProdEsc(v);
            if(dist<= r*r){
                t = p.t;
                return true;
            }
        }
        Ponto cTopo = Pt(Cbase.x + hCone*dCone.x,Cbase.y + hCone*dCone.y,Cbase.z + hCone*dCone.z);
        Vt co = O - cTopo;
        double k = r/hCone;
        double dv = D.ProdEsc(dCone);
        double cov = co.ProdEsc(dCone);
        Vt dPerp = Vt(D.x - dCone.x*dv,D.y - dCone.y*dv,D.z - dCone.z*dv);
        Vt coPerp = Vt(co.x - dCone.x*cov,co.y - dCone.y*cov,co.z - dCone.z*cov);

        double a = dPerp.ProdEsc(dPerp) - (k*k) * (dv*dv);
        double b = 2 *(dPerp.ProdEsc(coPerp) - (k*k) * dv * cov);
        double c = coPerp.ProdEsc(coPerp) - (k*k) * (cov*cov);

        double delta = b*b - 4*a*c;
        if (delta < 0 || fabs(a) < 1e-6) return false;

        double t1 = (-b - sqrt(delta)) / (2*a);
        double t2 = (-b + sqrt(delta)) / (2*a);

        
        if (t1 <= 1e-6 && t2 <= 1e-6) return false;
        else if (t1 > 1e-6 && t2 <= 1e-6) t = t1;
        else if (t1 <= 1e-6 && t2 > 1e-6) t = t2;
        else t = min(t1, t2);



        Ponto pI = Pt(O.x + D.x*t, O.y + D.y*t,O.z + D.z*t);
        double h = (pI - Cbase).ProdEsc(dCone);

        if (h < 0 || h > hCone) return false;

        
        return true;
    }
    RGB pinta(Ponto &O, Ponto &P,Ponto &pF, RGB &iF, RGB &iA){
        Vt D = P -O; D.normaliza();
        Ponto pI= Ponto(O.x + t*D.x, O.y + t*D.y, O.z + t*D.z);
                
        Vt aux = pI - Cbase;
        double proj = aux.ProdEsc(dCone);
        Vt vx = Vt(aux.x - proj*dCone.x, aux.y - proj*dCone.y, aux.z - proj*dCone.z);
        double k = r / hCone;
        Vt n = Vt((vx.x - k*proj*dCone.x),(vx.y - k*proj*dCone.y), (vx.z - k*proj*dCone.z));
        
        n.normaliza();
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

#endif