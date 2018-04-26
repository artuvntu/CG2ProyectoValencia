//
//  Camera.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/16/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "Camera.hpp"

void Camara::easyPosition(){
    std::cout << "a";
    gluLookAt(this->XYZ[0], this->XYZ[1], this->XYZ[2], this->XYZ[3], this->XYZ[4], this->XYZ[5], this->XYZ[6], this->XYZ[7], this->XYZ[8]);
}
void Camara::move(int type,int intensidad){
    std::cout << "MOVE \n";
    int realType = 0;
    realType += type/4;
    if (type%2) {
         intensidad = -intensidad;
    }
    this->movement[realType] += intensidad * this->multipler[realType*2+(type/2%2)];
    std::cout << realType  <<" "<<intensidad <<" "<<this->movement[realType]<<std::endl;
    switch (realType) {
        case 0:
            std::cout <<"Switch\n";
            this->XYZ[2] = movement[realType];
            this->XYZ[5] = movement[realType] + 1;
            break;
        case 1:
            
        default:
            break;
    }
}

