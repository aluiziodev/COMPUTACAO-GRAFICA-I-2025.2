#include <iostream>
#include <vector>
#include <cmath>


#include "../CLASSES/OBJETOS/Esfera.h"
#include "../CLASSES/OBJETOS/Cilindro.h"
#include "../CLASSES/OBJETOS/Cone.h"
#include "../CLASSES/OBJETOS/Plano.h"
#include "../CLASSES/OBJETOS/Triangulo.h"
#include "../CLASSES/OBJETOS/Malha.h"
#include "../CLASSES/UTILS/Janela.h"
#include "../CLASSES/UTILS/Vetores.h"
#include "../CLASSES/UTILS/Objeto.h"
#include "../CLASSES/UTILS/Transformacoes.h"
#include "../CLASSES/UTILS/Camera.h"
#include "../CLASSES/UTILS/Matriz.h"
#include "../CLASSES/UTILS/Luz.h"
#include "../CLASSES/UTILS/LuzPontual.h"
#include "../CLASSES/UTILS/LuzSpot.h"
#include "../CLASSES/UTILS/LuzDirecional.h"
#include "../CLASSES/UTILS/Canvas.h"

#include "../CLASSES/INTERFACE/Interface.h"

#include "OBJETOS/SnowMan.h"
#include "OBJETOS/Arvore.h"
#include "OBJETOS/Poste.h"
#include "OBJETOS/Banco.h"
#include "OBJETOS/placa.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../LIBS/stb_image.h"



using namespace std;



