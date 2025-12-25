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
    bool temBase;
    Cone(double raio, double alt, Ponto centro, Vect d){
        r = raio;
        Cbase = centro;
        hCone = alt;
        dCone = d; dCone.normaliza();
        kdif = {0, 0, 0};
        kesp = {0, 0, 0};
        kamb = {0, 0, 0};
        m = 0;
        usaText = false;
        temBase = true;
    }

    Vt normal(Ponto &pI){
        Vt aux = pI - Cbase;
        double proj = aux.ProdEsc(dCone);
        Vt vx = Vt(aux.x - proj*dCone.x, aux.y - proj*dCone.y, aux.z - proj*dCone.z);
        double k = r / hCone;
        Vt n = Vt((vx.x - k*proj*dCone.x),(vx.y - k*proj*dCone.y), (vx.z - k*proj*dCone.z));
        n.normaliza();
        return n;
    }

    bool intersecta(Ponto &O, Ponto &P) {
        Vt D = P-O; D.normaliza();
        if(temBase){
            Plano p = Plano(Cbase, dCone);
            if(p.intersecta(O, P)){
                Ponto pI = O.pontoIntersecao(p.t, D);
                Vt v = pI - Cbase;
                double dist = v.ProdEsc(v);
                if(dist<= r*r){
                    t = p.t;
                    return true;
                }
            }
        }
        Ponto cTopo = Cbase.pontoIntersecao(hCone, dCone);
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



        Ponto pI = O.pontoIntersecao(t,D);
        double h = (pI - Cbase).ProdEsc(dCone);

        if (h < 0 || h > hCone) return false;

        
        return true;
    }

    RGB pintaTextura(Ponto &O, Ponto &P, Ponto &pf,RGB &iF,RGB &iA){
        return pinta(O, P, pf, iF, iA);
    }

    void aplicaTransformacao(Matriz &T) override{
        Cbase = T * Cbase;

        Matriz R = T;
        R(0,3) = R(1,3) = R(2,3) = 0;

        dCone = R * dCone;
        dCone.normaliza();

        r *= sqrt(pow(R(0,0),2) + pow(R(0,1),2) + pow(R(0,2),2));
        hCone *= sqrt(pow(R(1,0),2) + pow(R(1,1),2) + pow(R(1,2),2));
    }

};

#endif