//
//  Camera.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/16/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "Camera.hpp"

void Camara::easyPosition(){
    gluLookAt(this->XYZ[0], this->XYZ[1], this->XYZ[2], this->XYZ[3], this->XYZ[4], this->XYZ[5], this->XYZ[6], this->XYZ[7], this->XYZ[8]);
//    glTranslated(this->XYZ[0], this->XYZ[1], this->XYZ[2]);
//    glRotated(this->Angles[0], 0, 1, 0);
//    glRotated(this->Angles[1], 1, 0, 0);
//    glRotated(this->Angles[2], 0, 0, 1);
//    for (auto i: this->XYZ) {
//        std::cout << " " << i;
//    }
//    for (auto i : this->Angles) {
//        std::cout << " " << i;
//    }
//    std::cout << std::endl;
}
void Camara::keyboardMove(int type,double intensidad){
    int realType = 0;
    double m;
    double tm[3];
    realType += (type/2)%6;
    if (type%2) {
         intensidad = -intensidad;
    }
    m = intensidad * this->multipler[realType+(6*(type/12))];
//    std::cout << "LETRA "<<realType  <<" DIRECCION "<<intensidad <<" ATURBO "<<  this->multipler[realType+(6*(type/12))]<<" DIV "<< type/12 <<std::endl;

    switch (realType) {
        case 0:
            tm[0] = (cos(this->Angles[1])*sin(Angles[0]));
            tm[1] = (sin(this->Angles[1]));
            tm[2] = (cos(this->Angles[1])*cos(Angles[0]));
            for(int i=0;i<3;i++){
                this->XYZ[i] += m * tm[i];
                this->XYZ[i+3] += m *tm[i] ;
            }
            break;
        case 1:
            tm[0] = (sin(Angles[0]+1.57));
            tm[1] = 0;
            tm[2] = (cos(Angles[0]+1.57));
            for(int i=0;i<3;i++){
                this->XYZ[i] += m * tm[i];
                this->XYZ[i+3] += m *tm[i] ;
            }
            break;
        case 2:
            tm[0] = (cos(this->Angles[1]+1.57)*sin(Angles[0]));
            tm[1] = (sin(this->Angles[1]+1.57));
            tm[2] = (cos(this->Angles[1]+1.57)*cos(Angles[0]));
            for(int i=0;i<3;i++){
                this->XYZ[i] += m * tm[i];
                this->XYZ[i+3] += m *tm[i] ;
            }

            break;
        case 3:
            this->Angles[0] += m;
            tm[0] = (cos(this->Angles[1])*sin(Angles[0]));
            tm[1] = (sin(this->Angles[1]));
            tm[2] = (cos(this->Angles[1])*cos(Angles[0]));
            this->XYZ[3] = this->XYZ[0]+tm[0];
            this->XYZ[4] = this->XYZ[1]+tm[1];
            this->XYZ[5] = this->XYZ[2]+tm[2];
            
            break;
        case 4:
            this->Angles[1] += m;
            tm[0] = (cos(this->Angles[1])*sin(Angles[0]));
            tm[1] = (sin(this->Angles[1]));
            tm[2] = (cos(this->Angles[1])*cos(Angles[0]));
            this->XYZ[3] = this->XYZ[0]+tm[0];
            this->XYZ[4] = this->XYZ[1]+tm[1];
            this->XYZ[5] = this->XYZ[2]+tm[2];
            break;
        case 5:
            this->Angles[2] += m;
            this->XYZ[6] = cos(Angles[2]);
            this->XYZ[7] = sin(Angles[2]);
            break;
        default:
            std::cout<<"Valor no legible Camara" << std::endl;
            return;
            break;
    }
    glutPostRedisplay();
}

