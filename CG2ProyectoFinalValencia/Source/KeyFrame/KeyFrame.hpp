//
//  KeyFrame.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/02/18.
//  Copyright © 2018 vApps. All rights reserved.
//
#include "../../Libraries.hpp"

#define KEYFRAMEESTADONORMAL 0
#define KEYFRAMEESTADOBUSCANDOINT 1
#define KEYFRAMEPATHFILE "CG2ProyectoFinalValencia.vkf" //vKeyFrame

class KeyFrame{
public:
	void teclaActivaMenu();
    void teclaDeMenu(unsigned char tecla);
	bool menuActivado = false;
    void guardar();
    void cargar();
//private:
    unsigned int estado = KEYFRAMEESTADONORMAL;
    void escribeMenu(int tipo = 0);
};
struct _keyframemovimiento{
    unsigned char typo;
    double cantidad;
    double step; 
}typedef KeyFrameMovimiento;