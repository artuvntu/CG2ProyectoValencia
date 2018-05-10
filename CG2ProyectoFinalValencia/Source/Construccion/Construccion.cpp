//
//  Construccion.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/8/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "Construccion.hpp"

void Construccion::inicializar(Primitivas *primitivasactual, CargadorImage *cargadorImageactual, KeyFrame *keyFrameactual){
    this->vPrimitivas = primitivasactual;
    this->vCargadorImage = cargadorImageactual;
    this->vKeyFrame = keyFrameactual;
}
void Construccion::teclaActivaMenu(){
    this->estado = inicial;
}
void Construccion::escribeMenu(Construccion::ConstruccionEstados estado){
    switch (estado) {
        case inicial:
            std::cout<<"S->Salir\n";
            break;
            
        default:
            std::cout<<"Construccion escribe menu estado no encontrado\n";
            break;
    }
}
void Construccion::drawCursor(Construccion::ConstruccionEstados estado){
    std::cout<<"CG2ProyectoFinalValenciaC " << " $ ";
}
void Construccion::teclaDeMenu(unsigned char tecla){
    
}
