//
//  main.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/12/18.
//  Copyright © 2018 vApps. All rights reserved.
//  Esto es una prueba desde Linux
//  Esto es una pruena desde Windows

#include "main.hpp"

void iniciarOpenGL(void);
void dibuja(void);
void reajusta(int ancho,int largo);
void teclado(unsigned char tecla,int x,int y);
void teclasEspecciales(int tecla,int x,int y);
void raton(int x,int y);
void clickRaton(int boton, int estado, int x, int y);
void animacion(void);
//    w,s,a,d,q,e,h,l,j,k,u,i MINMAY
char teclasMovimiento[25] = "wsadqehlkjuiWSADQEHLKJUI";
bool blockCursor = false;
bool wrapCursor = false;
int cursorAnterior[2];
int ventana [2];
double movMouse;
CargadorImage vCargadorImage;
TypeTexture vTypeTexture;
Camara vCamara;
Primitivas vPrimitivas;

int main(int argc,char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("vProyecto Final");
    iniciarOpenGL();
    glutDisplayFunc(dibuja);
    glutReshapeFunc(reajusta);
    glutKeyboardFunc(teclado);
    glutPassiveMotionFunc(raton);
    glutMouseFunc(clickRaton);
    glutSpecialFunc(teclasEspecciales);
    glutIdleFunc(animacion);
    glutMainLoop();
    return 0;
}

void iniciarOpenGL(void){
    glClearColor(1, 1, 1, 0);
    
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
//    LUZ
    
    glEnable(GL_COLOR_MATERIAL);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    
//    Pruebas
    vTypeTexture.skybox = vCargadorImage.newTypeTexture();
    vCargadorImage.newTexture("CG2ProyectoFinalValencia/Textureimg/cielo01.tga");
    vCargadorImage.newTexture("CG2ProyectoFinalValencia/Textureimg/pasto01.tga");
    vTypeTexture.fachadaCasaExterna = vCargadorImage.newTypeTexture();
    vCargadorImage.newTexture("CG2ProyectoFinalValencia/Textureimg/casa01.tga");
    vCargadorImage.newTexture("CG2ProyectoFinalValencia/Textureimg/casa02.tga");
}

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    vCamara.easyPosition();
    vCargadorImage.setDefaultTypeTexture(vTypeTexture.skybox);
    vPrimitivas.mundo(vCargadorImage.getGLIndexForElement(1), 0, 24, vCargadorImage.getGLIndexForElement(0), vCargadorImage.getGLIndexForElement(0));
    vCargadorImage.setDefaultTypeTexture(vTypeTexture.fachadaCasaExterna);
    vPrimitivas.setTextPared(2, vCargadorImage.getGLIndexForElement(0),vCargadorImage.getGLIndexForElement(1));
    vPrimitivas.prismaEstandar(0x01<<16, 10, 10, 10);
    glutSwapBuffers ( );
}
void reajusta(int ancho,int largo){
    if (largo == 0) largo = 1;
    glViewport(0, 0, ancho, largo);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-5,5,-5,5,0.2,20);
    glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 250.0);
    glMatrixMode(GL_MODELVIEW);
    ventana[0] = ancho;
    ventana[1] = largo;
}
void teclado(unsigned char tecla,int x,int y){
    if (tecla == 27){
        blockCursor = false;
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        return;
    }
    for (int i=0; teclasMovimiento[i] != '\0'; i++) {
        if (teclasMovimiento[i] == tecla) {
            vCamara.keyboardMove(i);
            return;
        }
    }
}
void teclasEspecciales(int tecla,int x,int y){
    glutPostRedisplay();
}
int c = 0;
void raton(int x,int y){
    if (wrapCursor){
        if (x == cursorAnterior[0]) {
            std::cout<<c<<"HOLA\n";
            c++;
            return;
        }
        wrapCursor = false;
        c=0;
        std::cout<<c<<"ADIOS\n";

    }
    if (blockCursor) {
        int w[2] = {x,y};
        bool wrap = false;
        vCamara.keyboardMove(7,((double)(x-cursorAnterior[0]))/50);
        vCamara.keyboardMove(9,((double)(y-cursorAnterior[1]))/50);
        if (x>(ventana[0]-1)) {
            w[0] = 1;
            wrap = true;
        }
        if (x<(1)) {
            w[0] = ventana[0]-1;
            wrap = true;
        }
        if (y>(ventana[1]-1)) {
            w[1] = 1;
            wrap = true;
        }
        if (y<(1)) {
            w[1] = ventana[1]-1;
            wrap = true;
        }
        if (wrap) {
            glutWarpPointer(w[0], w[1]);
            wrapCursor = true;
        }
        cursorAnterior[0] = w[0];
        cursorAnterior[1] = w[1];
    }

}
void clickRaton(int boton, int estado, int x, int y){
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
        if (blockCursor == false){
            cursorAnterior[0] = x;
            cursorAnterior[1] = y;
            glutSetCursor(GLUT_CURSOR_NONE);
        }
        blockCursor = true;
    }
}

void animacion(void){
}
