#ifndef PLACA_H
#define PLACA_H


#include "../../CLASSES/UTILS/Transformacoes.h"
#include "../../CLASSES/UTILS/ObjetoMulti.h"


#include "../../CLASSES/OBJETOS/Cilindro.h"
#include "../../CLASSES/OBJETOS/Triangulo.h"
#include "../../CLASSES/OBJETOS/Malha.h"


using namespace std;


struct Placa : ObjetoMulti{
   Placa(string nome){
       this->nome = nome;
       this->componentes = vector<Objeto *>();


       //MALHA PLACA
       Ponto cbase = Pt(35, 3.5, -12);
       double h = 0.4;
       double a = 2;
       double c = 3.5;


       Ponto v0(cbase.x - a, cbase.y + h, cbase.z );
       Ponto v1(cbase.x - a, cbase.y - h, cbase.z );
       Ponto v2(cbase.x + a, cbase.y + h, cbase.z );
       Ponto v3(cbase.x + a, cbase.y - h, cbase.z );
       Ponto v4(cbase.x + c, cbase.y , cbase.z );
       vector<Ponto> vertices = {v0, v1, v2, v3, v4};


       Triangulo f0(vertices[0], vertices[1], vertices[2]);
       Triangulo f1(vertices[1], vertices[3], vertices[2]);
       Triangulo f2(vertices[2], vertices[4], vertices[3]);


       vector<Triangulo> faces = { f0, f1, f2};


       Malha *placac = new Malha(nome, vertices, faces);
       placac->kdif = RGB(0.645, 0.371, 0.175);
       placac->kesp = RGB(0.645, 0.371, 0.175);
       placac->kamb = RGB(0.645, 0.371, 0.175);
       placac->m = 3;
       addComponente(*placac);


       Malha *placab = new Malha(nome, vertices, faces);
       placab->kdif = RGB(0.545, 0.271, 0.075);
       placab->kesp = RGB(0.545, 0.271, 0.075);
       placab->kamb = RGB(0.545, 0.271, 0.075);
       placab->m = 3;
       Matriz t = Transformacoes::rotacaoArbitrarioOrigem(20, Vt(0.23, 0.03, 0.75)) * Transformacoes::rotacaoY(180) *
       Transformacoes::transladar(-35, -3, +12);
       placab->aplicaTransformacao(t);
       Matriz v = Transformacoes::transladar(36, 2, -12);
       placab->aplicaTransformacao(v);
       addComponente(*placab);


       double aresta = 3.5;
       double h2 = 0.1;
       Ponto cbase2 = Pt(35.4 , 0.05 , -12.45);
       Ponto v5(cbase2.x - h2, cbase2.y, cbase2.z - h2);
       Ponto v6(cbase2.x + h2, cbase2.y, cbase2.z - h2);
       Ponto v7(cbase2.x - h2, cbase2.y, cbase2.z + h2);
       Ponto v8(cbase2.x + h2, cbase2.y, cbase2.z + h2);
       Ponto v9(cbase2.x - h2, cbase2.y + aresta, cbase2.z - h2);
       Ponto v10(cbase2.x + h2, cbase2.y + aresta, cbase2.z - h2);
       Ponto v11(cbase2.x - h2, cbase2.y + aresta, cbase2.z + h2);
       Ponto v12(cbase2.x + h2, cbase2.y + aresta, cbase2.z + h2);
       vector<Ponto> vertices2 = {v5, v6, v7, v8, v9, v10, v11, v12};


       Triangulo f3(vertices2[0], vertices2[2], vertices2[1]);
       Triangulo f4(vertices2[1], vertices2[2], vertices2[3]);
       Triangulo f5(vertices2[4], vertices2[5], vertices2[6]);
       Triangulo f6(vertices2[5], vertices2[7], vertices2[6]);
       Triangulo f7(vertices2[0], vertices2[4], vertices2[1]);
       Triangulo f8(vertices2[1], vertices2[4], vertices2[5]);
       Triangulo f9(vertices2[2], vertices2[3], vertices2[6]);
       Triangulo f10(vertices2[3], vertices2[7], vertices2[6]);
       Triangulo f11(vertices2[0], vertices2[2], vertices2[4]);
       Triangulo f12(vertices2[2], vertices2[6], vertices2[4]);
       Triangulo f13(vertices2[1], vertices2[5], vertices2[3]);
       Triangulo f14(vertices2[3], vertices2[5], vertices2[7]);


       vector<Triangulo> faces2 = { f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14};


       //PES DO BANCO
       Malha *placaA = new Malha(nome, vertices2, faces2);
       placaA->kdif = RGB(0.545, 0.271, 0.075);
       placaA->kesp = RGB(0.545, 0.271, 0.075);
       placaA->kamb = RGB(0.545, 0.271, 0.075);
       placaA->m = 1;
       addComponente(*placaA);
   }
};




#endif

