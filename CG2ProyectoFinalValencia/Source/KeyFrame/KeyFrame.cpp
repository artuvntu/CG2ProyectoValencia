//
//  KeyFrame.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/02/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "KeyFrame.hpp"
#define MAXINT 99999
#define MAXTIPOSREPETICION 6

#define KEYFRAMEVERSIONCABECERA 0x20FF

void KeyFrame::escribeMenu() {
    switch (estado) {
        case inicialKF:
            if (vAnimaciones.size()!=0) {
                std::cout<<"V->Set Global Activar animaciones Forever "<<this->animacionInfinitasActivas<<"\n3->Actual Forever "<<this->vAnimaciones[animacionActualPuntero].repetitivo<<"\nC->Cambiar Animacion\nP->Editar Animacion\nX->Eliminar Animacion\nB->Actual Regresivo "<<this->vAnimaciones[animacionActualPuntero].regresivo<<"\nm->Mostrar Animaciones Disponibles\n5->Reproducir\n";
            }else std::cout<<"Crea una Animacion\n";
            if (varMovimientos.size()!=0) {
                std::cout<<"M->Mostrar Move\n4->Prueba Movimiento\n";
            }else{
                std::cout<<"Crea objetos con move Movimiento\n";
            }
            std::cout << "1->Guardar\n2->Cargar\nN->Nuevo\nZ->Salir\n";
            break;
        case pmovimiento:
            if (varMovimientos.size()!=0) {
                std::cout<<"C->Cambio MoveMoviemiento\nM->Mostrar Disponibles\n3->ResetActual\n";
            }else {
                std::cout<<"Crea objetos con Move Movimiento\n";
            }
            std::cout<<"Z->Salir\n";
            break;
        case buscandoUIntKF:
            vUIClassAux.escribeMenu();
            break;
        case editandoCuadroClave:
            if (varMovimientos.size()!=0) {
                if (vAnimaciones[animacionActualPuntero].cuadrosClaves.size()!=0) {
                    std::cout<<"C->Cambio cuadro clave\nM->Mostrar cuadros clave\nm->Mostrar MoveMv Utilizados\nX->Borrar Cuadro clave\nB->Set time\nP->Cambiar Move Moviemiento\n4->Regresar al principio\n3->ResetActual\n";
                }
                std::cout<<"N->Nuevo cuadro Clave\nZ->Salir\n";
            }else{
                std::cout<<"Crea objetos con Move Movimiento\n";
            }
            break;
        default:
            std::cout << "Error Escribir menu KeyFrame\n";
            break;
    }
}
void KeyFrame::drawCursor(){
    if (estado == buscandoUIntKF) {
        vUIClassAux.drawCursor();
        return;
    }
    std::cout<<"CG2ProyectoFinalValenciaKF " << this->KeyFrameEstadosToChar[(unsigned char)estado] << " $ ";
}
void KeyFrame::teclaActivaMenu() {
    vAnimacionesForever.clear();
    if (this->varMovimientos.size()==0) {
        std::cout<<"Crea objetos con Move Movimiento\n";
        return;
    }
    std::cout << "Inicio de KeyFrame Menu\n";
    this->menuActivado = true;
    this->estado = inicialKF;
//    this->keyframeActualPuntero = 0;
//    this->animacionActualPuntero = 0;
    escribeMenu();
    drawCursor();
}
void KeyFrame::teclaDeMenu(unsigned char tecla) {
    guardar();
    if (tecla == '|'&&this->estado!=buscandoUIntKF) {
        std::cout<<std::endl;
        this->escribeMenu();
        drawCursor();
        return;
    }
    switch (this->estado) {
        case inicialKF:
            this->teclaDeMenuInicial(tecla);
            break;
        case pmovimiento:
            this->teclaDeMenuPruebaMovimiento(tecla);
            break;
        case buscandoUIntKF:
            if(this->vUIClassAux.teclaDeMenu(tecla)){
                ejecutaAccionBuscarUInt();
            }
            break;
        case editandoCuadroClave:
            this->teclaDeMenuEditarKF(tecla);
            break;
        default:
            std::cout<< "KeyFrame Error estado desconocido\n";
            break;
    }
}
void KeyFrame::teclaDeMenuInicial(unsigned char tecla){
    bool salta = true;
    bool auxBolean = true;
    if (vAnimaciones.size()!=0) {
        switch (tecla) {
            case 'v':
            case 'V':
                std::cout<<"AnimacionesFoever: ";
                if (this->animacionInfinitasActivas) {
                    std::cout<<"Desactivadas\n";
                    this->animacionInfinitasActivas = false;
                    pararTodaAnimacionDisponible();
                }else{
                    std::cout<<"Activadas\n";
                    this->animacionInfinitasActivas = true;
                }
                break;
            case 'c':
            case 'C':
                std::cout<<"Cambiar Animacion\n";
                escribeAnimacionesDisponibles();
                this->estado = buscandoUIntKF;
                this->vUIClassAux.empezarABuscarUInt(&animacionActualPuntero, (unsigned int) vAnimaciones.size(), (unsigned char *)&estado, (unsigned char) inicialKF, (unsigned char) inicialKF, (unsigned char)nadaKF, (unsigned char) nadaKF,(unsigned char*) &tipoAccionDespuesBuscarInt);
                break;
            case 'p':
            case 'P':
                if (varMovimientos.size()!=0) {
                    std::cout<<"Editando Key Frames\n";
                    if (moveMovimientoActualPuntero>=varMovimientos.size()) {
                        std::cout<<"var movieminto fuera de rango\n";
                        moveMovimientoActualPuntero = (unsigned int) varMovimientos.size()-1;
                    }
                    describeAnimacion(&vAnimaciones[animacionActualPuntero]);
                    if (this->vAnimaciones[animacionActualPuntero].cuadrosClaves.size()!=0) {
                        this->keyframeActualPuntero = (unsigned int) this->vAnimaciones[animacionActualPuntero].cuadrosClaves.size()-1;
                        recrearAnimacionHastaFinal(&vAnimaciones[animacionActualPuntero], keyframeActualPuntero);
                        if (vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].movimientos.size()!=0) {
                            this->movimientoActualPuntero = (unsigned int) vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].movimientos.size()-1;
                                moveMovimientoActualPuntero = vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].movimientos[movimientoActualPuntero].cual;
                        }else{
                            movimientoActualPuntero = 0;
                            vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].movimientos.push_back(KeyFrameMoveMovimiento());
                            vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].movimientos[movimientoActualPuntero].cual = moveMovimientoActualPuntero;
                            vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].movimientos[movimientoActualPuntero].posicionInicial = varMovimientos[vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].movimientos[movimientoActualPuntero].cual].value;
                        }
                        this->vUIClassAux.empezarABuscarMove(&varMovimientos[vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].movimientos[movimientoActualPuntero].cual].value,NULL, NULL, NULL, NULL, NULL, &varMovimientos[vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].movimientos[movimientoActualPuntero].cual].value, NULL, NULL, 0.1, 1, 22.5, 90);
                    }else this->keyframeActualPuntero = 0;
                    this->estado = editandoCuadroClave;
                    escribeMenu();
                }else std::cout<<"Crea un objeto antes\n";
                drawCursor();
                break;
            case 'X':
            case 'x':
                if (animacionActualPuntero<vAnimaciones.size()) {
                    std::cout<<"Eliminando";
                    this->describeAnimacion(&vAnimaciones[animacionActualPuntero]);
                    vAnimaciones.erase(vAnimaciones.begin()+animacionActualPuntero);
                    if (animacionActualPuntero>=vAnimaciones.size()) {
                        animacionActualPuntero =(unsigned int) vAnimaciones.size()-1;
                    }
                }else std::cout<<"Puntero fuera de rango\n";
                drawCursor();
                break;
            case 'B':
            case 'b':
                std::cout<<"Regresivo ";
                this->vAnimaciones[animacionActualPuntero].regresivo = !this->vAnimaciones[animacionActualPuntero].regresivo;
                if (this->vAnimaciones[animacionActualPuntero].regresivo) std::cout<<"Activado\n";
                else std::cout<<"Desactivado\n";
                drawCursor();
                break;
            case '3':
                std::cout<<"Repetitivo ";
                this->vAnimaciones[animacionActualPuntero].repetitivo = !this->vAnimaciones[animacionActualPuntero].repetitivo;
                if(this->vAnimaciones[animacionActualPuntero].repetitivo)std::cout<<"Activado\n";
                else std::cout<<"Desactivado\n";
                drawCursor();
                break;
            case 'm':
                std::cout<<"Mostrar\n";
                this->escribeAnimacionesDisponibles();
                drawCursor();
                break;
            case '5':
                for (unsigned int i = 0; i<vAnimacionesActivas.size(); i++) {
                    if (vAnimacionesActivas[i]==animacionActualPuntero) {
                        auxBolean = false;
                    }
                }
                if (auxBolean) {
                    vAnimacionesActivas.push_back(animacionActualPuntero);
                }
                break;
            default:
                salta = false;
                break;
        }
        if (salta) return;
    }
    salta = true;
    if (varMovimientos.size()!=0) {
        switch (tecla) {
            case 'M':
            case 'm':
                std::cout<<"Mostrar move Movimientos\n";
                this->escribeMovimientosDisponibles();
                drawCursor();
                break;
            case '4':
                std::cout<<"Prueba movimiento\n";
                pararTodaAnimacionDisponible();
                if (movimientoActualPuntero>=varMovimientos.size())movimientoActualPuntero=(unsigned int)varMovimientos.size()-1;
                temporalPosicionAnteriorPruebaMovimiento = varMovimientos[movimientoActualPuntero].value;
                this->vUIClassAux.empezarABuscarMove(&varMovimientos[movimientoActualPuntero].value, NULL, NULL, NULL, NULL, NULL, &varMovimientos[movimientoActualPuntero].value, NULL, NULL, 0.1, 1, 22.5, 90);
                this->estado = pmovimiento;
                escribeMenu();
                drawCursor();
                break;
            default:
                salta = false;
                break;
        }
        if (salta) return;
    }
    switch (tecla) {
        case 1:
            std::cout<<"Guardando\n";
            guardar();
            break;
        case 2:
            std::cout<<"Cargando\n";
            cargar();
            break;
        case 'N':
        case 'n':
            std::cout<<"Nuevo: ";
            vAnimaciones.push_back(keyFrameAnimacion());
            animacionActualPuntero =(unsigned int) vAnimaciones.size()-1;
            estado = buscandoUIntKF;
            vUIClassAux.empezarABuscarString(vAnimaciones[animacionActualPuntero].id, MAXCHAR, (unsigned char*)&estado, (unsigned char)inicialKF, (unsigned char) inicialKF, (unsigned char) nadaKF, (unsigned char) nadaKF,(unsigned char*) &tipoAccionDespuesBuscarInt);
            break;
        case 'z':
        case 'Z':
            pararTodaAnimacionDisponible();
            menuActivado = false;
            estado = inicialKF;
            std::cout<<"Fuera menu KeyFrame\n";
            recargarAnimacionesForever();
            break;
        default:
            break;
    }    
}
void KeyFrame::teclaDeMenuPruebaMovimiento(unsigned char tecla){
    bool saltar = true;
    if (varMovimientos.size()!=0) {
        switch (tecla) {
            case 'c':
            case 'C':
                std::cout<<"Cambio\n";
                escribeMovimientosDisponibles();
                estado = buscandoUIntKF;
                varMovimientos[movimientoActualPuntero].value = temporalPosicionAnteriorPruebaMovimiento;
                this->vUIClassAux.empezarABuscarUInt(&movimientoActualPuntero,(unsigned int) varMovimientos.size(), (unsigned char *)&estado, (unsigned char)pmovimiento, (unsigned char)pmovimiento, (unsigned char)pruebaMovimientoEmpezarMove, (unsigned char)nadaKF, (unsigned char*)&tipoAccionDespuesBuscarInt);
                break;
            case 'm':
            case 'M':
                std::cout<<"Mostrar\n";
                escribeMovimientosDisponibles();
                drawCursor();
                break;
            case '3':
                varMovimientos[movimientoActualPuntero].value = temporalPosicionAnteriorPruebaMovimiento;
                break;
            default:
                saltar = this->vUIClassAux.teclaMove(tecla);
                break;
        }
        if (saltar) return;
    }
    switch (tecla) {
        case 'z':
        case 'Z':
            this->estado = inicialKF;
            if (movimientoActualPuntero<varMovimientos.size()) {
                varMovimientos[movimientoActualPuntero].value = temporalPosicionAnteriorPruebaMovimiento;
            }
            escribeMenu();
            drawCursor();
            break;
        default:
            break;
    }
}
void KeyFrame::escribeAnimacionesDisponibles(){
    for (int i=0; i<this->vAnimaciones.size(); i++) {
        std::cout<<i<<" ";
        this->describeAnimacion(&this->vAnimaciones[i]);
    }
}
void KeyFrame::describeAnimacion(keyFrameAnimacion *animacion){
    std::cout<<"Animacion N: \""<<animacion->id<<"\" C: "<<animacion->cuadrosClaves.size()<<" Forever: "<<animacion->repetitivo << " Repeat: "<<animacion->regresivo<<std::endl;
}
void KeyFrame::actualizaAnimacion(){
    if (this->animacionInfinitasActivas&&!this->menuActivado) {
        for (unsigned long i : this->vAnimacionesForever) {
            if(!this->reproduceAnimacion(&(this->vAnimaciones[i]))) std::cout<<"Problema en actualizacion no deberia dar False\n";
        }
    }
    for (unsigned long j = 0; j < this->vAnimacionesActivas.size(); j++) {
        if (!this->reproduceAnimacion(&(this->vAnimaciones[this->vAnimacionesActivas[j]]))) {
            this->vAnimacionesActivas.erase(this->vAnimacionesActivas.begin() + j);
        }
    }
    glutPostRedisplay();
}
void KeyFrame::aCeroTodosMovimientosDisponibles(){
    for (int i = 0; i<this->varMovimientos.size(); i++) {
        this->varMovimientos[i].value = 0;
    }
}
//False to end true to continue
bool KeyFrame::reproduceAnimacion(keyFrameAnimacion *animacion){
    tkf = &animacion->cuadrosClaves[animacion->cuadroActual];
    for (unsigned int i = 0; i<tkf->movimientos.size(); i++) {
        tmvmv = &tkf->movimientos[i];
        if (animacion->ascendente) this->varMovimientos[tmvmv->cual].value += tmvmv->incremento;
        else this->varMovimientos[tmvmv->cual].value -= tmvmv->incremento;
    }
    animacion->pasoActual++;
    if (animacion->pasoActual > animacion->cuadrosClaves[animacion->cuadroActual].duracion) {
        animacion->pasoActual = 0;
        if (animacion->ascendente) {
            if (animacion->cuadroActual+1>=animacion->cuadrosClaves.size()) {
                if (animacion->regresivo) {
                    animacion->ascendente = false;
                }else{
                    animacion->cuadroActual = 0;
                    this->pararAnimacion(animacion);
                    return animacion->repetitivo;
                }
            }else animacion->cuadroActual++;
        }else{
            if (animacion->cuadroActual==0) {
                animacion->ascendente = true;
                pararAnimacion(animacion);
                return animacion->repetitivo;
            }animacion->cuadroActual--;
        }
    }
    return true;
}
void KeyFrame::guardar() {
    FILE * archivo = fopen(KEYFRAMEPATHFILE, "w");
    unsigned int cabecera = KEYFRAMEVERSIONCABECERA;
    unsigned int numeroMovimientos = (unsigned int) this->varMovimientos.size();
    unsigned int numeroAnimaciones = (unsigned int) this->vAnimaciones.size();
    unsigned int numeroKF = 0;
    unsigned int numerMvMv = 0;
    if (archivo == NULL) {
        std::cout << "Archivo no se logro crear KeyFrame\n";
        return;
    }
    fwrite(&cabecera, sizeof(unsigned int), 1, archivo);
    fwrite(&numeroMovimientos, sizeof(unsigned int), 1, archivo);
    fwrite(&numeroAnimaciones, sizeof(unsigned int), 1, archivo);
    for (unsigned int i = 0; i<numeroAnimaciones; i++) {
        fwrite(&vAnimaciones[i].id, sizeof(char), MAXCHAR, archivo);
        fwrite(&vAnimaciones[i].repetitivo, sizeof(bool), 1, archivo);
        fwrite(&vAnimaciones[i].regresivo, sizeof(bool), 1, archivo);
        numeroKF = (unsigned int) vAnimaciones[i].cuadrosClaves.size();
        fwrite(&numeroKF, sizeof(unsigned int), 1, archivo);
        for (unsigned int j = 0; j<numeroKF; j++) {
            fwrite(&vAnimaciones[i].cuadrosClaves[j].duracion, sizeof(unsigned int), 1, archivo);
            numerMvMv = (unsigned int)vAnimaciones[i].cuadrosClaves[j].movimientos.size();
            fwrite(&numerMvMv, sizeof(unsigned int), 1, archivo);
            for (unsigned int k = 0; k<numerMvMv; k++) {
                fwrite(varMovimientos[vAnimaciones[i].cuadrosClaves[j].movimientos[k].cual].name, sizeof(char), MAXCHAR, archivo);
                fwrite(&vAnimaciones[i].cuadrosClaves[j].movimientos[k].posicionInicial, sizeof(double), 1, archivo);
                fwrite(&vAnimaciones[i].cuadrosClaves[j].movimientos[k].posicionFinal, sizeof(double), 1, archivo);
                fwrite(&vAnimaciones[i].cuadrosClaves[j].movimientos[k].incremento, sizeof(double), 1, archivo);
            }
        }
    }
    fclose(archivo);
}
void KeyFrame::cargar(){
    FILE * archivo = fopen(KEYFRAMEPATHFILE, "r");
    unsigned int cabecera = 0;
    unsigned int numeroMovimientos = 0;
    unsigned int numeroAnimaciones = 0;
    unsigned int numeroKF = 0;
    unsigned int numerMvMv = 0;
    char nombreAux[MAXCHAR] = "";
    if (archivo == NULL) {
        std::cout << "Archivo no se logro crear KeyFrame\n";
        fclose(archivo);
        guardar();
        return;
    }
    fread(&cabecera, sizeof(unsigned int), 1, archivo);
    if (cabecera!=KEYFRAMEVERSIONCABECERA) {
        std::cout<<"KeyFrame: Version incorrecta"<<cabecera<<" "<<KEYFRAMEVERSIONCABECERA<<"\n";
        fclose(archivo);
        return;
    }
    fread(&numeroMovimientos, sizeof(unsigned int), 1, archivo);
    if (numeroMovimientos!= (unsigned int)varMovimientos.size()) {
        std::cout<<"Numero de movimientos no coincide ten precaución\n";
    }
    fread(&numeroAnimaciones, sizeof(unsigned int), 1, archivo);
    for (unsigned int i = 0; i<numeroAnimaciones; i++) {
        vAnimaciones.push_back(keyFrameAnimacion());
        fread(&vAnimaciones[i].id, sizeof(char), MAXCHAR, archivo);
        fread(&vAnimaciones[i].repetitivo, sizeof(bool), 1, archivo);
        fread(&vAnimaciones[i].regresivo, sizeof(bool), 1, archivo);
        fread(&numeroKF, sizeof(unsigned int), 1, archivo);
        for (unsigned int j = 0; j<numeroKF; j++) {
            vAnimaciones[i].cuadrosClaves.push_back(KeyFrameKeyFrame());
            fread(&vAnimaciones[i].cuadrosClaves[j].duracion, sizeof(unsigned int), 1, archivo);
            fread(&numerMvMv, sizeof(unsigned int), 1, archivo);
            for (unsigned int k = 0; k<numerMvMv; k++) {
                vAnimaciones[i].cuadrosClaves[j].movimientos.push_back(KeyFrameMoveMovimiento());
                fread(nombreAux, sizeof(char), MAXCHAR, archivo);
                if(!this->echateABuscarPorNombre(nombreAux, &vAnimaciones[i].cuadrosClaves[j].movimientos[k].cual)){
                    std::cout<<nombreAux<<" No encontre\n";
                }
                fread(&vAnimaciones[i].cuadrosClaves[j].movimientos[k].posicionInicial, sizeof(double), 1, archivo);
                fread(&vAnimaciones[i].cuadrosClaves[j].movimientos[k].posicionFinal, sizeof(double), 1, archivo);
                fread(&vAnimaciones[i].cuadrosClaves[j].movimientos[k].incremento, sizeof(double), 1, archivo);
            }
        }
        asegurarIntegridadAnimacion(&vAnimaciones[i]);
    }
    fclose(archivo);
    std::cout<<"KeyFrame: "<<vAnimaciones.size()<<" Cargadas\n";
}
void KeyFrame::inicializar(){
    this->cargar();
    recargarAnimacionesForever();
}
void KeyFrame::escribeMovimientosDisponibles(){
    std::cout<< "Posibles movimientos\n";
    for (int i = 0; i<this->varMovimientos.size(); i++) {
        std::cout<<i<<" "<<this->varMovimientos[i].name<<" valor "<<this->varMovimientos[i].value << std::endl;
    }
}
void KeyFrame::pararAnimacion(keyFrameAnimacion *animacion){
    animacion->ascendente = true;
    for (long i=(long)animacion->cuadrosClaves.size()-1; i>=0; i--) {
        for (auto j : animacion->cuadrosClaves[i].movimientos) {
            this->varMovimientos[j.cual].value = j.posicionInicial;
        }
    }
    animacion->cuadroActual = 0;
    animacion->pasoActual = 0;
//    animacion->ascendente = true;
}
void KeyFrame::recargarAnimacionesForever(){
    this->vAnimacionesForever.clear();
    for (unsigned int i = 0; i<this->vAnimaciones.size(); i++) {
        if (this->vAnimaciones[i].repetitivo){
            this->vAnimacionesForever.push_back(i);
        }
    }
}
void KeyFrame::interpolarMoveMovimiento(KeyFrameMoveMovimiento *moveMovimiento,unsigned int duracion){
    moveMovimiento->incremento = (moveMovimiento->posicionFinal - moveMovimiento->posicionInicial)/duracion;
}
bool KeyFrame::reproduceAlgunaAnimacion(unsigned int cual){
    if (cual >= this->vAnimaciones.size()) {
        std::cout<<"Animacion no creada\n";
        return false;
    }
    if (this->vAnimaciones[cual].repetitivo) {
        std::cout<<"Animacion infinitta\n";
        this->pararAnimacion(&this->vAnimaciones[cual]);
        return false;
    }
    for (auto j : this->vAnimacionesActivas) {
        if (j == cual) {
            std::cout<<"Animacion ya ejecutando Cancelada";
            this->pararAnimacion(&(this->vAnimaciones[cual]));
            return false;
        }
    }
    this->pararAnimacion(&this->vAnimaciones[cual]);
    this->vAnimacionesActivas.push_back(cual);
    return true;
}
bool KeyFrame::echateABuscarPorNombre(char *nombre, unsigned int *donde){
    for (int i = 0; i<this->varMovimientos.size(); i++) {
        if (!memcmp(nombre, this->varMovimientos[i].name, sizeof(char)*50)) {
            *donde = i;
            return true;
        }
    }
    return false;
}
unsigned int KeyFrame::crearVarMovimiento(char *nombre){
    KeyFrameMovimiento moveNew;
    unsigned int r = (unsigned int) this->varMovimientos.size();
    for (unsigned int i=0; i<r; i++) {
        if (!memcmp(nombre, this->varMovimientos[i].name, sizeof(char)*50)) {
            return i;
        }
    }
    memcpy(moveNew.name, nombre, sizeof(char)*50);
    this->varMovimientos.push_back(moveNew);
    return r;
}
void KeyFrame::teclaDeMenuEditarKF(unsigned char tecla){
    bool salta = true;
    if (varMovimientos.size()!=0) {
        if (vAnimaciones[animacionActualPuntero].cuadrosClaves.size()!=0) {
            switch (tecla) {
                case 'c':
                case 'C':
                    std::cout<<"Cambio cuadro clave\n";
                    asegurarIntegridadCuadroClave(&vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero]);
                    asegurarIntegridadAnimacion(&vAnimaciones[animacionActualPuntero]);
                    this->escribeCuadrosClaveDisponiles(&vAnimaciones[animacionActualPuntero]);
                    estado = buscandoUIntKF;
                    this->vUIClassAux.empezarABuscarUInt(&keyframeActualPuntero, (unsigned int)vAnimaciones[animacionActualPuntero].cuadrosClaves.size(), (unsigned char*)&estado, (unsigned char)editandoCuadroClave, (unsigned char) editandoCuadroClave, (unsigned char) cambioCuadroClave, (unsigned char) cambioCuadroClave, (unsigned char*)&tipoAccionDespuesBuscarInt);
                    break;
                case 'M':
                    std::cout<<"Mostrando KF\n";
                    escribeCuadrosClaveDisponiles(&vAnimaciones[animacionActualPuntero]);
                    drawCursor();
                    break;
                case 'm':
                    std::cout<<"Mostrando mvmv usandos\n";
                    escribeMoveMovimientoDisponibles(&vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero]);
                    drawCursor();
                    break;
                case 'x':
                case 'X':
                    if (keyframeActualPuntero<vAnimaciones[animacionActualPuntero].cuadrosClaves.size()) {
                        std::cout<<"Elimidado ";
                        describeKeyFrame(&vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero]);
                        for (auto i : vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].movimientos) {
                            varMovimientos[i.cual].value = i.posicionInicial;
                        }
                        vAnimaciones[animacionActualPuntero].cuadrosClaves.erase(
                                                                             vAnimaciones[animacionActualPuntero].cuadrosClaves.begin()+
                                                                             keyframeActualPuntero);
                        keyframeActualPuntero = (unsigned int)vAnimaciones[animacionActualPuntero].cuadrosClaves.size() - 1;
                        this->recrearAnimacionHastaFinal(&vAnimaciones[animacionActualPuntero], keyframeActualPuntero);
                        this->asegurarIntegridadAnimacion(&vAnimaciones[animacionActualPuntero]);
                    }else {
                        std::cout<<"Error puntero fuera de rando\n";
                        keyframeActualPuntero  = (unsigned int)vAnimaciones[animacionActualPuntero].cuadrosClaves.size()-1;
                    }
                    drawCursor();
                    break;
                case 'B':
                case 'b':
                    std::cout<<"set time\n";
                    estado = buscandoUIntKF;
                    vUIClassAux.empezarABuscarUInt(&vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].duracion, MAXINT, (unsigned char *)&estado, (unsigned char)editandoCuadroClave, (unsigned char) editandoCuadroClave, (unsigned char)nadaKF, (unsigned char)nadaKF, (unsigned char*)&tipoAccionDespuesBuscarInt);
                    break;
                case 'p':
                case 'P':
                    std::cout<<"Cambio Move\n";
                    escribeMovimientosDisponibles();
                    estado = buscandoUIntKF;
                    asegurarIntegridadCuadroClave(&vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero]);
                    vUIClassAux.empezarABuscarUInt(&movimientoActualPuntero, (unsigned int)varMovimientos.size(), (unsigned char*)&estado, (unsigned char)editandoCuadroClave, (unsigned char)editandoCuadroClave, (unsigned char)cambioMvMVKf, (unsigned char) cambioMvMVKf, (unsigned char*)&tipoAccionDespuesBuscarInt);
                    break;
                case '3':
                    varMovimientos[vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].movimientos[moveMovimientoActualPuntero].cual].value=vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].movimientos[moveMovimientoActualPuntero].cual;
                    break;
                case '4':
                    std::cout<<"Creando keyframe to inicio duracion: \n";
