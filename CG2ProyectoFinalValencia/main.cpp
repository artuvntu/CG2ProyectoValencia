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
void funcionAnimacion(void);
//    w,s,a,d,q,e,h,l,j,k,u,i MINMAY
char teclasMovimiento[25] = "wsadqehlkjuiWSADQEHLKJUI";
bool blockCursor = false;
int ventana [2];

CargadorImage vCargadorImage;
Camara vCamara;
Primitivas vPrimitivas;
KeyFrame vKeyFrame;
Construccion vConstruccion;

PrimitivasSelectTexture forMundo[4];
std::vector<PrimitivasSelectTexture> prismaPruebas;
double posicion[3] = {0, 0, 0};
double tam[3] = {0, 0, 0};

int main(int argc,char * argv[]) {
    //48 11 0000
//    std::cout<<"Tam enteros sin signo "<<sizeof(unsigned int)<<std::endl;
//    std::cout<<sizeof(CargadorImageTexture)<<" " << sizeof(CargadorImageTexture*)<<std::endl;
//    char hola[50] = "HOLA";
//    char hol[50] = "HOLA";
//    char adi[50] = "ADIOS";
//    std::cout<< memcmp(hola, hol, sizeof(hola) )<<" "<<memcmp(adi, hola, sizeof(hola)); //0 true
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
    
    
    vCargadorImage.inicializar();
    vPrimitivas.inicializar(&vCargadorImage);
    vConstruccion.inicializar(&vPrimitivas, &vCargadorImage, &vKeyFrame);
    vKeyFrame.inicializar();
//    Pruebas
    
    forMundo[0].cualTextura = 0;
    forMundo[0].posicionInicio[1] = 0.5;
    forMundo[1].cualTextura = 1;
    forMundo[2].cualTextura = 5;
    posicion[1] = 10;
    for (int i=0; i<6; i++) {
        forMundo[3].cualTextura = i;
        prismaPruebas.push_back(forMundo[3]);
    }
    for (int j = 0; j<3; j++) {
        tam[j] = 20;
    }
    
}

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    vCamara.easyPosition();
    
    vPrimitivas.mundo(&forMundo[0], &forMundo[2], &forMundo[1]);
    
//    vPrimitivas.prismaEstandar(&prismaPruebas, posicion, tam);
    vConstruccion.dibuja();
    
    glutSwapBuffers ( );
}
void reajusta(int ancho,int largo){
	double aspecto = (((double)ancho) / ((double)largo))/2;
    if (largo == 0) largo = 1;
    glViewport(0, 0, ancho, largo);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-5,5,-5,5,0.2,20);
//    glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 250.0);
    glFrustum(-0.1*aspecto, 0.1*aspecto, -0.1*aspecto, 0.1*aspecto, 0.1, 250.0);
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
        vCamara.keyboardMove(4);
        return;
    }
    if (tecla == '\t') {
        vCamara.keyboardMove(5);
    }
    if (vKeyFrame.menuActivado) {
        vKeyFrame.teclaDeMenu(tecla);
        return;
    }
    if (vConstruccion.menuActivado) {
        vConstruccion.teclaDeMenu(tecla);
        return;
    }
    if (tecla == '!') {
        vKeyFrame.teclaActivaMenu();
        return;
    }
    if (tecla == '@') {
        vCargadorImage.reCargarArchivo();
        return;
    }
    if (tecla == '#') {
        vConstruccion.teclaActivaMenu();
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
    switch( tecla ) {
        case GLUT_KEY_PAGE_UP:
            vCamara.keyboardMove(0);
            break;
        case GLUT_KEY_PAGE_DOWN:
            vCamara.keyboardMove(1);
            break;
        case GLUT_KEY_HOME:
            vCamara.keyboardMove(2);
            break;
        case GLUT_KEY_END:
            vCamara.keyboardMove(3);
            break;
        case GLUT_KEY_UP:
            vCamara.keyboardMove(8);
            break;
        case GLUT_KEY_DOWN:
            vCamara.keyboardMove(9);
            break;
        case GLUT_KEY_LEFT:
            vCamara.keyboardMove(6);
            break;
        case GLUT_KEY_RIGHT:
            vCamara.keyboardMove(7);
            break;
        default:
            break;
    }
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

void funcionAnimacion(void){
    vKeyFrame.actualizaAnimacion();
}
