#ifndef QUATERNIOS_H
#define QUATERNIOS_H

#include "Vetores.h"
#include "Matriz.h"

typedef struct Quaternio{
    float w;
    Vect v;

    Quaternio(float w = 1, Vect v = Vt(0, 0, 0)){
        this->w = w;
        this->v = v;
    }

    float norma(){
        return sqrt(w * w + pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
    }

    Quaternio normaliza(){
        float norm = norma();
        if(norm>1e-6){
            return Quaternio(w/norm, v/norm);
        }
        return Quaternio(1.0, Vect(0, 0, 0));
    }

    Matriz matrizRotacao(){
        Matriz m = Matriz();

        m(0,0) = 1-2*(v.y*v.y + v.z*v.z);
        m(0,1) = 2*(v.x*v.y - w*v.z);
        m(0,2) = 2*(v.x*v.z + w*v.y);
        m(1,0) = 2*(v.x*v.y + w*v.z);
        m(1,1) = 1-2*(v.x*v.x + v.z*v.z);
        m(1,2) = 2*(v.y*v.z - w*v.x);
        m(2,0) = 2*(v.x*v.z - w*v.y);
        m(2,1) = 2*(v.y*v.z + w*v.x);
        m(2,2) = 1-2*(v.x*v.x + v.y*v.y);

        return m;




    }

}Qt;



#endif