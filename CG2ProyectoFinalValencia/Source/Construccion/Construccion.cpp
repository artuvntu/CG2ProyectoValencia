//
//  Construccion.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/8/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "Construccion.hpp"

#define CONSTRUCCIONVERSIONARCHIVOS 0x20FF

void Construccion::inicializar(Primitivas *primitivasactual, CargadorImage *cargadorImageactual, KeyFrame *keyFrameactual){
    this->vPrimitivas = primitivasactual;
    this->vCargadorImage = cargadorImageactual;
    this->vKeyFrame = keyFrameactual;
    char nombreAuxiliarPuerta01[MAXCHAR] = "puerta01";
    char nombreAuxiliarMaderaBlanca01[MAXCHAR]= "maderaBlanca01";
    char nombreAuxiliarLadrillo01[MAXCHAR] = "ladrillo01";
    char nombreAuxiliarVentana01[MAXCHAR] = "ventana01";
    char nombres[2][MAXCHAR] = {
        "accesoria01","zaguan01"
    };
    PrimitivasSelectTexture texturaAuxMaderaBlanca01 = PrimitivasSelectTexture();
    PrimitivasSelectTexture texturaAuxPuerta01 = PrimitivasSelectTexture();
    PrimitivasSelectTexture texturaAuxVentana01 = PrimitivasSelectTexture();
    PrimitivasSelectTexture texaux[3] = {PrimitivasSelectTexture(),PrimitivasSelectTexture()};
    if (!this->vCargadorImage->echateABuscarTexture(nombreAuxiliarPuerta01, &texturaAuxPuerta01.cualTextura)) {
        std::cout<< nombreAuxiliarPuerta01 << " No encontre esa textura :(\n";
    }
    if (!this->vCargadorImage->echateABuscarTexture(nombreAuxiliarMaderaBlanca01, &texturaAuxMaderaBlanca01.cualTextura)) {
        std::cout<< nombreAuxiliarMaderaBlanca01 << " No encontre esa textura :(\n";
    }
    if (!this->vCargadorImage->echateABuscarTexture(nombreAuxiliarLadrillo01, &this->defaultTexture.cualTextura)) {
        std::cout<< nombreAuxiliarLadrillo01 << " No encontre esa textura :(\n";
    }
    if (!this->vCargadorImage->echateABuscarTexture(nombreAuxiliarVentana01, &texturaAuxVentana01.cualTextura)) {
        std::cout<< nombreAuxiliarLadrillo01 << " No encontre esa textura :(\n";
    }
    if (!this->vCargadorImage->echateABuscarTexture(nombres[0], &texaux[0].cualTextura)) {
        std::cout<< nombres[0] << " No encontre esa textura :(\n";
    }
    if (!this->vCargadorImage->echateABuscarTexture(nombres[1], &texaux[1].cualTextura)) {
        std::cout<< nombres[1] << " No encontre esa textura :(\n";
    }
    this->puertaNormalTexturas.push_back(texturaAuxPuerta01);
    this->puertaNormalTexturas.push_back(texturaAuxMaderaBlanca01);
    this->puertaNormalTexturas.push_back(texturaAuxPuerta01);
    this->puertaNormalTexturas.push_back(texturaAuxMaderaBlanca01);
    this->puertaNormalTexturas.push_back(texturaAuxMaderaBlanca01);
    this->puertaNormalTexturas.push_back(texturaAuxMaderaBlanca01);
    
    texaux[2] = texaux[1];
    texaux[2].posicionInicio[0] = vCargadorImage->texturas[texaux[2].cualTextura].cantidadRep[1]/2.0;
    for (int i = 0; i<6; i++) {
        this->ventanaNormalTexturas.push_back(texturaAuxVentana01);
        this->accesoriaTextura.push_back(texaux[0]);
        this->zaguanTextureD.push_back(texaux[1]);
        this->zaguanTextureI.push_back(texaux[2]);
    }
    this->cargar();
    
    char nombreTexturaCielo[MAXCHAR] = "cielo01";
    char nombreTexturaSuelo[MAXCHAR] = "pasto01";
    if(!this->vCargadorImage->echateABuscarTexture(nombreTexturaCielo, &this->textureMundo[0].cualTextura))std::cout<<nombreTexturaCielo<<" no encontrada";
    if(!this->vCargadorImage->echateABuscarTexture(nombreTexturaSuelo, &this->textureMundo[1].cualTextura))std::cout<<nombreTexturaSuelo<<" no encontrada";
    this->textureMundo[2].cualTextura = this->textureMundo[2].cualTextura;
    this->textureMundo[0].posicionInicio[1] = 200;
    
}
void Construccion::teclaActivaMenu(){
    std::cout<<"Menu Construccion\n";
    this->estado = inicial;
    this->escribeMenu();
    this->drawCursor();
    this->menuActivado = true;
}
void Construccion::teclaDeMenu(unsigned char tecla){
    if (tecla == '|') {
        this->escribeMenu();
        this->drawCursor();
        return;
    }
    switch (estado) {
        case inicial:
            teclaDeMenuInicial(tecla);
            break;
        case agregarCosa:
            teclaDeMenuAgregarCosa(tecla);
            break;
        case editarCosa:
            teclaDeMenuEditarCosa(tecla);
            break;
        case borrarCosa:
            teclaDeMenuBorrarCosa(tecla);
            break;
        case buscaUInt:
            teclaDeMenuBuscaUInt(tecla);
            break;
        case modificarEscaleras:
            teclaDeMenuModificarEscaleras(tecla);
            break;
        case modificarPared:
            teclaDeMenuModificarPared(tecla);
            break;
        case modificarSuelo:
            teclaDeMenuModificarSuelo(tecla);
            break;
        case modificarTextura:
            teclaDeMenuTextura(tecla);
            break;
        default:
            std::cout<<"Error construccion estado no analizado\n";
            break;
    }
}
void Construccion::dibujaAntes(){
    this->vPrimitivas->mundo(&this->textureMundo[0], &this->textureMundo[2], &this->textureMundo[1]);
    for (int i = 0; i<this->yParedes.size(); i++) {
        this->dibujaPared(&(yParedes[i]));
    }
    for (int i = 0; i<this->ySuelos.size(); i++) {
        this->dibujaSuelo(&(ySuelos[i]));
    }
    for (int i = 0; i<this->yEscaleras.size(); i++) {
        this->dibujaEscaleras(&(yEscaleras[i]));
    }
    if (dibujaParedT) {
        this->dibujaPared(&this->paredTemporal);
    }
    if (dibujaEscaleraT) {
        this->dibujaEscaleras(&this->escalerasTemporales);
    }
    if (dibujaSueloT) {
        this->dibujaSuelo(&this->sueloTemporal);
    }
}
void Construccion::escribeMenu(){
    switch (this->estado) {
        case inicial:
            std::cout<<"C->Crear Cosas\nB->Borrar Cosas\nE->Editar Cosas\nL->Cargar De Archivo(Mejor no)\nG->Guardar En Archivo\nS->Salir\n";
            break;
        case agregarCosa:
            std::cout<<"G->Guardar\nS->Salir\nM->Modificar\n";
            break;
        case editarCosa:
            std::cout<<"Actual: "<<this->punteroEditar<<" Disponibles: "<<this->cuantosDisponiblesDe(this->objetoActual)<<"\nP->Mostrar Disponibles\nC->Cambiar\nM->Modificar\nT->Terminar\n";
            break;
        case borrarCosa:
            std::cout<<"Actual: "<<this->punteroEditar<<" Disponibles: "<<this->cuantosDisponiblesDe(this->objetoActual)<<"P->Mostrar Disponibles\nC->Cambiar\nD->Delete\nT->Terminar\n";
            break;
        case buscaUInt:
            std::cout<<"Accion: \""<<this->accionesBuscarUIntToChar[(unsigned char)this->accionDespuesBuscarInt]<<"\" V Actual: "<<*this->dondeGuardar<<" Max: "<<this->maxDondeGuardar<<" Write: "<<this->temporalIntFromKeyBoard<<" Regresar a "<<this->estadosToChar[(unsigned char)this->estadoARegresar]<<std::endl;
            break;
        case modificarPared:
            std::cout<<"wsadqeikjluory\n";
            this->describePared(*this->paredModificable);
            std::cout<<"T->Modificar Textura\nC->Copiar\nZ->Salir\nX->CambiarTipo\n";
            if (this->paredModificable->tipoPared != paredNormal) {
                std::cout<<"V->Tipo Ventana/Puerta\n";
            }
            break;
        case modificarSuelo:
            std::cout<<"ikjluo\n";
            this->describeSuelo(*this->sueloModificable);
            std::cout<<"C->Cambiar Vertice\nM->Mostrar Vertices\n\"\\n\"->Crear nuevo\nT->ModificarTexturas\nB->Borrar Vertice\nX->Salir\n";
            break;
        case modificarEscaleras:
            std::cout<<"wsadikjluo\n";
            this->describeEscaleras(*this->escalerasModificable);
            std::cout<<"T->Modificar Textura\nC->Copiar\nX->Salir\nV->No. Escalones\n";
            break;
        case modificarTextura:
            std::cout<<"M->Mostar\nC->Cambio Select Texture\nS->Set To Texture\nT->Terminar\n";
            break;
        default:
            std::cout<<"Construccion escribe menu estado no encontrado\n";
            break;
    }
}
void Construccion::drawCursor(){
    std::cout<<"CG2ProyectoFinalValenciaC "<< this->estadosToChar[(unsigned char)this->estado] << " $ ";
    if (this->estado == buscaUInt && this->temporalIntFromKeyBoard != 0) {
        std::cout<<temporalIntFromKeyBoard;
    }
}
void Construccion::escribeDisponibles(int cual){
    switch (cual) {
        case -1:
            this->escribeTipoConstruccion();
            break;
        case (int) pared:
            this->escribeParedesDisponibles();
            break;
        case (int) escalera:
            this->escribeEscalerasDisponibles();
            break;
        case (int) suelo:
            this->escribeSueloDisponibles();
            break;
        default:
            break;
    }
}
void Construccion::escribeTipoConstruccion(){
    for (int i = 0; i<3; i++) {
        std::cout<<i<<".- "<< this->tipoConstruccionToChar[i]<<std::endl;
    }
}
void Construccion::escribeParedesDisponibles(){
    for (int i = 0; i<this->yParedes.size(); i++) {
        std::cout<<i<<".- ";
        this->describePared(this->yParedes[i]);
    }
}
void Construccion::escribeSueloDisponibles(){
    for (int i = 0; i<this->ySuelos.size(); i++) {
        std::cout<<i<<".- ";
        this->describeSuelo(this->ySuelos[i]);
    }
}
void Construccion::escribeEscalerasDisponibles(){
    for (int i = 0; i<this->yEscaleras.size(); i++) {
        std::cout<<i<<".- ";
        this->describeEscaleras(this->yEscaleras[i]);
    }
}
void Construccion::describePared(ConstruccionPared pared){
    std::cout<<"Pared: \""<<pared.id<<"\" ";
    std::cout<<"P: ";
    vPrimitivas->describePunto(pared.vertice[0]);
    std::cout<<" T: ";
    vPrimitivas->describePunto(pared.vertice[1]);
    std::cout<<" A: "<<pared.angulo;
    if (pared.tipoPared != paredNormal) {
        std::cout<<" "<<this->ConstruccionTipoParedToChar[(unsigned int)pared.tipoPared]<<" ";
        switch (pared.tipoPared) {
            case paredVentana:
                std::cout<<this->ConstruccionTipoVentanaToChar[(unsigned int)pared.tipoVentana];
                break;
            case paredPuerta:
                std::cout<<this->ConstruccionTipoPuertaToChar[(unsigned int)pared.tipoPuerta];
                break;
            default:
                break;
        }
    }
    std::cout<<std::endl;
}
void Construccion::describeSuelo(ConstruccionSuelo suelo){
    std::cout<<"Suelo: \""<<suelo.id<<"\"";
    if (suelo.vertices.size()!=0) {
        std::cout<<" P: ";
        vPrimitivas->describePunto(suelo.vertices[0]);
    }
    std::cout<<" V: "<<suelo.vertices.size()<<std::endl;
}
void Construccion::describeEscaleras(ConstruccionEscaleras escaleras){
    std::cout<<"Escaleras: \""<<escaleras.id<<"\" ";
    std::cout<<"P: ";
    vPrimitivas->describePunto(escaleras.vertice[0]);
    std::cout<<" T: ";
    vPrimitivas->describePunto(escaleras.vertice[1]);
    std::cout<<" A: "<<escaleras.angulo<<" E: "<<escaleras.cantidadEscalones<<std::endl;
}
void Construccion::teclaDeMenuInicial(unsigned char tecla){
    switch (tecla) {
        case 'c':
        case 'C':
            //Crear
            std::cout<<"Crear\n";
            this->escribeDisponibles(-1);
            this->empezarABuscarUint((unsigned int *)&(this->objetoActual), 3, agregarCosa,empezarACrear);
            break;
        case 'B':
        case 'b':
            //Borrar
            std::cout<<"Borrar\n";
            this->escribeDisponibles(-1);
            this->empezarABuscarUint((unsigned int *)&(this->objetoActual), 3, borrarCosa);
            break;
        case 'E':
        case 'e':
            //Editar
            std::cout<<"Editar\n";
            this->escribeDisponibles(-1);
            this->empezarABuscarUint((unsigned int *)&(this->objetoActual), 3, editarCosa);
            break;
        case 'l':
        case 'L':
            //Load
            std::cout<<"Cargar\n";
            this->cargar();
            this->drawCursor();
            break;
        case 'g':
        case 'G':
            //Guardar
            std::cout<<"Guardar\n";
            this->guardar();
            this->drawCursor();
            break;
        case 'S':
        case 's':
            //Salir
            this->ventanasADibujar.clear();
            for (int i = 0; i<this->yParedes.size(); i++) {
                if (yParedes[i].tipoPared == paredVentana) {
                    this->ventanasADibujar.push_back(i);
                }
            }
            std::cout<<"Fuera menu Construccion\n";
            this->menuActivado = false;
            break;
        default:
            std::cout<<"Error\n";
            break;
    }
}
void Construccion::teclaDeMenuBuscaUInt(unsigned char tecla){
    if (tecla >= 48 && tecla <= 57) {
        std::cout << (tecla -48);
        this->temporalIntFromKeyBoard= (this->temporalIntFromKeyBoard * 10)+(tecla - 48);
        if (this->temporalIntFromKeyBoard >= this->maxDondeGuardar){
            std::cout<<"\nNumero mayor a los disponibles\n";
            this->estado = this->estadoAnterior;
            this->estadoAnterior = inicial;
            this->estadoARegresar = inicial;
            this->drawCursor();
        }
    }else if (tecla == 13){
        std::cout <<std::endl;
        *this->dondeGuardar = this->temporalIntFromKeyBoard;
        this->temporalIntFromKeyBoard = 0;
        this->estado = this->estadoARegresar;
        this->estadoARegresar = inicial;
        this->estadoAnterior = inicial;
        this->ejecutaAccionDespuesBuscarUInt();
        this->escribeMenu();
        this->drawCursor();
    }else{
        std::cout<<"\nCancelado\n";
        this->estado = this->estadoAnterior;
        this->estadoARegresar = inicial;
        this->estadoAnterior = inicial;
        this->drawCursor();
    }
}
void Construccion:: teclaDeMenuAgregarCosa(unsigned char tecla){
    switch (tecla) {
        case 'm':
        case 'M':
            //Modificar
            std::cout<<"Modificar\n";
            this->empezarAModificar(-1, agregarCosa);
            break;
        case 'g':
        case 'G':
            //Guardar
            std::cout<<"Guardar\n";
            this->guardarModificacionTemporal();
            this->estado = inicial;
            this->escribeMenu();
            this->drawCursor();
            break;
        case 's':
        case 'S':
            //Salir
            std::cout<<"Salir\n";
            this->cancelarModificacionTemporal();
            this->estado = inicial;
            this->escribeMenu();
            this->drawCursor();
            break;
        default:
            break;
    }
}
void Construccion::teclaDeMenuEditarCosa(unsigned char tecla){
    switch (tecla) {
        case 'p':
        case 'P':
            //Mostrar
            std::cout<<"Mostrar Disponibles\n";
            this->escribeDisponibles((unsigned int)this->objetoActual);
            this->drawCursor();
            break;
        case 'c':
        case 'C':
            //Cambiar Elegido
            std::cout<<"Cambio Eleccion\n";
            this->empezarABuscarUint(&this->punteroEditar,(unsigned int) this->cuantosDisponiblesDe(this->objetoActual), editarCosa);
            break;
        case 'm':
        case 'M':
            //Modificar
            if (this->cuantosDisponiblesDe(this->objetoActual)!=0) {
                std::cout<<"Modificando "<<this->punteroEditar;
                this->empezarAModificar(this->punteroEditar, editarCosa);
            }else{
                std::cout<<"No existe elemento que modificar\n";
                this->drawCursor();
            }
            break;
        case 't':
        case 'T':
            //Terminar
            std::cout<<"Terminar\n";
            this->estado = inicial;
            this->escribeMenu();
            this->drawCursor();
        default:
            break;
    }
}
void Construccion::teclaDeMenuBorrarCosa(unsigned char tecla){
    switch (tecla) {case 'p':
        case 'P':
            //Mostrar
            std::cout<<"Mostrar Disponibles\n";
            this->escribeDisponibles((unsigned int)this->objetoActual);
            this->drawCursor();
            break;
        case 'c':
        case 'C':
            //Cambiar Elegido
            std::cout<<"Cambio Eleccion\n";
            this->empezarABuscarUint(&this->punteroEditar,(unsigned int) this->cuantosDisponiblesDe(this->objetoActual), borrarCosa);
            break;
        case 'd':
        case 'D':
            //Delete
            if (this->cuantosDisponiblesDe(this->objetoActual)!=0) {
                std::cout<<"Borrando "<<this->punteroEditar;
                this->borrarObjeto(this->objetoActual, this->objetoActual);
            }else{
                std::cout<<"No existe elemento que modificar\n";
                this->drawCursor();
            }
            break;
        case 't':
        case 'T':
            //Terminar
            std::cout<<"Terminar\n";
            this->estado = inicial;
            this->escribeMenu();
            this->drawCursor();
        default:
            break;
    }
}
void Construccion::teclaDeMenuModificarPared(unsigned char tecla){
    switch (tecla) {
        case 't':
        case 'T':
            //Textura
            std::cout<<"Textura\n";
            this->empezarAModificarTextura(&(this->paredModificable->texturaMain), modificarPared);
            break;
        case 'z':
        case 'Z':
            //Salir
            std::cout<<"Salir\n";
            this->estado = this->estadoARegresarModificar;
            this->escribeMenu();
            this->drawCursor();
            break;
        case 'x':
        case 'X':
            //Cambiar
            std::cout<<"Cambiar tipo\n";
            this->escribeEnOrdencharArray(this->ConstruccionTipoParedToChar, 3);
            this->empezarABuscarUint((unsigned int *)&this->paredModificable->tipoPared, 3, modificarPared,modificarParedAsegurateCambioTipoCompleto);
            break;
        case 'v':
        case 'V':
            //Cambia tipo
            switch (this->paredModificable->tipoPared) {
                case paredPuerta:
                    std::cout<<"Cambia tipo puerta\n";
                    this->escribeEnOrdencharArray(this->ConstruccionTipoPuertaToChar, 5);
                    this->empezarABuscarUint((unsigned int*)&this->paredModificable->tipoPuerta, 5, modificarPared,modificarParedAsegurateCambioTipoCompleto);
                    break;
                case paredVentana:
                    std::cout<<"Cambia tipo ventana\n";
                    this->escribeEnOrdencharArray(this->ConstruccionTipoVentanaToChar, 2);
                    this->empezarABuscarUint((unsigned int *)&this->paredModificable->tipoVentana, 2, modificarPared,modificarParedAsegurateCambioTipoCompleto);
                    break;
                case paredNormal:
                default:
                    std::cout<<"No creo que pueda modificar eso\n";
                    break;
            }
            break;
        case 'C':
        case 'c':
            //Copiar
            std::cout<<"Copiar\n";
            this->empezarABuscarUint(&this->auxiliarBasura,(unsigned int) this->yParedes.size(), modificarPared,copiTexture);
            break;
        case 'w':
        case 'W':
            this->paredModificable->vertice[0].coordenadas[2] -= 1;
            break;
        case 'S':
        case 's':
            this->paredModificable->vertice[0].coordenadas[2] += 1;
            break;
        case 'a':
        case 'A':
            this->paredModificable->vertice[0].coordenadas[0] -= 1;
            break;
        case 'd':
        case 'D':
            this->paredModificable->vertice[0].coordenadas[0] += 1;
            break;
        case 'q':
        case 'Q':
            this->paredModificable->vertice[0].coordenadas[1] += 1;
            break;
        case 'e':
        case 'E':
            this->paredModificable->vertice[0].coordenadas[1] -= 1;
            break;
        case 'i':
        case 'I':
            this->paredModificable->vertice[1].coordenadas[2] += 1;
            break;
        case 'k':
        case 'K':
            this->paredModificable->vertice[1].coordenadas[2] -= 1;
            break;
        case 'j':
        case 'J':
            this->paredModificable->vertice[1].coordenadas[0] -= 1;
            break;
        case 'l':
        case 'L':
            this->paredModificable->vertice[1].coordenadas[0] += 1;
            break;
        case 'u':
        case 'U':
            this->paredModificable->vertice[1].coordenadas[1] += 1;
            break;
        case 'o':
        case 'O':
            this->paredModificable->vertice[1].coordenadas[1] -= 1;
            break;
        case 'r':
        case 'R':
            this->paredModificable->angulo += 0.785;
            break;
        case 'y':
        case 'Y':
            this->paredModificable->angulo -= 0.785;
            break;
        default:
            break;
    }
    asegurarIntegridadParedCalculos(this->paredModificable);
}
void Construccion::teclaDeMenuModificarSuelo(unsigned char tecla){
    switch (tecla) {
        case 'C':
        case 'c':
            //Cambio
            std::cout<<"Cambio\n";
            describePuntos(sueloModificable->vertices);
            this->empezarABuscarUint(&this->punteroModificarSuelo, (unsigned int)this->sueloModificable->vertices.size(), modificarSuelo);
            break;
        case 'm':
        case 'M':
            //Mostrar
            std::cout<<"Mostrar\n";
            describePuntos(sueloModificable->vertices);
            this->drawCursor();
            break;
        case 13:
            //Crear nuevo
            std::cout<<"Nuevo\n";
            this->sueloModificable->vertices.push_back(Cg2ValenciaPunto3D());
            if (this->sueloModificable->vertices.size()!=0) {
                for (int i = 0; i<3; i++) {
                    this->sueloModificable->vertices[this->sueloModificable->vertices.size()-1].coordenadas[i] = this->sueloModificable->vertices[this->sueloModificable->vertices.size()-2].coordenadas[i];
                }
            }
            this->punteroModificarSuelo = (unsigned int)this->sueloModificable->vertices.size()-1;
            drawCursor();
            break;
        case 'b':
        case 'B':
            //Borrar
            if (this->sueloModificable->vertices.size()<4) {
                std::cout<<"No puedo tener menos de tres Vertices\n";
            }else{
                if (this->punteroModificarSuelo<this->sueloModificable->vertices.size()) {
                    std::cout<<"Borrado\n";
                    this->sueloModificable->vertices.erase(this->sueloModificable->vertices.begin()+this->punteroModificarSuelo);
                    if (this->punteroModificarSuelo>=this->sueloModificable->vertices.size()) {
                        this->punteroModificarSuelo = (unsigned int) this->sueloModificable->vertices.size()-1;
                    }
                }else{
                    std::cout<<"Error puntero fuera de rango\n";
                    this->punteroModificarSuelo = (unsigned int) this->sueloModificable->vertices.size()-1;
                }
                
            }
            this->drawCursor();
            break;
        case 't':
        case 'T':
            //Cambiar Texture
            std::cout<<"Cambio texture\n";
            this->empezarAModificarTextura(&this->sueloModificable->texturaMain, modificarSuelo);
            break;
        case 'x':
        case 'X':
            //Salir
            std::cout<<"Salir\n";
            this->estado = this->estadoARegresarModificar;
            this->escribeMenu();
            this->drawCursor();
            break;
        case 'i':
        case 'I':
            this->sueloModificable->vertices[this->punteroModificarSuelo].coordenadas[2] -= 1;
            break;
        case 'k':
        case 'K':
            this->sueloModificable->vertices[this->punteroModificarSuelo].coordenadas[2] += 1;
            break;
        case 'j':
        case 'J':
            this->sueloModificable->vertices[this->punteroModificarSuelo].coordenadas[0] -= 1;
            break;
        case 'l':
        case 'L':
            this->sueloModificable->vertices[this->punteroModificarSuelo].coordenadas[0] += 1;
            break;
        case 'u':
        case 'U':
            this->sueloModificable->vertices[this->punteroModificarSuelo].coordenadas[1] += 1;
            break;
        case 'o':
        case 'O':
            this->sueloModificable->vertices[this->punteroModificarSuelo].coordenadas[1] -= 1;
            break;
        case 'q':
        case 'Q':
            for (int i = 0; i<this->sueloModificable->vertices.size(); i++) {
                this->sueloModificable->vertices[i].coordenadas[1] += 1;
            }
            break;
        case 'e':
        case 'E':
            for (int i = 0; i<this->sueloModificable->vertices.size(); i++) {
                this->sueloModificable->vertices[i].coordenadas[1] -= 1;
            }
            break;
        default:
            break;
    }
}
void Construccion::teclaDeMenuModificarEscaleras(unsigned char tecla){
    switch (tecla) {
        case 't':
        case 'T':
            //Textura
            std::cout<<"Textura\n";
            this->empezarAModificarTextura(&(this->paredModificable->texturaMain), modificarEscaleras);
            break;
        case 'x':
        case 'X':
            //Salir
            std::cout<<"Salir\n";
            this->estado = this->estadoARegresarModificar;
            this->escribeMenu();
            this->drawCursor();
            break;
        case 'C':
        case 'c':
            //Copiar
            std::cout<<"Copiar\n";
            this->empezarABuscarUint(&this->auxiliarBasura,(unsigned int) this->yEscaleras.size(), modificarEscaleras,copiTexture);
            break;
        case 'v':
        case 'V':
            //Set no. Escalones
            std::cout<<"No. Escalones\n";
            this->empezarABuscarUint(&this->escalerasModificable->cantidadEscalones, 100, modificarEscaleras);
            break;
        case 'w':
        case 'W':
            this->escalerasModificable->vertice[0].coordenadas[2] -= 1;
            break;
        case 'S':
        case 's':
            this->escalerasModificable->vertice[0].coordenadas[2] += 1;
            break;
        case 'a':
        case 'A':
            this->escalerasModificable->vertice[0].coordenadas[0] -= 1;
            break;
        case 'd':
        case 'D':
            this->escalerasModificable->vertice[0].coordenadas[0] += 1;
            break;
        case 'q':
        case 'Q':
            this->escalerasModificable->vertice[0].coordenadas[1] += 1;
            break;
        case 'e':
        case 'E':
            this->escalerasModificable->vertice[0].coordenadas[1] -= 1;
            break;
        case 'i':
        case 'I':
            this->escalerasModificable->vertice[1].coordenadas[2] += 1;
            break;
        case 'k':
        case 'K':
            this->escalerasModificable->vertice[1].coordenadas[2] -= 1;
            break;
        case 'j':
        case 'J':
            this->escalerasModificable->vertice[1].coordenadas[0] -= 1;
            break;
        case 'l':
        case 'L':
            this->escalerasModificable->vertice[1].coordenadas[0] += 1;
            break;
        case 'u':
        case 'U':
            this->escalerasModificable->vertice[1].coordenadas[1] += 1;
            break;
        case 'o':
        case 'O':
            this->escalerasModificable->vertice[1].coordenadas[1] -= 1;
            break;
        case 'r':
        case 'R':
            this->escalerasModificable->angulo += 45;
            break;
        case 'y':
        case 'Y':
            this->escalerasModificable->angulo -= 45;
            break;
        default:
            break;
    }
}
void Construccion::teclaDeMenuTextura(unsigned char tecla){
    switch (tecla) {
        case 'M':
        case 'm':
            //Mostrar
            std::cout<<"Mostrando\n";
            vCargadorImage->escribeTexturasDisponibles();
            this->drawCursor();
            break;
        case 'S':
        case 's':
            //Set Texture
            std::cout<<"Set Texture\n";
            this->empezarABuscarUint(&(this->texturaModificable->at(this->punteroModificarTextura).cualTextura),(unsigned int) this->vCargadorImage->texturas.size(), modificarTextura);
            break;
        case 'c':
        case 'C':
            //Cambio
            std::cout<<"Cambio Texture\n";
            this->empezarABuscarUint(&this->punteroModificarTextura, (unsigned int)this->texturaModificable->size(), modificarTextura);
            break;
        case 'T':
        case 't':
            //Terminado
            std::cout<<"Terminado\n";
            this->estado = estadoARegresarTextura;
            break;
        default:
            break;
    }
}
void Construccion::empezarAModificar(int cual, Construccion::ConstruccionEstados regresar){
    bool auxboleana = true;
    this->estadoARegresarModificar = regresar;
    if (cual == -1) {
        switch (this->objetoActual) {
            case pared:
                this->paredTemporal = ConstruccionPared();
                for (int i = 0; auxboleana; i++) {
                    sprintf(this->paredTemporal.id, "Pared+%04d",i);
                    auxboleana = false;
                    for (unsigned long j = 0; j<this->yParedes.size(); j++) {
                        if (!(memcmp(this->paredTemporal.id, this->yParedes[j].id, sizeof(char)*MAXCHAR))) {
                            auxboleana = true;
                            break;
                        }
                    }
                }
                if (yParedes.size()!=0) {
                    for (int i = 0; i<PRIMITIVARVTPRISMAESTANDAR; i++) {
                        this->paredTemporal.texturaMain.push_back(this->yParedes[yParedes.size()-1].texturaMain[i]);
                    }
                    //Texturas
                    this->paredTemporal.texturaMain[0].posicionInicio[0] += this->yParedes[yParedes.size()-1].vertice[1].coordenadas[0];
                    this->paredTemporal.texturaMain[2].posicionInicio[0] += this->yParedes[yParedes.size()-1].vertice[1].coordenadas[0];
                    //coordenadas
                    for (int i = 0; i<3; i++) {
                        this->paredTemporal.vertice[0].coordenadas[i] = this->yParedes[yParedes.size()-1].vertice[0].coordenadas[i];
                        this->paredTemporal.vertice[1].coordenadas[i] = this->yParedes[yParedes.size()-1].vertice[1].coordenadas[i];
                    }
                        this->paredTemporal.vertice[0].coordenadas[0] += this->yParedes[yParedes.size()-1].vertice[1].coordenadas[0];
                    

                }else{
                    for (int i = 0; i<PRIMITIVARVTPRISMAESTANDAR; i++) {
                        this->paredTemporal.texturaMain.push_back(this->defaultTexture);
                    }
                    for (int i = 0; i<3; i++) {
                        this->paredTemporal.vertice[1].coordenadas[i] = 1;
                    }
                }
                this->empezarAModificarPared(&this->paredTemporal);
                this->dibujaParedT = true;
                break;
            case escalera:
                this->escalerasTemporales = ConstruccionEscaleras();
                for (int i = 0; auxboleana; i++) {
                    sprintf(this->escalerasTemporales.id, "Escalera+%04d",i);
                    auxboleana = false;
                    for (unsigned long j = 0; j<this->yEscaleras.size(); j++) {
                        if (!(memcmp(this->escalerasTemporales.id, this->yEscaleras[j].id, sizeof(char)*MAXCHAR))) {
                            auxboleana = true;
                            break;
                        }
                    }
                }
                if (yEscaleras.size()!=0) {
                    for (int i=0; i<PRIMITIVARVTPRISMAESTANDAR; i++) {
                        this->escalerasTemporales.texturaMain.push_back(this->yEscaleras[this->yEscaleras.size()-1].texturaMain[i]);
                    }
                    for (int i = 0; i<3; i++) {
                        this->escalerasTemporales.vertice[0].coordenadas[i] = this->yEscaleras[yEscaleras.size()-1].vertice[0].coordenadas[i];
                        this->escalerasTemporales.vertice[1].coordenadas[i] = this->yEscaleras[yEscaleras.size()-1].vertice[1].coordenadas[i];
                    }
                    this->escalerasTemporales.vertice[0].coordenadas[0] += this->yEscaleras[yEscaleras.size()-1].vertice[1].coordenadas[0];
                    this->escalerasTemporales.vertice[0].coordenadas[1] += this->yEscaleras[yEscaleras.size()-1].vertice[1].coordenadas[1];
                    this->escalerasTemporales.cantidadEscalones = this->yEscaleras[yEscaleras.size()-1].cantidadEscalones;
                }else{
                    for (int i=0; i<PRIMITIVARVTPRISMAESTANDAR; i++) {
                        this->escalerasTemporales.texturaMain.push_back(this->defaultTexture);
                    }
                    for (int i = 0; i<3; i++) {
                        this->escalerasTemporales.vertice[1].coordenadas[i] = 1;
                    }
                    this->escalerasTemporales.cantidadEscalones = 5;
                }
                this->empezarAModificarEscalera(&this->escalerasTemporales);
                this->dibujaEscaleraT = true;
                break;
            case suelo:
                this->sueloTemporal = ConstruccionSuelo();
                for (int i = 0; auxboleana; i++) {
                    sprintf(this->sueloTemporal.id, "Suelo+%04d",i);
                    auxboleana = false;
                    for (unsigned long j = 0; j<this->ySuelos.size(); j++) {
                        if (!(memcmp(this->sueloTemporal.id, this->ySuelos[j].id, sizeof(char)*MAXCHAR))) {
                            auxboleana = true;
                            break;
                        }
                    }
                }
                for (int i = 0; i<PRIMITIVARVTSUELOPOLIGONAL; i++) {
                    this->sueloTemporal.texturaMain.push_back(this->defaultTexture);
                }
                sueloTemporal.vertices.push_back(Cg2ValenciaPunto3D());
                sueloTemporal.vertices.push_back(Cg2ValenciaPunto3D());
                sueloTemporal.vertices.push_back(Cg2ValenciaPunto3D());
                if (yParedes.size()>1) {
                    for (int i=0;i<3; i++) {
                        sueloTemporal.vertices[0].coordenadas[i] = yParedes[yParedes.size()-2].vertice[0].coordenadas[i]+yParedes[yParedes.size()-2].vertice[1].coordenadas[i];
                        sueloTemporal.vertices[1].coordenadas[i] = yParedes[yParedes.size()-1].vertice[0].coordenadas[i];
                        sueloTemporal.vertices[2].coordenadas[i] =yParedes[yParedes.size()-1].vertice[0].coordenadas[i]+yParedes[yParedes.size()-1].vertice[1].coordenadas[i];
                    }
                }else{
                    sueloTemporal.vertices[1].coordenadas[0] = 10;
                    sueloTemporal.vertices[2].coordenadas[2] = -10;
                }
                for (int i =0; i<sueloTemporal.vertices.size(); i++) {
                    sueloTemporal.vertices[i].coordenadas[1] = 0.05;
                }
                this->empezarAModificarSuelo(&this->sueloTemporal);
                this->aseguraIntegridadSueloTam(&this->sueloTemporal);
                this->dibujaSueloT = true;
                break;
            default:
                break;
        }
    }else{
        if (cual<this->cuantosDisponiblesDe(this->objetoActual)) {
            switch (this->objetoActual) {
                case pared:
                    this->empezarAModificarPared(&(this->yParedes[cual]));
                    break;
                case suelo:
                    this->empezarAModificarSuelo(&(this->ySuelos[cual]));
                    break;
                case escalera:
                    this->empezarAModificarEscalera(&(this->yEscaleras[cual]));
                    break;
                default:
                    break;
            }
        }else{
            std::cout<<"No existe seleccion\n";
            return;
        }
    }
    this->escribeMenu();
    this->drawCursor();
}
void Construccion::empezarAModificarPared(ConstruccionPared *pared){
    this->estado = modificarPared;
    this->paredModificable = pared;
}
void Construccion::empezarAModificarSuelo(ConstruccionSuelo *suelo){
    this->estado = modificarSuelo;
    this->sueloModificable = suelo;
    this->punteroModificarSuelo = (unsigned int) this->sueloModificable->vertices.size()-1;
}
void Construccion::empezarAModificarEscalera(ConstruccionEscaleras *escaleras){
    this->estado = modificarEscaleras;
    this->escalerasModificable = escaleras;
}
void Construccion::empezarAModificarTextura(std::vector<PrimitivasSelectTexture> *texturas, Construccion::ConstruccionEstados estadoRegresar){
    this->estadoARegresarTextura = estadoRegresar;
    this->texturaModificable = texturas;
    this->estado = modificarTextura;
    this->escribeMenu();
    this->drawCursor();
}
void Construccion::guardarModificacionTemporal(){
    switch (this->objetoActual) {
        case pared:
            if (this->paredTemporal.tipoPared == paredVentana) {
                this->ventanasADibujar.push_back(this->yParedes.size());
            }
            this->yParedes.push_back(this->paredTemporal);
            break;
        case escalera:
            this->yEscaleras.push_back(this->escalerasTemporales);
            break;
        case suelo:
            this->ySuelos.push_back(this->sueloTemporal);
            break;
        default:
            break;
    }
    this->cancelarModificacionTemporal();
}
void Construccion::cancelarModificacionTemporal(){
//    std::cout<<"Checa si es necesario\n";
    std::cout<<this->tipoConstruccionToChar[(unsigned int)this->objetoActual]<<std::endl;
    this->dibujaSueloT = false;
    this->dibujaParedT = false;
    this->dibujaEscaleraT = false;
//    switch (this->objetoActual) {
//        case escalera:
//            this->dibujaEscaleraT = false;
//            break;
//        case pared:
//            this->dibujaParedT = false;
//            break;
//        case suelo:
//            this->dibujaParedT = false;
//            break;
//        default:
//            break;
//    }
}
void Construccion::borrarObjeto(unsigned long cual, Construccion::ConstruccionTipoConstruccion tipo){
    switch (tipo) {
        case pared:
            if (cual<this->yParedes.size()) {
                if (this->yParedes[cual].tipoPared == paredVentana) {
                    for (int i = 0; i<this->ventanasADibujar.size(); i++) {
                        if (this->ventanasADibujar[i]==cual) {
                            this->ventanasADibujar.erase(this->ventanasADibujar.begin()+i);
                            break;
                        }
                    }
                }
                this->yParedes.erase(yParedes.begin()+cual);
            }
            break;
        case escalera:
            if (cual<this->yEscaleras.size()) {
                this->yEscaleras.erase(yEscaleras.begin()+cual);
            }
            break;
        case suelo:
            if(cual<this->ySuelos.size()){
                this->ySuelos.erase(ySuelos.begin()+cual);
            }
            break;
        default:
            break;
    }
}
void Construccion::empezarABuscarUint(unsigned int *a, unsigned int max, ConstruccionEstados estadoRegresar,ConstruccionAccionDespuesBuscarUInt accion){
    if (max == 0){
        std::cout<<"No hay donde elegir "<<this->estadosToChar[(unsigned char)estadoRegresar]<<std::endl;
        return;
    }
    this->estadoAnterior = this->estado;
    this->dondeGuardar = a;
    this->maxDondeGuardar = max;
    this->estadoARegresar = estadoRegresar;
    this->accionDespuesBuscarInt = accion;
    this->estado = buscaUInt;
    this->temporalIntFromKeyBoard = 0;
    this->escribeMenu();
    this->drawCursor();
}
void Construccion::ejecutaAccionDespuesBuscarUInt(){
    switch (this->accionDespuesBuscarInt) {
        case nada:
            
            break;
        case copiTexture:
            switch (this->objetoActual) {
                case pared:
                    for (int i =0; i<6; i++) {
                        this->paredModificable->texturaMain[i] = this->yParedes[auxiliarBasura].texturaMain[i];
                    }
                    this->aseguraIntegridadParedTam(paredModificable);
                    this->asegurarIntegridadParedCalculos(paredModificable);
                    break;
                case escalera:
                    
                    break;
                case suelo:
                    
                    break;
                default:
                    break;
            }
            std::cout<<"No implementado copitexture accion despues de Buscar UInt\n";
            break;
        case empezarACrear:
            this->empezarAModificar(-1, this->estado);
            break;
        case modificarParedAsegurateCambioTipoCompleto:
            this->aseguraIntegridadParedTam(this->paredModificable);
            this->asegurarIntegridadParedCalculos(this->paredModificable);
            break;
        default:
            std::cout<<"Error ejecuccion accion no conocida\n";
            break;
    }
}
void Construccion::aseguraIntegridadParedTam(ConstruccionPared *pared){
    PrimitivasSelectTexture temporal;
    char auxnom[MAXCHAR];
    while (pared->texturaMain.size()<6) {
        std::cout<<"Este error no deberia existir checalo urgente asegurarIntegridadPared\n";
        pared->texturaMain.push_back(temporal);
    }
    while (pared->texturaMain.size()>6) {
        pared->texturaMain.erase(pared->texturaMain.end()-1);
    }
    while (pared->vertice.size()<2) {
        std::cout<<"Este error no deberia existir checalo urgente asegurarIntegridadPared 2\n";
        pared->vertice.push_back(Cg2ValenciaPunto3D());
    }
    while (pared->vertice.size()>2) {
        pared->vertice.erase(pared->vertice.end()-1);
    }
    switch (pared->tipoPared) {
        case paredVentana:
            switch (pared->tipoVentana) {
                case ventanaNormal:
                    this->aseguraIntegridadParedTamByNumber(pared,1 , 3);
                    memcpy(&auxnom[1], pared->id, sizeof(char)*MAXCHAR);
                    auxnom[0] = 'v';
                    pared->cualVarMovimiento = this->vKeyFrame->crearVarMovimiento(auxnom);
                    break;
                case ventananulo:
                default:
                    break;
            }
            break;
        case paredPuerta:
            switch (pared->tipoPuerta) {
                case puertaNormal:
                case cortinaAccesoria:
                case zaguanIzquiedo:
                case zaguanDerecho:
                    this->aseguraIntegridadParedTamByNumber(pared, 1, 2);
                    pared->cualVarMovimiento = this->vKeyFrame->crearVarMovimiento(pared->id);
                    break;
                case puertanulo:
                default:
                    break;
            }
            break;
        case paredNormal:
            pared->tipoPuerta = puertanulo;
            pared->tipoVentana = ventananulo;
            break;
        default:
            break;
    }
}
void Construccion::aseguraIntegridadParedTamByNumber(ConstruccionPared *pared, unsigned int texturas, unsigned int segmentos){
    for (int j = 0; j<texturas; j++) {
        for (int i=0; i<6; i++) {
            pared->texturaMain.push_back(pared->texturaMain[i]);
        }
    }
    for (int j=0; j<segmentos; j++) {
        pared->vertice.push_back(pared->vertice[0]);
        pared->vertice.push_back(pared->vertice[1]);
    }

}
void Construccion::asegurarIntegridadParedCalculos(ConstruccionPared *pared){
    switch (pared->tipoPared) {
        case paredVentana:
            switch (pared->tipoVentana) {
                case ventanaNormal:
                    this->asegurarIntegridadParedVentanaNormalCalculos(pared);
                    break;
                case ventananulo:
                default:
                    break;
            }
            break;
        case paredPuerta:
            switch (pared->tipoPuerta) {
                case puertaNormal:
                    this->asegurarIntegridadParedPuertaNormalCalculos(pared);
                    break;
                case cortinaAccesoria:
                case zaguanIzquiedo:
                case zaguanDerecho:
                    this->asegurarIntegridadParedPuertaNormalCalculos2(pared);
                    break;
                case puertanulo:
                default:
                    break;
            }
            break;
        case paredNormal:
            
        default:
            break;
    }
}

