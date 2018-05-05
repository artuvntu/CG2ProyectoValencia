//
//  Primitivas.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/26/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "../../Libraries.hpp"
#include "../KeyFrame/KeyFrame.hpp"
#include "../CargadorImage/CargadorImage.hpp"
#define GROSORPARED 1

#define ALTOPARED 25

#define PRIMITIVASTEXTPARED 0
#define PRIMITIVASTEXTPAREDTAM 1
#define PRIMITIVASTEXTPAREDINICIOX 2
#define PRIMITIVASTEXTPAREDINICIOY 3

class Primitivas {
public:
    enum TypePared{Normal, Ventana, Puerta};
    void mundo(GLuint suelo,int inicio,int fin, GLuint cielo, GLuint bobeda);
    void setTextPared(int typo,int cantidad, ... );
    void setTextParedTam(int cantidad, ...);
    void resetTextParedTam();
    void setTextParedInicioX(int cantidad, ...);
    
    void pared(int repeticionText,unsigned int typeText,TypePared type,double distancia);
//private:
    void prismaEstandar(unsigned int typeText,double x,double y, double z,int fondo=1,int tapa=0);
    GLuint textPared[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    double textParedTam[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    double textParedInicioX[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    double textParedInicioY[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    KeyFrame *vKeyFrame;
    CargadorImage *vCargadorImage;
};
