#ifndef JANELA_H
#define JANELA_H

#include <bits/stdc++.h>


typedef struct RGB { 
    double r, g, b;

    RGB(double r=0, double g=0, double b=0){
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void padronizaRGB(){
        this->r = 255*r;
        this->g = 255*g;
        this->b = 255*b;
    }

    void normalizaRGB(){
        this->r = r/255;
        this->g = g/255;
        this->b = b/255;
    }

    RGB arroba(RGB &c){
        return RGB(r*c.r, g*c.g, b*c.b);
    }

} RGB;

typedef struct Canvas{
    int w, h;
    vector<RGB> janela;

    Canvas(int w, int h){
        this->w = w;
        this->h = h;
        this->janela = vector<RGB> (w*h, {100, 100, 100});
    }

    void GeraImg(const string& filename) {
        ofstream out(filename);
        out << "P3\n" << w << " " << h << "\n255\n";
        for (int i = 0; i < w*h; i++) {
            out << janela[i].r << " " << janela[i].g << " " << janela[i].b << "\n";
        }
        out.close();
    }
} Canvas;


#endif

