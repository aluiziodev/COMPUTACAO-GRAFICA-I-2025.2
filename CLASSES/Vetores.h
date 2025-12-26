#ifndef VETORES_H
#define VETORES_H

#include <bits/stdc++.h>

using namespace std;

typedef struct Vect{
    double x, y, z, a;

    Vect(double x=0, double y=0, double z=0){
        this->x = x;
        this->y = y;
        this->z = z;
        this->a = 0;
    }

    Vect operator-(const Vect &v) const {
        return Vect(x-v.x, y-v.y, z-v.z);
    }
    Vect operator*(const double &v)const {
        return Vect(x*v, y*v, z*v);
    }
    Vect operator+(const double &v)const {
        return Vect(x+v, y+v, z+v);
    }
    Vect operator+(const Vect &v) const {
        return Vect(x+v.x, y+v.y, z+v.z);
    }

    double ProdEsc(const Vect &v) const{
        return (x*v.x)+(y*v.y)+(z*v.z);
    }
    Vect prodVet(const Vect &v) const{
        return Vect(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }

    double norma() const{
        return sqrt((x*x) + (y*y) + (z*z));
    }

    void normaliza(){
        double n = norma();
        if(n>1e-9){
            x = x/n;
            y = y/n;
            z = z/n;
        }
    }

} Vt;





typedef struct Ponto{
    double x, y, z, a;

    Ponto(double x=0, double y=0, double z=0){
        this->x = x;
        this->y = y;
        this->z = z;
        this->a = 1;
    }

    Ponto pontoIntersecao(const double &t, Vect &dr) const {
        return Ponto(x + t*dr.x, y + t*dr.y,z + t*dr.z);
    }
    
    Vect operator-(const Ponto &v) const{
        return Vect(x-v.x, y-v.y, z-v.z);
    }
    Ponto operator+(const Vect &v) const{
        return Ponto(x+v.x, y+v.y, z+v.z);
    }

} Pt;

#endif

