#ifndef MALHA_H
#define MALHA_H

#include <bits/stdc++.h>
#include "../../CLASSES/Janela.h"
#include "../../CLASSES/Vetores.h"
#include "../../CLASSES/Objeto.h"
#include "Triangulo.h"


struct Malha : Objeto{
    vector<Ponto> vertices;
    vector<Triangulo> faces;
    Vt N;

    Malha(vector<Ponto> v, vector<Triangulo> f){
        vertices = v;
        faces = f;
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
        for(auto &tri : faces){
            if(tri.intersecta(O, P) && (tmin<0 || tmin>tri.t)){
                tmin = tri.t;
                N = tri.normal(P);
            }
        }
        if(tmin<0) return false;
        else{
            t = tmin;
            return true;
        }
    }

    RGB pintaTextura(Luz &L, Ponto &O, Ponto &P){
        return pinta(L, O, P);
    }
    
    void aplicaTransformacao(Matriz &T) override{
        for(auto &v : vertices){
            v = T * v;
        }
        for(auto &tri : faces){
            tri.aplicaTransformacao(T);
        }
    }
    
};
#endif