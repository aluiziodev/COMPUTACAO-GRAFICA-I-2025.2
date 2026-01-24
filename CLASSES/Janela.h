#ifndef JANELA_H
#define JANELA_H

#include <bits/stdc++.h>


using namespace std;

typedef struct RGB { 
    double r, g, b;

    
    RGB(double r=0, double g=0, double b=0){
        this->r = r;
        this->g = g;
        this->b = b;
    }

    RGB operator+=(const RGB &c){
        this->r += c.r;
        this->g += c.g;
        this->b += c.b;
        return *this;
    }

    void clamp(){
        this->r = min(1.0, max(0.0, r));
        this->g = min(1.0, max(0.0, g));
        this->b = min(1.0, max(0.0, b));
    }

    void padronizaRGB(){
        this->r = 255.0*r;
        this->g = 255.0*g;
        this->b = 255.0*b;
    }

    void normalizaRGB(){
        this->r = r/255.0;
        this->g = g/255.0;
        this->b = b/255.0;
    }

    RGB arroba(RGB &c){
        return RGB(r*c.r, g*c.g, b*c.b);
    }

} RGB;


#endif