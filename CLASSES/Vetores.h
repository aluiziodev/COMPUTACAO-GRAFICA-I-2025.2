#ifndef VETORES_H
#define VETORES_H

#include <bits/stdc++.h>

using namespace std;

typedef struct Vect{
    double x, y, z;

    Vect(double x=0, double y=0, double z=0){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vect operator-(Vect &v){
        return Vect(x-v.x, y-v.y, z-v.z);
    }

    Vect operator*(const double &v){
        return Vect(x*v, y*v, z*v);

    }

    Vect operator+(double &v){
        return Vect(x+v, y+v, z+v);

    }

    double ProdEsc(Vect &v){
        return (x*v.x)+(y*v.y)+(z*v.z);
    }

    void normaliza(){
        double norma = sqrt((x*x) + (y*y) + (z*z));
        x = x/norma;
        y = y/norma;
        z = z/norma;
    }

} Vt;







typedef struct Ponto{
    double x, y, z;

    Ponto(double x=0, double y=0, double z=0){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vect operator-(Ponto &v){
        return Vect(x-v.x, y-v.y, z-v.z);
    }

    Vect operator+(Ponto &v){
        return Vect(x+v.x, y+v.y, z+v.z);
    }

} Pt;

#endif