int main(int argc, char **argv){


    int texW, texH, Canais;
    unsigned char* textura_grama = stbi_load("../TEXTURAS/paisagemNeve3.jpg", &texW, &texH, &Canais, 0);
    if (!textura_grama) {
        cerr << "Erro ao carregar textura!\n";
        return -1;
    }

    int texW2, texH2, Canais2;
    unsigned char* textura_grama2 = stbi_load("../TEXTURAS/neve.jpg", &texW2, &texH2, &Canais2, 0);
    if (!textura_grama2) {
        cerr << "Erro ao carregar textura!\n";
        return -1;
    }
    

    int texW3, texH3, Canais3;
    unsigned char* textura_grama3 = stbi_load("../TEXTURAS/paisagemNeve3.jpg", &texW3, &texH3, &Canais3, 0);
    if (!textura_grama3) {
        cerr << "Erro ao carregar textura!\n";
        return -1;
    }


    int nLin = 500;
    int nCol = 500;


    //-----------VISTA PERSPECTIVA--------------

    Camera Cam(500, 500, Pt(28.0, 15.0, 0.0));
    Cam.LookAt(Pt(26.0, 0, 20.0));
    Cam.zoomOut(1.9);
   
    //--------------VISTA OBLIQUA POR PADRAO É CABINET--------------

    //Camera Cam(500, 500, Pt(38.0, 23.0, 0.0));
    //Cam.obliqua = true;
    //Cam.zoomOrtho(130);


    // --------------VISTA OBLIQUA CAVALIER--------------

    //Camera Cam(500, 500, Pt(38.0, 23.0, 0.0));
    //Cam.obliqua = true;
    //Cam.zoomOrtho(130);
    //Cam.L = 1; //Cavalier


    //-------------- VISTA ORTOGRAFICA FRONTAL--------------

    //Camera Cam(500, 500, Pt(27.0, 13.0, 0.0));
    //Cam.ortografica = true;
    //Cam.zoomOrtho(130);


    //--------------VISTA ORTOGRAFICA LATERAL--------------

    // Camera Cam(500, 500, Pt(60.0, 22.0, 20.0));
    // Cam.LookAt(Pt(19.0, 22.0, 20.0));
    // Cam.ortografica = true;
    // Cam.zoomOrtho(130);

    //--------------VISTA ORTOGRAFICA SUPERIOR--------------

    // Camera Cam(500, 500, Pt(27.0, 80.0, 20.0));
    // Cam.LookAt(Pt(27.0, 0.0, 20.0));
    // Cam.ortografica = true;
    // Cam.zoomOrtho(130);

    vector<Objeto *> cena;
    vector<Luz *> luzes;

    // PLANO CHAO

    Plano pChao("Chao", Pt(0, 0, 0), Vt(0, 1, 0));
    pChao.colocaText(textura_grama2, texW2, texH2, Canais2);
    pChao.ud = Vt(1.0, 0.0, 0.0); 
    pChao.vd = Vt(0.0, 0.0, 1.0); 
    pChao.m = 1;
    cena.push_back(&pChao);

    //PLANO 2 (PAREDE LATERAL)

    Plano pLat("Vista", Pt(0.0, 1.0, 1.0), Vt(1.0, 0.0, 0.0));
    pLat.colocaText(textura_grama, texW, texH, Canais);
    pLat.ud = Vt(0.0, 1.0, 0.0); 
    pLat.vd = Vt(0.0, 0.0, 1.0); 
    pLat.m = 1;
    cena.push_back(&pLat);



    //PLANO 3 (PAREDE FRONTAL)

    Plano pFront("Vista", Pt(1.0, 1.0, 60.0), Vt(0.0, 0.0, -1.0));
    pFront.colocaText(textura_grama3, texW3, texH3, Canais3);
    pFront.ud = Vt(1.0, 0.0, 0.0); 
    pFront.vd = Vt(0.0, 1.0, 0.0);
    pFront.m = 1;
    cena.push_back(&pFront);



    Matriz translacaoOrigemSnowM = Transformacoes::transladar(-12.5, 0, -15);
    Matriz rotY30 = Transformacoes::rotacaoY(-30);
    Matriz translacaoSnowman = Transformacoes::transladar(15.0, 0, 37.0);
    SnowMan snowman("SnowMan");
    snowman.aplicaTransformacao(translacaoOrigemSnowM);
    snowman.aplicaTransformacao(rotY30);
    snowman.aplicaTransformacao(translacaoSnowman);
    snowman.adicionaCena(cena);


    Poste poste("Poste 1");
    Matriz transladaPoste = Transformacoes::transladar(24, 0, 15);
    poste.aplicaTransformacao(transladaPoste);
    poste.adicionaCena(cena);


    Poste poste2("Poste 2");
    Matriz transladaOrigem = Transformacoes::transladar(-18, 0, -17);
    Matriz transladaPoste2 = Transformacoes::transladar(15, 0, 32);
    Matriz rotY180 = Transformacoes::rotacaoY(180);
    poste2.aplicaTransformacao(transladaOrigem);
    poste2.aplicaTransformacao(rotY180);
    poste2.aplicaTransformacao(transladaPoste2);
    poste2.adicionaCena(cena);



    Poste poste3("Poste 3");
    Matriz transladaPoste3 = Transformacoes::transladar(24, 0, -3);
    poste3.aplicaTransformacao(transladaPoste3);
    poste3.adicionaCena(cena);




    Poste poste4("Poste 4");
    Matriz transladaPoste4 = Transformacoes::transladar(15, 0, 14);
    poste4.aplicaTransformacao(transladaOrigem);
    poste4.aplicaTransformacao(rotY180);
    poste4.aplicaTransformacao(transladaPoste4);
    poste4.adicionaCena(cena);




    Arvore arvore("Arvore 3");
    Matriz transladaOrigemArv = Transformacoes::transladar(-14.0, 0, -23.0);
    Matriz escalaArv1 = Transformacoes::escalar(1.5, 1.5, 1.5);
    Matriz transladaArv = Transformacoes::transladar(19.0, 0.0, 43.0);
    arvore.aplicaTransformacao(transladaOrigemArv);
    arvore.aplicaTransformacao(escalaArv1);
    arvore.aplicaTransformacao(transladaArv);
    arvore.adicionaCena(cena);

    Arvore arvore2("Arvore 4");
    Matriz transladaArv2 = Transformacoes::transladar(24, 0, 20);
    arvore2.aplicaTransformacao(transladaArv2);
    arvore2.adicionaCena(cena);


    Arvore arvore3("Arvore 5");
    Matriz transladaArv3 = Transformacoes::transladar(38, 0, 15);
    arvore3.aplicaTransformacao(transladaArv3);
    arvore3.adicionaCena(cena);



    Arvore arvore4("Arvore 2");
    Matriz escalaArv2 = Transformacoes::escalar(0.7, 0.7, 0.7);
    Matriz transladaArv4 = Transformacoes::transladar(7, 0, 33);
    arvore4.aplicaTransformacao(transladaOrigemArv);
    arvore4.aplicaTransformacao(escalaArv2);
    arvore4.aplicaTransformacao(transladaArv4);
    arvore4.adicionaCena(cena);

    Arvore arvore5("Arvore 1");
    Matriz transladaArv5= Transformacoes::transladar(-7, 0, -10.0);
    arvore5.aplicaTransformacao(transladaArv5);
    arvore5.adicionaCena(cena);

    Banco banco1("Banco 1");
    banco1.adicionaCena(cena);

    Banco banco2("Banco 2");
    Matriz transladaOrigemBanco = Transformacoes::transladar(-14.1, -1.9, -23.05);
    Matriz transladaBanco2= Transformacoes::transladar(42.0, 1.9, 23.05);
    banco2.aplicaTransformacao(transladaOrigemBanco);
    banco2.aplicaTransformacao(rotY180);
    banco2.aplicaTransformacao(transladaBanco2);
    banco2.adicionaCena(cena);

    Placa placa("Placa 1");
    placa.adicionaCena(cena);
    Matriz espelho = Transformacoes::EspelharXY();
    Matriz cis  = Transformacoes::cisalharXY(0.3, 0.0);
    placa.aplicaTransformacao(cis);
    placa.aplicaTransformacao(espelho);

    RGB iF(0.25,0.25,0.25);
    //RGB iFd(0.5, 0.5, 0.7);
    RGB iFp(0.35, 0.35, 0.55);
    RGB iA(0.19, 0.19, 0.24);

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

    LuzPontual LuzPont(iFp, Pt(70.0, 80.0, 0.1));
    luzes.push_back(&LuzPont);

    Canvas canvas(nCol, nLin, &Cam, iA);

    for(Objeto* obj : cena){
        canvas.adicionarObjeto(obj);
    }
    for(Luz* luz : luzes){
        canvas.adicionarLuz(luz);
    }

    if(Cam.ortografica)
        canvas.GeraImgOrto("ORTOGRAFICA.ppm");
    else if(Cam.obliqua)
        canvas.GeraImgObl("OBLIQUAcavalier.ppm");
    else
        canvas.GeraImg("PERSPECTIVA.ppm");


    cout << "imagem renderizada com sucesso \n";

    Interface::inicializa(argc, argv, nCol, nLin, &canvas, "Trabalho Final - Computacao Grafica 1");

    glutMainLoop();

    return 0;

};