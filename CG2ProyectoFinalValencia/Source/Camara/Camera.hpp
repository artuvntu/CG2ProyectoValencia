//
//  Camera.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/16/18.
//  Copyright © 2018 vApps. All rights reserved.
//
#include "../../Libraries.hpp"

class Camara{
public:
    void easyPosition();
    void move(int type,int intesidad = 1);
private:
//    w,s,a,d,q,e,h,l,j,k,u,i MINMAY
    double movement[6] = {0, 0, 0, 0, 0, 0};
    int multipler[12] = {1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2};
    double XYZ[9] = {0, 0, 0, 0, 0, -1, 0, 1, 0};
};
struct _tipoMovimiento {
    
}typedef TipoMovimiento;
