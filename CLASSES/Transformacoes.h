#ifndef TRANSFORMACOES_H
#define TRANSFORMACOES_H

#include "Matriz.h"
#include "Quaternios.h"
using namespace std;

class Transformacoes {
public:   
    static Matriz rotacaoX(double angulo) {
        Matriz rot;
        double rad = angulo * M_PI / 180.0;
        double c = cos(rad);
        double s = sin(rad);

        rot(1,1) = c;  rot(1,2) = -s; 
        rot(2,1) = s;  rot(2,2) = c;  

        return rot;
    }

    static Matriz rotacaoY(double angulo) {
        Matriz rot;
        double rad = angulo * M_PI / 180.0;
        double c = cos(rad);
        double s = sin(rad);

        rot(0,0) = c;  rot(0,2) = s;
        rot(2,0) = -s; rot(2,2) = c;


        return rot;
    }

    static Matriz rotacaoZ(double angulo) {
        Matriz rot;
        double rad = angulo * M_PI / 180.0;
        double c = cos(rad);
        double s = sin(rad);

        rot(0,0) = c;  rot(0,1) = -s; 
        rot(1,0) = s;  rot(1,1) = c; 


        return rot;
    }

    static Matriz rotacaoArbitrarioOrigem(double angulo, Vect eixo){ // eixo tem que passar pela origem
        Matriz rot;
        double rad = angulo * M_PI / 180.0;
        double c = cos(rad/2);
        double s = sin(rad/2);
        Quaternio q = Quaternio(c, Vect(eixo.x*s, eixo.y*s, eixo.z*s));
        rot = q.matrizRotacao();

        

        return rot;



    }


    static Matriz transladar(double dx, double dy, double dz){
        Matriz tra; 

        tra(0,3) = dx;
        tra(1,3) = dy;
        tra(2,3) = dz;

        return tra;
    }

    static Matriz escalar(double sx, double sy, double sz){
        Matriz esc;

        esc(0,0) = sx;
        esc(1,1) = sy;
        esc(2,2) = sz;
        
        return esc;
    }

    static Matriz cisalharXY(double shx, double shy){
        Matriz cis;

        cis(0,1) = shx;
        cis(1,0) = shy;
    
        return cis;
    }

    static Matriz cisalharXZ(double shx, double shz){
        Matriz cis;

        cis(0,2) = shx;
        cis(2,0) = shz;

        return cis;
    }

    static Matriz cisalharYZ(double shy, double shz){
        Matriz cis;

        cis(1,2) = shy; 
        cis(2,1) = shz;

        return cis;
    }

    static Matriz EspelharXZ(){
        Matriz m;
        m(1,1) = -1;

        return m;
    }

    static Matriz EspelharYZ(){
        Matriz m;
        m(0,0) = -1;

        return m;
    }

    static Matriz EspelharXY(){
        Matriz m;
        m(2,2) = -1;

        return m;
    }
};


#endif