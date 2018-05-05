//
//  KeyFrame.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/02/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "KeyFrame.hpp"


void KeyFrame::teclaActivaMenu() {
    this->resetAnimacionesEnCurso();
	this->menuActivado = true;
    std::cout << "Inicio de KeyFrame Menu\n";
    this->escribeMenu();
    this->drawCursor();
    this->estado = inicial;
//    std::cout << (int)(unsigned char) '0' << " Hola " << (int)(unsigned char) '9' << std::endl;
}
void KeyFrame::moverMovimiento(int mov){
    double aumento = 0;
    int division = mov/2;
    if (!division) {
        aumento = 359;
    }else{
        if (division == 1) {
            aumento = 0.1;
        }else{
            division -= 2;
            aumento = pow(10, division);
        }
    }
    if (mov%2) {
        aumento = -aumento;
    }
    this->varMovimientos[this->pruebamovimientoActualPuntero].value += aumento;
    glutPostRedisplay();
}
void KeyFrame::teclaDeMenu(unsigned char tecla) {
    switch (this->estado) {
        case inicial:
            this->teclaDeMenuInicial(tecla);
            break;
        case pmovimiento:
            this->teclaDeMenuPruebaMovimiento(tecla);
            break;
        case pmovimientoCambio:
            this->teclaDeMenuPruebaMovimientoCambio(tecla);
            break;
        case animacion:
            this->teclaDeMenuAnimacion(tecla);
            break;
        case animacionCambio:
            this->teclaDeMenuAnimacionCambio(tecla);
            break;
        case animacionNueva:
            this->teclaDeMenuanimacionNueva(tecla);
            break;
        default:
            std::cout<< "KeyFrame Error estado desconocido\n";
            this->teclaActivaMenu();
            break;
    }
}
void KeyFrame::escribeMenu(int tipo) {
    switch (tipo) {
    case 0:
        std::cout << "C->Cantidad movimientos\nP->Prueba Movimiento\nA->Animacion\nS->Salir\n";
        break;
    case 1:
        std::cout << "23[0.1],45[1],67[10],89[100],01[359]\nM->Mostrar\nC->Cambio movimiento\nS->Salir\n";
        break;
    case 2:
        std::cout << "C->Cambio\nN->Nuevo\nR->Reproducir\nF->ReproducirSiempre\nD->Eliminar\nE->Editar";
        break;
    case 3:
        std::cout << "23[0.1],45[1],67[10],89[100],01[359]\nS->Save KeyFrame\nT->SetTime\nC->Cambio Movimiento\nM->Mostrar Movimientos\nR->Set Repeat\nG->Guardar\nQ->Salir (Cuidado no se guardaran Cambios)\n";
        break;
    default:
        std::cout << "Error Escribir menu KeyFrame\n";
        break;
    }
}
void KeyFrame::drawCursor(){
    std::cout<<"CG2ProyectoFinalValencia $ ";
}
void KeyFrame::cargar() {
    FILE * archivo = fopen(KEYFRAMEPATHFILE, "r");
    if (archivo == NULL) {
        std::cout << "Archivo no encontrado KeyFrame\n";
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
        std::cout << "Archivo no se logro crear KeyFrame\n";
        return;
    }
    fwrite(&numeroMovimientos, sizeof(unsigned int), 1, archivo);
    
}
void KeyFrame::inicializar(unsigned int cantidad,std::string nombre){
    if (cantidad > 100) cantidad = 100;
    for (int i = 0; i<cantidad; i++) {
        this->varMovimientos.push_back(KeyFrameMovimiento());
        this->varMovimientos[i].value = 0;
        this->varMovimientos[i].name = nombre + std::to_string(i);
    }
}
void KeyFrame::escribeCabecera(int tipo){
    switch (tipo) {
        case 0:
            //movimiento
            std::cout<< "Actual " << this->pruebamovimientoActualPuntero <<" Nombre: \""<<this->varMovimientos[this->pruebamovimientoActualPuntero].name<< "\" Disponibles " << this->varMovimientos.size() << std::endl;
            break;
        case 1:
            //animacion
            std::cout<<"Actual: "<<this->animcacionActualPuntero << " Disponibles " << this->vAnimaciones.size() << std::endl;
            break;
        case 2:
            //nueva animacion
            std::cout<<"KFUsados: "<<this->temporalAnimacion.cuadrosClaves.size() <<" KFDuracion: "<<this->temporalCuadroClave.duracion;
            this->escribeTipoRepeticionSegun(this->temporalAnimacion.repeticion);
            std::cout<<" ActualMov: " << this->pruebamovimientoActualPuntero <<" Nombre: \""<<this->varMovimientos[this->pruebamovimientoActualPuntero].name<< "\" Disponibles: " << this->varMovimientos.size() << std::endl;
            break;
        default:
            std::cout<<"Error keyframe escribe Cabecera\n";
            break;
    }
}
void KeyFrame::escribeMovimientos(){
    std::cout<< "Posibles movimientos\n";
    for (int i = 0; i<this->varMovimientos.size(); i++) {
        std::cout<<i<<" name "<<this->varMovimientos[i].name<<" valor "<<this->varMovimientos[i].value << std::endl;
    }
}
void KeyFrame::teclaDeMenuInicial(unsigned char tecla){
    std::cout << tecla << std::endl;
    switch (tecla) {
        case 'c':
        case 'C':
            std::cout<< "Tam "<<this->varMovimientos.size() << " Cap: " << this->varMovimientos.capacity() << std::endl;
            break;
        case 'p':
        case 'P':
            if (this->varMovimientos.size()==0) {
                std::cout<<"Error KeyFrame no inicializado\n";
            }else{
                this->escribeCabecera(0);
                this->escribeMenu(1);
                this->estado = pmovimiento;
            }
            break;
        case 'a':
        case 'A':
            this->escribeCabecera(1);
            this->escribeMenu(2);
            this->estado = animacion;
            break;
        case 's':
        case 'S':
            std::cout<< "Fuera de KeyFrame Menu\n";
            this->menuActivado = false;
            this->resetAnimacionesEnCurso();
            this->estado = inicial;
            return;
        default:
            std::cout << "Sin Coincidencia\n";
            this->drawCursor();
            break;
    }
    this->drawCursor();
}
void KeyFrame::teclaDeMenuPruebaMovimiento(unsigned char tecla){
    switch (tecla) {
        case 'c':
        case 'C':
            std::cout <<tecla<<"\nIngresa numero -> ";
            this->temporalIntFromKeyBoard = 0;
            this->estado = pmovimientoCambio;
            break;
        case 's':
        case 'S' :
            std::cout << tecla << std::endl;
            this->teclaActivaMenu();
            break;
        case 'm':
        case 'M':
            this->escribeMovimientos();
            break;
        default:
            if (tecla >= 48 && tecla <= 57) {
                this->moverMovimiento((int)tecla-48);
            }
            break;
    }
}
void KeyFrame::teclaDeMenuPruebaMovimientoCambio(unsigned char tecla,KeyFrameEstados proximoestado){
    if (tecla >= 48 && tecla <= 57){
        std::cout << (tecla - 48);
        this->temporalIntFromKeyBoard = (this->temporalIntFromKeyBoard * 10)+(tecla - 48);
        if (this->temporalIntFromKeyBoard >= this->varMovimientos.size()){
            std::cout<<"\nNumero mayor a los disponibles\n";
            this->drawCursor();
            this->estado = proximoestado;
        }
    }else if (tecla == 13){
        this->pruebamovimientoActualPuntero = this->temporalIntFromKeyBoard;
        this->temporalIntFromKeyBoard = 0;
        this->escribeCabecera(0);
        this->drawCursor();
        this->estado = proximoestado;
    }else{
        std::cout<<"\nCancelado\n";
        this->estado = proximoestado;
        this->drawCursor();
    }
}
void KeyFrame::teclaDeMenuAnimacion(unsigned char tecla){
    std::cout<<tecla<<std::endl;
    switch (tecla) {
        case 'c':
        case 'C':
            if (this->vAnimaciones.size() == 0) {
                std::cout<<"Primero Crea una\n";
            }else{
                std::cout <<tecla<<"\nIngresa numero -> ";
                this->temporalIntFromKeyBoard = 0;
                this->estado = animacionCambio;
            }
            this->drawCursor();
            break;
        case 's':
        case 'S':
            this->teclaActivaMenu();
            break;
        case 'n':
        case 'N':
            //                  Try With
            this->temporalAnimacion = keyFrameAnimacion();
            this->temporalCuadroClave = KeyFrameKeyFrame();
            this->temporalMoveMovimiento = KeyFrameMoveMovimiento();
            this->escribeCabecera(2);
            this->escribeMenu(3);
            this->drawCursor();
            this->estado = animacionNueva;
            break;
        case 'R':
        case 'r':
//            Reproducir
            break;
        case 'D':
        case 'd':
//            Delete
            break;
        case 'E':
        case 'e':
//            Editar
            break;
        case 'F':
        case 'f':
//            Forever
            break;
        default:
            std::cout<<"\nKeyFrame::teclaDeMenuAnimacion Fuera Menu\n";
            this->drawCursor();
            break;
    }
}
void KeyFrame::teclaDeMenuAnimacionCambio(unsigned char tecla){
    if (tecla >= 48 && tecla <= 57){
        std::cout << (tecla - 48);
        this->temporalIntFromKeyBoard = (this->temporalIntFromKeyBoard * 10)+(tecla - 48);
        if (this->temporalIntFromKeyBoard >= this->vAnimaciones.size()){
            std::cout<<"\nNumero mayor a los disponibles\n";
            this->drawCursor();
            this->estado = animacion;
        }
    }else if (tecla == 13){
        this->animcacionActualPuntero = this->temporalIntFromKeyBoard;
        this->temporalIntFromKeyBoard = 0;
        this->escribeCabecera(1);
        this->drawCursor();
        this->estado = animacion;
    }else{
        std::cout<<"\nCancelado\n";
        this->estado = animacion;
        this->drawCursor();
    }
}
void KeyFrame::teclaDeMenuanimacionNueva(unsigned char tecla){
    std::cout << tecla;
    unsigned char temporalTipoRepeticion;
    switch (tecla) {
        case 'S':
        case 's':
            if (this->temporalCuadroClave.movimientos.size()==0&&this->temporalCuadroClave.duracion == 0) {
                std::cout<< "Keyframe vacio Agrega movimiento\n";
            }else{
                std::cout<<"Key Frame Guardado\n";
                this->temporalAnimacion.cuadrosClaves.push_back(this->temporalCuadroClave);
                this->temporalCuadroClave = KeyFrameKeyFrame();
            }
            this->drawCursor();
            break;
        case 'c':
        case 'C':
            if (this->vAnimaciones.size() == 0) {
                std::cout<<"Primero Crea una\n";
            }else{
                std::cout <<tecla<<"\nIngresa numero -> ";
                this->temporalIntFromKeyBoard = 0;
                this->estado = animacionCambio;
            }
            this->drawCursor();
            break;
        case 't':
        case 'T':
            std::cout<< "\nEn consola digite numero-> ";
            std::cin>> this->temporalCuadroClave.duracion;
            this->escribeCabecera(2);
            this->drawCursor();
            break;
        case 'M':
        case 'm':
            this->escribeMovimientos();
            this->drawCursor();
            break;
        case 'r':
        case 'R':
            this->escribeTiposRepeticion();
            std::cout<<"En consola digite tipo Repeticion: ";
            std::cin >> temporalTipoRepeticion;
            this->temporalAnimacion.repeticion = (KeyFrameTipoRepeticion) temporalTipoRepeticion;
            this->drawCursor();
            break;
        case 'G':
        case 'g':
            if (this->temporalAnimacion.cuadrosClaves.size() == 0) {
                std::cout<<"\nHey primero crea un cuadro clave XD\n";
                this->drawCursor();
            }else{
                std::cout<<"\nAnimacion Guardada\n";
                this->vAnimaciones.push_back(this->temporalAnimacion);
                this->temporalAnimacion = keyFrameAnimacion();
                if (this->temporalAnimacion.repeticion == circular || this->temporalAnimacion.repeticion == regresivoCircular) {
                    this->vAnimacionesForever.push_back(this->vAnimaciones.size()-1);
                }
                this->describeAnimacion(this->vAnimaciones.back());
                this->escribeMenu(2);
                this->drawCursor();
                this->estado = animacion;
            }
            break;
        case 'Q':
        case 'q':
            this->teclaActivaMenu();
            break;
        default:
            break;
    }
}
void KeyFrame::escribeTiposRepeticion(){
    std::cout<<"\nnulo=0,volverAlInicio=1,circular=2,regresivo=3,regresvoCircular=4\n";
}
void KeyFrame::escribeTipoRepeticionSegun(KeyFrameTipoRepeticion rep){
    switch (rep) {
        case nulo:
            std::cout<<"Nulo ";
            break;
        case volverAlInicio:
            std::cout<<"Volver al inicio ";
            break;
        case circular:
            std::cout<<"Circular ";
            break;
        case regresivo:
            std::cout<<"Regresivo ";
            break;
        case regresivoCircular:
            std::cout<<"Regresivo Circular ";
            break;
        default:
            break;
    }
}
void KeyFrame::describeAnimacion(keyFrameAnimacion animacion){
    std::cout<<"Animacion Cuadros: "<<animacion.cuadrosClaves.size();
    this->escribeTipoRepeticionSegun(animacion.repeticion);
    std::cout<<std::endl;
}
int valor = 0;
void KeyFrame::actualizaAnimacion(){
    if(!this->menuActivado){
        std::cout << " " << valor++ << " \n";
    }else {
        if (this->reproduccionExterna != -1) {
            this->reproduceAnimacion(this->vAnimaciones[this->reproduccionExterna]);
        }
    }
}
void KeyFrame::resetAnimacionesEnCurso(){
    for (auto i : this->varMovimientos) {
        i.value = 0;
    }
}
void KeyFrame::reproduceAnimacion(keyFrameAnimacion animacion){
    int aumento = 1;
    if (!animacion.ascendente) aumento = -1;
    if ((long)animacion.cuadroActual + aumento <= 0 ) {
        
    }else{
        
    }
    
}
