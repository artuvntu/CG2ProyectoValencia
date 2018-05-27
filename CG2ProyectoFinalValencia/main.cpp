//
//  main.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/12/18.
//  Copyright © 2018 vApps. All rights reserved.
//  Esto es una prueba desde Linux
//  Esto es una pruena desde Windows
//  Esto significa que se creo casi por completo en Mac
//

#include "main.hpp"

void iniciarOpenGL(void);
void dibuja(void);
void reajusta(int ancho,int largo);
void teclado(unsigned char tecla,int x,int y);
void teclasEspecciales(int tecla,int x,int y);
void raton(int x,int y);
void clickRaton(int boton, int estado, int x, int y);
void funcionAnimacion(void);
//    w,s,a,d,q,e,h,l,j,k,u,i MINMAY
//char teclasMovimiento[25] = "wsadqehlkjuiWSADQEHLKJUI";
bool blockCursor = false;
int ventana [2];

CargadorImage vCargadorImage;
Camara vCamara;
Primitivas vPrimitivas;
KeyFrame vKeyFrame;
Construccion vConstruccion;
CreadorObjetos vCreadorObjetos;
AcomodadorObjetos vAcomodadorObjetos;

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
    glutIdleFunc(funcionAnimacion);
    glutMainLoop();
    return 0;
}

void iniciarOpenGL(void){
    glClearColor(0.2, 0.2, 0.2, 0);
    
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
    
    vCamara.inicializar();
    vCargadorImage.inicializar();
    vPrimitivas.inicializar(&vCargadorImage);
    vConstruccion.inicializar(&vPrimitivas, &vCargadorImage, &vKeyFrame);
    vCreadorObjetos.inicializar(&vPrimitivas, &vKeyFrame, &vCargadorImage, &vCamara);
    vAcomodadorObjetos.inicializar(&vCreadorObjetos,&vCamara);
    vKeyFrame.inicializar(); //Siempre Al ultimo
//    Pruebas
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}
void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    vCamara.easyPosition();
    if (vCreadorObjetos.bloquearDibujo) {
        vCreadorObjetos.dibuja();
    }else{
        vConstruccion.dibujaAntes();
        vAcomodadorObjetos.dibuja();
        vConstruccion.dibujaDespues();
    }
    glutSwapBuffers ( );
}
void reajusta(int ancho,int largo){
    if (largo == 0) largo = 1;
	double aspecto = (((double)ancho) / ((double)largo))/2;
    glViewport(0, 0, ancho, largo);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-5,5,-5,5,0.2,20);
//    glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 250.0);
    glFrustum(-0.1*aspecto, 0.1*aspecto, -0.1*aspecto, 0.1*aspecto, 0.1, 2500.0);
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
    if (tecla == ' ') {
        vCamara.keyboardMove(4+12);
        return;
    }
    if (tecla == '\t') {
        vCamara.keyboardMove(5+12);
        return;
    }
    if (tecla == '@') {
        vCargadorImage.reCargarArchivo();
        return;
    }
    if (vKeyFrame.menuActivado) {
        vKeyFrame.teclaDeMenu(tecla);
        return;
    }
    if (vConstruccion.menuActivado) {
        vConstruccion.teclaDeMenu(tecla);
        return;
    }
    if (vCreadorObjetos.menuActivado) {
        vCreadorObjetos.teclaDeMenu(tecla);
        return;
    }
    if (vAcomodadorObjetos.menuActivado) {
        vAcomodadorObjetos.teclaDeMenu(tecla);
        return;
    }
    if(vCamara.menuActivado){
        vCamara.teclaDeMenu(tecla);
        return;
    }
    if (tecla == '!') {
        vKeyFrame.teclaActivaMenu();
        return;
    }
    if (tecla == '#') {
        vConstruccion.teclaActivaMenu();
        return;
    }
    if(tecla == '$'){
        vCreadorObjetos.teclaActivaMenu();
        return;
    }
    if (tecla == '%') {
        vAcomodadorObjetos.teclaActivaMenu();
        return;
    }
    if (tecla == '^') {
        vCamara.teclaActivaMenu();
        return;
    }
    if (vCamara.teclaMove(tecla)) {
        return;
    }
    if (tecla == '+') {
        std::cout<<"Programa terminado\n";
        vKeyFrame.guardar();
        vConstruccion.guardar();
        vCreadorObjetos.guardar();
        vAcomodadorObjetos.guardar();
        exit(0);
    }
    if (tecla == '-') {
        std::cout<<"Guardando\n";
        vKeyFrame.guardar();
        vConstruccion.guardar();
        vCreadorObjetos.guardar();
        vAcomodadorObjetos.guardar();
    }
    if (tecla >= '0' && tecla <= '9') {
        vKeyFrame.reproduceAlgunaAnimacion((unsigned int) tecla - '0');
    }
}
void teclasEspecciales(int tecla,int x,int y){
    switch( tecla ) {
        case GLUT_KEY_PAGE_UP:
            vCamara.keyboardMove(0+12);
            break;
        case GLUT_KEY_PAGE_DOWN:
            vCamara.keyboardMove(1+12);
            break;
        case GLUT_KEY_HOME:
            vCamara.keyboardMove(2+12);
            break;
        case GLUT_KEY_END:
            vCamara.keyboardMove(3+12);
            break;
        case GLUT_KEY_UP:
            vCamara.keyboardMove(8+12);
            break;
        case GLUT_KEY_DOWN:
            vCamara.keyboardMove(9+12);
            break;
        case GLUT_KEY_LEFT:
            vCamara.keyboardMove(6+12);
            break;
        case GLUT_KEY_RIGHT:
            vCamara.keyboardMove(7+12);
            break;
        default:
            break;
    }
//    glutPostRedisplay();
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
//    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
//        if (blockCursor == false){
//            glutWarpPointer(ventana[0], ventana[1]);
//            glutSetCursor(GLUT_CURSOR_NONE);
//            blockCursor = true;
//        }
//    }
}

void funcionAnimacion(void){
    vKeyFrame.actualizaAnimacion();
}
