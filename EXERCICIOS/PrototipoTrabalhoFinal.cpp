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
    unsigned char* textura_grama = stbi_load("../../TEXTURAS/gramado.jpg", &texW2, &texH2, &Canais2, 0);
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

    Plano pFront(Pt(1.0, 1.0, 35.0), Vt(0.0, 0.0, -1.0));
    pFront.kdif = RGB(0.529, 0.808, 0.922);
    pFront.kesp = RGB(0.529, 0.808, 0.922);
    pFront.kamb = RGB(0.529, 0.808, 0.922);
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
    esfera1.m = 1;
    cena.push_back(&esfera1);

    //ESFERA 2 CORPO SNOWMAN

    Esfera esfera2(2, 1.15, Pt(12.5, 3.5, 15.0));
    esfera2.kdif = RGB(1.0, 1.0, 1.0);
    esfera2.kesp = RGB(1.0, 1.0, 1.0);
    esfera2.kamb = RGB(1.0, 1.0, 1.0);
    esfera2.m = 1;
    cena.push_back(&esfera2);

    //ESFERA 3 CORPO SNOWMAN

    Esfera esfera3(3, 0.75, Pt(12.5, 5.05, 15.0));
    esfera3.kdif = RGB(1.0, 1.0, 1.0);
    esfera3.kesp = RGB(1.0, 1.0, 1.0);
    esfera3.kamb = RGB(1.0, 1.0, 1.0);
    esfera3.m = 1;
    cena.push_back(&esfera3);

    //ESFERA 4 OLHO SNOWMAN

    Esfera esfera4(4, 0.15, Pt(12.15, 5.05, 14.3));
    esfera4.kdif = RGB(0.0, 0.0, 0.0);
    esfera4.kesp = RGB(0.0, 0.0, 0.0);
    esfera4.kamb = RGB(0.0, 0.0, 0.0);
    esfera4.m = 1;
    cena.push_back(&esfera4);

    //ESFERA 5 OLHO SNOWMAN

    Esfera esfera5(5, 0.15, Pt(12.85, 5.05, 14.3));
    esfera5.kdif = RGB(0.0, 0.0, 0.0);
    esfera5.kesp = RGB(0.0, 0.0, 0.0);
    esfera5.kamb = RGB(0.0, 0.0, 0.0);
    esfera5.m = 1;
    cena.push_back(&esfera5);

    //CILINDRO 1 CHAPEU SNOWMAN

    Cilindro cilindro1(6, 0.85, 0.05, Pt(12.5, 5.6, 15.0), Vt(0,1,0));
    cilindro1.kdif = RGB(0.59, 0.29, 0.0);
    cilindro1.kesp = RGB(0.59, 0.29, 0.0);
    cilindro1.kamb = RGB(0.59, 0.29, 0.0);
    cilindro1.m = 1;
    cena.push_back(&cilindro1);


    //CILINDRO 2 CHAPEU SNOWMAN

    Cilindro cilindro2(7, 0.70, 1.2, Pt(12.5, 5.65, 15.0), Vt(0,1,0));
    cilindro2.kdif = RGB(0.59, 0.29, 0.0);
    cilindro2.kesp = RGB(0.59, 0.29, 0.0);
    cilindro2.kamb = RGB(0.59, 0.29, 0.0);
    cilindro2.m = 1;
    cena.push_back(&cilindro2);


    




    Cam.zoomIn(1.2);

    
    RGB iF(0.75,0.75,0.75);
    RGB iA(0.2, 0.2, 0.2);

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