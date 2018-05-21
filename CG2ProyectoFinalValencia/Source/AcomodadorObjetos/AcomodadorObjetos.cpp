//
//  AcomodadorObjetos.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/15/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "AcomodadorObjetos.hpp"

#define ACOMODAROBJETOVERSIONARCHIVO 0x18FF

void AcomodadorObjetos::inicializar(CreadorObjetos *co, UIClassAux *uic, Camara *cam){
    this->vCreadorObjetos = co;
    this->vUIClassAux = uic;
    this->vCamara = cam;
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
            if(this->vUIClassAux->teclaDeMenu(tecla)){
                this->ejecutaAccionDespuesBuscarUInt(accionDespuesBuscarUInt);
            }
//            this->teclaDeMenuBuscaUInt(tecla);
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
    this->vUIClassAux->empezarABuscarMove(&this->yAcomodos[puntero].ubicacion[0].coordenadas[0], &this->yAcomodos[puntero].ubicacion[0].coordenadas[1], &this->yAcomodos[puntero].ubicacion[0].coordenadas[2], &this->yAcomodos[puntero].ubicacion[2].coordenadas[0], &this->yAcomodos[puntero].ubicacion[2].coordenadas[1], &this->yAcomodos[puntero].ubicacion[2].coordenadas[2], &this->yAcomodos[puntero].ubicacion[1].coordenadas[0], &this->yAcomodos[puntero].ubicacion[1].coordenadas[1], &this->yAcomodos[puntero].ubicacion[1].coordenadas[2], 0.1, 1, 11.25, 45);
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
            std::cout<<"N->Nuevo\n1->Guardar en Archivo\n2->Cargar (Mejor no)\nP->Set tipo\nZ->Salir\n";
            break;
        case BuscaUInt:
            this->vUIClassAux->escribeMenu();
            break;
        default:
            break;
    }
}
void AcomodadorObjetos::drawCursor(){
    if (this->estado == BuscaUInt) {
        this->vUIClassAux->drawCursor();
    }else{
        std::cout<<"CG2ProyectoFinalValenciaC "<< this->AcomodadorObjetosEstadosToChar[(unsigned char) this->estado] << " $ ";
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
                this->estado = BuscaUInt;
                this->vUIClassAux->empezarABuscarUInt(&puntero, (unsigned int)yAcomodos.size(), (unsigned char *)&this->estado, (unsigned char)inicialAO, (unsigned char)inicialAO, (unsigned char) cambioPuntero, (unsigned char) nada,(unsigned char*)&accionDespuesBuscarUInt);
                break;
            case 'X':
            case 'x':
                if (puntero<yAcomodos.size()) {
                    std::cout<<"Eliminado\n";
                    yAcomodos.erase(yAcomodos.begin()+puntero);
                    if (puntero>=yAcomodos.size()) {
                        puntero = (unsigned int)yAcomodos.size()-1;
                    }
                    if (yAcomodos.size()!=0) {
                        this->vUIClassAux->empezarABuscarMove(&this->yAcomodos[puntero].ubicacion[0].coordenadas[0], &this->yAcomodos[puntero].ubicacion[0].coordenadas[1], &this->yAcomodos[puntero].ubicacion[0].coordenadas[2], &this->yAcomodos[puntero].ubicacion[2].coordenadas[0], &this->yAcomodos[puntero].ubicacion[2].coordenadas[1], &this->yAcomodos[puntero].ubicacion[2].coordenadas[2], &this->yAcomodos[puntero].ubicacion[1].coordenadas[0], &this->yAcomodos[puntero].ubicacion[1].coordenadas[1], &this->yAcomodos[puntero].ubicacion[1].coordenadas[2], 0.1, 1, 11.25, 45);
                    }
                }else std::cout<<"Error no deberia estar disponible la opcion\n";
                this->drawCursor();
                break;
            case 'p':
            case 'P':
                vCreadorObjetos->escribeObjetosDisponibles();
                this->estado = BuscaUInt;
                this->vUIClassAux->empezarABuscarUInt(&yAcomodos[puntero].cual, (unsigned int)vCreadorObjetos->yObjetos.size(),(unsigned char *) &this->estado, (unsigned char)inicialAO, (unsigned char) inicialAO, (unsigned char) nada, (unsigned char) nada, (unsigned char *)&accionDespuesBuscarUInt);
                break;
            case '3':
                std::cout<<"Copiar\n";
                yAcomodos.push_back(yAcomodos[puntero]);
                puntero =(unsigned int) yAcomodos.size()-1;
                yAcomodos[puntero].ubicacion[0].coordenadas[0] = vCamara->posActual.XYZ[3];
                yAcomodos[puntero].ubicacion[0].coordenadas[1] = vCamara->posActual.XYZ[4];
                yAcomodos[puntero].ubicacion[0].coordenadas[2] = vCamara->posActual.XYZ[5];
                this->vUIClassAux->empezarABuscarMove(&this->yAcomodos[puntero].ubicacion[0].coordenadas[0], &this->yAcomodos[puntero].ubicacion[0].coordenadas[1], &this->yAcomodos[puntero].ubicacion[0].coordenadas[2], &this->yAcomodos[puntero].ubicacion[2].coordenadas[0], &this->yAcomodos[puntero].ubicacion[2].coordenadas[1], &this->yAcomodos[puntero].ubicacion[2].coordenadas[2], &this->yAcomodos[puntero].ubicacion[1].coordenadas[0], &this->yAcomodos[puntero].ubicacion[1].coordenadas[1], &this->yAcomodos[puntero].ubicacion[1].coordenadas[2], 0.1, 1, 11.25, 45);
                this->drawCursor();
                break;
            default:
                saltar = this->vUIClassAux->teclaMove(tecla);
                break;
        }
        if (saltar) return;
    }
    switch (tecla) {
        case 'n':
        case 'N':
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
            yAcomodos[puntero].ubicacion[0].coordenadas[0] = vCamara->posActual.XYZ[3];
            yAcomodos[puntero].ubicacion[0].coordenadas[1] = vCamara->posActual.XYZ[4];
            yAcomodos[puntero].ubicacion[0].coordenadas[2] = vCamara->posActual.XYZ[5];
            this->pintaPunteroSeleccion = true;
            this->vUIClassAux->empezarABuscarMove(&this->yAcomodos[puntero].ubicacion[0].coordenadas[0], &this->yAcomodos[puntero].ubicacion[0].coordenadas[1], &this->yAcomodos[puntero].ubicacion[0].coordenadas[2], &this->yAcomodos[puntero].ubicacion[2].coordenadas[0], &this->yAcomodos[puntero].ubicacion[2].coordenadas[1], &this->yAcomodos[puntero].ubicacion[2].coordenadas[2], &this->yAcomodos[puntero].ubicacion[1].coordenadas[0], &this->yAcomodos[puntero].ubicacion[1].coordenadas[1], &this->yAcomodos[puntero].ubicacion[1].coordenadas[2], 0.1, 1, 11.25, 45);
            this->drawCursor();
            break;
        case '1':
            std::cout<<"Guardar de archivo\n";
            this->guardar();
            this->drawCursor();
            break;
        case '2':
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
void AcomodadorObjetos::ejecutaAccionDespuesBuscarUInt(unsigned char accion){
    AcomodadorObjetosAccionesBuscaUInt a = (AcomodadorObjetosAccionesBuscaUInt) accion;
    switch (a) {
        case nada:
            break;
        case cambioPuntero:
            this->vUIClassAux->empezarABuscarMove(&this->yAcomodos[puntero].ubicacion[0].coordenadas[0], &this->yAcomodos[puntero].ubicacion[0].coordenadas[1], &this->yAcomodos[puntero].ubicacion[0].coordenadas[2], &this->yAcomodos[puntero].ubicacion[2].coordenadas[0], &this->yAcomodos[puntero].ubicacion[2].coordenadas[1], &this->yAcomodos[puntero].ubicacion[2].coordenadas[2], &this->yAcomodos[puntero].ubicacion[1].coordenadas[0], &this->yAcomodos[puntero].ubicacion[1].coordenadas[1], &this->yAcomodos[puntero].ubicacion[1].coordenadas[2], 0.1, 1, 11.25, 45);
            break;
        default:
            break;
    }
    this->escribeMenu();
    this->drawCursor();
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
