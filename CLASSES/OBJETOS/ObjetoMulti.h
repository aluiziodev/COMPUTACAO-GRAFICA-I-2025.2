#ifndef OBJETOMULTI_H
#define OBJETOMULTI_H

#include <bits/stdc++.h>
#include "../../CLASSES/Janela.h"
#include "../../CLASSES/Vetores.h"
#include "../../CLASSES/Objeto.h"
#include "Triangulo.h"

struct ObjetoMulti : Objeto
{
    vector<Objeto> obj;
    Vt N;

    ObjetoMulti(vector<Objeto> obj){
        this->obj = obj;
        kdif = {0, 0, 0};
        kesp = {0, 0, 0};
        kamb = {0, 0, 0};
        m = 0;
        usaText = false;
    }

    Vt normal(Ponto &/*pI*/){
        return N;
    }

    bool intersecta(Ponto &O, Ponto &P){
        double tmin = -1.0;
        for(auto &comp : obj){
            if(comp.intersecta(O, P) && (tmin<0 || tmin>comp.t)){
                tmin = comp.t;
                N = comp.normal(P);
            }
        }
        if(tmin<0) return false;
        else{
            t = tmin;
            return true;
        }
    }

    RGB pintaTextura(const Luz &L, Ponto &O, Ponto &P){
        return pinta(L, O, P);
    }
    
    void aplicaTransformacao(Matriz &T) override{
        for(auto &comp : obj){
            comp.aplicaTransformacao(T);
        }
    }

};





#endif