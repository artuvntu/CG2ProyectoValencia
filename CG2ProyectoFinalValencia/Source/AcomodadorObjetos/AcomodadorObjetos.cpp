//
//  AcomodadorObjetos.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/15/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "AcomodadorObjetos.hpp"

#define ACOMODAROBJETOVERSIONARCHIVO 0x18FF

void AcomodadorObjetos::inicializar(CreadorObjetos *co){
    this->vCreadorObjetos = co;
    this->cargar();
}

void AcomodadorObjetos::dibuja(){
    if (pintaPunteroSeleccion) {
        for (unsigned int i = 0; i<yAcomodos.size(); i++) {
            glPushMatrix();
            glTranslated(yAcomodos[i].ubicacion[0].coordenadas[0], yAcomodos[i].ubicacion[0].coordenadas[1], yAcomodos[i].ubicacion[0].coordenadas[2]);
            glRotated(yAcomodos[i].ubicacion[1].coordenadas[0], 1, 0, 0);
            glRotated(yAcomodos[i].ubicacion[1].coordenadas[1], 0, 1, 0);
            glRotated(yAcomodos[i].ubicacion[1].coordenadas[2], 0, 0, 1);
            glScaled(yAcomodos[i].ubicacion[2].coordenadas[0], yAcomodos[i].ubicacion[2].coordenadas[1], yAcomodos[i].ubicacion[2].coordenadas[2]);
            if (i == puntero) {
                glColor3f(1, 0.6, 0.6);
                vCreadorObjetos->dibujaObjeto(yAcomodos[i].cual);
                glColor3f(1, 1, 1);
            }else{
                vCreadorObjetos->dibujaObjeto(yAcomodos[i].cual);
            }
            glPopMatrix();
        }
    }else{
        for (unsigned int i = 0; i<yAcomodos.size();i++){
            glPushMatrix();
            glTranslated(yAcomodos[i].ubicacion[0].coordenadas[0], yAcomodos[i].ubicacion[0].coordenadas[1], yAcomodos[i].ubicacion[0].coordenadas[2]);
            glRotated(yAcomodos[i].ubicacion[1].coordenadas[0], 1, 0, 0);
            glRotated(yAcomodos[i].ubicacion[1].coordenadas[1], 0, 1, 0);
            glRotated(yAcomodos[i].ubicacion[1].coordenadas[2], 0, 0, 1);
            glScaled(yAcomodos[i].ubicacion[2].coordenadas[0], yAcomodos[i].ubicacion[2].coordenadas[1], yAcomodos[i].ubicacion[2].coordenadas[2]);
            vCreadorObjetos->dibujaObjeto(yAcomodos[i].cual);
            glPopMatrix();
        }
    }
}
void AcomodadorObjetos::teclaDeMenu(unsigned char tecla){
    this->guardar();
    if (tecla == '|') {
        std::cout<<"|\n";
        this->escribeMenu();
        this->drawCursor();
    }
    switch (estado) {
        case inicialAO:
            this->teclaDeMenuInicial(tecla);
            break;
        case BuscaUInt:
            this->teclaDeMenuBuscaUInt(tecla);
            break;
        default:
            break;
    }
}
void AcomodadorObjetos::teclaActivaMenu(){
    this->estado = inicialAO;
    puntero = 0;
    this->menuActivado = true;
    if (yAcomodos.size()!=0) {
        this->pintaPunteroSeleccion = true;
    }
    this->escribeMenu();
    this->drawCursor();
}
void AcomodadorObjetos::escribeMenu(){
    switch (estado) {
        case inicialAO:
            if (yAcomodos.size()!=0) {
                this->describeAcomodo(&yAcomodos[puntero]);
                std::cout<<"Actual: "<<puntero<<" Disponibles: "<<yAcomodos.size()<<"\nM->Mostar Disponibles\nC->Cambiar\nX->Delete\n";
            }else std::cout<<"Crea un acomodo\n";
            std::cout<<"V->Nuevo\nB->Guardar en Archivo\nN->Cargar (Mejor no)\nP->Set tipo\nZ->Salir\n";
            break;
        case BuscaUInt:
            std::cout<<"Accion: \""<<this->AcomodadorObjetosAccionesBuscaUIntToChar[(unsigned char) this->accionDespuesBuscarUInt]<<"\" V Actual: "<<*this->dondeGuardar<<" Max: "<<this->maxDondeGuardar<<" Write: "<<this->temporalIntFromKeyBoard<<" Regresar a "<<this->AcomodadorObjetosEstadosToChar[(unsigned char)this->estadoARegresarBUInt]<<std::endl;
            break;
        default:
            break;
    }
}
void AcomodadorObjetos::drawCursor(){
    std::cout<<"CG2ProyectoFinalValenciaC "<< this->AcomodadorObjetosEstadosToChar[(unsigned char) this->estado] << " $ ";
    if (this->estado == BuscaUInt && this->temporalIntFromKeyBoard != 0) {
        std::cout<<temporalIntFromKeyBoard;
    }
}
void AcomodadorObjetos::teclaDeMenuInicial(unsigned char tecla){
    bool saltar = true;
    if (yAcomodos.size()!=0) {
        switch (tecla) {
            case 'm':
            case 'M':
                std::cout<<"Mostrando\n";
                this->escribeAcomodosDisponibles();
                this->drawCursor();
                break;
            case 'c':
            case 'C':
                std::cout<<"Cambio\n";
                this->escribeAcomodosDisponibles();
                empezarABuscarUInt(&puntero, (unsigned int) yAcomodos.size(), inicialAO);
                break;
            case 'X':
            case 'x':
                if (puntero<yAcomodos.size()) {
                    std::cout<<"Eliminado\n";
                    yAcomodos.erase(yAcomodos.begin()+puntero);
                    if (puntero>=yAcomodos.size()) {
                        puntero = (unsigned int)yAcomodos.size()-1;
                    }
                }else std::cout<<"Error no deberia estar disponible la opcion\n";
                this->drawCursor();
                break;
            case 'p':
            case 'P':
                vCreadorObjetos->escribeObjetosDisponibles();
                this->empezarABuscarUInt(&yAcomodos[puntero].cual, (unsigned int)vCreadorObjetos->yObjetos.size(), inicialAO);
                break;
            default:
                saltar = this->moviminetoModificarObjeto(tecla, &yAcomodos[puntero]);
                break;
        }
        if (saltar) return;
    }
    switch (tecla) {
        case 'v':
        case 'V':
            if (vCreadorObjetos->yObjetos.size()==0) {
                std::cout<<"Crea primero objetos\n";
                return;
            }
            std::cout<<"Nuevo\n";
            yAcomodos.push_back(AcomodadorObjetosAcomodo());
            puntero = (unsigned int)yAcomodos.size()-1;
            yAcomodos[puntero].ubicacion[2].coordenadas[0] = 1;
            yAcomodos[puntero].ubicacion[2].coordenadas[1] = 1;
            yAcomodos[puntero].ubicacion[2].coordenadas[2] = 1;
            if (yAcomodos.size()>=2) {
                yAcomodos[puntero].ubicacion[0].coordenadas[0] = yAcomodos[yAcomodos.size()-2].ubicacion[0].coordenadas[0];
                yAcomodos[puntero].ubicacion[0].coordenadas[1] = yAcomodos[yAcomodos.size()-2].ubicacion[0].coordenadas[1];
                yAcomodos[puntero].ubicacion[0].coordenadas[2] = yAcomodos[yAcomodos.size()-2].ubicacion[0].coordenadas[2];
            }
            this->pintaPunteroSeleccion = true;
            this->drawCursor();
            break;
        case 'B':
        case 'b':
            std::cout<<"Guardar de archivo\n";
            this->guardar();
            this->drawCursor();
            break;
        case 'n':
        case 'N':
            std::cout<<"Cargando archivo\n";
            this->cargar();
            this->drawCursor();
            break;
        case 'z':
        case 'Z':
            std::cout<<"Fuera de acomodador\n";
            this->estado = inicialAO;
            this->pintaPunteroSeleccion = false;
            this->menuActivado = false;
            break;
        default:
            break;
    }

}
void AcomodadorObjetos::teclaDeMenuBuscaUInt(unsigned char tecla){
    if (tecla >= 48 && tecla <= 57) {
        std::cout << (tecla -48);
        this->temporalIntFromKeyBoard= (this->temporalIntFromKeyBoard * 10)+(tecla - 48);
        if (this->temporalIntFromKeyBoard >= this->maxDondeGuardar){
            std::cout<<"\nNumero mayor a los disponibles\n";
            this->estado = this->estadoAnterior;
            this->estadoAnterior = inicialAO;
            this->estadoARegresarBUInt = inicialAO;
            this->drawCursor();
        }
    }else if (tecla == 13){
        std::cout <<std::endl;
        *this->dondeGuardar = this->temporalIntFromKeyBoard;
        this->temporalIntFromKeyBoard = 0;
        this->estado = this->estadoARegresarBUInt;
        this->estadoARegresarBUInt = inicialAO;
        this->estadoAnterior = inicialAO;
        this->ejecutaAccionDespuesBuscarUInt();
        this->escribeMenu();
        this->drawCursor();
    }else{
        std::cout<<"\nCancelado\n";
        this->estado = this->estadoAnterior;
        this->estadoARegresarBUInt = inicialAO;
        this->estadoAnterior = inicialAO;
        this->drawCursor();
    }
}
void AcomodadorObjetos::empezarABuscarUInt(unsigned int *dondeGuardad, unsigned int max, AcomodadorObjetos::AcomodadorObjetosEstados estadoRegresar,AcomodadorObjetosAccionesBuscaUInt accion ){
    this->accionDespuesBuscarUInt = accion;
    this->estadoAnterior = estado;
    this->estadoARegresarBUInt = estadoRegresar;
    this->estado = BuscaUInt;
    this->maxDondeGuardar = max;
    this->dondeGuardar = dondeGuardad;
    this->escribeMenu();
    this->drawCursor();
}
void AcomodadorObjetos::ejecutaAccionDespuesBuscarUInt(){
    switch (this->accionDespuesBuscarUInt) {
        case nada:
            break;
        default:
            break;
    }
}
void AcomodadorObjetos::escribeAcomodosDisponibles(){
    for (int i = 0; i<yAcomodos.size(); i++) {
        std::cout<<i<<".- ";
        this->describeAcomodo(&yAcomodos[i]);
    }
}
void AcomodadorObjetos::describeAcomodo(AcomodadorObjetos::AcomodadorObjetosAcomodo *acomodo){
    std::cout<<vCreadorObjetos->yObjetos[acomodo->cual].id<<" ";
    for (int i = 0; i<9; i++) {
        std::cout<<acomodo->ubicacion[i/3].coordenadas[i%3]<<" ";
    }
    std::cout<<std::endl;
}
void AcomodadorObjetos::guardar(){
    FILE * archivo = fopen(ACOMODADOROBJETOSPATHFILE, "w");
    unsigned int cabecera = ACOMODAROBJETOVERSIONARCHIVO;
    unsigned int cantidad = (unsigned int) this->yAcomodos.size();
    if (archivo == NULL) {
        std::cout<<"Acomodar objeto no enocntre archivo\n";
        return;
    }
    fwrite(&cabecera, sizeof(unsigned int), 1, archivo);
    fwrite(&cantidad, sizeof(unsigned int), 1, archivo);
    for (unsigned int i = 0; i<cantidad; i++) {
        fwrite(yAcomodos[i].ubicacion[0].coordenadas, sizeof(double), 3, archivo);
        fwrite(yAcomodos[i].ubicacion[1].coordenadas, sizeof(double), 3, archivo);
        fwrite(yAcomodos[i].ubicacion[2].coordenadas, sizeof(double), 3, archivo);
        fwrite(vCreadorObjetos->yObjetos[yAcomodos[i].cual].id, sizeof(char), 50, archivo);
    }
    fclose(archivo);
}
void AcomodadorObjetos::cargar(){
    FILE * archivo = fopen(ACOMODADOROBJETOSPATHFILE, "r");
    unsigned int cabecera = 0;
    unsigned int cantidad = 0;
    char nombreAux [50] = "";
    if (archivo == NULL) {
        std::cout<<"Acomodar objeto no enocntre archivo\n";
        this->guardar();
        return;
    }
    fread(&cabecera, sizeof(unsigned int), 1, archivo);
    if (cabecera != ACOMODAROBJETOVERSIONARCHIVO) {
        std::cout<<"Archivo no compatible posible diferencia de version\n";
        return;
    }
    fread(&cantidad, sizeof(unsigned int), 1, archivo);
    for (unsigned int i = 0; i<cantidad; i++) {
        yAcomodos.push_back(AcomodadorObjetosAcomodo());
        fread(yAcomodos[i].ubicacion[0].coordenadas, sizeof(double), 3, archivo);
        fread(yAcomodos[i].ubicacion[1].coordenadas, sizeof(double), 3, archivo);
        fread(yAcomodos[i].ubicacion[2].coordenadas, sizeof(double), 3, archivo);
        fread(nombreAux, sizeof(char), 50, archivo);
        if (!vCreadorObjetos->echateABuscar(nombreAux, &yAcomodos[i].cual)) {
            std::cout<<nombreAux<<" No lo encontre\n";
        }
    }
    std::cout<<"Acomodador Objetos: "<<this->yAcomodos.size()<<"Cargadas \n";
    fclose(archivo);
}
bool AcomodadorObjetos::moviminetoModificarObjeto(unsigned char tecla, AcomodadorObjetos::AcomodadorObjetosAcomodo *acomodo){
    int signo = 1;
    int cual = 0;
    int coor = 0;
    bool despacio = true;
    for (int i = 0; i<18*2; i++) {
        if (tecla == this->teclasMovimientoModificarObjeto[i]) {
            if (i/18!=0) despacio = false;
            i = i%18;
            if (i%2) signo = -1;
            i = i/2;
            cual = i/3;
            coor = i%3;
            if (cual == 1) {
                if (despacio) acomodo->ubicacion[cual].coordenadas[coor] += 11.25*signo;
                else acomodo->ubicacion[cual].coordenadas[coor] += 22.5*signo;
            }else{
                if (despacio) acomodo->ubicacion[cual].coordenadas[coor] += 0.1*signo;
                else acomodo->ubicacion[cual].coordenadas[coor] += 1*signo;
            }
            break;
        }
    }
    return false;
}
