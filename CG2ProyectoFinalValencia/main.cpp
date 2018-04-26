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
void animacion(void);
//    w,s,a,d,q,e,h,l,j,k,u,i MINMAY
char teclasMovimiento[25] = "wWsSaAdDqQeEhHlLjJkKuUiI";

CargadorImage vCargadorImage;
TypeTexture vTypeTexture;
Camara vCamara;

int main(int argc,char * argv[]) {
    for (int i = 0; i<10; i++) {
        std::cout<< i/4 <<" "<<i%2<< " "<<i/2%2<< std::endl;
    }
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
    
//    glutSetCursor(GLUT_CURSOR_NONE);
    
//    Pruebas
    vTypeTexture.skybox = vCargadorImage.newTypeTexture();
    vCargadorImage.newTexture("CG2ProyectoFinalValencia/Textureimg/cielo01.tga");
    vCargadorImage.newTexture("CG2ProyectoFinalValencia/Textureimg/pasto01.tga");
    vTypeTexture.fachadaCasaExterna = vCargadorImage.newTypeTexture();
    vCargadorImage.newTexture("CG2ProyectoFinalValencia/Textureimg/casa01.tga");
    
}

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    vCamara.easyPosition();
    glTranslated(-0.5, -0.5, -1);
    vCargadorImage.setDefaultTypeTexture(vTypeTexture.skybox);
    vCargadorImage.easyGetText(0);
    glBegin(GL_POLYGON);{
        glTexCoord2d(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2d(1, 0);
        glVertex3f(1, 0, 0);
        glTexCoord2d(1, 1);
        glVertex3f(1, 1, 0);
        glTexCoord2d(0, 1);
        glVertex3f(0, 1, 0);
    }glEnd();

    glutSwapBuffers ( );
}
void reajusta(int ancho,int largo){
    if (largo == 0) largo = 1;
    glViewport(0, 0, ancho, largo);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-5,5,-5,5,0.2,20);
    glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);
    glMatrixMode(GL_MODELVIEW);
}
void teclado(unsigned char tecla,int x,int y){
    switch (tecla) {
        case 'a':
        case 'A':
            vCamara.move(2);
            break;
        case 's':
        case 'S':
            break;
        case 'd':
        case 'D':
            break;
        case 'w':
        case 'W':
            vCamara.move(0);
            break;
        case 'q':
        case 'Q':
            
            break;
        default:
            break;
    }
    glutPostRedisplay();
}
void teclasEspecciales(int tecla,int x,int y){
    glutPostRedisplay();
}
void raton(int x,int y){
//    std::cout << x << " " << y << std::endl ;
//    glutWarpPointer(20, 20);
}

void animacion(void){
}
