//
//  Primitivas.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/26/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "../../Libraries.hpp"

#define GROSORPARED 2
#define ALTOPARED 25

class Primitivas {
public:
    enum TypePared{Normal, Ventana, Puerta};
    void mundo(GLuint suelo,int inicio,int fin, GLuint cielo, GLuint bobeda);
    void setTextPared(int cantidad, ... );
    void setTamTextPared(int cantidad, ...);
    void resetTamTextPared();
    void pared(int repeticionText,unsigned int typeText,TypePared type,double distancia);
//private:
    void prismaEstandar(unsigned int typeText,double x,double y, double z);
    GLuint textPared[6] = {0, 0, 0, 0, 0, 0};
    int tamTextPared[6] = {1, 1, 1, 1, 1, 1};
};

