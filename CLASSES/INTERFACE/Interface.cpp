#include "Interface.h"

Canvas *Interface::canvas = nullptr;
int Interface::largura = 0;
int Interface::altura = 0;
string Interface::objSelecionado = "Out";

void Interface::inicializa(int argc, char **argv, int w, int h, Canvas *canvas, string titulo) {
    Interface::canvas = canvas;
    Interface::largura = w;
    Interface::altura = h;
    Interface::objSelecionado = -1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(w, h);
    glutCreateWindow(titulo.c_str());
    glutReshapeFunc(reshape);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
}

void Interface::display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, largura, 0, altura);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (canvas) {
        float zoomX = (float)largura / canvas->w;
        float zoomY = (float)altura / canvas->h;
        float zoomFinal = min(zoomX, zoomY);

        int offsetX = (largura - canvas->w * zoomFinal) / 2;
        int offsetY = (altura - canvas->h * zoomFinal) / 2;

        glRasterPos2i(offsetX, offsetY + canvas->h * zoomFinal);
        glPixelZoom(zoomFinal, -zoomFinal);

        glDrawPixels(
            canvas->w,
            canvas->h,
            GL_RGB,
            GL_FLOAT,
            canvas->janela.data()
        );

        glPixelZoom(1.0f, 1.0f);
        glDisable(GL_DEPTH_TEST);

        if(objSelecionado!="Out"){
            glColor3f(1, 1, 1); // branco
            imprimeObj(10, altura - 25,
            "Objeto selecionado: ID = " + objSelecionado);
        }
    }

    glutSwapBuffers();
}

void Interface::mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (canvas) {
            
            float zoom;
            int offX, offY;
            float zx = (float)largura / canvas->w;
            float zy = (float)altura / canvas->h;
            zoom = min(zx, zy);
            offX = (largura - canvas->w * zoom) / 2;
            offY = (altura  - canvas->h * zoom) / 2;
            int yGL = altura - y; // converter y do GLUT (topo) para OpenGL (base)
            int cx = x - offX;
            int cy = yGL - offY; // remover offset
            if (cx < 0 || cy < 0 ||
                cx >= canvas->w * zoom ||
                cy >= canvas->h * zoom) {
                objSelecionado = "Out";
                glutPostRedisplay();
                return;
            }

    
            int i = cx / zoom; // desfaz o zoom
            int j = cy / zoom;

            
            j = canvas->h - 1 - j; // inverter y (porque a imagem foi desenhada com PixelZoom negativo)

            objSelecionado = canvas->pick(i, j);
            glutPostRedisplay();
                
        }
    }
}

void Interface::reshape(int w, int h) {
    largura = w;
    altura  = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutPostRedisplay();
}

void Interface::imprimeObj(float x, float y, const string &text){
        glRasterPos2d(x, y);
        for(char c : text){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }