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

void KeyFrame::escribeMenu(KeyFrameEstados tipo) {
    switch (tipo) {
        case inicial:
            std::cout << "F->Set Animacion Forever "<<this->animacionInfinitasActivas<<"\nC->Cantidad movimientos\nP->Prueba Movimiento\nA->Animacion\nS->Salir\nG->Guardar En Archivo\nL->Cargar De Archivo\n";
            break;
        case pmovimiento:
            std::cout << "23[0.1],45[1],67[10],89[100],01[359]\nR->Reset All\nM->Mostrar\nC->Cambio movimiento\nS->Salir\n";
            break;
        case animacion:
            std::cout << "C->Cambio\nN->Nueva\nR->Reproducir\nP->Parar Reproduccion\nF->ReproducirSiempre\nD->Eliminar\nE->Editar Reproduccion\nM->Mostrar\nS->Salir\n";
            break;
        case animacionNueva:
            std::cout << "23[0.1],45[1],67[10],89[100],01[359]\nS->Save KeyFrame\nT->SetTime\nC->Cambio Movimiento\nM->Mostrar Movimientos\nR->Set Reproduccion\nF->Repetitivo\n\nG->Guardar\n\"-\"->Reset\nQ->Salir (Cuidado no se guardaran Cambios)\n";
            break;
        default:
            std::cout << "Error Escribir menu KeyFrame\n";
            break;
    }
}
void KeyFrame::escribeCabecera(KeyFrameEstados tipo){
    switch (tipo) {
        case pmovimiento:
            std::cout<< "Actual " << this->movimientoActualPuntero <<" Nombre: \""<<this->varMovimientos[this->movimientoActualPuntero].name<< "\" Disponibles " << this->varMovimientos.size() << std::endl;
            break;
        case animacion:
            std::cout<<"Actual: "<<this->animacionActualPuntero << " Disponibles " << this->vAnimaciones.size() << std::endl;
            break;
        case animacionNueva:
            std::cout<<"KFUsados: "<<this->temporalAnimacion.cuadrosClaves.size() <<" KFDuracion: "<<this->temporalCuadroClave.duracion<<" Repeticion ";
            this->escribeTipoRepeticionSegun(this->temporalAnimacion.tipoReproduccion);
            std::cout<<" ActualMov: " << this->movimientoActualPuntero <<" Nombre: \""<<this->varMovimientos[this->movimientoActualPuntero].name<< "\" Disponibles: " << this->varMovimientos.size() << std::endl;
            break;
        default:
            std::cout<<"Error keyframe escribe Cabecera\n";
            break;
    }
}
void KeyFrame::drawCursor(){
    std::cout<<"CG2ProyectoFinalValenciaKF " << this->nameEstado(this->estado) << " $ ";
}
void KeyFrame::teclaActivaMenu() {
    std::cout << "Inicio de KeyFrame Menu\n";
    this->menuActivado = true;
    this->teclaDeMenuInicialReset();
    
//    this->aCeroTodosMovimientosDisponibles();
    glutPostRedisplay();
}
void KeyFrame::teclaDeMenuInicialReset(){
    this->estado = inicial;
    this->escribeMenu(inicial);
    this->drawCursor();
}
void KeyFrame::teclaDeMenu(unsigned char tecla) {
    if (tecla == '|'&&this->estado!=buscandoUIntKF) {
        std::cout<<std::endl;
        this->escribeMenu(this->estado);
        drawCursor();
        return;
    }
    switch (this->estado) {
        case inicial:
            this->teclaDeMenuInicial(tecla);
            break;
        case pmovimiento:
            this->teclaDeMenuPruebaMovimiento(tecla);
            break;
        case animacion:
            this->teclaDeMenuAnimacion(tecla);
            break;
        case animacionNueva:
            this->teclaDeMenuAnimacionNueva(tecla);
            break;
        case buscandoUIntKF:
            this->teclaDeMenuBuscandoUInt(tecla);
            break;
        default:
            std::cout<< "KeyFrame Error estado desconocido\n";
            this->teclaDeMenuInicialReset();
            break;
    }
}
void KeyFrame::teclaDeMenuInicial(unsigned char tecla){
    std::cout << tecla << std::endl;
    switch (tecla) {
        case 'f':
        case 'F':
            if (this->animacionInfinitasActivas) {
                std::cout<<"Desactivadas\n";
                this->animacionInfinitasActivas = false;
                this->pararAnimacionesFromVector(this->vAnimacionesForever);
            }else{
                std::cout<<"Activadas\n";
                this->animacionInfinitasActivas = true;
            }
            break;
        case 'c':
        case 'C':
            std::cout<< "Tam "<<this->varMovimientos.size() << " Cap: " << this->varMovimientos.capacity() << std::endl;
            break;
        case 'p':
        case 'P':
            if (this->varMovimientos.size()==0) {
                std::cout<<"Error KeyFrame no inicializado\n";
            }else{
                this->temporalPosicionAnteriorPruebaMovimiento = this->varMovimientos[this->movimientoActualPuntero].value;
                this->escribeCabecera(pmovimiento);
                this->escribeMenu(pmovimiento);
                this->estado = pmovimiento;
            }
            break;
        case 'a':
        case 'A':
            this->escribeCabecera(animacion);
            this->escribeMenu(animacion);
            this->estado = animacion;
            break;
        case 's':
        case 'S':
            std::cout<< "Fuera de KeyFrame Menu\n";
            this->menuActivado = false;
            if (this->reproduccionExterna>=0) {
                this->pararAnimacion(&(this->vAnimaciones[this->reproduccionExterna]));
                this->reproduccionExterna = -1;
            }
//            this->aCeroTodosMovimientosDisponibles();
            glutPostRedisplay();
            return;
        case 'g':
        case 'G':
            std::cout<<"Guardando\n";
            this->guardar();
            break;
        case 'l':
        case 'L':
            std::cout << "Cargando\n";
            this->cargar();
            break;
        default:
            std::cout << "Sin Coincidencia\n";
            break;
    }
    this->drawCursor();
}
void KeyFrame::teclaDeMenuPruebaMovimiento(unsigned char tecla){
    switch (tecla) {
        case 'c':
        case 'C':
            std::cout<<"Cambio\n";
            this->varMovimientos[this->movimientoActualPuntero].value = this->temporalPosicionAnteriorPruebaMovimiento;
            glutPostRedisplay();
            this->empezarABuscarUInt(&this->movimientoActualPuntero,(unsigned int) this->varMovimientos.size(), this->estado,cambioPunteroMovimientoSetTemporal);
            drawCursor();
            break;
        case 's':
        case 'S' :
            std::cout << "Salir" << std::endl;
            this->varMovimientos[this->movimientoActualPuntero].value = this->temporalPosicionAnteriorPruebaMovimiento;
            glutPostRedisplay();
            this->teclaDeMenuInicialReset();
            break;
        case 'm':
        case 'M':
            std::cout << "Mostrar" << std::endl;
            this->escribeMovimientos();
            this->drawCursor();
            break;
        case 'r':
        case 'R':
            std::cout << "Reset" << std::endl;
            this->varMovimientos[this->movimientoActualPuntero].value = 0;
            this->temporalIntFromKeyBoard = 0;
            glutPostRedisplay();
            this->drawCursor();
            break;
        default:
            if (tecla >= 48 && tecla <= 57) {
                this->varMovimientos[this->movimientoActualPuntero].value += this->moverMovimiento((int)tecla-48);
                glutPostRedisplay();
            }
            break;
    }
}
void KeyFrame::teclaDeMenuAnimacion(unsigned char tecla){
    std::cout<<tecla<<std::endl;
    unsigned int temporalUInt;
    switch (tecla) {
        case 'c':
        case 'C':
            this->escribeAnimacionesDisponibles();
            this->empezarABuscarUInt(&this->animacionActualPuntero,(unsigned int) this->vAnimaciones.size(), this->estado);
            this->drawCursor();
            break;
        case 's':
        case 'S':
            this->teclaActivaMenu();
            break;
        case 'n':
        case 'N':
            this->temporalAnimacion = keyFrameAnimacion();
            this->temporalCuadroClave = KeyFrameKeyFrame();
            this->temporalMoveMovimiento = KeyFrameMoveMovimiento();
            this->temporalMoveMovimiento.posicionInicial = this->varMovimientos[0].value;
            this->escribeCabecera(animacionNueva);
            this->escribeMenu(animacionNueva);
            this->drawCursor();
            this->estado = animacionNueva;
            break;
        case 'p':
        case 'P':
//            Parar
            if (this->reproduccionExterna<0) {
                if (this->vAnimaciones.size()==0) {
                    std::cout<<"No hay que Parar\n";
                }else{
                    this->pararAnimacion(&(this->vAnimaciones[this->animacionActualPuntero]));
                }
            }else{
                this->pararAnimacion(&(this->vAnimaciones[reproduccionExterna]));
                this->reproduccionExterna = -1;
            }
            drawCursor();
            break;
        case 'R':
        case 'r':
//            Reproducir
            if (this->vAnimaciones.size()==0) {
                std::cout<<"No hay animacion\n";
                drawCursor();
            }else{
                pararAnimacion(&(this->vAnimaciones[this->animacionActualPuntero]));
                glutPostRedisplay();
                this->reproduccionExterna = (int) this->animacionActualPuntero;
                drawCursor();
            }
            break;
        case 'M':
        case 'm':
//            Mostrar
            this->escribeAnimacionesDisponibles();
            drawCursor();
            break;
        case 'D':
        case 'd':
//            Delete
            if (this->vAnimaciones.size()==0) {
                std::cout<<"No hay animacion\n";
                drawCursor();
            }else{
                this->vAnimaciones.erase(this->vAnimaciones.begin() + this->animacionActualPuntero);
                std::cout<<"Borrado\n";
                if (this->animacionActualPuntero != 0 && this->animacionActualPuntero >= this->vAnimaciones.size()) {
                    std::cout<<"Recorriendo puntero\n";
                    this->animacionActualPuntero--;
                    this->escribeCabecera(this->estado);
                }
                drawCursor();
            }
            break;
        case 'E':
        case 'e':
//            Editar
            this->escribeTiposRepeticion();
            this->empezarABuscarUInt((unsigned int*)&(this->vAnimaciones[this->animacionActualPuntero].tipoReproduccion), MAXTIPOSREPETICION, this->estado,necesitoCrearUltimoKeyFrame);
            this->drawCursor();
            break;
        case 'F':
        case 'f':
//            Forever
            this->vAnimaciones[animacionActualPuntero].repetitivo = !this->vAnimaciones[animacionActualPuntero].repetitivo;
            if (this->vAnimaciones[animacionActualPuntero].repetitivo) {
                std::cout<<"Repetitivo\n";
            }else{
                std::cout<<"No Repetitivo\n";
            }
            this->drawCursor();
            break;
        default:
            std::cout<<"KeyFrame::teclaDeMenuAnimacion Fuera Menu\n";
            this->drawCursor();
            break;
    }
}

