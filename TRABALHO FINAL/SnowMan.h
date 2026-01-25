#ifndef SNOW_MAN_H
#define SNOW_MAN_H

#include "../CLASSES/ObjetoMulti.h"
#include "../CLASSES/OBJETOS/Esfera.h"
#include "../CLASSES/OBJETOS/Cilindro.h"
#include "../CLASSES/OBJETOS/Cone.h"
#include "../CLASSES/OBJETOS/Plano.h"
#include "../CLASSES/OBJETOS/Triangulo.h"
#include "../CLASSES/OBJETOS/Malha.h"

using namespace std;

struct SnowMan : ObjetoMulti{
    

    SnowMan(int id){
        this->id = id;
        this->componentes = vector<Objeto*>();
        Esfera *esfera1 = new Esfera(1, 1.5, Pt(12.5, 1.5, 15.0));
        esfera1->kdif = RGB(1.0, 1.0, 1.0);
        esfera1->kesp = RGB(1.0, 1.0, 1.0);
        esfera1->kamb = RGB(1.0, 1.0, 1.0);
        esfera1->m = 3;
        addComponente(*esfera1);

        Esfera *esfera2 = new Esfera(2, 1.15, Pt(12.5, 3.5, 15.0));
        esfera2->kdif = RGB(1.0, 1.0, 1.0);
        esfera2->kesp = RGB(1.0, 1.0, 1.0);
        esfera2->kamb = RGB(1.0, 1.0, 1.0);
        esfera2->m = 3;
        addComponente(*esfera2);

        Esfera *esfera3= new Esfera(3, 0.75, Pt(12.5, 5.05, 15.0));
        esfera3->kdif = RGB(1.0, 1.0, 1.0);
        esfera3->kesp = RGB(1.0, 1.0, 1.0);
        esfera3->kamb = RGB(1.0, 1.0, 1.0);
        esfera3->m = 3;
        addComponente(*esfera3);

        Esfera *esfera4= new Esfera(4, 0.145, Pt(12.15, 5.05, 14.4));
        esfera4->kdif = RGB(0.0, 0.0, 0.0);
        esfera4->kesp = RGB(0.0, 0.0, 0.0);
        esfera4->kamb = RGB(0.0, 0.0, 0.0);
        esfera4->m = 1;
        addComponente(*esfera4);

        Esfera *esfera5 = new Esfera(5, 0.145, Pt(12.85, 5.05, 14.4));
        esfera5->kdif = RGB(0.0, 0.0, 0.0);
        esfera5->kesp = RGB(0.0, 0.0, 0.0);
        esfera5->kamb = RGB(0.0, 0.0, 0.0);
        esfera5->m = 1;
        addComponente(*esfera5);

        Cilindro *cilindro1= new Cilindro(6, 1.1, 0.09, Pt(12.5, 5.5, 15.0), Vt(0,1,0));
        cilindro1->kdif = RGB(0.59, 0.29, 0.0);
        cilindro1->kesp = RGB(0.59, 0.29, 0.0);
        cilindro1->kamb = RGB(0.59, 0.29, 0.0);
        cilindro1->m = 1;
        addComponente(*cilindro1);

        Cilindro *cilindro2 = new Cilindro(7, 0.70, 1.2, Pt(12.5, 5.5, 15.0), Vt(0,1,0));
        cilindro2->kdif = RGB(0.59, 0.29, 0.0);
        cilindro2->kesp = RGB(0.59, 0.29, 0.0);
        cilindro2->kamb = RGB(0.59, 0.29, 0.0);
        cilindro2->m = 1;
        addComponente(*cilindro2);
        

        Cilindro *cilindro3 = new Cilindro(8, 0.75, 0.2, Pt(12.5, 5.6, 15.0), Vt(0,1,0));
        cilindro3->kdif = RGB(1., 0.008, 0.006);
        cilindro3->kesp = RGB(1., 0.008, 0.006);
        cilindro3->kamb = RGB(1., 0.008, 0.006);
        cilindro3->m = 1;
        addComponente(*cilindro3);

        Cone *cone1 = new Cone(9, 0.15, 0.5, Pt(12.5, 4.95, 14.2), Vt(0.1, -0.3, -1.0));
        cone1->kdif = RGB(1.0, 0.647, 0.0);
        cone1->kesp = RGB(1.0, 0.647, 0.0);
        cone1->kamb = RGB(1.0, 0.647, 0.0);
        cone1->m = 1;
        cone1->temBase = false;
        addComponente(*cone1);

        Esfera *esfera6 = new Esfera(10, .2, Pt(12.5, 1.7, 13.5));
        esfera6->kdif = RGB(0.2, 0.2, 0.2);
        esfera6->kesp = RGB(0.2, 0.2, 0.2);
        esfera6->kamb = RGB(0.2, 0.2, 0.2);
        esfera6->m = 1;
        addComponente(*esfera6);

        Esfera *esfera7 = new Esfera(11, .2, Pt(12.5, 3.7, 13.9));
        esfera7->kdif = RGB(0.2, 0.2, 0.2);
        esfera7->kesp = RGB(0.2, 0.2, 0.2);
        esfera7->kamb = RGB(0.2, 0.2, 0.2);
        esfera7->m = 1;
        addComponente(*esfera7);

        Cilindro *cilindro4 = new Cilindro(12, 0.1, 2.1, Pt(12, 3.9, 15.0), Vt(-1.0, 0.4, 0.0));
        cilindro4->kdif = RGB(0.545, 0.271, 0.075);
        cilindro4->kesp = RGB(0.545, 0.271, 0.075);
        cilindro4->kamb = RGB(0.545, 0.271, 0.075);
        cilindro4->m = 1;
        addComponente(*cilindro4);

        Cilindro *cilindro5 = new Cilindro(13, 0.1, 2.1, Pt(13, 3.9, 15.0), Vt(1.0, -0.3, 0.0));
        cilindro5->kdif = RGB(0.545, 0.271, 0.075);
        cilindro5->kesp = RGB(0.545, 0.271, 0.075);
        cilindro5->kamb = RGB(0.545, 0.271, 0.075);
        cilindro5->m = 1;
        addComponente(*cilindro5);

    }
};







#endif

