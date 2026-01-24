#ifndef CANVAS_H
#define CANVAS_H

#include <bits/stdc++.h>
#include "Janela.h"
#include "Objeto.h"
#include "Camera.h"
#include "Luz.h"

using namespace std; 




typedef struct Canvas{
    int w, h;
    double wJan, hJan;
    Camera *cam;
    RGB iA;
    vector<RGB> janela;
    vector<Objeto> cena;
    vector<Luz> luzes;

    Canvas(int w, int h, double wJanela, double hJanela,Camera *cam, RGB iA){
        this->w = w;
        this->h = h;
        this->janela = vector<RGB> (w*h, RGB(0.0, 0.0, 0.0));
        this->wJan = wJanela;
        this->hJan = hJanela;
        this->cam = cam;
        this->iA = iA;
    }

    void GeraImg(const string& filename) {

        ofstream out(filename);
        out << "P3\n" << w << " " << h << "\n255\n";
        for (int i = 0; i < w*h; i++) {
            double r = janela[i].r;
            double g = janela[i].g;
            double b = janela[i].b;

            r = min(1.0, max(0.0, r));
            g = min(1.0, max(0.0, g));
            b = min(1.0, max(0.0, b));

            int R = int(r * 255.0);
            int G = int(g * 255.0);
            int B = int(b * 255.0);

            out << R << " " << G << " " << B << "\n";
        }
        out.close();
    }
} Canvas;


#endif

