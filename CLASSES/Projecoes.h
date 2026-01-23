#ifndef PROJECOES_H
#define PROJECOES_H
#include <bits/stdc++.h>

#include "Matriz.h"
using namespace std;

class Projecoes {
public:

    static Matriz projObliqua(double angulo, double lambda){
        if (lambda>1 || lambda<=0) lambda = 1;
        Matriz proj;
        double rad = angulo * M_PI / 180.0;
        double c = cos(rad);
        double s = sin(rad); 
        proj (0,2) = lambda*c;
        proj (1,2) = lambda*s;
        proj (2,2) = 0.0;

        return proj;
    }

    static Matriz projOrtograficaFrontal(){
        Matriz proj;
        proj (2, 2) = 0.0;
        return proj;
    }

    static Matriz projOrtograficaSuperior(){
        Matriz proj;
        proj (2, 2) = 0.0;
        return proj;
    }

    static Matriz projOrtograficaFrontal(){
        Matriz proj;
        proj (1, 1) = 0.0;
        proj (1, 2) = 1.0;
        proj (2, 2) = 0.0;
        return proj;
    }

    static Matriz projOrtograficaLateral(){
        Matriz proj;
        proj (0, 0) = 0.0;
        proj (0, 1) = 1.0;
        proj (1, 1) = 0.0;
        proj (1, 2) = 1.0;
        proj (2, 2) = 0.0;
        return proj;
    }






};





#endif