#ifndef JANELA_H
#define JANELA_H

#include <iostream>
#include <vector>
#include <cmath>
#include <filesystem>


using namespace std;

typedef struct RGB { 
    float r, g, b;

    
    RGB(double r=0, double g=0, double b=0){
        this->r = float(r);
        this->g = float(g);
        this->b = float(b);
    }

    RGB operator+=(const RGB &c){
        this->r += c.r;
        this->g += c.g;
        this->b += c.b;
        return *this;
    }

    void clamp(){
        this->r = min(float(1), max(float(0), r));
        this->g = min(float(1), max(float(0), g));
        this->b = min(float(1), max(float(0), b));
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