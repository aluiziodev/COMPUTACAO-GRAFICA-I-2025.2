#include <bits/stdc++.h>

#include "../CLASSES/OBJETOS/Esfera.h"
#include "../CLASSES/OBJETOS/Cilindro.h"
#include "../CLASSES/OBJETOS/Cone.h"
#include "../CLASSES/OBJETOS/Plano.h"
#include "../CLASSES/OBJETOS/Triangulo.h"
#include "../CLASSES/OBJETOS/Malha.h"
#include "../CLASSES/Janela.h"
#include "../CLASSES/Vetores.h"
#include "../CLASSES/Objeto.h"
#include "../CLASSES/Transformacoes.h"
#include "../CLASSES/Camera.h"
#include "../CLASSES/Matriz.h"
#include "../CLASSES/Luz.h"
#include "../CLASSES/LuzPontual.h"
#include "../CLASSES/LuzSpot.h"
#include "../CLASSES/LuzDirecional.h"
#include "../CLASSES/Canvas.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../LIBS/stb_image.h"



using namespace std;



int main(){

    int texW2, texH2, Canais2;
    unsigned char* textura_grama = stbi_load("../../TEXTURAS/neve.jpg", &texW2, &texH2, &Canais2, 0);
    if (!textura_grama) {
        cerr << "Erro ao carregar textura!\n";
        return -1;
    }


    int nLin = 500;
    int nCol = 500;

    Camera Cam(500, 500, Pt(12.5, 5, 0.0));



    vector<Objeto *> cena;
    vector<Luz *> luzes;



    // PLANO CHAO

    Plano pChao(Pt(0, 0, 0), Vt(0, 1, 0));
    pChao.colocaText(textura_grama, texW2, texH2, Canais2);
    pChao.ud = Vt(1.0, 0.0, 0.0); 
    pChao.vd = Vt(0.0, 0.0, 1.0); 
    pChao.m = 1;
    cena.push_back(&pChao);



    //PLANO 3 (PAREDE FRONTAL)

    Plano pFront(Pt(1.0, 1.0, 60.0), Vt(0.0, 0.0, -1.0));
    pFront.kdif = RGB(0.329, 0.608, 0.922);
    pFront.kesp = RGB(0.329, 0.608, 0.922);
    pFront.kamb = RGB(0.329, 0.608, 0.922);
    pFront.m = 1;
    cena.push_back(&pFront);



    //PLANO 5 (TETO)
/*
    Plano pTeto(Pt(0.0, 50.0, 0.0), Vt(0.0, -1.0, 0.0));
    pTeto.kdif = RGB(0.529, 0.808, 0.922);
    pTeto.kesp = RGB(0.529, 0.808, 0.922);
    pTeto.kamb = RGB(0.529, 0.808, 0.922);
    pTeto.m = 1;
    cena.push_back(&pTeto); */


    //ESFERA 1 CORPO SNOWMAN

    Esfera esfera1(1, 1.5, Pt(12.5, 1.5, 15.0));
    esfera1.kdif = RGB(1.0, 1.0, 1.0);
    esfera1.kesp = RGB(1.0, 1.0, 1.0);
    esfera1.kamb = RGB(1.0, 1.0, 1.0);
    esfera1.m = 3;
    cena.push_back(&esfera1);

    //ESFERA 2 CORPO SNOWMAN

    Esfera esfera2(2, 1.15, Pt(12.5, 3.5, 15.0));
    esfera2.kdif = RGB(1.0, 1.0, 1.0);
    esfera2.kesp = RGB(1.0, 1.0, 1.0);
    esfera2.kamb = RGB(1.0, 1.0, 1.0);
    esfera2.m = 3;
    cena.push_back(&esfera2);

    //ESFERA 3 CORPO SNOWMAN

    Esfera esfera3(3, 0.75, Pt(12.5, 5.05, 15.0));
    esfera3.kdif = RGB(1.0, 1.0, 1.0);
    esfera3.kesp = RGB(1.0, 1.0, 1.0);
    esfera3.kamb = RGB(1.0, 1.0, 1.0);
    esfera3.m = 3;
    cena.push_back(&esfera3);

    //ESFERA 4 OLHO SNOWMAN

    Esfera esfera4(4, 0.145, Pt(12.15, 5.05, 14.4));
    esfera4.kdif = RGB(0.0, 0.0, 0.0);
    esfera4.kesp = RGB(0.0, 0.0, 0.0);
    esfera4.kamb = RGB(0.0, 0.0, 0.0);
    esfera4.m = 1;
    cena.push_back(&esfera4);

    //ESFERA 5 OLHO SNOWMAN

    Esfera esfera5(5, 0.145, Pt(12.85, 5.05, 14.4));
    esfera5.kdif = RGB(0.0, 0.0, 0.0);
    esfera5.kesp = RGB(0.0, 0.0, 0.0);
    esfera5.kamb = RGB(0.0, 0.0, 0.0);
    esfera5.m = 1;
    cena.push_back(&esfera5);

    //CILINDRO 1 CHAPEU SNOWMAN

    Cilindro cilindro1(6, 1.1, 0.09, Pt(12.5, 5.5, 15.0), Vt(0,1,0));
    cilindro1.kdif = RGB(0.59, 0.29, 0.0);
    cilindro1.kesp = RGB(0.59, 0.29, 0.0);
    cilindro1.kamb = RGB(0.59, 0.29, 0.0);
    cilindro1.m = 1;
    cena.push_back(&cilindro1);


    //CILINDRO 2 CHAPEU SNOWMAN

    Cilindro cilindro2(7, 0.70, 1.2, Pt(12.5, 5.5, 15.0), Vt(0,1,0));
    cilindro2.kdif = RGB(0.59, 0.29, 0.0);
    cilindro2.kesp = RGB(0.59, 0.29, 0.0);
    cilindro2.kamb = RGB(0.59, 0.29, 0.0);
    cilindro2.m = 1;
    cena.push_back(&cilindro2);

    //CILINDRO 3 DETALHE NO CHAPEU
    Cilindro cilindro3(8, 0.75, 0.2, Pt(12.5, 5.6, 15.0), Vt(0,1,0));
    cilindro3.kdif = RGB(1., 0.008, 0.006);
    cilindro3.kesp = RGB(1., 0.008, 0.006);
    cilindro3.kamb = RGB(1., 0.008, 0.006);
    cilindro3.temBase = false;
    cilindro3.temTampa = false;
    cilindro3.m = 1;
    cena.push_back(&cilindro3);
    
    //CONE NARIZ SNOWMAN
    Cone cone1(9, 0.15, 0.5, Pt(12.5, 4.95, 14.2), Vt(0.1, -0.3, -1.0));
    cone1.kdif = RGB(1.0, 0.647, 0.0);
    cone1.kesp = RGB(1.0, 0.647, 0.0);
    cone1.kamb = RGB(1.0, 0.647, 0.0);
    cone1.m = 1;
    cone1.temBase = false;
    cena.push_back(&cone1);

    //ESFERA 6 BOTAO SNOWMAN

    Esfera esfera6(10, .2, Pt(12.5, 1.7, 13.5));
    esfera6.kdif = RGB(0.2, 0.2, 0.2);
    esfera6.kesp = RGB(0.2, 0.2, 0.2);
    esfera6.kamb = RGB(0.2, 0.2, 0.2);
    esfera6.m = 1;
    cena.push_back(&esfera6);

    //ESFERA 7 BOTAO SNOWMAN

    Esfera esfera7(11, .2, Pt(12.5, 3.7, 13.9));
    esfera7.kdif = RGB(0.2, 0.2, 0.2);
    esfera7.kesp = RGB(0.2, 0.2, 0.2);
    esfera7.kamb = RGB(0.2, 0.2, 0.2);
    esfera7.m = 1;
    cena.push_back(&esfera7);

    //CILINDRO 4 BRACO ESQUERDO SNOWMAN
    Cilindro cilindro4(12, 0.1, 2.1, Pt(12, 3.9, 15.0), Vt(-1.0, 0.4, 0.0));
    cilindro4.kdif = RGB(0.545, 0.271, 0.075);
    cilindro4.kesp = RGB(0.545, 0.271, 0.075);
    cilindro4.kamb = RGB(0.545, 0.271, 0.075);
    cilindro4.m = 1;
    cena.push_back(&cilindro4);

    //CILINDRO 5 BRACO DIREITO SNOWMAN
    Cilindro cilindro5(13, 0.1, 2.1, Pt(13, 3.9, 15.0), Vt(1.0, -0.3, 0.0));
    cilindro5.kdif = RGB(0.545, 0.271, 0.075);
    cilindro5.kesp = RGB(0.545, 0.271, 0.075);
    cilindro5.kamb = RGB(0.545, 0.271, 0.075);
    cilindro5.m = 1;
    cena.push_back(&cilindro5);


    //CILINDRO 6 POSTE DE LUZ
    Cilindro cilindro6(13, 0.2, 12, Pt(18, 0, 17.0), Vt(0, 1, 0.0));
    cilindro6.kdif = RGB(0.4, 0.4, 0.4);
    cilindro6.kesp = RGB(0.4, 0.4, 0.4);
    cilindro6.kamb = RGB(0.4, 0.4, 0.4);
    cilindro6.m = 5;
    cena.push_back(&cilindro6);

    //CILINDRO 7 LUMINARIA DO POSTE
    Cilindro cilindro7(14, 0.2, 4, Pt(18, 11.8, 17.0), Vt(-1.0, 0.0, 0.0));
    cilindro7.kdif = RGB(0.4, 0.4, 0.4);
    cilindro7.kesp = RGB(0.4, 0.4, 0.4);
    cilindro7.kamb = RGB(0.4, 0.4, 0.4);
    cilindro7.m = 5;
    cilindro7.temTampa = true;
    cilindro7.temBase = true;
    cena.push_back(&cilindro7);


    //ESFERA 8 LAMPADA DO POSTE
    Esfera esfera8(15, 0.35, Pt(14.1, 11.58, 17.0));
    esfera8.kdif = RGB(1.0, 1.0, 0.8);
    esfera8.kesp = RGB(1.0, 1.0, 0.8);
    esfera8.kamb = RGB(1.0, 1.0, 0.8);
    esfera8.m = 0.5;
    cena.push_back(&esfera8);


    //CILINDRO 8 BASE DO POSTE
    Cilindro cilindro8(16, 0.9, 2, Pt(18, 0, 17.0), Vt(0, 1, 0.0));
    cilindro8.temTampa = true;
    cilindro8.temBase = true;
    cilindro8.kdif = RGB(0.4, 0.4, 0.4);
    cilindro8.kesp = RGB(0.4, 0.4, 0.4);
    cilindro8.kamb = RGB(0.4, 0.4, 0.4);
    cilindro8.m = 5;
    cena.push_back(&cilindro8);


    //CILINDRO 9 TRONCO ARVORE
    Cilindro cilindro9(17, 0.3, 4, Pt(14, 0, 23.0), Vt(0, 1, 0.0));
    cilindro9.kdif = RGB(0.545, 0.271, 0.075);
    cilindro9.kesp = RGB(0.545, 0.271, 0.075);
    cilindro9.kamb = RGB(0.545, 0.271, 0.075);
    cilindro9.m = 5;
    cena.push_back(&cilindro9);

    //ESFERA 9 FOLHAS ARVORE
    Esfera esfera9(18, 5, Pt(14, 8.5, 23.0));
    esfera9.kdif = RGB(0.0, 0.5, 0.0);
    esfera9.kesp = RGB(0.0, 0.5, 0.0);
    esfera9.kamb = RGB(0.0, 0.5, 0.0);
    esfera9.m = 5;
    cena.push_back(&esfera9);

    //ESFERA 10 FOLHAS ARVORE
    Esfera esfera10(19, 4, Pt(13.8, 13.5, 23.0));
    esfera10.kdif = RGB(0.0, 0.5, 0.0);
    esfera10.kesp = RGB(0.0, 0.5, 0.0);
    esfera10.kamb = RGB(0.0, 0.5, 0.0);
    esfera10.m = 10;
    cena.push_back(&esfera10);
    
    Matriz transladaArv = Transformacoes::transladar(4, 0, 2);
    cilindro9.aplicaTransformacao(transladaArv);
    esfera9.aplicaTransformacao(transladaArv);
    esfera10.aplicaTransformacao(transladaArv);

    RGB iF(0.5,0.5,0.75);
    RGB iA(0.2, 0.2, 0.2);

    LuzSpot luzS(iF, Vt(0,-1,0), 30.0,  Pt(14.1, 11, 17.0));
    luzS.apontarPara(esfera1.Cesf);
    luzes.push_back(&luzS);

    LuzDirecional luzP(iF, Vt(-0.67, -0.67, 1.0));
    luzes.push_back(&luzP);

    Canvas canvas(nCol, nLin, &Cam, iA);

    for(Objeto* obj : cena){
        canvas.adicionarObjeto(obj);
    }
    for(Luz* luz : luzes){
        canvas.adicionarLuz(luz);
    }

     canvas.GeraImg("prototipo.ppm");
     cout << "concluido \n";
     stbi_image_free(textura_grama);

     return 0;

};