void Construccion::asegurarIntegridadParedVentanaNormalCalculos(ConstruccionPared *pared){
    if (pared->texturaMain.size()!=12||pared->vertice.size()!=8) {
        std::cout<<"Uso incorrecto de funcion asegurarIntegridadParedVentanaNormal\n";
    }
    for (int i = 0; i<6; i++) {
        pared->texturaMain[6+i].posicionInicio[1] = pared->texturaMain[i].posicionInicio[1] + pared->vertice[1].coordenadas[1]*0.9;
        
    }
    for (int i = 0; i<6; i+=2) {
        pared->vertice[2+i] = pared->vertice[0];
        pared->vertice[3+i] = pared->vertice[1];
    }
    pared->vertice[3].coordenadas[1] = pared->vertice[1].coordenadas[1]*0.5;

    pared->vertice[4].coordenadas[1] = pared->vertice[1].coordenadas[1]*0.5;
    pared->vertice[5].coordenadas[1] = pared->vertice[1].coordenadas[1]*0.4;
    
    pared->vertice[6].coordenadas[1] = pared->vertice[1].coordenadas[1]*0.9;
    pared->vertice[7].coordenadas[1] = pared->vertice[1].coordenadas[1]*0.1;

}
void Construccion::asegurarIntegridadParedPuertaNormalCalculos(ConstruccionPared *pared){
    if (pared->texturaMain.size()!=12||pared->vertice.size()!=6) {
        std::cout<<"Uso incorrecto de funcion asegurarIntegridadParedPuertaNormal\n";
    }
  
    for (int i = 0; i<6; i++) {
        pared->texturaMain[6+i].posicionInicio[1] = pared->texturaMain[i].posicionInicio[1] + pared->vertice[1].coordenadas[1]*0.9;
        
    }
    for (int i = 0; i<4; i+=2) {
        pared->vertice[2+i] = pared->vertice[0];
        pared->vertice[3+i] = pared->vertice[1];
    }
    pared->vertice[3].coordenadas[1] = pared->vertice[1].coordenadas[1]*0.9;

    pared->vertice[4].coordenadas[1] += pared->vertice[1].coordenadas[1]*0.9;
    pared->vertice[5].coordenadas[1] = pared->vertice[1].coordenadas[1]*0.1;
    
}
void Construccion::asegurarIntegridadParedPuertaNormalCalculos2(ConstruccionPared *pared){
    if (pared->texturaMain.size()!=12||pared->vertice.size()!=6) {
        std::cout<<"Uso incorrecto de funcion asegurarIntegridadParedPuertaNormal\n";
    }
    
    for (int i = 0; i<6; i++) {
        pared->texturaMain[6+i].posicionInicio[1] = pared->texturaMain[i].posicionInicio[1] + pared->vertice[1].coordenadas[1]*0.9;
        
    }
    for (int i = 0; i<4; i+=2) {
        pared->vertice[2+i] = pared->vertice[0];
        pared->vertice[3+i] = pared->vertice[1];
    }
    pared->vertice[3].coordenadas[2] = pared->vertice[1].coordenadas[2]*0.6;
    pared->vertice[3].coordenadas[1] = pared->vertice[1].coordenadas[1]*0.9;
    
    pared->vertice[4].coordenadas[1] += pared->vertice[1].coordenadas[1]*0.9;
    pared->vertice[5].coordenadas[1] = pared->vertice[1].coordenadas[1]*0.1;
    
    if (pared->tipoPuerta == zaguanIzquiedo) {
        pared->vertice[3].coordenadas[0] = -pared->vertice[1].coordenadas[0];
        pared->vertice[5].coordenadas[0] = -pared->vertice[1].coordenadas[0];
    }
    
}

