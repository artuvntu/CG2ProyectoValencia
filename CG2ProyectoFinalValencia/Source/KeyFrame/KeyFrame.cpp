//
//  KeyFrame.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/02/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "KeyFrame.hpp"

void KeyFrame::teclaActivaMenu() {
	this->menuActivado = true;
    std::cout << "Inicio de KeyFrame Menu\n";
    this->escribeMenu();
}
void KeyFrame::teclaDeMenu(unsigned char tecla) {
    if (this->estado == KEYFRAMEESTADOBUSCANDOINT) {
        
    }
    switch (tecla){

    default:
        break;
    }
}
void KeyFrame::escribeMenu(int tipo) {
    switch (tipo) {
    case 0:
        std::cout << "P->Cantidad keyFrame/nO->Movimiento/nI->Guardar/nU->Animacion/n";
        break;
    case 1:
        //9
        std::cout << "/nC->Cambio movimiento/nWSADQEHLKJUITGFHRY/nZ->Salir/nX->Guardar";
        break;
    case 2:
        std::cout << "/nC->Cambio/nN->Nuevo/nR->Reproducir/nV->ReproducirSiempre";
        break;
    default:
        std::cout << "Error Escribir menu KeyFrame/n";
        break;
    }
}
void KeyFrame::cargar() {
    FILE * archivo = fopen(KEYFRAMEPATHFILE, "r");
    if (archivo == NULL) {
        std::cout << "Archivo no encontrado KeyFrame/n";
        this->guardar();
        return;
    }
}
void KeyFrame::guardar() {
    FILE * archivo = fopen(KEYFRAMEPATHFILE, "w");
    unsigned int numeroMovimientos = 0;
    unsigned int numeroAnimaciones = 0;
    unsigned int numeroKeyFrame = 0;
    unsigned int numeroModificacionMovimientos = 0;
    if (archivo == NULL) {
        std::cout << "Archivo no se logro crear KeyFrame/n";
        return;
    }
    fwrite(&numeroMovimientos, sizeof(unsigned int), 1, archivo);
    
}