#ifndef ESFERA_H
#define ESFERA_H


#include <bits/stdc++.h>
#include "../../CLASSES/Janela.h"
#include "../../CLASSES/Vetores.h"
#include "../../CLASSES/Objeto.h"

using namespace std;

struct Esfera : Objeto{
    double r;
    Ponto Cesf;

    Esfera(double raio, Ponto centro){
        r = raio;
        Cesf = centro;
        kdif = {0, 0, 0};
        kesp = {0, 0, 0};
        kamb = {0, 0, 0};
        m = 0;
        usaText = false;
    }

    Vt normal(Ponto &pI){
        Vect n = pI - Cesf; 
        n.normaliza();
        return n;
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
    

    RGB pintaTextura(Ponto &O, Ponto &P, Ponto &pf,RGB &iF,RGB &iA){
     return pinta(O, P, pf, iF, iA);
    }

    void aplicaTransformacao(Matriz &T) override{
        Cesf = T * Cesf;
        
        double s = sqrt(
            T(0,0)*T(0,0) +
            T(0,1)*T(0,1) +
            T(0,2)*T(0,2)
        );

        r *= s;
    }




};

#endif