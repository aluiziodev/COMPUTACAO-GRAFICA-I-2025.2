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
    Camera *cam;
    RGB iA;
    vector<RGB> janela;
    vector<int> pickBuffer;
    vector<Objeto*> cena;
    vector<Luz*> luzes;

    Canvas(int w, int h,Camera *cam, RGB iA){
        this->w = w;
        this->h = h;
        this->janela = vector<RGB> (w*h, RGB(0.0, 0.0, 0.0));
        this->cam = cam;
        this->pickBuffer = vector<int>(w*h, -1);
        this->iA = iA;
    }

    void adicionarLuz(Luz *luz){
        luzes.push_back(luz);
    }

    void adicionarObjeto(Objeto *obj){
        cena.push_back(obj);
    }

    void GeraImg(const string& filename) {

        for(int g = 0; g<h; g++){
            for(int c = 0; c<w; c++){
                Objeto* hit = nullptr;

                double x = cam->xmin + (cam->xmax - cam->xmin) * (c + 0.5) / w;
                double y = cam->ymax - (cam->ymax - cam->ymin) * (g + 0.5) / h;

                Ponto P = cam->posicao +
                        cam->U * x +
                        cam->V * y +
                        cam->W * cam->d;

                double tmin = -1.0;

                RGB corFinal(0,0,0);

                for(Objeto *obj : cena){
                    if(obj->intersecta(cam->posicao, P)){
                        if(obj->t>0 && (tmin<0 || obj->t<tmin)){
                            tmin = obj->t;
                            hit = obj;
                            
                            Vt D = P - cam->posicao; D.normaliza();

                            Ponto pI= cam->posicao.pontoIntersecao(obj->t, D);
                            // cone.temBase = true;
                            RGB cor(0,0,0);

                            cor = obj->kamb.arroba(iA);
                            for(const Luz* L : luzes){
                                if(shadowRay(pI, *L, obj, cena)){
                                    continue;
                                }
                                else if(obj->usaText){
                                    cor += obj->pintaTextura(*L, cam->posicao, P);
                                }
                                else{
                                    cor += obj->pinta(*L, cam->posicao, P);
                                }
                            }
                            // cone.temBase = false;
                            corFinal = cor;
                            
                        }
                    }
                }

                if(hit){
                    pickBuffer[g*w + c] = hit->id;
                }

                corFinal.clamp();
                janela[g*w+c] = corFinal;
                    
            }

        }
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


    int pick(int mouseX, int mouseY){
        return pickBuffer[mouseY*w + mouseX];
    }
    
} Canvas;


#endif

