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

CargadorImage vCargadorImage;

int main(int argc,char * argv[]) {
    std::vector<std::string> a;
    a.push_back("Hola mundo");
    a.push_back("Como estas?");
    
    for (auto aon : a) {
        std::cout << aon.size() << std::endl;
    }
    std::cout << vCargadorImage.newTypeTexture(9) << std::endl;
    std::cout << vCargadorImage.newTypeTexture() << std::endl;
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
}

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1, 1, 0);
    glTranslated(0, 0, -1);
    glBegin(GL_POLYGON);{
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
        glVertex3f(0, 1, 0);
        glVertex3f(1, 1, 0);
    }glEnd();

    glutSwapBuffers ( );
}
void reajusta(int ancho,int largo){
    if (largo == 0) largo = 1;
    glViewport(0, 0, ancho, largo);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-5,5,-5,5,0.2,20);
    
    glFrustum(-0.1, 0.1, -1.0, 0.1, 0.1, 170.0);
    glMatrixMode(GL_MODELVIEW);
}
void teclado(unsigned char tecla,int x,int y){
    switch (tecla) {
        case 'a':
        case 'A':
            break;
        case 's':
        case 'S':
            break;
        case 'd':
        case 'D':
            break;
        case 'w':
        case 'W':
            break;
        case 'q':
        case 'Q':
            
            break;
        default:
            break;
    }
}
void teclasEspecciales(int tecla,int x,int y){
    
}
void raton(int x,int y){
	std::cout << x << " " << y << std::endl ;
    glutWarpPointer(20, 20);
}

void animacion(void){
}
