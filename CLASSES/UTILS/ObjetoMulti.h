
#ifndef OBJETO_MULTI_H
#define OBJETO_MULTI_H  

#include <iostream>
#include <vector>
#include <cmath>


#include "Objeto.h"
#include "Vetores.h"

struct ObjetoMulti {
    string nome;
    vector<Objeto *> componentes;

    virtual ~ObjetoMulti() {}

    void addComponente(Objeto &obj){
        componentes.push_back(&obj);
    }

    void aplicaTransformacao(Matriz &M){
        for (auto *obj : componentes){
            obj->aplicaTransformacao(M);
        }
    }

    void adicionaCena(vector<Objeto *> &cena){
        for (auto *obj: componentes){
            cena.push_back(obj);
        }
    }
};



#endif