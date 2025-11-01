#include <bits/stdc++.h>

#include "../CLASSES/OBJETOS/Esfera.h"
#include "../CLASSES/OBJETOS/Cilindro.h"
#include "../CLASSES/OBJETOS/Cone.h"
#include "../CLASSES/OBJETOS/Plano.h"
#include "../CLASSES/Janela.h"
#include "../CLASSES/Vetores.h"
#include "../CLASSES/Objeto.h"

/*Plano 1: Chão
>> Ponto P_pi = (0, -150cm, 0)
>> Vetor unitário normal ao plano: n = (0, 1., 0.)
>> Kd = Ke = Ka = Textura de madeira

Plano 2: Parede lateral direita 
>> Ponto P_pi = (200cm, -150cm, 0)
>> Vetor unitário normal ao plano: n = (-1., 0., 0.)
>> Kd = Ke = Ka = (0.686, 0.933, 0.933)

Plano 3: Parede frontal 
>> Ponto P_pi = (200cm, -150cm, -400cm)
>> Vetor unitário normal ao plano: n = (0., 0., 1.)
>> Kd = Ke = Ka = (0.686, 0.933, 0.933)

Plano 4: Parede lateral esquerda
>> Ponto P_pi = (-200cm, -150cm, 0cm)
>> Vetor unitário normal ao plano: n = (1., 0., 0.)
>> Kd = Ke = Ka = (0.686, 0.933, 0.933)

Plano 5: Teto
>> Ponto P_pi = (0cm, 150cm, 0cm)
>> Vetor unitário normal ao plano: n = (0., -1., 0.)
>> Kd = Ke = Ka = (0.933, 0.933, 0.933)*/

int main(){

    // PROPRIEDADES CANVAS
    double wJanela = 0.6;
    double hJanela = 0.6;
    double dJanela = 0.3;
    int nLin = 500;
    int nCol = 500;

    double Dx = wJanela/nCol;
    double Dy = hJanela/nLin;

    Canvas canvas(nLin, nCol);

    Ponto Olho = Ponto(0, 0, 0);
    

    // PLANO 1 (CHAO)
    Plano pChao(Pt(0, -1.5, 0.0), Vt(0.0, 1.0, 0.0));

    // PLANO 2 (LATERAL DIREITA)

    Plano pLatDir(Pt(2.0, -1.5, 0.0), Vt(-1.0, 0.0, 0.0));
    pLatDir.kdif = RGB(0.686, 0.933, 0.933);
    pLatDir.kesp = RGB(0.686, 0.933, 0.933);
    pLatDir.kamb = RGB(0.686, 0.933, 0.933);

    //PLANO 3 (PAREDE FRONTAL)

    Plano pParFront(Pt(2.0, -1.5, -4.0), Vt(0.0, 0.0, 1.0));
    pParFront.kamb = RGB(0.686, 0.933, 0.933);
    pParFront.kesp = RGB(0.686, 0.933, 0.933);
    pParFront.kdif = RGB(0.686, 0.933, 0.933);
}