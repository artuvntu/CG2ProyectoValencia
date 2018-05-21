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
    double posicionInicio[2] = {0,0};
    this->obtenerPosicionFinalEInicial(posicionFinal,posicionInicio, cielo, 200, 200);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[cielo->cualTextura].glIndex);
    glPushMatrix();
    for (int i = 0; i<4; i++) {
        glRotated(90, 0, 1, 0);
        glNormal3d(0, 0, -1);
        glBegin(GL_POLYGON);
        glTexCoord2d(cielo->posicionInicio[0], posicionInicio[1]);
        glVertex3f(-100, 0, -100);
        glTexCoord2d(posicionFinal[0], posicionInicio[1]);
        glVertex3f(100, 0, -100);
        glTexCoord2d(posicionFinal[0], posicionFinal[1]);
        glVertex3f(100, 200, -100);
        glTexCoord2d(posicionInicio[0], posicionFinal[1]);
        glVertex3f(-100, 200, -100);
        glEnd();
    }
    glPopMatrix();
    this->obtenerPosicionFinalEInicial(posicionFinal, posicionInicio, suelo, 200, 200);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[suelo->cualTextura].glIndex);
    glNormal3d(0, -1, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(suelo->posicionInicio[0], posicionInicio[1]);
    glVertex3f(-100, 0, 100);
    glTexCoord2d(posicionFinal[0], posicionInicio[1]);
    glVertex3f(100, 0, 100);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
    glVertex3f(100, 0, -100);
    glTexCoord2d(posicionInicio[0], posicionFinal[1]);
    glVertex3f(-100, 0, -100);
    glEnd();
    this->obtenerPosicionFinalEInicial(posicionFinal, posicionInicio, boveda, 200, 200);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[boveda->cualTextura].glIndex);
    glNormal3d(0, 1, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(boveda->posicionInicio[0], posicionInicio[1]);
    glVertex3f(-100, 200, 100);
    glTexCoord2d(posicionFinal[0], posicionInicio[1]);
    glVertex3f(100, 200, 100);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
    glVertex3f(100, 200, -100);
    glTexCoord2d(posicionInicio[0], posicionFinal[1]);
    glVertex3f(-100, 200, -100);
    glEnd();
}
void Primitivas::planoEstandar(std::vector<PrimitivasSelectTexture> *vector, unsigned int desdeDonde, double *posicion, double *tam){
    if (vector->size()-desdeDonde<PRIMITIVAVRTPLANO) {
        std::cout<<"Plano estandar error tam vector\n";
    }
    double posicionFinal[2] = {0,0};
    double posicionInicial[2] = {0,0};
    double lugarTerminal[2] = {posicion[0]+tam[0],posicion[1]+tam[1]};
    PrimitivasSelectTexture *tActual = &vector->at(desdeDonde);
    this->obtenerPosicionFinalEInicial(posicionFinal, posicionInicial, tActual, tam[0], tam[1]);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[tActual->cualTextura].glIndex);
    glNormal3d(0, 0, -1);
    glBegin(GL_POLYGON);
    glTexCoord2d(posicionInicial[0], posicionInicial[1]);
    glVertex3d(posicion[0], posicion[1], posicion[2]);
    glTexCoord2d(posicionFinal[0], posicionInicial[1]);
    glVertex3d(lugarTerminal[0], posicion[1], posicion[2]);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
    glVertex3d(lugarTerminal[0], lugarTerminal[1], posicion[2]);
    glTexCoord2d(posicionInicial[0], posicionFinal[1]);
    glVertex3d(posicion[0], lugarTerminal[1], posicion[2]);
    glEnd();
}
void Primitivas::prismaEstandar(std::vector<PrimitivasSelectTexture>*vectorSelecTexture,unsigned int desdeDonde,double posicion[3],double tam[3],double angulo){
    if (vectorSelecTexture->size()-desdeDonde< PRIMITIVARVTPRISMAESTANDAR){
        std::cout<<"Prisma estandar Error tam vectorSelec\n";
        return;
    }   //3.14
    PrimitivasSelectTexture *tActual;
    double posicionFinal[2] = {0, 0};
    double posicionInicio[2] = {0, 0};
    double anguloSuplementario = angulo+1.57;
    double puntos[3][2];
    puntos[0][0] = tam[0]*cos(angulo);
    puntos[0][1] = tam[0]*sin(angulo);
    puntos[2][0] = (-tam[2])*cos(anguloSuplementario);
    puntos[2][1] = (-tam[2])*sin(anguloSuplementario);
    
    puntos[1][0] = puntos[0][0] + puntos[2][0];
    puntos[1][1] = puntos[0][1] + puntos[2][1];

    tActual = &((*vectorSelecTexture)[0+desdeDonde]);
    this->obtenerPosicionFinalEInicial(posicionFinal,posicionInicio, tActual, tam[0], tam[1]);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[tActual->cualTextura].glIndex);
    glNormal3d(0, 0, -1);
    glBegin(GL_POLYGON);
    glTexCoord2d(posicionInicio[0], posicionInicio[1]);
        glVertex3d(posicion[0], posicion[1], posicion[2]);
    glTexCoord2d(posicionFinal[0], posicionInicio[1]);
        glVertex3d(posicion[0]+puntos[0][0], posicion[1], posicion[2]+puntos[0][1]);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
        glVertex3d(posicion[0]+puntos[0][0], posicion[1]+tam[1], posicion[2]+puntos[0][1]);
    glTexCoord2d(posicionInicio[0], posicionFinal[1]);
        glVertex3d(posicion[0], posicion[1]+tam[1], posicion[2]);
    glEnd();
    tActual = &((*vectorSelecTexture)[1+desdeDonde]);
    this->obtenerPosicionFinalEInicial(posicionFinal,posicionInicio, tActual, tam[2], tam[1]);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[tActual->cualTextura].glIndex);
    glNormal3d(-1, 0, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(posicionInicio[0], posicionInicio[1]);
        glVertex3d(posicion[0]+puntos[0][0], posicion[1], posicion[2]+puntos[0][1]);
    glTexCoord2d(posicionFinal[0], posicionInicio[1]);
        glVertex3d(posicion[0]+puntos[1][0], posicion[1], posicion[2]+puntos[1][1]);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
        glVertex3d(posicion[0]+puntos[1][0], posicion[1]+tam[1], posicion[2]+puntos[1][1]);
    glTexCoord2d(posicionInicio[0], posicionFinal[1]);
        glVertex3d(posicion[0]+puntos[0][0], posicion[1]+tam[1], posicion[2]+puntos[0][1]);
    glEnd();
    tActual = &((*vectorSelecTexture)[2+desdeDonde]);
    this->obtenerPosicionFinalEInicial(posicionFinal,posicionInicio, tActual, tam[0], tam[1]);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[tActual->cualTextura].glIndex);
    glNormal3d(0, 0, 1);
    glBegin(GL_POLYGON);
    glTexCoord2d(posicionInicio[0], posicionInicio[1]);
        glVertex3d(posicion[0]+puntos[2][0], posicion[1], posicion[2]+puntos[2][1]);
    glTexCoord2d(posicionFinal[0], posicionInicio[1]);
        glVertex3d(posicion[0]+puntos[1][0], posicion[1], posicion[2]+puntos[1][1]);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
        glVertex3d(posicion[0]+puntos[1][0], posicion[1]+tam[1], posicion[2]+puntos[1][1]);
    glTexCoord2d(posicionInicio[0], posicionFinal[1]);
        glVertex3d(posicion[0]+puntos[2][0], posicion[1]+tam[1], posicion[2]+puntos[2][1]);
    glEnd();
    tActual = &((*vectorSelecTexture)[3+desdeDonde]);
    this->obtenerPosicionFinalEInicial(posicionFinal,posicionInicio, tActual, tam[2], tam[1]);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[tActual->cualTextura].glIndex);
    glNormal3d(1, 0, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(posicionInicio[0], posicionInicio[1]);
        glVertex3d(posicion[0], posicion[1], posicion[2]);
    glTexCoord2d(posicionFinal[0], posicionInicio[1]);
        glVertex3d(posicion[0]+puntos[2][0], posicion[1], posicion[2]+puntos[2][1]);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
        glVertex3d(posicion[0]+puntos[2][0], posicion[1]+tam[1], posicion[2]+puntos[2][1]);
    glTexCoord2d(posicionInicio[0], posicionFinal[1]);
        glVertex3d(posicion[0], posicion[1]+tam[1], posicion[2]);
    glEnd();///
    tActual = &((*vectorSelecTexture)[4+desdeDonde]);
    this->obtenerPosicionFinalEInicial(posicionFinal,posicionInicio, tActual, tam[0], tam[2]);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[tActual->cualTextura].glIndex);
    glNormal3d(0, 1, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(posicionInicio[0], posicionInicio[1]);
        glVertex3d(posicion[0], posicion[1], posicion[2]);
    glTexCoord2d(posicionFinal[0], posicionInicio[1]);
        glVertex3d(posicion[0]+puntos[0][0], posicion[1], posicion[2]+puntos[0][1]);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
        glVertex3d(posicion[0]+puntos[1][0], posicion[1], posicion[2]+puntos[1][1]);
    glTexCoord2d(posicionInicio[0], posicionFinal[1]);
        glVertex3d(posicion[0]+puntos[2][0], posicion[1], posicion[2]+puntos[2][1]);
    glEnd();
    tActual = &((*vectorSelecTexture)[5+desdeDonde]);
    this->obtenerPosicionFinalEInicial(posicionFinal,posicionInicio, tActual, tam[0], tam[2]);
    glBindTexture(GL_TEXTURE_2D, this->vCargadorImage->texturas[tActual->cualTextura].glIndex);
    glNormal3d(0, -1, 0);
    glBegin(GL_POLYGON);
    glTexCoord2d(posicionInicio[0], posicionInicio[1]);
        glVertex3d(posicion[0], posicion[1]+tam[1], posicion[2]);
    glTexCoord2d(posicionFinal[0], posicionInicio[1]);
        glVertex3d(posicion[0]+puntos[0][0], posicion[1]+tam[1], posicion[2]+puntos[0][1]);
    glTexCoord2d(posicionFinal[0], posicionFinal[1]);
        glVertex3d(posicion[0]+puntos[1][0], posicion[1]+tam[1], posicion[2]+puntos[1][1]);
    glTexCoord2d(posicionInicio[0], posicionFinal[1]);
        glVertex3d(posicion[0]+puntos[2][0], posicion[1]+tam[1], posicion[2]+puntos[2][1]);
    glEnd();
}
void Primitivas::inicializar(CargadorImage *cargadorImagenes){
    this->vCargadorImage = cargadorImagenes;
}
void Primitivas::obtenerPosicionFinalEInicial(double *posicionFinal, double *posicionInicial, PrimitivasSelectTexture *selectTexture, double x, double y){
    double temporal[2] = {x, y};
    double cantidadRepeticiones = -1;
    for (int i = 0; i<2; i++) {
        cantidadRepeticiones = this->vCargadorImage->texturas[selectTexture->cualTextura].cantidadRep[i];
        if (cantidadRepeticiones == -1) {
            posicionInicial[i] = 0;
            posicionFinal[i] = 1;
        }else{
            posicionInicial[i] = selectTexture->posicionInicio[i]/cantidadRepeticiones;
            posicionFinal[i] = (temporal[i] / cantidadRepeticiones) + posicionInicial[i];
        }
    }
}
void Primitivas::escaleras(std::vector<PrimitivasSelectTexture> *vectorSelectTexture, unsigned int desdeDonde, double *posicion, double *tam,unsigned int canEscalones, double angulo){
    double tamEscalones[2] = {tam[0]/canEscalones,tam[1]/canEscalones};
    double ayudaCrearPrismasTam [3] = {tamEscalones[0], tamEscalones[1], tam[2]};
    double ayudaCrearPrismaPosicion[3] = {0, 0, 0};
    std::vector<PrimitivasSelectTexture> vectorT;
    if (vectorSelectTexture->size()-desdeDonde!=PRIMITIVARVTPRISMAESTANDAR) {
        std::cout<<"Error Escaleras\n";
        return;
    }
    for (int i = 0; i<6; i++) {
        vectorT.push_back(vectorSelectTexture->at(i+desdeDonde));
    }
    
    glPushMatrix();{
        glTranslated(posicion[0], posicion[1], posicion[2]);
        glRotated(angulo, 0, 1, 0);
        for (int i =0; i<canEscalones; i++) {
            this->prismaEstandar(&vectorT, 0, ayudaCrearPrismaPosicion, ayudaCrearPrismasTam, 0);
            ayudaCrearPrismaPosicion[0] += tamEscalones[0];
            ayudaCrearPrismaPosicion[1] += tamEscalones[1];
            
            vectorT[0].posicionInicio[0] += tamEscalones[0];
            vectorT[0].posicionInicio[1] += tamEscalones[1];
            
            vectorT[2].posicionInicio[0] += tamEscalones[0];
            vectorT[2].posicionInicio[1] += tamEscalones[1];
            
            vectorT[1].posicionInicio[1] += tamEscalones[1];
            
            vectorT[3].posicionInicio[1] += tamEscalones[1];
            
            vectorT[4].posicionInicio[0] += tamEscalones[0];
            
            vectorT[5].posicionInicio[0] += tamEscalones[0];

        }
    }glPopMatrix();
    
}
void Primitivas::sueloPoligonal(std::vector<PrimitivasSelectTexture> *vectorSelecTexture,unsigned int desdeDonde, std::vector<Cg2ValenciaPunto3D> *vectorVertices){
    if (vectorSelecTexture->size()-desdeDonde<2) {
        std::cout<<"Suelo incompleto\n";
        return;
    }
    double multiplicador[2] = {vCargadorImage->texturas[vectorSelecTexture->at(0).cualTextura].cantidadRep[0],vCargadorImage->texturas[vectorSelecTexture->at(0).cualTextura].cantidadRep[1]};
    if (multiplicador[0] == -1 || multiplicador[1] == -1) {
        std::cout<<"No me rompere la cabeza analizando texturas -1 jaja\n";
        multiplicador[0] = 30;
        multiplicador[1] = 30;
    }
    if (vectorVertices->size()>2) {
        glBindTexture(GL_TEXTURE_2D, vCargadorImage->texturas[vectorSelecTexture->at(desdeDonde).cualTextura].glIndex);
        glNormal3d(0, -1, 0);
        glBegin(GL_POLYGON);
        glTexCoord2d(vectorSelecTexture->at(desdeDonde).posicionInicio[0], vectorSelecTexture->at(desdeDonde).posicionInicio[1]);
        glVertex3dv(vectorVertices->at(0).coordenadas);
        for (unsigned int i =1; i<vectorVertices->size(); i++) {
//            glTexCoord2d((vectorVertices->at(0).coordenadas[0]-vectorVertices->at(i).coordenadas[0]+vectorSelecTexture->at(desdeDonde).posicionInicio[0])/multiplicador[0],(vectorVertices->at(0).coordenadas[2]-vectorVertices->at(i).coordenadas[2]+vectorSelecTexture->at(desdeDonde).posicionInicio[1])/multiplicador[1] );
            glTexCoord2d(((vectorVertices->at(0).coordenadas[0]-vectorVertices->at(i).coordenadas[0])/multiplicador[0])+vectorSelecTexture->at(desdeDonde).posicionInicio[0],((vectorVertices->at(0).coordenadas[2]-vectorVertices->at(i).coordenadas[2])/multiplicador[1])+vectorSelecTexture->at(desdeDonde).posicionInicio[1] );
            glVertex3dv(vectorVertices->at(i).coordenadas);
        }
        glEnd();
    }
    glPushMatrix();
    glTranslated(0, -0.1, 0);
    multiplicador[0] = vCargadorImage->texturas[vectorSelecTexture->at(1).cualTextura].cantidadRep[0];
    multiplicador[1] = vCargadorImage->texturas[vectorSelecTexture->at(1).cualTextura].cantidadRep[1];
    if (multiplicador[0] == -1 || multiplicador[1] == -1) {
        std::cout<<"No me rompere la cabeza analizando texturas -1 jaja\n";
        multiplicador[0] = 30;
        multiplicador[1] = 30;
    }
    if (vectorVertices->size()>2) {
        glBindTexture(GL_TEXTURE_2D, vCargadorImage->texturas[vectorSelecTexture->at(desdeDonde+1).cualTextura].glIndex);
        glNormal3d(0, 1, 0);
        glBegin(GL_POLYGON);
        glTexCoord2d(vectorSelecTexture->at(desdeDonde+1).posicionInicio[0], vectorSelecTexture->at(desdeDonde+1).posicionInicio[1]);
        glVertex3dv(vectorVertices->at(0).coordenadas);
        for (unsigned int i =1; i<vectorVertices->size(); i++) {
            glTexCoord2d(((vectorVertices->at(0).coordenadas[0]-vectorVertices->at(i).coordenadas[0])/multiplicador[0])+vectorSelecTexture->at(desdeDonde+1).posicionInicio[0],((vectorVertices->at(0).coordenadas[2]-vectorVertices->at(i).coordenadas[2])/multiplicador[1])+vectorSelecTexture->at(desdeDonde+1).posicionInicio[1] );
            glVertex3dv(vectorVertices->at(i).coordenadas);
        }
        glEnd();
    }
    glPopMatrix();
}
#define CRUCETATAMESPACIO 10
void Primitivas::cruceta(bool changeColor){
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINES);
    if (changeColor) {
        glColor3f(0, 1, 1);
        glVertex3d(-0.5, 0, 0);
        glVertex3d(0.5, 0, 0);
        glColor3f(1, 0, 1);
        glVertex3d(0, -0.5, 0);
        glVertex3d(0, 0.5, 0);
        glColor3f(1, 1, 0);
        glVertex3d(0, 0, -0.5);
        glVertex3d(0, 0, 0.5);
    }else{
        for (int i = -CRUCETATAMESPACIO; i<CRUCETATAMESPACIO; i++) {
            if (i == 0) {
                glVertex3f(-CRUCETATAMESPACIO, 0, i);
                glVertex3f(-1, 0, i);
                glVertex3f(1, 0, i);
                glVertex3f(CRUCETATAMESPACIO, 0, i);
                
                glVertex3f(i, 0, -CRUCETATAMESPACIO);
                glVertex3f(i, 0, -1);
                glVertex3f(i, 0, 1);
                glVertex3f(i, 0, CRUCETATAMESPACIO);
                
            }else{
                glVertex3f(-CRUCETATAMESPACIO, 0, i);
                glVertex3f(CRUCETATAMESPACIO, 0, i);
                
                glVertex3f(i, 0, -CRUCETATAMESPACIO);
                glVertex3f(i, 0, CRUCETATAMESPACIO);
            }
        }
        glColor3f(1, 0, 0);
        glVertex3d(-1, 0, 0);
        glVertex3d(1, 0, 0);
        glColor3f(0, 1, 0);
        glVertex3d(0, -1, 0);
        glVertex3d(0, 1, 0);
        glColor3f(0, 0, 1);
        glVertex3d(0, 0, -1);
        glVertex3d(0, 0, 1);

    }
    glColor3f(1, 1, 1);
    glEnd();
    glEnable(GL_TEXTURE_2D);
}
void Primitivas::describeSelecTextureVector(std::vector<PrimitivasSelectTexture> *vector){
    for (unsigned int i = 0; i<vector->size(); i++) {
        std::cout<<i<<".- ";
        this->vCargadorImage->describeTextura(&vCargadorImage->texturas[vector->at(i).cualTextura]);
    }
}
void Primitivas::describePunto(Cg2ValenciaPunto3D punto){
    std::cout<<"{"<<punto.coordenadas[0]<<", "<<punto.coordenadas[1]<<", "<<punto.coordenadas[2]<<"}";
}
#define PRIMITIVAESFERARESOLUCION 20.0
void Primitivas::esferaEstandar(std::vector<PrimitivasSelectTexture> *vector, unsigned int desdeDonde, double diametro, unsigned int porcion){
    if (vector->size()-desdeDonde<PRIMITIVAVRTESFERA) {
        std::cout<<"Llamada Esfera Corrupta\n";
        return;
    }
    double posicionTextura[2] = {0,0};
    double posicionInicio[2] = {0,0};
    double recorrido = diametro*6.28318531;
    double angulos[2];
    double radio = diametro/2;
    double vertices[4][3] {
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0}
    };
    PrimitivasSelectTexture selectActual = vector->at(desdeDonde);
    CargadorImageTexture texturaActual = vCargadorImage->texturas[selectActual.cualTextura];
    glBindTexture(GL_TEXTURE_2D,texturaActual.glIndex);
    if(porcion == 0) porcion = 1;
    for (int i = 0; i<2; i++) {
        posicionInicio[i] = selectActual.posicionInicio[i]/PRIMITIVAESFERARESOLUCION;
        if (texturaActual.cantidadRep[i] == -1) {
            posicionTextura[i] = (1.0/(double)porcion)/PRIMITIVAESFERARESOLUCION;
        }else{
            posicionTextura[i] = ((recorrido/texturaActual.cantidadRep[i])/(double)porcion)/PRIMITIVAESFERARESOLUCION;
        }
    }
    angulos[0] = (6.28318531/porcion)/PRIMITIVAESFERARESOLUCION;
    angulos[1] = 3.141592654/PRIMITIVAESFERARESOLUCION;
    for (int i = 0; i<PRIMITIVAESFERARESOLUCION; i++) {
        for (int j = 0; j<PRIMITIVAESFERARESOLUCION; j++) {
            vertices[0][0] = radio*cos(angulos[0]*i)*sin(angulos[1]*j);
            vertices[0][1] = radio*cos(angulos[1]*j);
            vertices[0][2] = radio*sin(angulos[0]*i)*sin(angulos[1]*j);
            
            vertices[1][0] = radio*cos(angulos[0]*i)*sin(angulos[1]*(j+1));
            vertices[1][1] = radio*cos(angulos[1]*(j+1));
            vertices[1][2] = radio*sin(angulos[0]*i)*sin(angulos[1]*(j+1));
            
            vertices[2][0] = radio*cos(angulos[0]*(i+1))*sin(angulos[1]*(j+1));
            vertices[2][1] = radio*cos(angulos[1]*(j+1));
            vertices[2][2] = radio*sin(angulos[0]*(i+1))*sin(angulos[1]*(j+1));
            
            vertices[3][0] = radio*cos(angulos[0]*(i+1))*sin(angulos[1]*j);
            vertices[3][1] = radio*cos(angulos[1]*j);
            vertices[3][2] = radio*sin(angulos[0]*(i+1))*sin(angulos[1]*j);
            
            glBegin(GL_POLYGON);
            glNormal3dv(vertices[0]);
            glTexCoord2d((posicionTextura[0]*i)+posicionInicio[0], (-posicionTextura[1]*j)+posicionInicio[1]);
            glVertex3dv(vertices[0]);
            
            glNormal3dv(vertices[1]);
            glTexCoord2d((posicionTextura[0]*i)+posicionInicio[0], (-posicionTextura[1]*(j+1))+posicionInicio[1]);
            glVertex3dv(vertices[1]);
            
            glNormal3dv(vertices[2]);
            glTexCoord2d((posicionTextura[0]*(i+1))+posicionInicio[0], (-posicionTextura[1]*(j+1))+posicionInicio[1]);
            glVertex3dv(vertices[2]);
            
            glNormal3dv(vertices[3]);
            glTexCoord2d((posicionTextura[0]*(i+1))+posicionInicio[0], (-posicionTextura[1]*j)+posicionInicio[1]);
            glVertex3dv(vertices[3]);
            
            glEnd();
            
        }
    }
}
void Primitivas::cilindroEstandar(std::vector<PrimitivasSelectTexture> *vector, unsigned int desdeDonde, double diametro, double altura,unsigned int porcion){
    if (vector->size()-desdeDonde<PRIMITIVARVTCILINDRO) {
        std::cout<<"Llamada Cilindro Corrupta\n";
        return;
    }
    double recorridoTapas[2][2]{
        {0,0},
        {0,0}
    };
    double centroTexturas[2][2] = {
        {0,0},
        {0,0}
    };
    
    if (porcion == 0) porcion = 1;
    double posicionTextura[2] = {0,0};
    double posicionInicio = 0;
    double recorrido = diametro*6.28318531;
    double angulo = (6.28318531/porcion)/PRIMITIVAESFERARESOLUCION;
    double radio = diametro/2;
    double vertices[4][3] {
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0}
    };
    
    PrimitivasSelectTexture selectActual = vector->at(desdeDonde);
    CargadorImageTexture texturaActual = vCargadorImage->texturas[selectActual.cualTextura];
    
    PrimitivasSelectTexture selectTapas[2] = {
        vector->at(desdeDonde+1),vector->at(desdeDonde+2)
    };
    CargadorImageTexture texturaTapas[2] = {
        vCargadorImage->texturas[selectTapas[0].cualTextura],vCargadorImage->texturas[selectTapas[1].cualTextura]
    };
    
    posicionInicio = selectActual.posicionInicio[0]/PRIMITIVAESFERARESOLUCION;
    if (texturaActual.cantidadRep[0] == -1) {
        posicionTextura[0] = (1.0/porcion)/PRIMITIVAESFERARESOLUCION;
    }else {
        posicionTextura[0] = ((recorrido/texturaActual.cantidadRep[0])/(double)porcion)/PRIMITIVAESFERARESOLUCION;
    }
    if (texturaActual.cantidadRep[0] == -1) {
        posicionTextura[1] = 1;
    }else{
        posicionTextura[1] = altura/texturaActual.cantidadRep[1];
    }
    
    for (int n = 0; n<2; n++) {
        for (int i = 0; i<2; i++) {
            if (texturaTapas[n].cantidadRep[i] == -1) {
                recorridoTapas[n][i] = 1;
            }else{
                recorridoTapas[n][i] = diametro/texturaTapas[n].cantidadRep[i];
            }
            centroTexturas[n][i]=recorridoTapas[n][i]/2;
            centroTexturas[n][i]=recorridoTapas[n][i]/2;
        }
    }
    
    
    for (int i = 0; i<PRIMITIVAESFERARESOLUCION; i++) {
        vertices[0][0] = radio*cos(angulo*i);
        vertices[0][1] = 0;
        vertices[0][2] = radio*sin(angulo*i);
        
        vertices[1][0] = radio*cos(angulo*(i+1));
        vertices[1][1] = 0;
        vertices[1][2] = radio*sin(angulo*(i+1));
        
        vertices[2][0] = radio*cos(angulo*(i+1));
        vertices[2][1] = altura;
        vertices[2][2] = radio*sin(angulo*(i+1));
        
        vertices[3][0] = radio*cos(angulo*i);
        vertices[3][1] = altura;
        vertices[3][2] = radio*sin(angulo*i);
        
        glBindTexture(GL_TEXTURE_2D,texturaActual.glIndex);
        glBegin(GL_POLYGON);
        glNormal3dv(vertices[0]);
        glTexCoord2d(posicionTextura[0]*i+posicionInicio, selectActual.posicionInicio[1]);
        glVertex3dv(vertices[0]);
        glTexCoord2d(posicionTextura[0]*(i+1)+posicionInicio, selectActual.posicionInicio[1]);
        glVertex3dv(vertices[1]);
        glTexCoord2d(posicionTextura[0]*(i+1)+posicionInicio, selectActual.posicionInicio[1]+posicionTextura[1]);
        glVertex3dv(vertices[2]);
        glTexCoord2d(posicionTextura[0]*i+posicionInicio, selectActual.posicionInicio[1]+posicionTextura[1]);
        glVertex3dv(vertices[3]);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D, texturaTapas[0].glIndex);
        glBegin(GL_POLYGON);
        glNormal3d(0.0, -1.0, 0.0);
        glTexCoord2d(centroTexturas[0][0]+selectTapas[0].posicionInicio[0], centroTexturas[0][1]+selectTapas[0].posicionInicio[1]);
        glVertex3f(0.0, 0.0, 0.0);
        glTexCoord2d(recorridoTapas[0][1]*cos(angulo*i)+selectTapas[0].posicionInicio[0], recorridoTapas[0][1]*sin(angulo*i)+selectTapas[0].posicionInicio[1]);
        glVertex3dv(vertices[0]);
        glTexCoord2d(recorridoTapas[0][1]*cos(angulo*(i+1))+selectTapas[0].posicionInicio[0], recorridoTapas[0][1]*sin(angulo*(i+1))+selectTapas[0].posicionInicio[1]);
        glVertex3dv(vertices[1]);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D, texturaTapas[1].glIndex);
        glBegin(GL_POLYGON);
        glNormal3d(0.0, 1.0, 0.0);
        glTexCoord2d(centroTexturas[1][0]+selectTapas[1].posicionInicio[0], centroTexturas[1][1]+selectTapas[1].posicionInicio[1]);
        glVertex3f(0.0, altura, 0.0);
        glTexCoord2d(recorridoTapas[1][1]*cos(angulo*i)+selectTapas[1].posicionInicio[0], recorridoTapas[1][1]*sin(angulo*i)+selectTapas[1].posicionInicio[1]);
        glVertex3dv(vertices[3]);
        glTexCoord2d(recorridoTapas[1][1]*cos(angulo*(i+1))+selectTapas[1].posicionInicio[0], recorridoTapas[1][1]*sin(angulo*(i+1))+selectTapas[1].posicionInicio[1]);
        glVertex3dv(vertices[2]);
        glEnd();
    }
}
void Primitivas::empiezaAModificarTexture(std::vector<PrimitivasSelectTexture> *v, unsigned char finMod, unsigned char *donde){
    this->vectorPrimitivasST = v;
    this->finModificacion = finMod;
    this->dondeModificar = donde;
    this->setTexture = true;
    punteroVectorPrimitivas = 0;
}
bool Primitivas::teclaDeMenuTextura(unsigned char tecla){
    return false;
}
void Primitivas::escribeMenu(){
    if (this->vectorPrimitivasST->size()==0) std::cout<<"Error Textura vacia :/\n";
    else{
        this->vCargadorImage->describeTextura(&this->vCargadorImage->texturas[vectorPrimitivasST->at(punteroVectorPrimitivas).cualTextura]);
        std::cout<<"Actual: "<<this->punteroVectorPrimitivas<<" Disponibles: "<< this->vectorPrimitivasST->size()<<"\nM->Mostrar Disponibles\nC->Cambiar\nV->Set Value\nX->Salir\nG->Copiar hasta\n";
    }
}
