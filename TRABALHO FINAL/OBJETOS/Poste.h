#ifndef POSTE_H
#define POSTE_H

#include "../../CLASSES/UTILS/ObjetoMulti.h"
#include "../../CLASSES/OBJETOS/Esfera.h"
#include "../../CLASSES/OBJETOS/Cilindro.h"
#include "../../CLASSES/OBJETOS/Cone.h"
#include "../../CLASSES/OBJETOS/Plano.h"
#include "../../CLASSES/OBJETOS/Triangulo.h"
#include "../../CLASSES/OBJETOS/Malha.h"

using namespace std;

struct Poste : ObjetoMulti{


    Poste(int id){
        this->id = id;
        this->componentes = vector<Objeto *>();

                //POSTE DE LUZ
        Cilindro *poste = new Cilindro(13, 0.2, 12, Pt(18, 0, 17.0), Vt(0, 1, 0.0));
        poste->kdif = RGB(0.4, 0.4, 0.4);
        poste->kesp = RGB(0.4, 0.4, 0.4);
        poste->kamb = RGB(0.4, 0.4, 0.4);
        poste->m = 5;
        addComponente(*poste);
        
        //LUMINARIA DO POSTE
        Cilindro *luminaria = new Cilindro(14, 0.2, 4, Pt(18, 11.8, 17.0), Vt(-1.0, 0.0, 0.0));
        luminaria->kdif = RGB(0.4, 0.4, 0.4);
        luminaria->kesp = RGB(0.4, 0.4, 0.4);
        luminaria->kamb = RGB(0.4, 0.4, 0.4);
        luminaria->m = 5;
        addComponente(*luminaria);
        
        //LAMPADA DO POSTE
        Esfera *lampadaPoste = new Esfera(15, 0.35, Pt(14.1, 11.58, 17.0));
        lampadaPoste->kdif = RGB(1.0, 1.0, 0.8);
        lampadaPoste->kesp = RGB(1.0, 1.0, 0.8);
        lampadaPoste->kamb = RGB(1.0, 1.0, 0.8);
        lampadaPoste->m = 0.5;
        addComponente(*lampadaPoste);
        
        //BASE DO POSTE
        Cilindro *basePoste = new Cilindro(16, 0.9, 2, Pt(18, 0, 17.0), Vt(0, 1, 0.0));
        basePoste->kdif = RGB(0.4, 0.4, 0.4);
        basePoste->kesp = RGB(0.4, 0.4, 0.4);
        basePoste->kamb = RGB(0.4, 0.4, 0.4);
        basePoste->m = 5;
        addComponente(*basePoste);  
        
    }
};





#endif
