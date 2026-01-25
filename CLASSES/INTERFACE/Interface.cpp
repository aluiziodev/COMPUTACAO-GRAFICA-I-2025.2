#include "Interface.h"

Canvas *Interface::canvas = nullptr;
int Interface::largura = 0;
int Interface::altura = 0;

void Interface::inicializa(int argc, char **argv, int w, int h, Canvas *canvas, string titulo) {
    Interface::canvas = canvas;
    Interface::largura = w;
    Interface::altura = h;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(w, h);
    glutCreateWindow(titulo.c_str());

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
}

void Interface::display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if(canvas){
        float zoomX = (float)largura / canvas->w;
        float zoomY = (float)altura / canvas->h;

        float zoomFinal = (zoomX < zoomY) ? zoomX : zoomY;

        int offsetX = (largura - (canvas->w * zoomFinal)) / 2;
        int offsetY = (altura - (canvas->h * zoomFinal)) / 2;

        glRasterPos2i(offsetX, offsetY + (canvas->h * zoomFinal));
        glPixelZoom(zoomFinal, -zoomFinal);

        glDrawPixels(canvas->w, canvas->h, GL_RGB, GL_FLOAT, canvas->janela.data());

    }

    glFlush();
    glutSwapBuffers();
}

void Interface::mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (canvas) {
            int pixelId = canvas->pick(x, y);
            if (pixelId != -1) {
                cout << "Objeto selecionado com ID: " << pixelId << endl;
            } else {
                cout << "Nenhum objeto selecionado." << endl;
            }
        }
    }
}