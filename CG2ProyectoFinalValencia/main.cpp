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
int ventana [2];
CargadorImage vCargadorImage;
TypeTexture vTypeTexture;
Camara vCamara;
Primitivas vPrimitivas;
KeyFrame vKeyFrame;

int main(int argc,char * argv[]) {
    //48 11 0000
    vPrimitivas.vKeyFrame = &vKeyFrame;
    vPrimitivas.vCargadorImage = &vCargadorImage;

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
    vPrimitivas.mundo(vCargadorImage.get(1), 0, 24, vCargadorImage.get(0), vCargadorImage.get(1));
    vCargadorImage.setDefaultTypeTexture(vTypeTexture.fachadaCasaExterna);
    vPrimitivas.setTextPared2(PRIMITIVASTEXTPARED, 2,vCargadorImage.get(0), vCargadorImage.get(1));
//    vPrimitivas.setTextPared(2, vCargadorImage.get(0),vCargadorImage.get(1));
    vPrimitivas.prismaEstandar(0, 10, 5, 2);
    glPushMatrix();{
        glTranslated(10, 10, 10);
        vPrimitivas.setTextPared2(PRIMITIVASTEXTPAREDINICIOY, 2, 0.5, 0.5);
        vPrimitivas.prismaEstandar(0, 10, 10, 10);
    }glPopMatrix();
    glutSwapBuffers ( );
}
void reajusta(int ancho,int largo){
	double aspecto = (((double)ancho) / ((double)largo))/2;
    if (largo == 0) largo = 1;
    glViewport(0, 0, ancho, largo);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-5,5,-5,5,0.2,20);
    glFrustum(-0.1*aspecto, 0.1*aspecto, -0.1, 0.1, 0.1, 250.0);
    glMatrixMode(GL_MODELVIEW);
    ventana[0] = ancho/2;
    ventana[1] = largo/2;
}
void teclado(unsigned char tecla,int x,int y){
    if (tecla == 27){
        blockCursor = false;
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        return;
    }
    if (vKeyFrame.menuActivado) {
        vKeyFrame.teclaDeMenu(tecla);
        return;
    }
    if (tecla == '!') {
        vKeyFrame.teclaActivaMenu();
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
void raton(int x,int y){
	if (blockCursor) {
		if (x != ventana[0] || y != ventana[1]) {
			glutWarpPointer(ventana[0], ventana[1]);
			vCamara.keyboardMove(7,((double)(x-ventana[0]))/50);
			vCamara.keyboardMove(9,((double)(y-ventana[1]))/50);
		}
	}
}
void clickRaton(int boton, int estado, int x, int y){
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
        if (blockCursor == false){
			glutWarpPointer(ventana[0], ventana[1]);
			glutSetCursor(GLUT_CURSOR_NONE);
			blockCursor = true;
        }
    }
}

void animacion(void){
}
