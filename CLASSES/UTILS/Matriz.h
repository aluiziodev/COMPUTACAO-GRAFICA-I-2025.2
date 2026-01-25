#ifndef MATRIZ_H
#define MATRIZ_H

#include <array>
#include <cmath>
#include "Vetores.h"

using namespace std;

typedef struct Matriz{
    array<double, 16> m;

    //Matriz identidade como valor inicial
    Matriz() {
        m =  {1, 0, 0, 0,
              0, 1, 0, 0,
              0, 0, 1, 0,
              0, 0, 0, 1};
    }

    //sao os retornos de referencia para a multiplicacao de matrizes (já que a gente usa o array é dessa forma que acessaa a linha e coluna)
    double& operator()(int linha, int coluna) {
        return m[linha * 4 + coluna];
    }
    const double& operator()(int linha, int coluna) const {
        return m[linha * 4 + coluna];
    }

    Matriz operator*(const Matriz &outra) const {
        Matriz resultado;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                resultado(i, j) = 0;
                for (int k = 0; k < 4; k++) {
                    resultado(i, j) += (*this)(i, k) * outra(k, j);
                }
            }
        }

        return resultado;
    }

    Ponto operator*(const Ponto &p) const {
        double x = (*this)(0, 0) * p.x + (*this)(0, 1) * p.y + (*this)(0, 2) * p.z + (*this)(0, 3) * p.a;
        double y = (*this)(1, 0) * p.x + (*this)(1, 1) * p.y + (*this)(1, 2) * p.z + (*this)(1, 3) * p.a;
        double z = (*this)(2, 0) * p.x + (*this)(2, 1) * p.y + (*this)(2, 2) * p.z + (*this)(2, 3) * p.a;
        double a = (*this)(3, 0) * p.x + (*this)(3, 1) * p.y + (*this)(3, 2) * p.z + (*this)(3, 3) * p.a;

        if(fabs(a)< 1e-8) return Ponto(x, y, z); //evita divisao por zero

        return Ponto(x/a, y/a, z/a);
    }

    Vect operator*(const Vect &v) const {
        double x = (*this)(0, 0) * v.x + (*this)(0, 1) * v.y + (*this)(0, 2) * v.z;
        double y = (*this)(1, 0) * v.x + (*this)(1, 1) * v.y + (*this)(1, 2) * v.z;
        double z = (*this)(2, 0) * v.x + (*this)(2, 1) * v.y + (*this)(2, 2) * v.z;

        return Vect(x, y, z);
    }

    Matriz transposta() const {
        Matriz resultado;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                resultado(i, j) = (*this)(j, i);
            }
        }

        return resultado;
    }


} Matriz;

#endif
