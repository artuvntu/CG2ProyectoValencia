//
//  Primitivas.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/26/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "Primitivas.hpp"

void Primitivas::mundo(PrimitivasSelectTexture *cielo,PrimitivasSelectTexture *boveda,PrimitivasSelectTexture *suelo){
    double posicionFinal[2] = {0, 0};
    this->obtenerPosicionFinal(posicionFinal, cielo, 200, 200);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[cielo->cualTextura].glIndex);
    glPushMatrix();
    for (int i = 0; i<4; i++) {
        glRotated(90, 0, 1, 0);
        glNormal3d(0, 0, -1);
        glBegin(GL_POLYGON);
        glTexCoord2d(cielo->posicionInicio[0], cielo->posicionInicio[1]);
        glVertex3f(-100, 0, -100);
        glTexCoord2d(posicionFinal[0], cielo->posicionInicio[1]);
        glVertex3f(100, 0, -100);
        glTexCoord2d(posicionFinal[0], posicionFinal[1]);
        glVertex3f(100, 200, -100);
        glTexCoord2d(cielo->posicionInicio[0], posicionFinal[1]);
        glVertex3f(-100, 200, -100);
        glEnd();
    }
    glPopMatrix();
    this->obtenerPosicionFinal(posicionFinal, suelo, 200, 200);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[suelo->cualTextura].glIndex);
    glNormal3d(0, -1, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(suelo->posicionInicio[0], suelo->posicionInicio[1]);
    glVertex3f(-100, 0, 100);
    glTexCoord2d(posicionFinal[0], suelo->posicionInicio[1]);
    glVertex3f(100, 0, 100);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
    glVertex3f(100, 0, -100);
    glTexCoord2d(suelo->posicionInicio[0], posicionFinal[1]);
    glVertex3f(-100, 0, -100);
    glEnd();
    this->obtenerPosicionFinal(posicionFinal, boveda, 200, 200);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[boveda->cualTextura].glIndex);
    glNormal3d(0, 1, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(boveda->posicionInicio[0], boveda->posicionInicio[1]);
    glVertex3f(-100, 200, 100);
    glTexCoord2d(posicionFinal[0], boveda->posicionInicio[1]);
    glVertex3f(100, 200, 100);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
    glVertex3f(100, 200, -100);
    glTexCoord2d(boveda->posicionInicio[0], posicionFinal[1]);
    glVertex3f(-100, 200, -100);
    glEnd();
}
void Primitivas::prismaEstandar(std::vector<PrimitivasSelectTexture>*vectorSelecTexture,double posicion[3],double tam[3]){
    if (vectorSelecTexture->size()!= PRIMITIVARVTPRISMAESTANDAR){
        std::cout<<"Prisma estandar Error tam vectorSelec\n";
        return;
    }
    PrimitivasSelectTexture *tActual;
    double posicionFinal[2] = {0, 0};
    tActual = &((*vectorSelecTexture)[0]);
    this->obtenerPosicionFinal(posicionFinal, tActual, tam[0], tam[1]);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[tActual->cualTextura].glIndex);
    glNormal3d(0, 0, -1);
    glBegin(GL_POLYGON);
    glTexCoord2d(tActual->posicionInicio[0], tActual->posicionInicio[1]);
        glVertex3d(posicion[0], posicion[1], posicion[2]);
    glTexCoord2d(posicionFinal[0], tActual->posicionInicio[1]);
        glVertex3d(posicion[0]+tam[0], posicion[1], posicion[2]);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
        glVertex3d(posicion[0]+tam[0], posicion[1]+tam[1], posicion[2]);
    glTexCoord2d(tActual->posicionInicio[0], posicionFinal[1]);
        glVertex3d(posicion[0], posicion[1]+tam[1], posicion[2]);
    glEnd();
    tActual = &((*vectorSelecTexture)[1]);
    this->obtenerPosicionFinal(posicionFinal, tActual, tam[2], tam[1]);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[tActual->cualTextura].glIndex);
    glNormal3d(-1, 0, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(tActual->posicionInicio[0], tActual->posicionInicio[1]);
        glVertex3d(posicion[0]+tam[0], posicion[1], posicion[2]);
    glTexCoord2d(posicionFinal[0], tActual->posicionInicio[1]);
        glVertex3d(posicion[0]+tam[0], posicion[1], posicion[2]-tam[2]);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
        glVertex3d(posicion[0]+tam[0], posicion[1]+tam[1], posicion[2]-tam[2]);
    glTexCoord2d(tActual->posicionInicio[0], posicionFinal[1]);
        glVertex3d(posicion[0]+tam[0], posicion[1]+tam[1], posicion[2]);
    glEnd();
    tActual = &((*vectorSelecTexture)[2]);
    this->obtenerPosicionFinal(posicionFinal, tActual, tam[0], tam[1]);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[tActual->cualTextura].glIndex);
    glNormal3d(0, 0, 1);
    glBegin(GL_POLYGON);
    glTexCoord2d(tActual->posicionInicio[0], tActual->posicionInicio[1]);
        glVertex3d(posicion[0], posicion[1], posicion[2]-tam[2]);
    glTexCoord2d(posicionFinal[0], tActual->posicionInicio[1]);
        glVertex3d(posicion[0]+tam[0], posicion[1], posicion[2]-tam[2]);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
        glVertex3d(posicion[0]+tam[0], posicion[1]+tam[1], posicion[2]-tam[2]);
    glTexCoord2d(tActual->posicionInicio[0], posicionFinal[1]);
        glVertex3d(posicion[0], posicion[1]+tam[1], posicion[2]-tam[2]);
    glEnd();
    tActual = &((*vectorSelecTexture)[3]);
    this->obtenerPosicionFinal(posicionFinal, tActual, tam[2], tam[1]);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[tActual->cualTextura].glIndex);
    glNormal3d(1, 0, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(tActual->posicionInicio[0], tActual->posicionInicio[1]);
        glVertex3d(posicion[0], posicion[1], posicion[2]);
    glTexCoord2d(posicionFinal[0], tActual->posicionInicio[1]);
        glVertex3d(posicion[0], posicion[1], posicion[2]-tam[2]);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
        glVertex3d(posicion[0], posicion[1]+tam[1], posicion[2]-tam[2]);
    glTexCoord2d(tActual->posicionInicio[0], posicionFinal[1]);
        glVertex3d(posicion[0], posicion[1]+tam[1], posicion[2]);
    glEnd();
    tActual = &((*vectorSelecTexture)[4]);
    this->obtenerPosicionFinal(posicionFinal, tActual, tam[0], tam[2]);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[tActual->cualTextura].glIndex);
    glNormal3d(0, 1, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(tActual->posicionInicio[0], tActual->posicionInicio[1]);
        glVertex3d(posicion[0], posicion[1], posicion[2]);
    glTexCoord2d(posicionFinal[0], tActual->posicionInicio[1]);
        glVertex3d(posicion[0]+tam[0], posicion[1], posicion[2]);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
        glVertex3d(posicion[0]+tam[0], posicion[1], posicion[2]-tam[2]);
    glTexCoord2d(tActual->posicionInicio[0], posicionFinal[1]);
        glVertex3d(posicion[0], posicion[1], posicion[2]-tam[2]);
    glEnd();
    tActual = &((*vectorSelecTexture)[5]);
    this->obtenerPosicionFinal(posicionFinal, tActual, tam[0], tam[2]);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[tActual->cualTextura].glIndex);
    glNormal3d(0, -1, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(tActual->posicionInicio[0], tActual->posicionInicio[1]);
        glVertex3d(posicion[0], posicion[1]+tam[1], posicion[2]);
    glTexCoord2d(posicionFinal[0], tActual->posicionInicio[1]);
        glVertex3d(posicion[0]+tam[0], posicion[1]+tam[1], posicion[2]);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
        glVertex3d(posicion[0]+tam[0], posicion[1]+tam[1], posicion[2]-tam[2]);
    glTexCoord2d(tActual->posicionInicio[0], posicionFinal[1]);
        glVertex3d(posicion[0], posicion[1]+tam[1], posicion[2]-tam[2]);
    glEnd();
}
void Primitivas::inicializar(CargadorImage *cargadorImagenes){
    this->vCargadorImage = cargadorImagenes;
}
void Primitivas::obtenerPosicionFinal(double *posicionFinal ,PrimitivasSelectTexture *selectTexture ,double x ,double y){
    int cantidadRepeticiones = -1;
    for (int i = 0; i<2; i++) {
        cantidadRepeticiones = this->vCargadorImage->texturas[selectTexture->cualTextura].cantidadRep[i];
        if (cantidadRepeticiones == -1) {
            posicionFinal[0] = 1 + selectTexture->posicionInicio[0];
            posicionFinal[1] = 1 + selectTexture->posicionInicio[1];
        }else{
            posicionFinal[0] = (x / cantidadRepeticiones) + selectTexture->posicionInicio[0];
            posicionFinal[1] = (y / cantidadRepeticiones) + selectTexture->posicionInicio[1];
        }
    }
}