void KeyFrame::teclaDeMenuAnimacionNueva(unsigned char tecla){
    switch (tecla) {
        case 'S':
        case 's':
            std::cout << tecla;
            if (this->temporalMoveMovimiento.posicionInicial != this->varMovimientos[this->temporalMoveMovimiento.cual].value) {
                //                        Proceso de agregar movemovimiento
                this->temporalMoveMovimiento.posicionFinal = this->varMovimientos[this->temporalMoveMovimiento.cual].value;
                this->temporalCuadroClave.movimientos.push_back(this->temporalMoveMovimiento);
                this->temporalMoveMovimiento = KeyFrameMoveMovimiento();
                this->temporalMoveMovimiento.posicionInicial = this->varMovimientos[this->temporalMoveMovimiento.cual].value;
            }
            if (this->temporalCuadroClave.movimientos.size()==0||this->temporalCuadroClave.duracion == 0) {
                std::cout<< "\nKeyframe vacio Agrega movimiento o Duracion\n";
            }else{
                std::cout<<"\nKey Frame Guardado\n";
                for (int i = 0; i<this->temporalCuadroClave.movimientos.size(); i++) {
                    this->interpolarMoveMovimiento(&(this->temporalCuadroClave.movimientos[i]));
                }
                this->temporalAnimacion.cuadrosClaves.push_back(this->temporalCuadroClave);
                this->temporalCuadroClave = KeyFrameKeyFrame();
                this->describeAnimacion(this->temporalAnimacion);
            }
            this->drawCursor();
            break;
        case 'c':
        case 'C':
            std::cout << "Cambio de MoveMovimiento\n";
            if (this->temporalMoveMovimiento.posicionInicial != this->varMovimientos[this->temporalMoveMovimiento.cual].value) {
                //Proceso de agregar movemovimiento
                std::cout<<"Guardado automatico"<< this->temporalCuadroClave.movimientos.size() << std::endl;
                this->temporalMoveMovimiento.posicionFinal = this->varMovimientos[this->temporalMoveMovimiento.cual].value;
                this->temporalCuadroClave.movimientos.push_back(this->temporalMoveMovimiento);
            }
            this->temporalMoveMovimiento = KeyFrameMoveMovimiento();
            empezarABuscarUInt(&(this->temporalMoveMovimiento.cual), (unsigned int) this->varMovimientos.size(), this->estado,cambioPunteroMovimientoSetPosicionInicial);
            this->drawCursor();
            break;
        case 't':
        case 'T':
            std::cout << "Set duracion\n";
            this->empezarABuscarUInt(&(this->temporalCuadroClave.duracion), MAXINT, this->estado);
            this->drawCursor();
            break;
        case 'M':
        case 'm':
            std::cout << tecla;
            this->escribeMovimientos();
            this->drawCursor();
            break;
        case 'r':
        case 'R':
            std::cout << tecla<<std::endl;
            this->empezarABuscarUInt((unsigned int*)(&this->temporalAnimacion.tipoReproduccion), MAXTIPOSREPETICION, this->estado);
            this->drawCursor();
            break;
        case 'G':
        case 'g':
            std::cout << tecla;
            if (this->temporalAnimacion.cuadrosClaves.size() == 0) {
                std::cout<<"\nHey primero crea un cuadro clave XD\n";
                this->drawCursor();
            }else{
                std::cout<<"\nAnimacion Guardada\n";
                if (this->temporalAnimacion.tipoReproduccion == regresarAlInicio) {
//                  duracion seteada a 50
                    this->crearKeyFrameForCircular(&(this->temporalAnimacion),50);
                }
                this->vAnimaciones.push_back(this->temporalAnimacion);
                this->temporalAnimacion = keyFrameAnimacion();
                if(this->temporalAnimacion.repetitivo){
                    this->vAnimacionesForever.push_back(this->vAnimaciones.size()-1);
                }
//                if (this->temporalAnimacion.tipoReproduccion == regresarAlInicioCircular || this->temporalAnimacion.tipoReproduccion == regresivoCircular) {
//                    this->vAnimacionesForever.push_back(this->vAnimaciones.size()-1);
//                }
                this->describeAnimacion(this->temporalAnimacion);
                this->escribeMenu(animacion);
                this->drawCursor();
                this->pararAnimacion(&(this->vAnimaciones.back()));
                glutPostRedisplay();
                this->temporalAnimacion = keyFrameAnimacion();
                this->estado = animacion;
            }
            break;
        case 'Q':
        case 'q':
            std::cout << tecla;
            this->teclaActivaMenu();
            break;
        case 'f':
        case 'F':
            this->temporalAnimacion.repetitivo = !this->temporalAnimacion.repetitivo;
            if (this->temporalAnimacion.repetitivo) {
                std::cout<<"Activado Repetitivo\n";
            }else {
                std::cout<<"Desactivado Repetitivo\n";
            }
            this->drawCursor();
            break;
        case '-':
            std::cout<<"restaurado\n";
            this->varMovimientos[this->temporalMoveMovimiento.cual].value = this->temporalMoveMovimiento.posicionInicial;
            glutPostRedisplay();
            drawCursor();
            break;
        default:
            if (tecla >= 48 && tecla <= 57) {
                this->varMovimientos[this->temporalMoveMovimiento.cual].value += this->moverMovimiento(tecla-48);
                glutPostRedisplay();
            }else{
                std::cout<<"\nFuera de rango menu keyframe nueva animacion\n";
            }
            break;
    }
}
void KeyFrame::escribeTiposRepeticion(){
    std::cout<<"nulo=0,brincarAlInicio=1,regresivo=2,regresarAlInicio=3\n";
}
void KeyFrame::escribeTipoRepeticionSegun(KeyFrameTipoReproduccion rep){
    switch (rep) {
        case nulo:
            std::cout<<"Nulo ";
            break;
        case brincarAlInicio:
            std::cout<<"Volver al inicio ";
            break;
        case regresivo:
            std::cout<<"Regresivo ";
            break;
        case regresarAlInicio:
            std::cout<<"Regresar al inicio ";
            break;
        default:
            std::cout<<"Error escribe tipo repeticion ";
            break;
    }
}
void KeyFrame::escribeAnimacionesDisponibles(){
    for (int i=0; i<this->vAnimaciones.size(); i++) {
        std::cout<<i<<" ";
        this->describeAnimacion(this->vAnimaciones[i]);
    }
}
void KeyFrame::describeAnimacion(keyFrameAnimacion animacion){
    std::cout<<"Animacion Cuadros: "<<animacion.cuadrosClaves.size()<<" Repeticion "<<animacion.repetitivo << " ";
    this->escribeTipoRepeticionSegun(animacion.tipoReproduccion);
    std::cout<<std::endl;
}
void KeyFrame::actualizaAnimacion(){
    if(!this->menuActivado){
        if (this->animacionInfinitasActivas) {
            for (unsigned long i : this->vAnimacionesForever) {
                if(!this->reproduceAnimacion(&(this->vAnimaciones[i]))) std::cout<<"Problema en actualizacion no deberia dar False\n";
            }
        }
        for (unsigned long j = 0; j < this->vAnimacionesActivas.size(); j++) {
            if (!this->reproduceAnimacion(&(this->vAnimaciones[this->vAnimacionesActivas[j]]))) {
                this->vAnimacionesActivas.erase(this->vAnimacionesActivas.begin() + j);
            }
        }
    }else {
        if (this->reproduccionExterna != -1) {
            if (!this->reproduceAnimacion(&(this->vAnimaciones[this->reproduccionExterna]))){
                std::cout<<"Reproduccion terminada\n";
                this->reproduccionExterna = -1;
                this->drawCursor();
            }else{
            }
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
    KeyFrameKeyFrame *tkf = &animacion->cuadrosClaves[animacion->cuadroActual];
    for (auto i : tkf->movimientos) {
        if (animacion->ascendente) this->varMovimientos[i.cual].value += i.incremento;
        else this->varMovimientos[i.cual].value -=i.incremento;
    }
    animacion->pasoActual++;
    if (animacion->pasoActual > animacion->cuadrosClaves[animacion->cuadroActual].duracion) {
        animacion->pasoActual = 0;
        int aumento = 1;
        if (!animacion->ascendente) aumento = -1;
        if ((animacion->cuadroActual + aumento < 0 )||( animacion->cuadroActual + aumento >= animacion->cuadrosClaves.size())) {
//            std::cout<<"AQUI\n";
            switch (animacion->tipoReproduccion) {
                case regresarAlInicio:
                    animacion->cuadroActual = 0;
                    return animacion->repetitivo;
                    break;
                case regresivo:
                    if (animacion->ascendente) {
                        animacion->ascendente = false;
                    }else{
                        animacion->ascendente = true;
                        animacion->cuadroActual = 0;
                        return animacion->repetitivo;
                    }
                    break;
                case brincarAlInicio:
                    this->pararAnimacion(animacion);
                    return animacion->repetitivo;
                case nulo:
                    //                    borrar
                    animacion->ascendente = true;
                    animacion->cuadroActual=0;
                    return animacion->repetitivo;
                default:
                    std::cout<<"Error key frame reproduce animacion\n";
                    break;
            }
        }else animacion->cuadroActual += aumento;
    }
    return true;
}


double KeyFrame::moverMovimiento(int mov){
    double aumento = 0;
    int division = mov/2;
    if (!division) {
        aumento = 360;
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
    return aumento;
}
void KeyFrame::guardar() {
    FILE * archivo = fopen(KEYFRAMEPATHFILE, "w");
    char *nombre = NULL;
    unsigned int cabecera = 0x19FF;
    unsigned int numeroMovimientos = (unsigned int) this->varMovimientos.size();
    unsigned int numeroAnimaciones = (unsigned int) this->vAnimaciones.size();
    unsigned int tipoRepeticionAnimacion = 0;
    unsigned int numeroKeyFrame = 0;
    unsigned int duracionKeyFrame = 0;
    unsigned int numeroMoveMoviemitos = 0;
//    unsigned int cualMoveMovimiento = 0;
    double posicionInicial = 0;
    double posicionFinal = 0;
    double incremento = 0;
    bool repetitivo = false;
    
    if (archivo == NULL) {
        std::cout << "Archivo no se logro crear KeyFrame\n";
        return;
    }
    fwrite(&cabecera, sizeof(unsigned int), 1, archivo);
    fwrite(&numeroMovimientos, sizeof(unsigned int), 1, archivo);
    fwrite(&numeroAnimaciones, sizeof(unsigned int), 1, archivo);
    for (int i = 0; i<numeroAnimaciones; i++) {
        tipoRepeticionAnimacion = (unsigned int) this->vAnimaciones[i].tipoReproduccion;
        repetitivo = this->vAnimaciones[i].repetitivo;
        numeroKeyFrame = (unsigned int)this->vAnimaciones[i].cuadrosClaves.size();
        fwrite(&tipoRepeticionAnimacion, sizeof(unsigned int), 1, archivo);
        fwrite(&repetitivo, sizeof(bool), 1, archivo);
        fwrite(&numeroKeyFrame, sizeof(unsigned int), 1, archivo);
        for (int j = 0; j<numeroKeyFrame; j++) {
            duracionKeyFrame = this->vAnimaciones[i].cuadrosClaves[j].duracion;
            numeroMoveMoviemitos = (unsigned int) this->vAnimaciones[i].cuadrosClaves[j].movimientos.size();
            fwrite(&duracionKeyFrame, sizeof(unsigned int), 1, archivo);
            fwrite(&numeroMoveMoviemitos, sizeof(unsigned int), 1, archivo);
            for (int k = 0; k<numeroMoveMoviemitos; k++) {
//                cualMoveMovimiento = this->vAnimaciones[i].cuadrosClaves[j].movimientos[k].cual;
                nombre = this->varMovimientos[this->vAnimaciones[i].cuadrosClaves[j].movimientos[k].cual].name;
                posicionInicial = this->vAnimaciones[i].cuadrosClaves[j].movimientos[k].posicionInicial;
                posicionFinal = this->vAnimaciones[i].cuadrosClaves[j].movimientos[k].posicionFinal;
                incremento = this->vAnimaciones[i].cuadrosClaves[j].movimientos[k].incremento;
                fwrite(&nombre, sizeof(char)*50, 1, archivo);
                fwrite(&posicionInicial, sizeof(double), 1, archivo);
                fwrite(&posicionFinal, sizeof(double), 1, archivo);
                fwrite(&incremento, sizeof(double), 1, archivo);
            }
            
        }
    }
    fclose(archivo);
    
}
void KeyFrame::cargar() {
    FILE * archivo = fopen(KEYFRAMEPATHFILE, "r");
    char nombre[50] = "";
    unsigned int cabecera = 0;
    unsigned int numeroMovimientos = 0;
    unsigned int numeroAnimaciones = 0;
    unsigned int tipoRepeticionAnimacion = 0;
    unsigned int numeroKeyFrame = 0;
    unsigned int duracionKeyFrame = 0;
    unsigned int numeroMoveMoviemitos = 0;
    unsigned int cualMoveMovimiento = 0;
    double posicionInicial = 0;
    double posicionFinal = 0;
    double incremento = 0;
    bool repetitivo = false;
    
    keyFrameAnimacion tAnimacion = keyFrameAnimacion();
    KeyFrameKeyFrame tKeyFrame = KeyFrameKeyFrame();
    KeyFrameMoveMovimiento tMoveMovimiento = KeyFrameMoveMovimiento();
    
    if (archivo == NULL) {
        std::cout << "Archivo no encontrado KeyFrame\n";
        this->guardar();
        return;
    }
    fread(&cabecera, sizeof(unsigned int), 1, archivo);
    if (cabecera != 0x19FF) {
        std::cout<<"Cabecera incompatible posible version anterios "<<cabecera<<"\n";
        fclose(archivo);
        return;
    }
    fread(&numeroMovimientos, sizeof(unsigned int), 1, archivo);
    if (numeroMovimientos != (unsigned int)this->varMovimientos.size()) {
        std::cout<<"Precaucion numero de movimientos incompatibles\n";
    }
    fread(&numeroAnimaciones, sizeof(unsigned int), 1, archivo);
    for (int i = 0; i<numeroAnimaciones; i++) {
        fread(&tipoRepeticionAnimacion, sizeof(unsigned int), 1, archivo);
        fread(&repetitivo, sizeof(bool), 1, archivo);
        fread(&numeroKeyFrame, sizeof(unsigned int), 1, archivo);
        for (int j = 0; j<numeroKeyFrame; j++) {
            fread(&duracionKeyFrame, sizeof(unsigned int), 1, archivo);
            fread(&numeroMoveMoviemitos, sizeof(unsigned int), 1, archivo);
            for (int k = 0; k<numeroMoveMoviemitos; k++) {
                fread(nombre, sizeof(char)*50, 1, archivo);
                if (!this->echateABuscarPorNombre(nombre, &cualMoveMovimiento)) {
                    std::cout<<"Archivo corrupto "<<k<<" "<<j<<" "<<i<<" espero no arruine lo demas\n";
                }
//                fread(&cualMoveMovimiento, sizeof(unsigned int), 1, archivo);
                fread(&posicionInicial, sizeof(double), 1, archivo);
                fread(&posicionFinal, sizeof(double), 1, archivo);
                fread(&incremento, sizeof(double), 1, archivo);
                tMoveMovimiento.cual = cualMoveMovimiento;
                tMoveMovimiento.posicionInicial = posicionInicial;
                tMoveMovimiento.posicionFinal = posicionFinal;
                tMoveMovimiento.incremento = incremento;
                tKeyFrame.movimientos.push_back(tMoveMovimiento);
                tMoveMovimiento = KeyFrameMoveMovimiento();
            }
            tKeyFrame.duracion = duracionKeyFrame;
            tAnimacion.cuadrosClaves.push_back(tKeyFrame);
            tKeyFrame = KeyFrameKeyFrame();
        }
        tAnimacion.repetitivo = repetitivo;
        tAnimacion.tipoReproduccion = (KeyFrameTipoReproduccion) tipoRepeticionAnimacion;
        this->vAnimaciones.push_back(tAnimacion);
        tAnimacion = keyFrameAnimacion();
    }
    this->escribeAnimacionesDisponibles();
    this->recargarAnimacionesForever();
}
void KeyFrame::inicializar(){
//    if (cantidad > 100) cantidad = 100;
    for (int i = 0; i<10; i++) {
        this->varMovimientos.push_back(KeyFrameMovimiento());
        this->varMovimientos[i].value = 0;
//        this->varMovimientos[i].name = nombre + std::to_string(i);
    }
//    std::cout<<"Inicializando KeyFrame\n";
    this->cargar();
}
void KeyFrame::escribeMovimientos(){
    std::cout<< "Posibles movimientos\n";
    for (int i = 0; i<this->varMovimientos.size(); i++) {
        std::cout<<i<<" name "<<this->varMovimientos[i].name<<" valor "<<this->varMovimientos[i].value << std::endl;
    }
}

void KeyFrame::empezarABuscarUInt(unsigned int *a, unsigned int max, KeyFrameEstados actual,KeyFrameTipoAccionDespuesBuscarUInt accion){
    if (max == 0) {
        std::cout << "No hay donde elegir " << this->nameEstado(actual);
        return;
    }
    this->tipoAccionDespuesBuscarInt = accion;
    this->dondeGuardar = a;
    this->temporalIntFromKeyBoard=0;
    this->estadoARegresar = actual;
    this->maxDondeGuardar = max;
    this->estado = buscandoUIntKF;
}
void KeyFrame::teclaDeMenuBuscandoUInt(unsigned char tecla){
    if (tecla >= 48 && tecla <= 57){
        std::cout << (tecla - 48);
        this->temporalIntFromKeyBoard = (this->temporalIntFromKeyBoard * 10)+(tecla - 48);
        if (this->temporalIntFromKeyBoard >= this->maxDondeGuardar){
                std::cout<<"\nNumero mayor a los disponibles\n";
            this->estado = this->estadoARegresar;
            this->estadoARegresar = inicial;
            this->drawCursor();
        }
    }else if (tecla == 13){
        std::cout <<std::endl;
        *this->dondeGuardar = this->temporalIntFromKeyBoard;
        this->temporalIntFromKeyBoard = 0;
        this->escribeCabecera(this->estadoARegresar);
        this->estado = this->estadoARegresar;
        this->estadoARegresar = inicial;
        switch (tipoAccionDespuesBuscarInt) {
            case cambioPunteroMovimientoSetPosicionInicial:
                this->temporalMoveMovimiento.posicionInicial=this->varMovimientos[this->temporalMoveMovimiento.cual].value;
                break;
            case necesitoCrearUltimoKeyFrame:
                if (this->vAnimaciones[this->animacionActualPuntero].tipoReproduccion == regresarAlInicio) {
                    this->crearKeyFrameForCircular(&(this->vAnimaciones[this->animacionActualPuntero]), 50);
                }
                break;
            case cambioPunteroMovimientoSetTemporal:
                this->temporalPosicionAnteriorPruebaMovimiento = this->varMovimientos[this->movimientoActualPuntero].value;
                break;
            case nada:
            default:
                break;
        }
        this->drawCursor();
    }else{
        std::cout<<"\nCancelado\n";
        this->estado = this->estadoARegresar;
        this->estadoARegresar = inicial;
        this->drawCursor();
    }
}
const char * KeyFrame::nameEstado(KeyFrameEstados estado){
    switch (estado) {
        case inicial:
            return "Inicial";
        case animacion:
            return "Animacion";
        case animacionNueva:
            return "Animacion Nueva";
        case pmovimiento:
            return "Prueba Movimiento";
        case buscandoUIntKF:
            return "Buscando UInt";
        default:
            return "NULO";
    }
}
void KeyFrame::pararAnimacion(keyFrameAnimacion *animacion){
    animacion->ascendente = true;
    for (long i=(long)animacion->cuadroActual; i>=0; i--) {
        for (auto j : animacion->cuadrosClaves[i].movimientos) {
            this->varMovimientos[j.cual].value = j.posicionInicial;
        }
    }
    animacion->cuadroActual = 0;
    animacion->pasoActual = 0;
}
void KeyFrame::recargarAnimacionesForever(){
//    KeyFrameTipoReproduccion tTypoRepeticion = nulo;
    this->vAnimacionesForever.clear();
    for (unsigned long i = 0; i<this->vAnimaciones.size(); i++) {
//        tTypoRepeticion = this->vAnimaciones[i].tipoReproduccion;
//        if (tTypoRepeticion == regresarAlInicioCircular || tTypoRepeticion == regresivoCircular) {
//            this->vAnimacionesForever.push_back(i);
//        }
        if (this->vAnimaciones[i].repetitivo){
            this->vAnimacionesForever.push_back(i);
        }
    }
}
void KeyFrame::crearKeyFrameForCircular(keyFrameAnimacion *animacion,unsigned int duracion){
    if (animacion->tipoReproduccion != regresarAlInicio) std::cout<<"Error crear keyframe no es Circular animacion dada\n";
    KeyFrameKeyFrame tKeyFrame;
    KeyFrameMoveMovimiento tMoveMovimiento;
    bool encontroMoveMovimiento = false;
    
    for (auto cuadroActual : animacion->cuadrosClaves) {
        for (auto moveMovimientoActual : cuadroActual.movimientos) {
            for (unsigned long i = 0; i<tKeyFrame.movimientos.size(); i++) {
                if (moveMovimientoActual.cual == tKeyFrame.movimientos[i].cual) {
                    encontroMoveMovimiento = true;
                    tKeyFrame.movimientos[i].posicionInicial = moveMovimientoActual.posicionFinal;
                }
            }
            if (encontroMoveMovimiento) {
                encontroMoveMovimiento = false;
            }else{
                tMoveMovimiento = KeyFrameMoveMovimiento();
                tMoveMovimiento.cual = moveMovimientoActual.cual;
                tMoveMovimiento.posicionFinal = moveMovimientoActual.posicionInicial;
                tMoveMovimiento.posicionInicial = moveMovimientoActual.posicionFinal;
                tKeyFrame.movimientos.push_back(tMoveMovimiento);
            }
        }
    }
    for (unsigned long a =0; tKeyFrame.movimientos.size(); a++) {
        this->interpolarMoveMovimiento(&(tKeyFrame.movimientos[a]));
    }
    animacion->cuadrosClaves.push_back(tKeyFrame);
}
void KeyFrame::interpolarMoveMovimiento(KeyFrameMoveMovimiento *moveMovimiento){
    moveMovimiento->incremento = (moveMovimiento->posicionFinal - moveMovimiento->posicionInicial)/moveMovimiento->incremento;
}
void KeyFrame::pararAnimacionesFromVector(std::vector<unsigned long> vector){
    for (unsigned long i : vector) {
        this->pararAnimacion(&(this->vAnimaciones[i]));
    }
}
void KeyFrame::pararTodasLasAnimacionesEnCurso(){
    this->pararAnimacionesFromVector(this->vAnimacionesForever);
    this->pararAnimacionesFromVector(this->vAnimacionesActivas);
}
bool KeyFrame::reproduceAlgunaAnimacion(unsigned long cual){
    if (cual >= this->vAnimaciones.size()) {
        std::cout<<"Animacion no creada\n";
        return false;
    }
    if (this->vAnimaciones[cual].repetitivo) {
        std::cout<<"Animacion infinitta\n";
        return false;
    }
    for (auto j : this->vAnimacionesActivas) {
        if (j == cual) {
            std::cout<<"Animacion ya ejecutando Cancelada";
            this->pararAnimacion(&(this->vAnimaciones[cual]));
            return false;
        }
    }
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
