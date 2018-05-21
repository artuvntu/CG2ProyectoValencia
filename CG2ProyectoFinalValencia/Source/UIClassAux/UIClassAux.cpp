//
//  UIClassAux.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/18/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "UIClassAux.hpp"

void UIClassAux::empezarABuscarUInt(unsigned int *dondeGuardar, unsigned int max, unsigned char *escribirEstado
                                    , unsigned char cambioCorrecto, unsigned char cambioCancelar, unsigned char parametroEjecucionCorrecto, unsigned char parametroCancelar, unsigned char * dondeparametro){
    if (max==0) {
        std::cout<<"No hay de donde elegir\n";
        *this->dondeEscribirEstado = cambioCancelar;
    }
    this->dondeGuardarUInt = dondeGuardar;
    this->maximo = max;
    this->dondeEscribirEstado = escribirEstado;
    this->cambioCorrecto = cambioCorrecto;
    this->cambioCancelar = cambioCancelar;
    this->parametroEjecucionCorrecto = parametroEjecucionCorrecto;
    this->parametroEjecucionCorrecto = parametroEjecucionCorrecto;
    this->parametroEjecucionCancelar = parametroCancelar;
    this->dondeGuardarParametroEjecucion = dondeparametro;
    this->temporalUIntKeyBoard = 0;
    this->estadoActual = buscandoUInt;
    this->escribeMenu();
    this->drawCursor();
}
void UIClassAux::empezarABuscarString(char *dondeGuardar, unsigned int max, unsigned char *escribirEstado, unsigned char cambioCorrecto, unsigned char cambioCancelar, unsigned char parametroEjecucionCorrecto, unsigned char parametroCancelar, unsigned char *dondeParametro){
    if (max==0) {
        std::cout<<"No hay de donde guardar\n";
        *this->dondeEscribirEstado = cambioCancelar;
    }
    this->dondeGuardarChar = dondeGuardar;
    this->maximo = max;
    this->dondeEscribirEstado = escribirEstado;
    this->cambioCorrecto = cambioCorrecto;
    this->cambioCancelar = cambioCancelar;
    this->parametroEjecucionCorrecto = parametroEjecucionCorrecto;
    this->temporalStringKeyBoard[0] = '\0';
    this->parametroEjecucionCorrecto = parametroEjecucionCorrecto;
    this->parametroEjecucionCancelar = parametroCancelar;
    this->dondeGuardarParametroEjecucion = dondeParametro;
    this->puntero = 0;
    this->estadoActual = buscandoString;
    this->escribeMenu();
    this->drawCursor();
}
bool UIClassAux::teclaDeMenu(unsigned char tecla){
    switch (estadoActual) {
        case buscandoString:
            return this->teclaDeMenuBuscandoString(tecla);
            break;
        case buscandoUInt:
            return this->teclaDeMenuBuscandoUInt(tecla);
            break;
        case sinBusqueda:
            std::cout<<"Problemas no inicializado\n";
        default:
            return false;
            break;
    }
}
bool UIClassAux::teclaDeMenuBuscandoUInt(unsigned char tecla){
    if (tecla >= 48 && tecla <= 57) {
        std::cout << (tecla -48);
        this->temporalUIntKeyBoard = (this->temporalUIntKeyBoard * 10)+(tecla - 48);
        if (this->temporalUIntKeyBoard >= this->maximo){
            std::cout<<"\nNumero mayor a los disponibles\n";
            *this->dondeEscribirEstado = this->cambioCancelar;
            this->estadoActual = sinBusqueda;
            *this->dondeGuardarParametroEjecucion = this->parametroEjecucionCancelar;
            return true;
        }
    }else if (tecla == 13){
        std::cout <<std::endl;
        *this->dondeGuardarUInt = this->temporalUIntKeyBoard;
        this->temporalUIntKeyBoard = 0;
        *this->dondeEscribirEstado = this->cambioCorrecto;
        this->estadoActual = sinBusqueda;
        *this->dondeGuardarParametroEjecucion = this->parametroEjecucionCorrecto;
        return true;
    }else if (tecla == 127){
        if (this->temporalUIntKeyBoard == 0) {
            std::cout<<"\nCancelado\n";
            this->temporalUIntKeyBoard = 0;
            *this->dondeEscribirEstado = this->cambioCancelar;
            this->estadoActual = sinBusqueda;
            *this->dondeGuardarParametroEjecucion = this->parametroEjecucionCancelar;
            return true;
        }else{
            std::cout <<std::endl;
            this->temporalUIntKeyBoard = this->temporalUIntKeyBoard/10;
            this->drawCursor();
        }
    }else{
        std::cout<<"\nCancelado\n";
        this->temporalUIntKeyBoard = 0;
        *this->dondeEscribirEstado = this->cambioCancelar;
        this->estadoActual = sinBusqueda;
        *this->dondeGuardarParametroEjecucion = this->parametroEjecucionCancelar;
        return true;
    }
    return false;
}
void UIClassAux::escribeMenu(){
    switch (this->estadoActual) {
        case buscandoString:
        case buscandoUInt:
            std::cout<<"SUPR->Cancelar\tENTER->Guardar\tBCAKDELETE->Retroceder\n";
            break;
        case sinBusqueda:
        default:
            std::cout<<"No se ha inicializado busqueda\n";
            break;
    }
}
void UIClassAux::drawCursor(){
    std::cout<<"CG2ProyectoFinalValenciaB "<<this->estadorToChar[(unsigned char)this->estadoActual]<<" $ ";
    switch (this->estadoActual) {
        case buscandoString:
            std::cout<<this->temporalStringKeyBoard;
            break;
        case buscandoUInt:
            if (this->temporalUIntKeyBoard!= 0) {
                std::cout<<this->temporalUIntKeyBoard;
            }
        case sinBusqueda:
        default:
            break;
    }
}
bool UIClassAux::teclaDeMenuBuscandoString(unsigned char tecla){
    if (tecla == 127) {
        if (puntero == 0) {
            std::cout<<"\nCancelar\n";
            this->temporalStringKeyBoard[0] = '\0';
            this->puntero = 0;
            *this->dondeEscribirEstado = this->cambioCancelar;
            this->estadoActual = sinBusqueda;
        }else{
            std::cout <<std::endl;
            puntero--;
            temporalStringKeyBoard[puntero] = '\0';
            this->drawCursor();
        }
        *this->dondeGuardarParametroEjecucion = this->parametroEjecucionCancelar;
        return true;
    }
    if (puntero>=maximo||tecla==13) {
        std::cout<<"\nTerminado\n";
        this->temporalStringKeyBoard[puntero] = '\0';
        memcpy(this->dondeGuardarChar, this->temporalStringKeyBoard, sizeof(char)*puntero+1);
        *this->dondeEscribirEstado = this->cambioCorrecto;
        this->puntero = 0;
        this->temporalStringKeyBoard[0] = '\0';
        this->estadoActual = sinBusqueda;
        *this->dondeGuardarParametroEjecucion = parametroEjecucionCorrecto;
        return true;
    }
    if ((tecla >= 48 && tecla <= 57)||(tecla >= 65 && tecla <= 90)||(tecla >= 97 && tecla <= 122)) {
        std::cout<<tecla;
        this->temporalStringKeyBoard[puntero] = tecla;
        puntero++;
    }
    return false;
}
void UIClassAux::empezarABuscarMove(double *ejex, double *ejey, double *ejez, double *ejeDx, double *ejeDy, double *ejeDz, double *ejeAx, double *ejeAy, double *ejeAz, double minMove, double maxMove, double minMoveA, double maxMoveA){
    if (ejex == NULL) this->dondeMove[0] = &basura;
    else this->dondeMove[0] = ejex;
    if (ejey == NULL) this->dondeMove[1] = &basura;
    else this->dondeMove[1] = ejey;
    if (ejez == NULL) this->dondeMove[2] = &basura;
    else this->dondeMove[2] = ejez;
    if (ejeDx == NULL) this->dondeMove[3] = &basura;
    else this->dondeMove[3] = ejeDx;
    if (ejeDy == NULL) this->dondeMove[4] = &basura;
    else this->dondeMove[4] = ejeDy;
    if (ejeDz == NULL) this->dondeMove[5] = &basura;
    else this->dondeMove[5] = ejeDz;
    if (ejeAx == NULL) this->dondeMove[6] = &basura;
    else this->dondeMove[6] = ejeAx;
    if (ejeAy == NULL) this->dondeMove[7] = &basura;
    else this->dondeMove[7] = ejeAy;
    if (ejeAz == NULL) this->dondeMove[8] = &basura;
    else this->dondeMove[8] = ejeAz;
    this->estadoActual = moveMovimiento;
    deltaMove[0] = minMove;
    deltaMove[1] = minMoveA;
    deltaMove[2] = maxMove;
    deltaMove[3] = maxMoveA;
}
bool UIClassAux::teclaMove(unsigned char tecla){
    double aumento = 0;
    int fast = 0;
    int wich = 0;
    int delta = 0;
    int axis = 0;
    for (int i = 0; i<6*3*2; i++) {
        if (this->teclasMoveMoviemito[i]==tecla) {
            fast = i%18;
            wich = fast%6;
            axis = fast/6;
            if (i/18) delta = 2;
            if(axis==2)aumento = deltaMove[1+delta];
            else aumento = deltaMove[0+delta];
            if (wich%2)aumento = -aumento;
            *this->dondeMove[(wich/2)+(axis*3)] += aumento;
            return true;
        }
    }
    return false;
}