unsigned long Construccion::cuantosDisponiblesDe(Construccion::ConstruccionTipoConstruccion tipo){
    switch (tipo) {
        case pared:
            return this->yParedes.size();
        case escalera:
            return this->yEscaleras.size();
        case suelo:
            return this->ySuelos.size();
        default:
            std::cout<<"Caso no analizado cuandots disponibles De tipo";
            return 0;
    }
}
void Construccion::empezarADibujarTemporal(){
    switch (this->objetoActual) {
        case pared:
            this->dibujaParedT = true;
            break;
        case suelo:
            this->dibujaSueloT = true;
            break;
        case escalera:
            this->dibujaEscaleraT = true;
            break;
        default:
            break;
    }
}
void Construccion::cargar(){
    FILE * archivo = fopen(CONSTRUCCIONPATHFILE, "r");
    unsigned int cabecera = 0;
    unsigned int cantidades = (unsigned int)this->yParedes.size();
    unsigned int aux = 0;
    
    ConstruccionPared tPared = ConstruccionPared();
    ConstruccionEscaleras tEscalera = ConstruccionEscaleras();
    PrimitivasSelectTexture tSelectTexture = PrimitivasSelectTexture();
    
    char nombreAux[MAXCHAR] = "";
    
    if (archivo==NULL) {
        std::cout<<"Archivo no encontrado\n";
        this->guardar();
        return;
    }
    fread(&cabecera, sizeof(unsigned int), 1, archivo);
    if (cabecera != CONSTRUCCIONVERSIONARCHIVOS) {
        std::cout<<"Cabecera incompatible posible incompatibilidad de versiones\n";
        fclose(archivo);
        return;
    }
    //Paredes
    fread(&cantidades, sizeof(unsigned int), 1, archivo);
    for (unsigned int i=0; i<cantidades; i++) {
        fread(&aux, sizeof(unsigned int), 1, archivo);
        tPared.tipoPared = (ConstruccionTipoPared) aux;
        fread(&aux, sizeof(unsigned int), 1, archivo);
        tPared.tipoVentana = (ConstruccionTipoVentana) aux;
        fread(&aux, sizeof(unsigned int), 1, archivo);
        tPared.tipoPuerta = (ConstruccionTipoPuerta) aux;
        fread(tPared.id, sizeof(char), MAXCHAR, archivo);
        fread(&tPared.angulo, sizeof(double), 1, archivo);
        for (unsigned int j = 0; j<2; j++) {
            fread(tPared.vertice[j].coordenadas, sizeof(double), 3, archivo);
        }
        for (unsigned int j = 0; j<6; j++) {
            fread(tSelectTexture.posicionInicio, sizeof(double), 2, archivo);
            fread(nombreAux, sizeof(char), MAXCHAR, archivo);
            if(!this->vCargadorImage->echateABuscarTexture(nombreAux, &tSelectTexture.cualTextura)) std::cout<<nombreAux<<" No encontrado \n";
            tPared.texturaMain.push_back(tSelectTexture);
            tSelectTexture = PrimitivasSelectTexture();
        }
        this->aseguraIntegridadParedTam(&tPared);
        this->asegurarIntegridadParedCalculos(&tPared);
        if (tPared.tipoPared == paredVentana) {
            this->ventanasADibujar.push_back(this->yParedes.size());
        }
        this->yParedes.push_back(tPared);
        tPared = ConstruccionPared();
    }
    
    //Escaleras
    fread(&cantidades, sizeof(unsigned int), 1, archivo);
    for (unsigned int i=0; i<cantidades; i++) {
        fread(tEscalera.id, sizeof(char), MAXCHAR, archivo);
        fread(&tEscalera.angulo, sizeof(double), 1, archivo);
        fread(&tEscalera.cantidadEscalones, sizeof(unsigned int), 1, archivo);
        fread(&aux, sizeof(unsigned int), 1, archivo);
        for (unsigned int j = 0; j<aux; j++) {
            tEscalera.vertice.push_back(Cg2ValenciaPunto3D());
            fread(tEscalera.vertice[j].coordenadas, sizeof(double), 3, archivo);
        }
        for (unsigned int j = 0; j<6; j++) {
            tEscalera.texturaMain.push_back(PrimitivasSelectTexture());
            fread(tEscalera.texturaMain[j].posicionInicio, sizeof(double), 2, archivo);
            fread(nombreAux, sizeof(char), MAXCHAR, archivo);
            if(!this->vCargadorImage->echateABuscarTexture(nombreAux, &tEscalera.texturaMain[j].cualTextura)) std::cout<<nombreAux<<" No encontrado \n";
        }
        this->yEscaleras.push_back(tEscalera);
        tEscalera = ConstruccionEscaleras();
    }
    //Suelos
    cantidades = (unsigned int) this->ySuelos.size();
    fread(&cantidades, sizeof(unsigned int), 1, archivo);
    for (unsigned int i=0; i<cantidades; i++) {
        ySuelos.push_back(ConstruccionSuelo());
        fread(ySuelos[i].id, sizeof(char), MAXCHAR, archivo);
        fread(&aux, sizeof(unsigned int), 1, archivo);
        for (unsigned int j = 0; j<aux; j++) {
            ySuelos[i].vertices.push_back(Cg2ValenciaPunto3D());
            fread(ySuelos[i].vertices[j].coordenadas, sizeof(double), 3, archivo);
        }
        for (unsigned int j = 0; j<2; j++) {
            ySuelos[i].texturaMain.push_back(PrimitivasSelectTexture());
            fread(ySuelos[i].texturaMain[j].posicionInicio, sizeof(double), 2, archivo);
            fread(nombreAux, sizeof(char), MAXCHAR, archivo);
            if(!this->vCargadorImage->echateABuscarTexture(nombreAux, &ySuelos[i].texturaMain[j].cualTextura)) std::cout<<nombreAux<<" No encontrado \n";
        }
        this->aseguraIntegridadSueloTam(&this->ySuelos[i]);
    }
    fclose(archivo);
    std::cout<<"Construccion: "<<this->yParedes.size()<<" "<<this->ySuelos.size()<<" "<<this->yEscaleras.size()<<" Cargadas\n";
}
void Construccion::guardar(){
    FILE * archivo = fopen(CONSTRUCCIONPATHFILE, "w");
    unsigned int cabecera = CONSTRUCCIONVERSIONARCHIVOS;
    unsigned int cantidades = (unsigned int)this->yParedes.size();
    unsigned int aux = 0;
    if (archivo==NULL) {
        std::cout<<"Error Guardando Archivo null\n";
        return;
    }
    fwrite(&cabecera, sizeof(unsigned int), 1, archivo);
    //Paredes
    fwrite(&cantidades, sizeof(unsigned int), 1, archivo);
    for (unsigned int i=0; i<cantidades; i++) {
        aux = (unsigned int) yParedes[i].tipoPared;
        fwrite(&aux, sizeof(unsigned int), 1, archivo);
        aux = (unsigned int) yParedes[i].tipoVentana;
        fwrite(&aux, sizeof(unsigned int), 1, archivo);
        aux = (unsigned int) yParedes[i].tipoPuerta;
        fwrite(&aux, sizeof(unsigned int), 1, archivo);
        fwrite(yParedes[i].id, sizeof(char), MAXCHAR, archivo);
        fwrite(&yParedes[i].angulo, sizeof(double), 1, archivo);
        for (unsigned int j = 0; j<2; j++) {
            fwrite(yParedes[i].vertice[j].coordenadas, sizeof(double), 3, archivo);
        }
        for (unsigned int j = 0; j<6; j++) {
            fwrite(yParedes[i].texturaMain[j].posicionInicio, sizeof(double), 2, archivo);
            fwrite(vCargadorImage->texturas[this->yParedes[i].texturaMain[j].cualTextura].nombreTexture, sizeof(char), MAXCHAR, archivo);
        }
    }
    //Escaleras
    cantidades = (unsigned int) this->yEscaleras.size();
    fwrite(&cantidades, sizeof(unsigned int), 1, archivo);
    for (unsigned int i=0; i<cantidades; i++) {
        fwrite(yEscaleras[i].id, sizeof(char), MAXCHAR, archivo);
        fwrite(&yEscaleras[i].angulo, sizeof(double), 1, archivo);
        fwrite(&yEscaleras[i].cantidadEscalones, sizeof(unsigned int), 1, archivo);
        aux = (unsigned int) yEscaleras[i].vertice.size();
        fwrite(&aux, sizeof(unsigned int), 1, archivo);
        for (unsigned int j = 0; j<aux; j++) {
            fwrite(yEscaleras[i].vertice[j].coordenadas, sizeof(double), 3, archivo);
        }
        for (unsigned int j = 0; j<6; j++) {
            fwrite(yEscaleras[i].texturaMain[j].posicionInicio, sizeof(double), 2, archivo);
            fwrite(vCargadorImage->texturas[this->yEscaleras[i].texturaMain[j].cualTextura].nombreTexture, sizeof(char), MAXCHAR, archivo);
        }
    }
    
    //Suelo
    cantidades = (unsigned int) this->ySuelos.size();
    fwrite(&cantidades, sizeof(unsigned int), 1, archivo);
    for (unsigned int i=0; i<cantidades; i++) {
        fwrite(ySuelos[i].id, sizeof(char), MAXCHAR, archivo);
        aux = (unsigned int) ySuelos[i].vertices.size();
        fwrite(&aux, sizeof(unsigned int), 1, archivo);
        for (unsigned int j = 0; j<aux; j++) {
            fwrite(ySuelos[i].vertices[j].coordenadas, sizeof(double), 3, archivo);
        }
        for (unsigned int j = 0; j<2; j++) {
            fwrite(ySuelos[i].texturaMain[j].posicionInicio, sizeof(double), 2, archivo);
            fwrite(vCargadorImage->texturas[this->ySuelos[i].texturaMain[j].cualTextura].nombreTexture, sizeof(char), MAXCHAR, archivo);
        }
    }
    fclose(archivo);
}
void Construccion::dibujaPared(ConstruccionPared *pared){
    switch (pared->tipoPared) {
        case paredNormal:
            vPrimitivas->prismaEstandar(&(pared->texturaMain),0 , pared->vertice[0].coordenadas, pared->vertice[1].coordenadas,pared->angulo);
            break;
        case paredVentana:
            switch (pared->tipoVentana) {
                case ventanaNormal:
                    vPrimitivas->prismaEstandar(&(pared->texturaMain),0 , pared->vertice[2].coordenadas, pared->vertice[3].coordenadas,pared->angulo);
                    vPrimitivas->prismaEstandar(&(pared->texturaMain),6 , pared->vertice[6].coordenadas, pared->vertice[7].coordenadas,pared->angulo);
                    break;
                case ventananulo:
                    vPrimitivas->prismaEstandar(&(pared->texturaMain),0 , pared->vertice[0].coordenadas, pared->vertice[1].coordenadas,pared->angulo);
                    break;
                default:
                    break;
            }
            break;
        case paredPuerta:
            switch (pared->tipoPuerta) {
                case puertaNormal:
                    //Cachito
                    vPrimitivas->prismaEstandar(&(pared->texturaMain),6 , pared->vertice[4].coordenadas, pared->vertice[5].coordenadas,pared->angulo);
                    //Puerta
                    vPrimitivas->prismaEstandar(&(this->puertaNormalTexturas),0 , pared->vertice[2].coordenadas, pared->vertice[3].coordenadas,pared->angulo+vKeyFrame->varMovimientos[pared->cualVarMovimiento].value+0.785);
                    break;
                case cortinaAccesoria:
                    vPrimitivas->prismaEstandar(&(pared->texturaMain),6 , pared->vertice[4].coordenadas, pared->vertice[5].coordenadas,pared->angulo);
                    pared->vertice[2].coordenadas[1] = 1 + vKeyFrame->varMovimientos[pared->cualVarMovimiento].value + pared->vertice[0].coordenadas[1];
                    pared->vertice[3].coordenadas[1] = pared->vertice[1].coordenadas[1] *0.9 - 1 - vKeyFrame->varMovimientos[pared->cualVarMovimiento].value;
                    vPrimitivas->prismaEstandar(&(this->accesoriaTextura),0 , pared->vertice[2].coordenadas, pared->vertice[3].coordenadas,pared->angulo);
                    break;
                case zaguanIzquiedo:
                    //Cachito
                    vPrimitivas->prismaEstandar(&(pared->texturaMain),6 , pared->vertice[4].coordenadas, pared->vertice[5].coordenadas,pared->angulo);
                    //Puerta
                    vPrimitivas->prismaEstandar(&(this->zaguanTextureI),0 , pared->vertice[2].coordenadas, pared->vertice[3].coordenadas,pared->angulo+vKeyFrame->varMovimientos[pared->cualVarMovimiento].value);
                    break;
                case zaguanDerecho:
                    //Cachito
                    vPrimitivas->prismaEstandar(&(pared->texturaMain),6 , pared->vertice[4].coordenadas, pared->vertice[5].coordenadas,pared->angulo);
                    //Puerta
                    vPrimitivas->prismaEstandar(&(this->zaguanTextureD),0 , pared->vertice[2].coordenadas, pared->vertice[3].coordenadas,pared->angulo+vKeyFrame->varMovimientos[pared->cualVarMovimiento].value);
                    break;
                case puertanulo:
                    vPrimitivas->prismaEstandar(&(pared->texturaMain),0 , pared->vertice[0].coordenadas, pared->vertice[1].coordenadas,pared->angulo);
                    break;
                default:
                    break;
            }
            break;
        
        default:
            std::cout<<"Tipo no reconocido pared";
            break;
    }
    glPopMatrix();
}
void Construccion::escribeEnOrdencharArray(char (*arreglo)[30], unsigned int cuantos){
    for (int i = 0; i<cuantos; i++) {
        std::cout<<i<<"-. "<<arreglo[i]<<std::endl;
    }
}
void Construccion::dibujaEscaleras(ConstruccionEscaleras *escalera){
    this->vPrimitivas->escaleras(&escalera->texturaMain, 0, escalera->vertice[0].coordenadas, escalera->vertice[1].coordenadas, escalera->cantidadEscalones, escalera->angulo);
}
void Construccion::dibujaSuelo(ConstruccionSuelo *suelo){
    suelo->texturaMain[2].posicionInicio[0] = this->vKeyFrame->varMovimientos[suelo->cualVarMovimiento[0]].value;
    suelo->texturaMain[3].posicionInicio[0] = this->vKeyFrame->varMovimientos[suelo->cualVarMovimiento[0]].value;
    
    suelo->texturaMain[2].posicionInicio[1] = this->vKeyFrame->varMovimientos[suelo->cualVarMovimiento[1]].value;
    suelo->texturaMain[3].posicionInicio[1] = this->vKeyFrame->varMovimientos[suelo->cualVarMovimiento[1]].value;
    
    this->vPrimitivas->sueloPoligonal(&suelo->texturaMain, 2, &suelo->vertices);
}
void Construccion::describePuntos(std::vector<Cg2ValenciaPunto3D> puntos){
    for (int i = 0; i<puntos.size(); i++) {
        std::cout<<i<<".- ";
        vPrimitivas->describePunto(puntos[i]);
        std::cout<<std::endl;
    }
}
void Construccion::aseguraIntegridadSueloTam(ConstruccionSuelo *suelo){
    char nombreAux[MAXCHAR];
    while (suelo->texturaMain.size()<2) {
        std::cout<<"Error no deberia estar revisar urgente\n";
        suelo->texturaMain.push_back(this->defaultTexture);
    }
    while (suelo->texturaMain.size()<4){
        suelo->texturaMain.push_back(suelo->texturaMain[0]);
        suelo->texturaMain.push_back(suelo->texturaMain[1]);
    }
    memcpy(nombreAux, suelo->id, sizeof(char)*MAXCHAR);
    nombreAux[10] = 'K';
    nombreAux[11] = '0';
    nombreAux[12] = '\0';
    suelo->cualVarMovimiento[0] = this->vKeyFrame->crearVarMovimiento(nombreAux);
//    nombreAux[10] = 'K';
    nombreAux[11] = '1';
//    nombreAux[12] = '\0';
    suelo->cualVarMovimiento[1] = this->vKeyFrame->crearVarMovimiento(nombreAux);
}
void Construccion::aseguraIntegridadSueloCalculos(ConstruccionSuelo *suelo){
    suelo->texturaMain[2].cualTextura = suelo->texturaMain[0].cualTextura;
    suelo->texturaMain[3].cualTextura = suelo->texturaMain[1].cualTextura;
    memcpy(suelo->texturaMain[2].posicionInicio, suelo->texturaMain[0].posicionInicio, sizeof(double)*2);
    memcpy(suelo->texturaMain[3].posicionInicio, suelo->texturaMain[1].posicionInicio, sizeof(double)*2);
}
void Construccion::dibujaDespues(){
    glEnable(GL_BLEND);
    for (int i = 0; i<this->ventanasADibujar.size(); i++) {
        if (yParedes[this->ventanasADibujar[i]].tipoPared != paredVentana) {
            std::cout<<"Se colo ";
            this->describePared(yParedes[this->ventanasADibujar[i]]);
            continue;
        }
        switch (yParedes[this->ventanasADibujar[i]].tipoVentana) {
            case ventananulo:
                break;
            case ventanaNormal:
                this->dibujaParedVentanaNormal(&yParedes[this->ventanasADibujar[i]]);
                break;
            default:
                break;
        }
    }
    if (this->dibujaParedT && this->paredTemporal.tipoPared == paredVentana) {
        this->dibujaParedVentanaNormal(&this->paredTemporal);
    }
    glDisable(GL_BLEND);
}
void Construccion::dibujaParedVentanaNormal(ConstruccionPared *pared){
    pared->vertice[4].coordenadas[0] = pared->vertice[0].coordenadas[0] + vKeyFrame->varMovimientos[pared->cualVarMovimiento].value;
    vPrimitivas->prismaEstandar(&this->ventanaNormalTexturas, 0, pared->vertice[4].coordenadas, pared->vertice[5].coordenadas, pared->angulo);
}
