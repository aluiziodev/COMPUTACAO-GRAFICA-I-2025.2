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

    Camera Cam(500, 500, Pt(25.0, 25.0, 0.0));

    Cam.LookAt(Pt(25.0, 0.0, 40.0));

    Cam.zoomOut(2);




    vector<Objeto *> cena;
    vector<Luz *> luzes;



    // PLANO CHAO

    Plano pChao(Pt(0, 0, 0), Vt(0, 1, 0));
    pChao.colocaText(textura_grama, texW2, texH2, Canais2);
    pChao.ud = Vt(1.0, 0.0, 0.0); 
    pChao.vd = Vt(0.0, 0.0, 1.0); 
    pChao.m = 1;
    cena.push_back(&pChao);

    //PLANO 2 (PAREDE LATERAL)

    Plano pLat(Pt(0.0, 1.0, 1.0), Vt(1.0, 0.0, 0.0));
    pLat.kdif = RGB(0.329, 0.608, 0.922);
    pLat.kesp = RGB(0.329, 0.608, 0.922);
    pLat.kamb = RGB(0.329, 0.608, 0.922);
    pLat.m = 1;
    cena.push_back(&pLat);



    //PLANO 3 (PAREDE FRONTAL)

    Plano pFront(Pt(1.0, 1.0, 60.0), Vt(0.0, 0.0, -1.0));
    pFront.kdif = RGB(0.329, 0.608, 0.922);
    pFront.kesp = RGB(0.329, 0.608, 0.922);
    pFront.kamb = RGB(0.329, 0.608, 0.922);
    pFront.m = 1;
    cena.push_back(&pFront);




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


    //POSTE DE LUZ
    Cilindro poste(13, 0.2, 12, Pt(18, 0, 17.0), Vt(0, 1, 0.0));
    poste.kdif = RGB(0.4, 0.4, 0.4);
    poste.kesp = RGB(0.4, 0.4, 0.4);
    poste.kamb = RGB(0.4, 0.4, 0.4);
    poste.m = 5;
    cena.push_back(&poste);
    //LUMINARIA DO POSTE
    Cilindro luminaria(14, 0.2, 4, Pt(18, 11.8, 17.0), Vt(-1.0, 0.0, 0.0));
    luminaria.kdif = RGB(0.4, 0.4, 0.4);
    luminaria.kesp = RGB(0.4, 0.4, 0.4);
    luminaria.kamb = RGB(0.4, 0.4, 0.4);
    luminaria.m = 5;
    cena.push_back(&luminaria);
    //LAMPADA DO POSTE
    Esfera lampadaPoste(15, 0.35, Pt(14.1, 11.58, 17.0));
    lampadaPoste.kdif = RGB(1.0, 1.0, 0.8);
    lampadaPoste.kesp = RGB(1.0, 1.0, 0.8);
    lampadaPoste.kamb = RGB(1.0, 1.0, 0.8);
    lampadaPoste.m = 0.5;
    cena.push_back(&lampadaPoste);
    //BASE DO POSTE
    Cilindro basePoste(16, 0.9, 2, Pt(18, 0, 17.0), Vt(0, 1, 0.0));
    basePoste.kdif = RGB(0.4, 0.4, 0.4);
    basePoste.kesp = RGB(0.4, 0.4, 0.4);
    basePoste.kamb = RGB(0.4, 0.4, 0.4);
    basePoste.m = 5;
    cena.push_back(&basePoste);
    Matriz transladaPoste = Transformacoes::transladar(24, 0, 15);
    poste.aplicaTransformacao(transladaPoste);
    luminaria.aplicaTransformacao(transladaPoste);
    lampadaPoste.aplicaTransformacao(transladaPoste);
    basePoste.aplicaTransformacao(transladaPoste);



    //POSTE DE LUZ 2
    Cilindro poste2(13, 0.2, 12, Pt(18, 0, 17.0), Vt(0, 1, 0.0));
    poste2.kdif = RGB(0.4, 0.4, 0.4);
    poste2.kesp = RGB(0.4, 0.4, 0.4);
    poste2.kamb = RGB(0.4, 0.4, 0.4);
    poste2.m = 5;
    cena.push_back(&poste2);
    //LUMINARIA DO POSTE 2
    Cilindro luminaria2(14, 0.2, 4, Pt(18, 11.8, 17.0), Vt(-1.0, 0.0, 0.0));
    luminaria2.kdif = RGB(0.4, 0.4, 0.4);
    luminaria2.kesp = RGB(0.4, 0.4, 0.4);
    luminaria2.kamb = RGB(0.4, 0.4, 0.4);
    luminaria2.m = 5;
    cena.push_back(&luminaria2);
    //LAMPADA DO POSTE 2
    Esfera lampadaPoste2(15, 0.35, Pt(14.1, 11.58, 17.0));
    lampadaPoste2.kdif = RGB(1.0, 1.0, 0.8);
    lampadaPoste2.kesp = RGB(1.0, 1.0, 0.8);
    lampadaPoste2.kamb = RGB(1.0, 1.0, 0.8);
    lampadaPoste2.m = 0.5;
    cena.push_back(&lampadaPoste2);
    //BASE DO POSTE 2
    Cilindro basePoste2(16, 0.9, 2, Pt(18, 0, 17.0), Vt(0, 1, 0.0));
    basePoste2.kdif = RGB(0.4, 0.4, 0.4);
    basePoste2.kesp = RGB(0.4, 0.4, 0.4);
    basePoste2.kamb = RGB(0.4, 0.4, 0.4);
    basePoste2.m = 5;
    cena.push_back(&basePoste2);
    Matriz transladaOrigem = Transformacoes::transladar(-18, 0, -17);
    Matriz transladaPoste2 = Transformacoes::transladar(15, 0, 32);
    Matriz rotY = Transformacoes::rotacaoY(180);
    poste2.aplicaTransformacao(transladaOrigem);
    luminaria2.aplicaTransformacao(transladaOrigem);
    lampadaPoste2.aplicaTransformacao(transladaOrigem);
    basePoste2.aplicaTransformacao(transladaOrigem);
    poste2.aplicaTransformacao(rotY);
    luminaria2.aplicaTransformacao(rotY);
    lampadaPoste2.aplicaTransformacao(rotY);
    basePoste2.aplicaTransformacao(rotY);
    poste2.aplicaTransformacao(transladaPoste2);
    luminaria2.aplicaTransformacao(transladaPoste2);
    lampadaPoste2.aplicaTransformacao(transladaPoste2);
    basePoste2.aplicaTransformacao(transladaPoste2);



    //POSTE DE LUZ 3
    Cilindro poste3(13, 0.2, 12, Pt(18, 0, 17.0), Vt(0, 1, 0.0));
    poste3.kdif = RGB(0.4, 0.4, 0.4);
    poste3.kesp = RGB(0.4, 0.4, 0.4);
    poste3.kamb = RGB(0.4, 0.4, 0.4);
    poste3.m = 5;
    cena.push_back(&poste3);
    //LUMINARIA DO POSTE
    Cilindro luminaria3(14, 0.2, 4, Pt(18, 11.8, 17.0), Vt(-1.0, 0.0, 0.0));
    luminaria3.kdif = RGB(0.4, 0.4, 0.4);
    luminaria3.kesp = RGB(0.4, 0.4, 0.4);
    luminaria3.kamb = RGB(0.4, 0.4, 0.4);
    luminaria3.m = 5;
    cena.push_back(&luminaria3);
    //LAMPADA DO POSTE 3
    Esfera lampadaPoste3(15, 0.35, Pt(14.1, 11.58, 17.0));
    lampadaPoste3.kdif = RGB(1.0, 1.0, 0.8);
    lampadaPoste3.kesp = RGB(1.0, 1.0, 0.8);
    lampadaPoste3.kamb = RGB(1.0, 1.0, 0.8);
    lampadaPoste3.m = 0.5;
    cena.push_back(&lampadaPoste3);
    //CBASE DO POSTE 3
    Cilindro basePoste3(16, 0.9, 2, Pt(18, 0, 17.0), Vt(0, 1, 0.0));
    basePoste3.kdif = RGB(0.4, 0.4, 0.4);
    basePoste3.kesp = RGB(0.4, 0.4, 0.4);
    basePoste3.kamb = RGB(0.4, 0.4, 0.4);
    basePoste3.m = 5;
    cena.push_back(&basePoste3);
    Matriz transladaPoste3 = Transformacoes::transladar(24, 0, -3);
    poste3.aplicaTransformacao(transladaPoste3);
    luminaria3.aplicaTransformacao(transladaPoste3);
    lampadaPoste3.aplicaTransformacao(transladaPoste3);
    basePoste3.aplicaTransformacao(transladaPoste3);



    //POSTE DE LUZ 4
    Cilindro poste4(13, 0.2, 12, Pt(18, 0, 17.0), Vt(0, 1, 0.0));
    poste4.kdif = RGB(0.4, 0.4, 0.4);
    poste4.kesp = RGB(0.4, 0.4, 0.4);
    poste4.kamb = RGB(0.4, 0.4, 0.4);
    poste4.m = 5;
    cena.push_back(&poste4);
    //LUMINARIA DO POSTE 4
    Cilindro luminaria4(14, 0.2, 4, Pt(18, 11.8, 17.0), Vt(-1.0, 0.0, 0.0));
    luminaria4.kdif = RGB(0.4, 0.4, 0.4);
    luminaria4.kesp = RGB(0.4, 0.4, 0.4);
    luminaria4.kamb = RGB(0.4, 0.4, 0.4);
    luminaria4.m = 5;
    cena.push_back(&luminaria4);
    //LAMPADA DO POSTE 4
    Esfera lampadaPoste4(15, 0.35, Pt(14.1, 11.58, 17.0));
    lampadaPoste4.kdif = RGB(1.0, 1.0, 0.8);
    lampadaPoste4.kesp = RGB(1.0, 1.0, 0.8);
    lampadaPoste4.kamb = RGB(1.0, 1.0, 0.8);
    lampadaPoste4.m = 0.5;
    cena.push_back(&lampadaPoste4);
    //BASE DO POSTE 4
    Cilindro basePoste4(16, 0.9, 2, Pt(18, 0, 17.0), Vt(0, 1, 0.0));
    basePoste4.kdif = RGB(0.4, 0.4, 0.4);
    basePoste4.kesp = RGB(0.4, 0.4, 0.4);
    basePoste4.kamb = RGB(0.4, 0.4, 0.4);
    basePoste4.m = 5;
    cena.push_back(&basePoste4);
    Matriz transladaPoste4 = Transformacoes::transladar(15, 0, 14);
    poste4.aplicaTransformacao(transladaOrigem);
    luminaria4.aplicaTransformacao(transladaOrigem);
    lampadaPoste4.aplicaTransformacao(transladaOrigem);
    basePoste4.aplicaTransformacao(transladaOrigem);
    poste4.aplicaTransformacao(rotY);
    luminaria4.aplicaTransformacao(rotY);
    lampadaPoste4.aplicaTransformacao(rotY);
    basePoste4.aplicaTransformacao(rotY);
    poste4.aplicaTransformacao(transladaPoste4);
    luminaria4.aplicaTransformacao(transladaPoste4);
    lampadaPoste4.aplicaTransformacao(transladaPoste4);
    basePoste4.aplicaTransformacao(transladaPoste4);




    //CILINDRO TRONCO ARVORE
    Cilindro tronco(17, 0.3, 4, Pt(14, 0, 23.0), Vt(0, 1, 0.0));
    tronco.kdif = RGB(0.545, 0.271, 0.075);
    tronco.kesp = RGB(0.545, 0.271, 0.075);
    tronco.kamb = RGB(0.545, 0.271, 0.075);
    tronco.m = 5;
    cena.push_back(&tronco);
    //ESFERA FOLHAS ARVORE INF
    Esfera folhasInf(18, 5, Pt(14, 8.5, 23.0));
    folhasInf.kdif = RGB(0.0, 0.5, 0.0);
    folhasInf.kesp = RGB(0.0, 0.5, 0.0);
    folhasInf.kamb = RGB(0.0, 0.5, 0.0);
    folhasInf.m = 5;
    cena.push_back(&folhasInf);
    //ESFERA FOLHAS ARVORE SUP
    Esfera folhasSup(19, 4, Pt(13.8, 13.5, 23.0));
    folhasSup.kdif = RGB(0.0, 0.5, 0.0);
    folhasSup.kesp = RGB(0.0, 0.5, 0.0);
    folhasSup.kamb = RGB(0.0, 0.5, 0.0);
    folhasSup.m = 10;
    cena.push_back(&folhasSup);
    Matriz transladaArv = Transformacoes::transladar(5, 0, 20);
    tronco.aplicaTransformacao(transladaArv);
    folhasInf.aplicaTransformacao(transladaArv);
    folhasSup.aplicaTransformacao(transladaArv);


    //CILINDRO TRONCO ARVORE 2
    Cilindro tronco2(17, 0.3, 4, Pt(14, 0, 23.0), Vt(0, 1, 0.0));
    tronco2.kdif = RGB(0.545, 0.271, 0.075);
    tronco2.kesp = RGB(0.545, 0.271, 0.075);
    tronco2.kamb = RGB(0.545, 0.271, 0.075);
    tronco2.m = 5;
    cena.push_back(&tronco2);
    //ESFERA FOLHAS ARVORE INF 2
    Esfera folhasInf2(18, 5, Pt(14, 8.5, 23.0));
    folhasInf2.kdif = RGB(0.0, 0.5, 0.0);
    folhasInf2.kesp = RGB(0.0, 0.5, 0.0);
    folhasInf2.kamb = RGB(0.0, 0.5, 0.0);
    folhasInf2.m = 5;
    cena.push_back(&folhasInf2);
    //ESFERA FOLHAS ARVORE SUP 2
    Esfera folhasSup2(19, 4, Pt(13.8, 13.5, 23.0));
    folhasSup2.kdif = RGB(0.0, 0.5, 0.0);
    folhasSup2.kesp = RGB(0.0, 0.5, 0.0);
    folhasSup2.kamb = RGB(0.0, 0.5, 0.0);
    folhasSup2.m = 10;
    cena.push_back(&folhasSup2);
    Matriz transladaArv2 = Transformacoes::transladar(24, 0, 20);
    tronco2.aplicaTransformacao(transladaArv2);
    folhasInf2.aplicaTransformacao(transladaArv2);
    folhasSup2.aplicaTransformacao(transladaArv2);



    //CILINDRO TRONCO ARVORE 3
    Cilindro tronco3(17, 0.3, 4, Pt(14, 0, 23.0), Vt(0, 1, 0.0));
    tronco3.kdif = RGB(0.545, 0.271, 0.075);
    tronco3.kesp = RGB(0.545, 0.271, 0.075);
    tronco3.kamb = RGB(0.545, 0.271, 0.075);
    tronco3.m = 5;
    cena.push_back(&tronco3);
    //ESFERA FOLHAS ARVORE INF 3
    Esfera folhasInf3(18, 5, Pt(14, 8.5, 23.0));
    folhasInf3.kdif = RGB(0.0, 0.5, 0.0);
    folhasInf3.kesp = RGB(0.0, 0.5, 0.0);
    folhasInf3.kamb = RGB(0.0, 0.5, 0.0);
    folhasInf3.m = 5;
    cena.push_back(&folhasInf3);
    //ESFERA FOLHAS ARVORE SUP 3
    Esfera folhasSup3(19, 4, Pt(13.8, 13.5, 23.0));
    folhasSup3.kdif = RGB(0.0, 0.5, 0.0);
    folhasSup3.kesp = RGB(0.0, 0.5, 0.0);
    folhasSup3.kamb = RGB(0.0, 0.5, 0.0);
    folhasSup3.m = 10;
    cena.push_back(&folhasSup3);
    Matriz transladaArv3 = Transformacoes::transladar(38, 0, 15);
    tronco3.aplicaTransformacao(transladaArv3);
    folhasInf3.aplicaTransformacao(transladaArv3);
    folhasSup3.aplicaTransformacao(transladaArv3);



    //CILINDRO TRONCO ARVORE
    Cilindro tronco4(17, 0.3, 4, Pt(14, 0, 23.0), Vt(0, 1, 0.0));
    tronco4.kdif = RGB(0.545, 0.271, 0.075);
    tronco4.kesp = RGB(0.545, 0.271, 0.075);
    tronco4.kamb = RGB(0.545, 0.271, 0.075);
    tronco4.m = 5;
    cena.push_back(&tronco4);
    //ESFERA FOLHAS ARVORE INF
    Esfera folhasInf4(18, 5, Pt(14, 8.5, 23.0));
    folhasInf4.kdif = RGB(0.0, 0.5, 0.0);
    folhasInf4.kesp = RGB(0.0, 0.5, 0.0);
    folhasInf4.kamb = RGB(0.0, 0.5, 0.0);
    folhasInf4.m = 5;
    cena.push_back(&folhasInf4);
    //ESFERA FOLHAS ARVORE SUP
    Esfera folhasSup4(19, 4, Pt(13.8, 13.5, 23.0));
    folhasSup4.kdif = RGB(0.0, 0.5, 0.0);
    folhasSup4.kesp = RGB(0.0, 0.5, 0.0);
    folhasSup4.kamb = RGB(0.0, 0.5, 0.0);
    folhasSup4.m = 10;
    cena.push_back(&folhasSup4);
    Matriz transladaArv4 = Transformacoes::transladar(-7, 0, 10);
    tronco4.aplicaTransformacao(transladaArv4);
    folhasInf4.aplicaTransformacao(transladaArv4);
    folhasSup4.aplicaTransformacao(transladaArv4);


    

    RGB iF(0.3,0.3,0.3);
    //RGB iFd(0.5, 0.5, 0.7);
    RGB iFp(0.3, 0.3, 0.5);
    RGB iA(0.2, 0.2, 0.2);

    LuzSpot luzS(iF, Vt(0,-1,0), 40.0,  Pt(38.1, 11, 32.0));
    luzS.apontarPara(Pt(35.1, 0, 32));
    luzes.push_back(&luzS);

    LuzSpot luzS2(iF, Vt(0,-1,0), 40.0,  Pt(18.9, 11, 32.0));
    luzS2.apontarPara(Pt(21.9, 0, 32));
    luzes.push_back(&luzS2);

    LuzSpot luzS3(iF, Vt(0,-1,0), 40.0,  Pt(38.1, 11, 14.0));
    luzS3.apontarPara(Pt(35.1, 0, 14));
    luzes.push_back(&luzS3);

    LuzSpot luzS4(iF, Vt(0,-1,0), 40.0,  Pt(18.9, 11, 14.0));
    luzS4.apontarPara(Pt(21.9, 0, 14.0));
    luzes.push_back(&luzS4);

    //LuzDirecional luzP(iFd, Vt(-0.67, -0.67, 1.0));
    //luzes.push_back(&luzP);

    LuzPontual LuzPont(iFp, Pt(0.1, 80.0, 59.9));
    luzes.push_back(&LuzPont);

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