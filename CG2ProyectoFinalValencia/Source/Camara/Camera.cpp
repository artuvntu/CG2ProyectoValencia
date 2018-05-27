//
//  Camera.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/16/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "Camera.hpp"

#define CAMARAVERSIONFILEACTUAL 0x18FF

void Camara::easyPosition(){
    gluLookAt(this->posActual.XYZ[0], this->posActual.XYZ[1], this->posActual.XYZ[2], this->posActual.XYZ[3], this->posActual.XYZ[4], this->posActual.XYZ[5], this->posActual.XYZ[6], this->posActual.XYZ[7], this->posActual.XYZ[8]);
    
}
void Camara::keyboardMove(int type,double intensidad){
    int realType = 0;
    double m;
    double tm[3];
    realType += (type/2)%6;
    if (type%2) {
         intensidad = -intensidad;
    }
    m = intensidad * this->multipler[realType+(6*(type/12))];
    switch (realType) {
        case 0:
//            tm[0] = (cos(this->posActual.Angles[1])*sin(this->posActual.Angles[0]));
//            tm[1] = (sin(this->this->posActual.Angles[1]));
//            tm[2] = (cos(this->this->posActual.Angles[1])*cos(this->posActual.Angles[0]));
            tm[0] = (sin(this->posActual.Angles[0]));
            tm[1] = (0);
            tm[2] = (cos(this->posActual.Angles[0]));
            for(int i=0;i<3;i++){
                this->posActual.XYZ[i] += m * tm[i];
                this->posActual.XYZ[i+3] += m *tm[i] ;
            }
            break;
        case 1:
            tm[0] = (sin(this->posActual.Angles[0]+1.57));
            tm[1] = 0;
            tm[2] = (cos(this->posActual.Angles[0]+1.57));
            for(int i=0;i<3;i++){
                this->posActual.XYZ[i] += m * tm[i];
                this->posActual.XYZ[i+3] += m *tm[i] ;
            }
            break;
        case 2:
//            tm[0] = (cos(this->this->posActual.Angles[1]+1.57)*sin(this->posActual.Angles[0]));
//            tm[1] = (sin(this->this->posActual.Angles[1]+1.57));
//            tm[2] = (cos(this->this->posActual.Angles[1]+1.57)*cos(this->posActual.Angles[0]));
            tm[0] = 0;
            tm[1] = 1;
            tm[2] = 0;
            for(int i=0;i<3;i++){
                this->posActual.XYZ[i] += m * tm[i];
                this->posActual.XYZ[i+3] += m *tm[i] ;
            }

            break;
        case 3:
            this->posActual.Angles[0] += m;
            tm[0] = (cos(this->posActual.Angles[1])*sin(this->posActual.Angles[0]));
            tm[1] = (sin(this->posActual.Angles[1]));
            tm[2] = (cos(this->posActual.Angles[1])*cos(this->posActual.Angles[0]));
            this->posActual.XYZ[3] = this->posActual.XYZ[0]+tm[0];
            this->posActual.XYZ[4] = this->posActual.XYZ[1]+tm[1];
            this->posActual.XYZ[5] = this->posActual.XYZ[2]+tm[2];
            
            break;
        case 4:
            this->posActual.Angles[1] += m;
            tm[0] = (cos(this->posActual.Angles[1])*sin(this->posActual.Angles[0]));
            tm[1] = (sin(this->posActual.Angles[1]));
            tm[2] = (cos(this->posActual.Angles[1])*cos(this->posActual.Angles[0]));
            this->posActual.XYZ[3] = this->posActual.XYZ[0]+tm[0];
            this->posActual.XYZ[4] = this->posActual.XYZ[1]+tm[1];
            this->posActual.XYZ[5] = this->posActual.XYZ[2]+tm[2];
            break;
        case 5:
            this->posActual.Angles[2] += m;
            this->posActual.XYZ[6] = cos(this->posActual.Angles[2]);
            this->posActual.XYZ[7] = sin(this->posActual.Angles[2]);
            break;
        default:
            std::cout<<"Valor no legible Camara" << std::endl;
            return;
            break;
    }
    glutPostRedisplay();
}
void Camara::describeCamaraPos(CamaraPos *pos){
    std::cout<<"CamaraPos: N: \""<<pos->id<<"\" P:{";
    for (int i=0; i<9; i++) {
        std::cout<<pos->XYZ[i]<<", ";
    }
    std::cout<<"} A:{";
    for (int i = 0;i<3;i++){
        std::cout<<pos->Angles[i]<<", ";
    }
    std::cout<<"}\n";
}
void Camara::teclaActivaMenu(){
    menuActivado = true;
    escribeMenu();
    drawCursor();
}
void Camara::teclaDeMenu(unsigned char tecla){
    guardar();
    if (tecla == '|') {
        escribeMenu();
        drawCursor();
    }
    switch (estado) {
        case inicial:
            teclaDeMenuInicial(tecla);
            break;
        case buscandoUInt:
            if(vUIClassAux.teclaDeMenu(tecla)){
                ejecutarAccionBUint();
            }
            break;
        default:
            break;
    }
}
void Camara::escribeMenu(){
    switch (estado) {
        case inicial:
            if (yCamaras.size()!=0) {
                std::cout<<"C->Cambio\nX->Delete\nP->Asignar\nB->Como Inicial\n";
            }else std::cout<<"Crea una\n";
            std::cout<<"1->Guardar\n2->Cargar (Mejor aun no)\nZ->Salir\nN->Nuevo\nM->Mostrar\n";
            break;
        case buscandoUInt:
            vUIClassAux.escribeMenu();
            break;
        default:
            break;
    }
}
void Camara::drawCursor(){
    if (estado == inicial) {
        vUIClassAux.drawCursor();
        return;
    }
    std::cout<<"CG2ProyectoFinalValenciaCAM Inicial $ ";
}
void Camara::inicializar(){
    this->cargar();
    this->cambiaPosCual(cualInicial);
    sprintf(posActual.id, "Actual");
}
void Camara::ejecutarAccionBUint(){
    switch (accionBUInt) {
        case 1:
            this->copiaSoloNumeros(&posActual, &yCamaras[puntero]);
            break;
            
        default:
            break;
    }
    escribeMenu();
    drawCursor();
}

