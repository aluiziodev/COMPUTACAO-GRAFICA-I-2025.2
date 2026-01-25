#ifndef INTERFACE_H
#define INTERFACE_H

#include "../../LIBS/freeglut/include/GL/freeglut.h"
#include "../UTILS/Canvas.h"

struct Interface {
    static Canvas* canvas;
    static int largura;
    static int altura;

    static void inicializa(int argc, char **argv, int w, int h, Canvas *canvas, string titulo);

    static void display();

    static void mouse(int button, int state, int x, int y);

};

#endif