//                    asegurarIntegridadCuadroClave(&vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero]);
//                    asegurarIntegridadAnimacion(&vAnimaciones[animacionActualPuntero]);
                    creaKeyFrameAlInicio(&vAnimaciones[animacionActualPuntero]);
                    recrearAnimacionHastaFinal(&vAnimaciones[animacionActualPuntero], keyframeActualPuntero);
                    estado = buscandoUIntKF;
                    vUIClassAux.empezarABuscarUInt(&vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].duracion, MAXINT, (unsigned char *)&estado, (unsigned char)editandoCuadroClave, (unsigned char) editandoCuadroClave, (unsigned char)nadaKF, (unsigned char)nadaKF, (unsigned char*)&tipoAccionDespuesBuscarInt);
                    break;
                default:
                    salta = this->vUIClassAux.teclaMove(tecla);
                    break;
            }
            if (salta) return;
        }
        switch (tecla) {
            case 'n':
            case 'N':
                std::cout<<"Nuevo\n";
                if (keyframeActualPuntero<vAnimaciones[animacionActualPuntero].cuadrosClaves.size()) {
                    asegurarIntegridadCuadroClave(&vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero]);
                }
                asegurarIntegridadAnimacion(&vAnimaciones[animacionActualPuntero]);
                moveMovimientoActualPuntero = 0;
                vAnimaciones[animacionActualPuntero].cuadrosClaves.push_back(KeyFrameKeyFrame());
                keyframeActualPuntero = (unsigned int)vAnimaciones[animacionActualPuntero].cuadrosClaves.size()-1;
                vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].movimientos.push_back(KeyFrameMoveMovimiento());
                movimientoActualPuntero = vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero].movimientos[moveMovimientoActualPuntero].cual;
                
                this->vUIClassAux.empezarABuscarMove(&varMovimientos[movimientoActualPuntero].value, NULL, NULL, NULL, NULL, NULL, &varMovimientos[movimientoActualPuntero].value, NULL, NULL, 0.1, 1, 22.5, 90);
                drawCursor();
                break;
            case 'z':
            case 'Z':
                std::cout<<"Salir\n";
                if (keyframeActualPuntero<vAnimaciones[animacionActualPuntero].cuadrosClaves.size()) {
                    asegurarIntegridadCuadroClave(&vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero]);
                }
                asegurarIntegridadAnimacion(&vAnimaciones[animacionActualPuntero]);
                estado = inicialKF;
                pararAnimacion(&vAnimaciones[animacionActualPuntero]);
                escribeMenu();
                drawCursor();
                break;
            default:
                break;
        }
    }
}
void KeyFrame::describeKeyFrame(KeyFrame::KeyFrameKeyFrame *kf){
    std::cout<<"Duracion: "<<kf->duracion<<" no.Mov: "<<kf->movimientos.size()<<std::endl;
}
void KeyFrame::creaKeyFrameAlInicio(KeyFrame::keyFrameAnimacion *animacion){
    //                    cambioCuadroClave
    if (animacion->cuadrosClaves.size()==0) {
        std::cout<<"Uso incorrecto de creaKeyFrameAlInicio()\n";
    }
    asegurarIntegridadCuadroClave(&animacion->cuadrosClaves[keyframeActualPuntero]);
    asegurarIntegridadAnimacion(animacion);
    KeyFrameKeyFrame temporal = KeyFrameKeyFrame();
    bool auxiliarBoleana = true;
    for (unsigned int i = 0; i<animacion->cuadrosClaves.size(); i++) {
        for (unsigned int j = 0; j<animacion->cuadrosClaves[i].movimientos.size(); j++) {
            auxiliarBoleana = true;
            for (unsigned int k = 0; k<temporal.movimientos.size(); k++) {
                if (temporal.movimientos[k].cual == animacion->cuadrosClaves[i].movimientos[j].cual) {
                    temporal.movimientos[k].posicionInicial = animacion->cuadrosClaves[i].movimientos[j].posicionFinal;
                    auxiliarBoleana = false;
                    break;
                }
            }
            if (auxiliarBoleana) {
                temporal.movimientos.push_back(KeyFrameMoveMovimiento());
                temporal.movimientos[temporal.movimientos.size()-1].cual = animacion->cuadrosClaves[i].movimientos[j].cual;
                temporal.movimientos[temporal.movimientos.size()-1].posicionFinal = animacion->cuadrosClaves[i].movimientos[j].posicionInicial;
                temporal.movimientos[temporal.movimientos.size()-1].posicionInicial = animacion->cuadrosClaves[i].movimientos[j].posicionFinal;
            }
        }
    }
    animacion->cuadrosClaves.push_back(temporal);
    keyframeActualPuntero = (unsigned int) animacion->cuadrosClaves.size() -1;
}
void KeyFrame::recrearAnimacionHastaFinal(KeyFrame::keyFrameAnimacion *animacion, unsigned int hastaDonde){
    if (hastaDonde>=animacion->cuadrosClaves.size()) {
//        std::cout<<"Uso incorrecto de funcion recrearAnimacionHastaFinal()\n";
        if (animacion->cuadrosClaves.size()==0) {
//            std::cout<<
            return;
        }
        hastaDonde = (unsigned int)animacion->cuadrosClaves.size()-1;
    }
    for (unsigned int i = 0; i<=hastaDonde; i++) {
        for (unsigned int j = 0; j<animacion->cuadrosClaves[i].movimientos.size(); j++) {
            varMovimientos[animacion->cuadrosClaves[i].movimientos[j].cual].value = animacion->cuadrosClaves[i].movimientos[j].posicionFinal;
        }
    }
}
void KeyFrame::asegurarIntegridadAnimacion(KeyFrame::keyFrameAnimacion *animacion){
    std::vector<KeyFrameMovimiento> temMovimiento;
    for (unsigned int a = 0; a<varMovimientos.size(); a++) {
        temMovimiento.push_back(KeyFrameMovimiento());
    }
    for (unsigned int b = 0; b<vAnimaciones.size(); b++) {
        if (animacion!=&vAnimaciones[b]) {
            for (long c = vAnimaciones[b].cuadrosClaves.size()-1; c>=0; c--) {
                for (unsigned int e = 0; e<vAnimaciones[b].cuadrosClaves[c].movimientos.size(); e++) {
                    temMovimiento[vAnimaciones[b].cuadrosClaves[c].movimientos[e].cual].value = vAnimaciones[b].cuadrosClaves[c].movimientos[e].posicionInicial;
                }
            }
        }else std::cout<<"Encontrado en "<<b<<"\n";
    }
    for (unsigned int i = 0; i<animacion->cuadrosClaves.size(); i++) {
        if (animacion->cuadrosClaves[i].duracion==0) {
            std::cout<<"Precaucion ";
            describeAnimacion(animacion);
            std::cout<<"\t"<<i<<".- ";
            describeKeyFrame(&animacion->cuadrosClaves[i]);
            animacion->cuadrosClaves[i].duracion = 1;
        }
        for (unsigned int j = 0; j<animacion->cuadrosClaves[i].movimientos.size(); j++) {
            animacion->cuadrosClaves[i].movimientos[j].posicionInicial=temMovimiento[animacion->cuadrosClaves[i].movimientos[j].cual].value;
            temMovimiento[animacion->cuadrosClaves[i].movimientos[j].cual].value = animacion->cuadrosClaves[i].movimientos[j].posicionFinal;
            interpolarMoveMovimiento(&animacion->cuadrosClaves[i].movimientos[j], animacion->cuadrosClaves[i].duracion);
        }
    }
}
void KeyFrame::asegurarIntegridadCuadroClave(KeyFrame::KeyFrameKeyFrame *kf){
    unsigned int i = 0;
    while (i<kf->movimientos.size()) {
        if (kf->movimientos[i].posicionInicial==varMovimientos[kf->movimientos[i].cual].value) {
            kf->movimientos.erase(kf->movimientos.begin()+i);
            std::cout<<"Borre "<<i<<" asegurarIntegridadCuadroClave\n";
        }else{
            kf->movimientos[i].posicionFinal = varMovimientos[kf->movimientos[i].cual].value;
            i++;
        }
    }
}
void KeyFrame::pararTodaAnimacionDisponible(){
    for (unsigned int i = 0; i<vAnimaciones.size(); i++) {
        pararAnimacion(&vAnimaciones[i]);
    }
}
void KeyFrame::escribeCuadrosClaveDisponiles(KeyFrame::keyFrameAnimacion *animacion){
    for (unsigned int i = 0; i<animacion->cuadrosClaves.size(); i++) {
        std::cout<<i<<".- ";
        describeKeyFrame(&animacion->cuadrosClaves[i]);
    }
}
void KeyFrame::escribeMoveMovimientoDisponibles(KeyFrame::KeyFrameKeyFrame *kf){
    for (unsigned int i = 0; i<kf->movimientos.size(); i++) {
        std::cout<<i<<".- ";
        describeMoveMovimiento(&kf->movimientos[i]);
    }
}
void KeyFrame::ejecutaAccionBuscarUInt(){
    switch (tipoAccionDespuesBuscarInt) {
        case cambioCuadroClave:
            recrearAnimacionHastaFinal(&vAnimaciones[animacionActualPuntero], keyframeActualPuntero);
            modificarCual(&vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero], &moveMovimientoActualPuntero, movimientoActualPuntero);
            break;
        case cambioMvMVKf:
            modificarCual(&vAnimaciones[animacionActualPuntero].cuadrosClaves[keyframeActualPuntero], &moveMovimientoActualPuntero, movimientoActualPuntero);
            break;
        case eliminacionCuadro:
            
            break;
        case nadaKF:
            break;
        case pruebaMovimientoEmpezarMove:
            this->vUIClassAux.empezarABuscarMove(&varMovimientos[movimientoActualPuntero].value, NULL, NULL, NULL, NULL, NULL, &varMovimientos[movimientoActualPuntero].value, NULL, NULL, 0.1, 1, 22.5, 90);
            break;
        default:
            break;
    }
    escribeMenu();
    drawCursor();
}
void KeyFrame::modificarCual(KeyFrame::KeyFrameKeyFrame *kf, unsigned int *donde, unsigned int cualMove){
    if (cualMove>=varMovimientos.size()) {
        std::cout<<"Cual movimiento fuera de range modificarCual()\n";
        cualMove =(unsigned int) varMovimientos.size()-1;
    }
    bool auxiliarbool = true;
    for (unsigned int i = 0; i<kf->movimientos.size(); i++) {
        if (kf->movimientos[i].cual == cualMove) {
            *donde = i;
            auxiliarbool = false;
            break;
        }
    }
    if (auxiliarbool) {
        kf->movimientos.push_back(KeyFrameMoveMovimiento());
        *donde = (unsigned int) kf->movimientos.size()-1;
        kf->movimientos[*donde].cual = cualMove;
        kf->movimientos[*donde].posicionInicial = varMovimientos[cualMove].value;
    }
    moveMovimientoActualPuntero = cualMove;
    this->vUIClassAux.empezarABuscarMove(&varMovimientos[moveMovimientoActualPuntero].value, NULL, NULL, NULL, NULL, NULL, &varMovimientos[moveMovimientoActualPuntero].value, NULL, NULL, 0.1, 1, 22.5, 90);
}
void KeyFrame::describeMoveMovimiento(KeyFrame::KeyFrameMoveMovimiento *mvmv){
    std::cout<<"MoveMove N: \""<<varMovimientos[mvmv->cual].name<<"\" I: "<<mvmv->posicionInicial<<" F: "<<mvmv->posicionFinal<<" +: "<<mvmv->incremento<<"\n";
}
