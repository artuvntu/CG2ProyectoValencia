//
//  Primitivas.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/26/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "Primitivas.hpp"

void Primitivas::mundo(GLuint suelo, int inicio, int fin, GLuint cielo, GLuint bobeda){
    glBindTexture(GL_TEXTURE_2D, cielo);
    glPushMatrix();
    for (int i = 0; i<4; i++) {
        glRotated(90, 0, 1, 0);
        glNormal3d(0, 0, -1);
        glBegin(GL_POLYGON);
        glTexCoord2d(0, 0);
        glVertex3f(-100, 0, -100);
        glTexCoord2d(1, 0);
        glVertex3f(100, 0, -100);
        glTexCoord2d(1, 1);
        glVertex3f(100, 200, -100);
        glTexCoord2d(0, 1);
        glVertex3f(-100, 200, -100);
        glEnd();
    }
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, suelo);
    glNormal3d(0, -1, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(inicio, inicio);
    glVertex3f(-100, 0, 100);
    glTexCoord2d(fin, inicio);
    glVertex3f(100, 0, 100);
    glTexCoord2d(fin, fin);
    glVertex3f(100, 0, -100);
    glTexCoord2d(inicio, fin);
    glVertex3f(-100, 0, -100);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, bobeda);
    glNormal3d(0, 1, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(0, 0);
    glVertex3f(-100, 200, 100);
    glTexCoord2d(1, 0);
    glVertex3f(100, 200, 100);
    glTexCoord2d(1, 1);
    glVertex3f(100, 200, -100);
    glTexCoord2d(0, 1);
    glVertex3f(-100, 200, -100);
    glEnd();
}
void Primitivas::setTextPared2(int typo, int cantidad, ...){
    va_list argumentos;
    va_start(argumentos, cantidad);
    if (cantidad > 8) cantidad = 8;
    double *donde;
    switch (typo) {
        case PRIMITIVASTEXTPARED:
            for (int i = 0; i<cantidad; i++) this->textPared[i] = va_arg(argumentos, GLuint);
            va_end(argumentos);
            return;
        case PRIMITIVASTEXTPAREDTAM:
        default:
            donde = this->textParedTam;
            break;
        case PRIMITIVASTEXTPAREDINICIOX:
            donde = this->textParedInicioX;
            break;
        case PRIMITIVASTEXTPAREDINICIOY:
            donde = this->textParedInicioY;
            break;
    }
    for (int i = 0; i<cantidad; i++) donde[i] = va_arg(argumentos, double);
    va_end(argumentos);
}
void Primitivas::setTextPared(int cantidad, ...){
    va_list argumentos;
    va_start(argumentos, cantidad);
    if (cantidad > 6) cantidad = 6;
    for (int i = 0; i<cantidad; i++) this->textPared[i] = va_arg(argumentos, GLuint);
    va_end(argumentos);
}
void Primitivas::setTextParedTam(int cantidad, ...){
    va_list argumentos;
    va_start(argumentos, cantidad);
    if (cantidad > 6) cantidad = 6;
    for (int i = 0; i<cantidad; i++) this->textParedTam[i] = va_arg(argumentos, double);
    va_end(argumentos);
}
void Primitivas::resetTextParedTam(){
    for (int i = 0; i<6; i++) this->textParedTam[i] = 1;
}
void Primitivas::prismaEstandar(unsigned int typeText, double x, double y, double z,double InicioX,double InicioY){
    unsigned char tActual;
    double distanciaText[2];
    tActual = (typeText>>20) & 0xF;
    distanciaText[0] = this->textParedTam[tActual]*x/10 + InicioX;
    distanciaText[1] = this->textParedTam[tActual]*y/10 + InicioY;
    glBindTexture(GL_TEXTURE_2D, this->textPared[tActual]);
    glNormal3d(0, 0, -1);
    glBegin(GL_POLYGON);
    glTexCoord2d(InicioX, InicioY);
    glVertex3d(0, 0, 0);
    glTexCoord2d(distanciaText[0], InicioY);
    glVertex3d(x, 0, 0);
    glTexCoord2d(distanciaText[0], distanciaText[1]);
    glVertex3d(x, y, 0);
    glTexCoord2d(InicioX, distanciaText[1]);
    glVertex3d(0, y, 0);
    glEnd();
    tActual = (typeText>>16) & 0xF;
    distanciaText[0] = this->textParedTam[tActual]*z/10 + InicioX;
    distanciaText[1] = this->textParedTam[tActual]*y/10 + InicioY;
    glBindTexture(GL_TEXTURE_2D, this->textPared[tActual]);
    glNormal3d(-1, 0, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(InicioX, InicioY);
    glVertex3d(x, 0, 0);
    glTexCoord2d(distanciaText[0], InicioY);
    glVertex3d(x, 0, -z);
    glTexCoord2d(distanciaText[0], distanciaText[1]);
    glVertex3d(x, y, -z);
    glTexCoord2d(InicioX, distanciaText[1]);
    glVertex3d(x, y, 0);
    glEnd();
    tActual = (typeText>>12) & 0xF;
    distanciaText[0] = this->textParedTam[tActual]*x/10 + InicioX;
    distanciaText[1] = this->textParedTam[tActual]*y/10 + InicioY;
    glBindTexture(GL_TEXTURE_2D, this->textPared[tActual]);
    glNormal3d(0, 0, -1);
    glBegin(GL_POLYGON);
    glTexCoord2d(InicioX, InicioY);
    glVertex3d(x, 0, -z);
    glTexCoord2d(distanciaText[0], InicioY);
    glVertex3d(0, 0, -z);
    glTexCoord2d(distanciaText[0], distanciaText[1]);
    glVertex3d(0, y, -z);
    glTexCoord2d(InicioX, distanciaText[1]);
    glVertex3d(x, y, -z);
    glEnd();
    tActual = (typeText>>8) & 0xF;
    distanciaText[0] = this->textParedTam[tActual]*z/10 + InicioX;
    distanciaText[1] = this->textParedTam[tActual]*y/10 + InicioY;
    glBindTexture(GL_TEXTURE_2D, this->textPared[tActual]);
    glNormal3d(1, 0, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(0, 0);
    glVertex3d(0, 0, -z);
    glTexCoord2d(distanciaText[0], 0);
    glVertex3d(0, 0, 0);
    glTexCoord2d(distanciaText[0], distanciaText[1]);
    glVertex3d(0, y, 0);
    glTexCoord2d(0, distanciaText[1]);
    glVertex3d(0, y, -z);
    glEnd();
    tActual = (typeText>>4) & 0xF;
    distanciaText[0] = this->textParedTam[tActual]*x/10 + InicioX;
    distanciaText[1] = this->textParedTam[tActual]*z/10 + InicioY;
    glBindTexture(GL_TEXTURE_2D, this->textPared[tActual]);
    glNormal3d(0, 1, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(0, 0);
    glVertex3d(0, 0, 0);
    glTexCoord2d(distanciaText[0], 0);
    glVertex3d(x, 0, 0);
    glTexCoord2d(distanciaText[0], distanciaText[1]);
    glVertex3d(x, 0, -z);
    glTexCoord2d(0, distanciaText[1]);
    glVertex3d(0, 0, -z);
    glEnd();
    tActual = (typeText) & 0xF;
    distanciaText[0] = this->textParedTam[tActual]*x/10 + InicioX;
    distanciaText[1] = this->textParedTam[tActual]*z/10 + InicioY;
    glBindTexture(GL_TEXTURE_2D, this->textPared[tActual]);
    glNormal3d(0, -1, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(0, 0);
    glVertex3d(0, y, 0);
    glTexCoord2d(distanciaText[0], 0);
    glVertex3d(x, y, 0);
    glTexCoord2d(distanciaText[0], distanciaText[1]);
    glVertex3d(x, y, -z);
    glTexCoord2d(0, distanciaText[1]);
    glVertex3d(0, y, -z);
    glEnd();
}
