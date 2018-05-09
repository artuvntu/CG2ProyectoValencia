//
//  Camera.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/16/18.
//  Copyright © 2018 vApps. All rights reserved.
//
#include "../../Libraries.hpp"

#define CAMARAPATHFILE "CG2ProyectoFinalValencia.vcam" //vCamara




class Camara{
public:
    enum CamaraEstados{
        inicial,buscandoUInt
    };
    void easyPosition();
    void keyboardMove(int type,double intesidad = 1);
    void mouseMove(int x,int y);
    void inicializar();
    void teclaActivaMenu();
    void teclaDeMenu(unsigned char tecla);
private:
    void teclaDeMenuInicial(unsigned char tecla);
    void teclaDeMenuBuscandoUInt(unsigned char tecla);
    void cargar();
    void guardar();
//    w,s,a,d,q,e,h,l,j,k,u,i MINMAY
    double multipler[12] = {1, 1, 1, 0.2, 0.2, 0.2, 1.5, 1.5, 1.5, 0.3, 0.3, 0.3};
    double XYZ[9] = {0, 15, 0, 0, 15, -1, 0, 1, 0};
    double Angles[3] = {3.14,0,1.57};
    
    CamaraEstados estado = inicial;
};
//struct _tipoMovimiento {
//    
//}typedef TipoMovimiento;
