#ifndef BANCO_H
#define BANCO_H

#include "../../CLASSES/UTILS/Transformacoes.h"
#include "../../CLASSES/UTILS/ObjetoMulti.h"

#include "../../CLASSES/OBJETOS/Esfera.h"
#include "../../CLASSES/OBJETOS/Cilindro.h"
#include "../../CLASSES/OBJETOS/Cone.h"
#include "../../CLASSES/OBJETOS/Plano.h"
#include "../../CLASSES/OBJETOS/Triangulo.h"
#include "../../CLASSES/OBJETOS/Malha.h"



using namespace std;


struct Banco : ObjetoMulti{


    Banco(int id){
        this->id = id;
        this->componentes = vector<Objeto *>();
        //MALHA PARALELEPIPEDO
        double aresta = 2;
        double h = 0.3/2.0;
        Ponto cbase = Pt(14 , 0.05 , 20);
        Ponto v0(cbase.x - h, cbase.y, cbase.z - h);
        Ponto v1(cbase.x + h, cbase.y, cbase.z - h);
        Ponto v2(cbase.x - h, cbase.y, cbase.z + h);
        Ponto v3(cbase.x + h, cbase.y, cbase.z + h);
        Ponto v4(cbase.x - h, cbase.y + aresta, cbase.z - h);
        Ponto v5(cbase.x + h, cbase.y + aresta, cbase.z - h);
        Ponto v6(cbase.x - h, cbase.y + aresta, cbase.z + h);
        Ponto v7(cbase.x + h, cbase.y + aresta, cbase.z + h);
        vector<Ponto> vertices = {v0, v1, v2, v3, v4,v5, v6, v7};

        Triangulo f0(vertices[0], vertices[2], vertices[1]);
        Triangulo f1(vertices[1], vertices[2], vertices[3]);
        Triangulo f2(vertices[4], vertices[5], vertices[6]);
        Triangulo f3(vertices[5], vertices[7], vertices[6]);
        Triangulo f4(vertices[0], vertices[4], vertices[1]);
        Triangulo f5(vertices[1], vertices[4], vertices[5]);
        Triangulo f6(vertices[2], vertices[3], vertices[6]);
        Triangulo f7(vertices[3], vertices[7], vertices[6]);
        Triangulo f8(vertices[0], vertices[2], vertices[4]);
        Triangulo f9(vertices[2], vertices[6], vertices[4]);
        Triangulo f10(vertices[1], vertices[5], vertices[3]);
        Triangulo f11(vertices[3], vertices[5], vertices[7]);
        
        vector<Triangulo> faces = { f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11};

        //PES DO BANCO
        Malha *peBanco1 = new Malha(20, vertices, faces);
        peBanco1->kdif = RGB(0.545, 0.271, 0.075);
        peBanco1->kesp = RGB(0.545, 0.271, 0.075);
        peBanco1->kamb = RGB(0.545, 0.271, 0.075);
        peBanco1->m = 1;
        addComponente(*peBanco1);
        

        Malha *peBanco2 = new Malha(21, vertices, faces);
        peBanco2->kdif = RGB(0.545, 0.271, 0.075);
        peBanco2->kesp = RGB(0.545, 0.271, 0.075);
        peBanco2->kamb = RGB(0.545, 0.271, 0.075);
        peBanco2->m = 1;
        Matriz transBanco2 = Transformacoes::transladar(0, 0, 6);
        peBanco2->aplicaTransformacao(transBanco2);
        addComponente(*peBanco2);
        

        Malha *peBanco3 = new Malha(22, vertices, faces);
        peBanco3->kdif = RGB(0.545, 0.271, 0.075);
        peBanco3->kesp = RGB(0.545, 0.271, 0.075);
        peBanco3->kamb = RGB(0.545, 0.271, 0.075);
        peBanco3->m = 1;
        Matriz transBanco3 = Transformacoes::transladar(-2.5, 0, 0);
        peBanco3->aplicaTransformacao(transBanco3);
        addComponente(*peBanco3);
        

        Malha *peBanco4 = new Malha(23, vertices, faces);
        peBanco4->kdif = RGB(0.545, 0.271, 0.075);
        peBanco4->kesp = RGB(0.545, 0.271, 0.075);
        peBanco4->kamb = RGB(0.545, 0.271, 0.075);
        peBanco4->m = 1;
        Matriz transBanco4 = Transformacoes::transladar(-2.5, 0, 6);
        peBanco4->aplicaTransformacao(transBanco4);
        addComponente(*peBanco4);
       

        //Assento do banco
        double aresta2 = 0.2;
        double h2 = 6.4/2.0;
        Ponto cbase2 = Pt(14.1 , 1.9 , 23.05);
        Ponto v8(cbase2.x - h2, cbase2.y, cbase2.z - h2);
        Ponto v9(cbase2.x, cbase2.y, cbase2.z - h2);
        Ponto v10(cbase2.x - h2, cbase2.y, cbase2.z + h2);
        Ponto v11(cbase2.x , cbase2.y, cbase2.z + h2);
        Ponto v12(cbase2.x - h2, cbase2.y + aresta2, cbase2.z - h2);
        Ponto v13(cbase2.x , cbase2.y + aresta2, cbase2.z - h2);
        Ponto v14(cbase2.x - h2, cbase2.y + aresta2, cbase2.z + h2);
        Ponto v15(cbase2.x , cbase2.y + aresta2, cbase2.z + h2);
        vector<Ponto> vertices2 = {v8, v9, v10, v11, v12,v13, v14, v15};

        Triangulo f12(vertices2[0], vertices2[2], vertices2[1]);
        Triangulo f13(vertices2[1], vertices2[2], vertices2[3]);
        Triangulo f14(vertices2[4], vertices2[5], vertices2[6]);
        Triangulo f15(vertices2[5], vertices2[7], vertices2[6]);
        Triangulo f16(vertices2[0], vertices2[4], vertices2[1]);
        Triangulo f17(vertices2[1], vertices2[4], vertices2[5]);
        Triangulo f18(vertices2[2], vertices2[3], vertices2[6]);
        Triangulo f19(vertices2[3], vertices2[7], vertices2[6]);
        Triangulo f20(vertices2[0], vertices2[2], vertices2[4]);
        Triangulo f21(vertices2[2], vertices2[6], vertices2[4]);
        Triangulo f22(vertices2[1], vertices2[5], vertices2[3]);
        Triangulo f23(vertices2[3], vertices2[5], vertices2[7]);

        vector<Triangulo> faces2 = { f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23};

        Malha *assentoBanco = new Malha(22, vertices2, faces2);
        assentoBanco->kdif = RGB(0.545, 0.271, 0.075);
        assentoBanco->kesp = RGB(0.545, 0.271, 0.075);
        assentoBanco->kamb = RGB(0.545, 0.271, 0.075);
        assentoBanco->m = 1;
        addComponente(*assentoBanco);
        

        //ENCOSTO DO BANCO
        Malha *encostoBanco = new Malha(22, vertices2, faces2);
        encostoBanco->kdif = RGB(0.545, 0.271, 0.075);
        encostoBanco->kesp = RGB(0.545, 0.271, 0.075);
        encostoBanco->kamb = RGB(0.545, 0.271, 0.075);
        encostoBanco->m = 1;

        Matriz rotBanco =  Transformacoes::rotacaoZ(90) * Transformacoes::transladar(-14.1 , -1.9 , -23.05) ;
        encostoBanco->aplicaTransformacao(rotBanco);
        Matriz voltaEncosto = Transformacoes::transladar(11.1 , 5.2 , 23.05);
        encostoBanco->aplicaTransformacao(voltaEncosto);
        addComponente(*encostoBanco);
        

    }


};



#endif