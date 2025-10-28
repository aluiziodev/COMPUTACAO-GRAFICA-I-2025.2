#include <bits/stdc++.h>
#include "../OBJETOS/Esfera.h"
#include "../OBJETOS/Cilindro.h"
#include "../OBJETOS/Cone.h"
#include "../OBJETOS/Plano.h"
#include "../OBJETOS/Janela.h"
#include "../OBJETOS/EstruturasGeo.h"

using namespace std;


int main(){

    // PROPRIEDADES CANVAS
    double wJanela = 60;
    double hJanela = 60;
    double dJanela = 30;
    int nLin = 500;
    int nCol = 500;

    double Dx = wJanela/nCol;
    double Dy = hJanela/nLin;

    Canvas canvas(nLin, nCol);

    Ponto Olho = Ponto(0, 0, 0);



    // PROPRIEDADES ESFERA
    Esfera esfera(40, Ponto(0, 0, -100));
    esfera.kdif = {0.7, 0.2, 0.2};
    esfera.kesp = {0.7, 0.2, 0.2};
    esfera.kamb = {0.7, 0.2, 0.2};
    esfera.m = 10;



    // PROPRIEDADES LUZ
    RGB I_F = {0.7, 0.7, 0.7}; 
    RGB I_A = {0.3,0.3,0.3};
    Ponto P_F(0, 60, -30);


    // PROPRIEDADES PLANOS
    Plano planoChao({0, -esfera.r, 0}, {0, 1, 0});
    planoChao.K_d = {0.2, 0.7, 0.2};
    planoChao.K_a = {0.2, 0.7, 0.2};
    planoChao.m = 1;

    Plano planoFundo({0, 0, -200}, {0, 0, 1});
    planoFundo.K_d = {0.3,0.3,0.7};
    planoFundo.K_a =  {0.3,0.3,0.7};
    planoFundo.m = 1;

    // PROPRIEDADES CILINDRO
    Cilindro cilindro(esfera.r/3, esfera.r*3, esfera.Cesf, Vt(-1/sqrt(3), 1/sqrt(3),-1/sqrt(3)));
    cilindro.kdif = {0.2,0.3,0.8};
    cilindro.kesp = {0.2,0.3,0.8};
    cilindro.kamb = {0.2,0.3,0.8};
    cilindro.m = 10;

    // PROPRIEDADES CONE
    Ponto cBaseCone = Ponto(
        cilindro.Cbase.x + cilindro.dCil.x * cilindro.hCil,
        cilindro.Cbase.y + cilindro.dCil.y * cilindro.hCil,
        cilindro.Cbase.z + cilindro.dCil.z * cilindro.hCil);
    Cone cone(1.5*esfera.r, (1.5*esfera.r)/3, cBaseCone, cilindro.dCil);
    cone.kdif = {0.8, 0.3, 0.2};
    cone.kesp = {0.8, 0.3, 0.2};
    cone.kamb = {0.8, 0.3, 0.2};
    cone.m = 10;

    // BASE DO CONE




    for(int g = 0; g<nLin; g++){
        for(int c = 0; c<nCol; c++){
            double x = -wJanela/2 + Dx/2 + c*Dx;
            double y = hJanela/2 - Dy/2 - g*Dy;
            Ponto P = Ponto(x, y , -dJanela);
            Vect D = P-Olho; D.normaliza();
            double t; double tmin = 1e9; int tipo = 0;
            if(esfera.IntersectaEsfera(Olho, D, t) && t<tmin){
                tmin = t;
                tipo = 1;
            }
            
            if(cilindro.IntersectaCilindro(Olho, D, t) && t<tmin){
                tmin = t;
                tipo = 2;
            }
            
            if(planoChao.IntersectaPlano(Olho, D, t) && t<tmin){
                tmin = t;
                tipo = 3;
            }
            
            if(planoFundo.IntersectaPlano(Olho, D,  t) && t<tmin){
                tmin = t;
                tipo = 4;
            }
            
            if(cone.IntersectaCone(Olho, D,  t) && t<tmin){
                tmin = t; tipo = 5;
            }
            if(cone.intersectaBaseCone(Olho, D,  t) && t<tmin){
                tmin = t; tipo = 5;
            }

            t = tmin;
            if(tipo==1){ // ESFERA
                
                Ponto pI= Ponto(Olho.x + t*D.x,Olho.y + t*D.y, Olho.z + t*D.z);

                Vect n = pI - esfera.Cesf; n.normaliza();

                Vect l = P_F - pI; l.normaliza();
                Vect v = {-D.x, -D.y, -D.z}; v.normaliza();
                Vect r = Vect(2*n.ProdEsc(l)*n.x - l.x, 2*n.ProdEsc(l)*n.y - l.y, 2*n.ProdEsc(l)*n.z - l.z);
                r.normaliza();

                RGB I_d = esfera.kdif.arroba(I_F);
                double nL = n.ProdEsc(l);
                double d = max(nL, 0.0);
                I_d.r = (I_d.r*d);
                I_d.g = (I_d.g*d);
                I_d.b = (I_d.b*d);

                RGB I_e = esfera.kesp.arroba(I_F);
                double vR = max(v.ProdEsc(r), 0.0);
                double e = pow(vR, esfera.m);
                I_e.r = (I_e.r * e);
                I_e.g = (I_e.g * e);
                I_e.b = (I_e.b * e);

                RGB I_a = esfera.kamb.arroba(I_A);
                int R = 255*(I_d.r+I_e.r+I_a.r);
                int G = 255*(I_d.g+I_e.g+I_a.g);
                int B = 255*(I_d.b+I_e.b+I_a.b);
                
                canvas.janela[g*nCol+c] = {double(min(255, R)), 
                                            double( min(255, G)), 
                                            double(min(255, B))};
                
            }
            else if(tipo==2){ // CILINDRO
                Ponto pI= Ponto(Olho.x + t*D.x,Olho.y + t*D.y, Olho.z + t*D.z);

                Vt aux = pI - cilindro.Cbase;
                Vt n = Vt(aux.x - (aux.ProdEsc(cilindro.dCil)*cilindro.dCil.x), 
                                    aux.y - (aux.ProdEsc(cilindro.dCil)*cilindro.dCil.y), 
                                    aux.z - (aux.ProdEsc(cilindro.dCil)*cilindro.dCil.z));
                n.normaliza();

                Vect l = P_F - pI; l.normaliza();
                Vect v = {-D.x, -D.y, -D.z}; v.normaliza();
                Vect r = Vect(2*n.ProdEsc(l)*n.x - l.x, 2*n.ProdEsc(l)*n.y - l.y, 2*n.ProdEsc(l)*n.z - l.z);
                r.normaliza();

                RGB I_d = cilindro.kdif.arroba(I_F);
                double nL = n.ProdEsc(l);
                double d = max(nL, 0.0);
                I_d.r = (I_d.r*d);
                I_d.g = (I_d.g*d);
                I_d.b = (I_d.b*d);

                RGB I_e = cilindro.kesp.arroba(I_F);
                double vR = max(v.ProdEsc(r), 0.0);
                double e = pow(vR, esfera.m);
                I_e.r = (I_e.r * e);
                I_e.g = (I_e.g * e);
                I_e.b = (I_e.b * e);

                RGB I_a = cilindro.kamb.arroba(I_A);
                int R = 255*(I_d.r+I_e.r+I_a.r);
                int G = 255*(I_d.g+I_e.g+I_a.g);
                int B = 255*(I_d.b+I_e.b+I_a.b);
                
                canvas.janela[g*nCol+c] = {double(min(255, R)), 
                                            double( min(255, G)), 
                                            double(min(255, B))};
            }
            else if(tipo==5){ // CONE
                Ponto pI= Ponto(Olho.x + t*D.x, Olho.y + t*D.y, Olho.z + t*D.z);

                Vt aux = pI - cone.Cbase;
                double proj = aux.ProdEsc(cone.dCone);
                Vt vx = Vt(aux.x - proj*cone.dCone.x, aux.y - proj*cone.dCone.y, aux.z - proj*cone.dCone.z);
                double k = cone.r / cone.hCone;
                Vt n = Vt((vx.x - k*proj*cone.dCone.x),(vx.y - k*proj*cone.dCone.y), (vx.z - k*proj*cone.dCone.z));
                n = Vt(-n.x, -n.y, -n.z); n.normaliza();

                Vect l = P_F - pI; l.normaliza();
                Vect v = {-D.x, -D.y, -D.z}; v.normaliza();
                Vect r = Vect(2*n.ProdEsc(l)*n.x - l.x, 2*n.ProdEsc(l)*n.y - l.y, 2*n.ProdEsc(l)*n.z - l.z);
                r.normaliza();

                RGB I_d = cone.kdif.arroba(I_F);
                double nL = n.ProdEsc(l);
                double d = max(nL, 0.0);
                I_d.r = (I_d.r*d);
                I_d.g = (I_d.g*d);
                I_d.b = (I_d.b*d);

                RGB I_e = cone.kesp.arroba(I_F);
                double vR = max(v.ProdEsc(r), 0.0);
                double e = pow(vR, esfera.m);
                I_e.r = (I_e.r * e);
                I_e.g = (I_e.g * e);
                I_e.b = (I_e.b * e);

                RGB I_a = cone.kamb.arroba(I_A);
                int R = 255*(I_d.r+I_e.r+I_a.r);
                int G = 255*(I_d.g+I_e.g+I_a.g);
                int B = 255*(I_d.b+I_e.b+I_a.b);
                
                canvas.janela[g*nCol+c] = {double(min(255, R)), 
                                            double( min(255, G)), 
                                            double(min(255, B))};
            }
            else if(tipo==3){
                Ponto pI = Ponto(planoChao.P0.x + t*D.x, planoChao.P0.y + t*D.y, planoChao.P0.z + t*D.z);
                
                Vect l = P_F - pI; l.normaliza();
                Vect v = {-D.x, -D.y, -D.z}; v.normaliza();
                Vect r = Vect(2*planoChao.N.ProdEsc(l)*planoChao.N.x - l.x, 
                            2*planoChao.N.ProdEsc(l)*planoChao.N.y - l.y,
                            2*planoChao.N.ProdEsc(l)*planoChao.N.z - l.z);
                r.normaliza();

                RGB I_d = planoChao.K_d.arroba(I_F);
                double nL = planoChao.N.ProdEsc(l);
                double d = max(nL, 0.0);
                I_d.r = (I_d.r*d);
                I_d.g = (I_d.g*d);
                I_d.b = (I_d.b*d);

                RGB I_e =  planoChao.K_e.arroba(I_F);
                double vR = max(v.ProdEsc(r), 0.0);
                double e = pow(vR, esfera.m);
                I_e.r = (I_e.r * e);
                I_e.g = (I_e.g * e);
                I_e.b = (I_e.b * e);

                RGB I_a = planoChao.K_a.arroba(I_A);

                
                if(esfera.esferaBloqueia(pI, P_F) || cilindro.cilindroBloqueia(pI, P_F) || cone.coneBloqueia(pI, P_F)){
                    I_a.padronizaRGB();
                    canvas.janela[g*nCol+c] =  I_a;
                }
                
                else{
                    int R = 255*(I_d.r+I_e.r+I_a.r);
                    int G = 255*(I_d.g+I_e.g+I_a.g);
                    int B = 255*(I_d.b+I_e.b+I_a.b);
                    
                    
                    canvas.janela[g*nCol+c] = {double(min(255, R)), 
                                                double( min(255, G)), 
                                                double(min(255, B))};
                }
            }
            else if(tipo==4){
                Ponto pI = Ponto(planoFundo.P0.x + t*D.x, planoFundo.P0.y + t*D.y, planoFundo.P0.z + t*D.z);

                
                Vect l = P_F - pI; l.normaliza();
                Vect v = {-D.x, -D.y, -D.z}; v.normaliza();
                Vect r = Vect(2*planoFundo.N.ProdEsc(l)*planoFundo.N.x - l.x, 
                            2*planoFundo.N.ProdEsc(l)*planoFundo.N.y - l.y,
                            2*planoFundo.N.ProdEsc(l)*planoFundo.N.z - l.z);
                r.normaliza();

                RGB I_d = planoFundo.K_d.arroba(I_F);
                double nL = planoFundo.N.ProdEsc(l);
                double d = max(nL, 0.0);
                I_d.r = (I_d.r*d);
                I_d.g = (I_d.g*d);
                I_d.b = (I_d.b*d);

                RGB I_e =  planoFundo.K_e.arroba(I_F);
                double vR = max(v.ProdEsc(r), 0.0);
                double e = pow(vR, esfera.m);
                I_e.r = (I_e.r * e);
                I_e.g = (I_e.g * e);
                I_e.b = (I_e.b * e);

                RGB I_a = planoFundo.K_a.arroba(I_A);
                
                
                if(esfera.esferaBloqueia(pI, P_F) || cilindro.cilindroBloqueia(pI, P_F) || cone.coneBloqueia(pI, P_F)){
                    I_a.padronizaRGB();
                    canvas.janela[g*nCol+c] =  I_a;
                }
                
                else{
                    int R = 255*(I_d.r+I_e.r+I_a.r);
                    int G = 255*(I_d.g+I_e.g+I_a.g);
                    int B = 255*(I_d.b+I_e.b+I_a.b);
                    
                    
                    canvas.janela[g*nCol+c] = {double(min(255, R)), 
                                                double( min(255, G)), 
                                                double(min(255, B))};
                }
            }
            
        }
        
    }

    canvas.GeraImg("tarefa4.ppm");

    return 0;

}