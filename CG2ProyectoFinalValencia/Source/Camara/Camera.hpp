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
    void keyboardMove(int type,double intesidad = 1);
    void mouseMove(int x,int y);
private:
//    w,s,a,d,q,e,h,l,j,k,u,i MINMAY
    double multipler[12] = {1, 1, 1, 0.2, 0.2, 0.2, 1.5, 1.5, 1.5, 0.3, 0.3, 0.3};
    double XYZ[9] = {0, 15, 0, 0, 15, -1, 0, 1, 0};
    double Angles[3] = {3.14,0,1.57};
    
};
//struct _tipoMovimiento {
//    
//}typedef TipoMovimiento;
