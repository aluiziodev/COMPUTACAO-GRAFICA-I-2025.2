#ifndef ARVORE_H
#define ARVORE_H

#include "../CLASSES/ObjetoMulti.h"
#include "../CLASSES/OBJETOS/Esfera.h"
#include "../CLASSES/OBJETOS/Cilindro.h"
#include "../CLASSES/OBJETOS/Cone.h"
#include "../CLASSES/OBJETOS/Plano.h"
#include "../CLASSES/OBJETOS/Triangulo.h"
#include "../CLASSES/OBJETOS/Malha.h"

using namespace std;

struct Arvore : ObjetoMulti{


    Arvore(int id){
        this->id = id;
        this->componentes = vector<Objeto *>();
        //CILINDRO TRONCO ARVORE
        Cilindro *tronco = new Cilindro(17, 0.3, 4, Pt(14, 0.01, 23.0), Vt(0, 1, 0.0));
        tronco->kdif = RGB(0.545, 0.271, 0.075);
        tronco->kesp = RGB(0.545, 0.271, 0.075);
        tronco->kamb = RGB(0.545, 0.271, 0.075);
        tronco->m = 5;
        addComponente(*tronco);
        //ESFERA FOLHAS ARVORE INF
        Esfera *folhasInf = new Esfera(18, 5, Pt(14, 8.5, 23.0));
        folhasInf->kdif = RGB(0.0, 0.5, 0.0);
        folhasInf->kesp = RGB(0.0, 0.5, 0.0);
        folhasInf->kamb = RGB(0.0, 0.5, 0.0);
        folhasInf->m = 5;
        addComponente(*folhasInf);
        //ESFERA FOLHAS ARVORE SUP
        Esfera *folhasSup = new Esfera(19, 4, Pt(13.8, 13.5, 23.0));
        folhasSup->kdif = RGB(0.0, 0.5, 0.0);
        folhasSup->kesp = RGB(0.0, 0.5, 0.0);
        folhasSup->kamb = RGB(0.0, 0.5, 0.0);
        folhasSup->m = 10;
        addComponente(*folhasSup);

    }

};




#endif