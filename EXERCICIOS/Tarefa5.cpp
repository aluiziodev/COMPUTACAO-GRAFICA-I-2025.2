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

#define STB_IMAGE_IMPLEMENTATION
#include "../LIBS/stb_image.h"



using namespace std;


int main(){

    int texW, texH, Canais;
    unsigned char* textura = stbi_load("../../TEXTURAS/madeira.jpg", &texW, &texH, &Canais, 0);
    if (!textura) {
        cerr << "Erro ao carregar textura!\n";
        return -1;
    }


    // PROPRIEDADES CANVAS
    double wJanela = 0.6;
    double hJanela = 0.6;
    double dJanela = 0.3;
    int nLin = 500;
    int nCol = 500;

    double Dx = wJanela/nCol;
    double Dy = hJanela/nLin;

    Canvas canvas(nLin, nCol);

    Ponto Olho = Ponto(0.0, 0.0, 0.0);
    

    // PLANO 1 (CHAO)
    Plano pChao(Pt(0, -1.5, 0.0), Vt(0.0, 1.0, 0.0));
    pChao.colocaText(textura, texW, texH, Canais);
    pChao.ud = Vt(1.0, 0.0, 0.0); //Eixo x
    pChao.vd = Vt(0.0, 0.0, 1.0); //Eixo y
    pChao.m = 1;


    // PLANO 2 (LATERAL DIREITA)

    Plano pLatDir(Pt(2.0, -1.5, 0.0), Vt(-1.0, 0.0, 0.0));
    pLatDir.kdif = RGB(0.686, 0.933, 0.933);
    pLatDir.kesp = RGB(0.686, 0.933, 0.933);
    pLatDir.kamb = RGB(0.686, 0.933, 0.933);
    pLatDir.m = 1;

    //PLANO 3 (PAREDE FRONTAL)

    Plano pParFront(Pt(2.0, -1.5, -4.0), Vt(0.0, 0.0, 1.0));
    pParFront.kamb = RGB(0.686, 0.933, 0.933);
    pParFront.kesp = RGB(0.686, 0.933, 0.933);
    pParFront.kdif = RGB(0.686, 0.933, 0.933);
    pParFront.m = 1;

    //PLANO 4 (LATERAL ESQUERDA)

    Plano pLatEsq(Pt(-2.0, -1.5, 0.0), Vt(1.0, 0.0, 0.0));
    pLatEsq.kamb = RGB(0.686, 0.933, 0.933);
    pLatEsq.kesp = RGB(0.686, 0.933, 0.933);
    pLatEsq.kdif = RGB(0.686, 0.933, 0.933);
    pLatEsq.m = 1;

    //PLANO 5 (TETO)

    Plano pTeto(Pt(0.0, 1.5, 0.0), Vt(0.0, -1.0, 0.0));
    pTeto.kdif = RGB(0.933, 0.933, 0.933);
    pTeto.kesp = RGB(0.933, 0.933, 0.933);
    pTeto.kamb = RGB(0.933, 0.933, 0.933);
    pTeto.m = 1;

    //CILINDRO 

    Cilindro cilindro(0.05, 0.9 , Pt(0.0, -1.5, -2.0), Vt(0.0, 1.0, 0.0));
    cilindro.kdif = RGB(0.824, 0.706, 0.549);
    cilindro.kesp = RGB(0.824, 0.706, 0.549);
    cilindro.kamb = RGB(0.824, 0.706, 0.549);
    cilindro.m = 1;

    //CONE

    Cone cone(0.9, 1.5, Pt (0.0, -0.6, -2.0), Vt(0.0, 1.0, 0.0));
    cone.temBase = false;
    cone.kdif = RGB(0.0, 1.0, 0.498);
    cone.kesp = RGB(0.0, 1.0, 0.498);
    cone.kamb = RGB(0.0, 1.0, 0.498);
    cone.m = 1;

    //ESFERA

    Esfera esfera(0.05, Pt(0.0, 0.95, -2.0));
    esfera.kdif = RGB(0.854, 0.647, 0.125);
    esfera.kesp = RGB(0.854, 0.647, 0.125);
    esfera.kamb = RGB(0.854, 0.647, 0.125);
    esfera.m = 1;

    //LUZ

    Ponto P_F(-1.0,1.4, -0.2);
    RGB I_F(0.7,0.7,0.7);
    RGB I_A(0.3, 0.3, 0.3);

    //CUBO

    double aresta = 0.4;
    double h = aresta/2.0;
    Ponto cbase = Pt(0.0 , -1.5 , -1.65);
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

    Malha malha(vertices, faces);
    malha.kdif = RGB(1., 0.078, 0.576);
    malha.kesp = RGB(1., 0.078, 0.576);
    malha.kamb = RGB(1., 0.078, 0.576);
    malha.m = 1;

    
    vector<Objeto *> cena = {&esfera, &cilindro, &pChao, &pParFront, &pLatDir, &pLatEsq, &pTeto, &cone, &malha};

    for(int g = 0; g<nLin; g++){
        for(int c = 0; c<nCol; c++){
            double x = -wJanela/2 + Dx/2 + c*Dx;
            double y = hJanela/2 - Dy/2 - g*Dy;
            Ponto P = Ponto(x, y , -dJanela);
            double tmin = -1.0;

            RGB cor;
            for(Objeto *obj : cena){
                if(obj->intersecta(Olho, P)){
                    if(obj->t>0 && (tmin<0 || obj->t<tmin)){
                        tmin = obj->t;
                        Vt D = P - Olho; D.normaliza();
                        Ponto pI= Olho.pontoIntersecao(obj->t, D);
                        cone.temBase = true;
                        if(shadowRay(pI, P_F, obj, cena)){
                            cor = obj->kamb.arroba(I_A);
                        }
                        else if(obj->usaText){
                            cor = obj->pintaTextura(Olho, P, P_F, I_F, I_A);
                        }
                        else{
                            cor = obj->pinta(Olho, P, P_F, I_F, I_A);
                        }
                        cone.temBase = false;
                    }
                }
            }

            canvas.janela[g*nCol+c] = cor;
            

            
            
        }
        
    }

    canvas.GeraImg("tarefa5.ppm");

    cout << "concluido \n";

    return 0;



    
}