void Camara::teclaDeMenuInicial(unsigned char tecla){
    bool salta = true;
    if (yCamaras.size()!= 0) {
        switch (tecla) {
            case 'c':
            case 'C':
                std::cout<<"Cambio\n";
                this->describeCamarasDisponibles();
                this->estado = buscandoUInt;
                this->vUIClassAux.empezarABuscarUInt(&puntero,(unsigned int) yCamaras.size(), (unsigned char*)&estado, (unsigned char)inicial, (unsigned char)inicial, 1, 0, &accionBUInt);
                break;
            case 'x':
            case 'X':
                if (puntero>=yCamaras.size()) {
                    std::cout<<"Error borrando\n";
                }else{
                    std::cout<<"Delete\n";
                    yCamaras.erase(yCamaras.begin()+puntero);
                    if (puntero>=yCamaras.size()) {
                        puntero = (unsigned int) yCamaras.size()-1;
                    }
                }
                drawCursor();
                break;
            case 'p':
            case 'P':
                std::cout<<"Asignado";
                this->describeCamaraPos(&posActual);
                this->copiaSoloNumeros(&yCamaras[puntero], &posActual);
                drawCursor();
                break;
            case 'b':
            case 'B':
                std::cout<<"Guardando como inical\n";
                this->cualInicial = puntero;
                drawCursor();
                break;
            default:
                salta = false;
                break;
        }
        if (salta) return;
    }
    switch (tecla) {
        case 'n':
        case 'N':
            yCamaras.push_back(posActual);
            puntero =(unsigned int) yCamaras.size()-1;
//            yCamaras[puntero] = posActual;
            estado = buscandoUInt;
            vUIClassAux.empezarABuscarString(yCamaras[puntero].id, MAXCHAR, (unsigned char*) &estado, (unsigned char) inicial, (unsigned char) inicial, 0, 0, &accionBUInt);
            break;
        case 'm':
        case 'M':
            this->describeCamarasDisponibles();
            drawCursor();
            break;
        case 'z':
        case 'Z':
            std::cout<<"Fuera de Menu Camara\n";
            this->menuActivado = false;
            break;
        case '1':
            std::cout<<"Guardando\n";
            guardar();
            drawCursor();
            break;
        case '2':
            std::cout<<"Cargando\n";
            cargar();
            drawCursor();
        default:
            teclaMove(tecla);
            break;
    }
}
void Camara::guardar(){
    FILE *archivo = fopen(CAMARAPATHFILE, "w");
    unsigned int cabecera = CAMARAVERSIONFILEACTUAL;
    unsigned int aux = 0;
    if (archivo==NULL) {
        std::cout<<"No logre crear Archivo vCamara\n";
    }
    fwrite(&cabecera, sizeof(unsigned int), 1, archivo);
    aux = (unsigned int) yCamaras.size();
    fwrite(&aux, sizeof(unsigned int), 1, archivo);
    for (unsigned int i = 0; i<aux; i++) {
        fwrite(yCamaras[i].id, sizeof(char), 50, archivo);
        fwrite(yCamaras[i].XYZ, sizeof(double), 9, archivo);
        fwrite(yCamaras[i].Angles, sizeof(double), 3, archivo);
    }
    fwrite(&cualInicial, sizeof(unsigned int), 1, archivo);
    fclose(archivo);
}
void Camara::cargar(){
    FILE *archivo = fopen(CAMARAPATHFILE, "r");
    unsigned int cabecera = 0;
    unsigned int aux = 0;
    if (archivo==NULL) {
        std::cout<<"No encontre archivo"<<CAMARAPATHFILE<<"\n";
        guardar();
        return;
    }
    fread(&cabecera, sizeof(unsigned int), 1, archivo);
    if (cabecera != CAMARAVERSIONFILEACTUAL) {
        std::cout<<"Versiones no coinciden "<<cabecera<<" "<<CAMARAVERSIONFILEACTUAL<<"\n";
        fclose(archivo);
        return;
    }
    fread(&aux, sizeof(unsigned int), 1, archivo);
    for (unsigned int i = 0; i<aux; i++) {
        yCamaras.push_back(CamaraPos());
        fread(yCamaras[i].id, sizeof(char), 50, archivo);
        fread(yCamaras[i].XYZ, sizeof(double), 9, archivo);
        fread(yCamaras[i].Angles, sizeof(double), 3, archivo);
    }
    fread(&cualInicial, sizeof(unsigned int), 1, archivo);
    fclose(archivo);
    std::cout<<"Camara: "<<yCamaras.size()<<" Cargadas\n";
}
void Camara::describeCamarasDisponibles(){
    describeCamaraPos(&posActual);
    std::cout<<std::endl;
    for (unsigned int i = 0; i<yCamaras.size(); i++) {
        describeCamaraPos(&yCamaras[i]);
    }
}
bool Camara::teclaMove(unsigned char tecla){
    for (int i=0; this->teclasMovimiento[i] != '\0'; i++) {
        if (this->teclasMovimiento[i] == tecla) {
            this->keyboardMove(i);
            return true;
        }
    }
    return false;
}
void Camara::cambiaPosCual(unsigned int c){
    if (c<yCamaras.size()) this->copiaSoloNumeros(&posActual, &yCamaras[c]);
    else std::cout<<"No exite Camara\n";
}
void Camara::copiaSoloNumeros(Camara::CamaraPos *destino, Camara::CamaraPos *fuente){
    for (int i =0; i<9; i++) {
        destino->XYZ[i] = fuente->XYZ[i];
    }
    for (int i = 0; i<3; i++) {
        destino->Angles[i] = fuente->Angles[i];
    }
}
