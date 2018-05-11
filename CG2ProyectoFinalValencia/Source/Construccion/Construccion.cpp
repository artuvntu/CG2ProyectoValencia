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
        default:
            std::cout<<"Error construccion estado no analizado\n";
            break;
    }
}
void Construccion::dibuja(){
    for (int i = 0; i<this->yParedes.size(); i++) {
        this->dibujaPared(&(yParedes[i]));
    }
    for (int i = 0; i<this->ySuelos.size(); i++) {
        
    }
    for (int i = 0; i<this->yEscaleras.size(); i++) {
        
    }
    if (dibujaParedT) {
        this->dibujaPared(&this->paredTemporal);
    }
    if (dibujaEscaleraT) {
        
    }
    if (dibujaSueloT) {
        
    }
}
void Construccion::escribeMenu(){
    switch (this->estado) {
        case inicial:
            std::cout<<"C->Crear Cosas\nB->Borrar Cosas\nE->Editar Cosas\nL->Cargar\nG->Guardar\nS->Salir\n";
            break;
        case agregarCosa:
            std::cout<<"G->Guardar\nS->Salir\nM->Modificar\n";
            break;
        case editarCosa:
            std::cout<<"Actual: "<<this->punteroEditar<<"Disponibles: "<<this->cuantosDisponiblesDe(this->objetoActual)<<"P->Mostrar Disponibles\nC->Cambiar\nM->Modificar\nT->Terminar\n";
            break;
        case borrarCosa:
            std::cout<<"Actual: "<<this->punteroEditar<<"Disponibles: "<<this->cuantosDisponiblesDe(this->objetoActual)<<"P->Mostrar Disponibles\nC->Cambiar\nD->Delete\nT->Terminar\n";
            break;
        case buscaUInt:
            std::cout<<"Accion: \""<<this->accionesBuscarUIntToChar[(unsigned char)this->accionDespuesBuscarInt]<<"\" V Actual: "<<*this->dondeGuardar<<" Max: "<<this->maxDondeGuardar<<" Write: "<<this->temporalIntFromKeyBoard<<" Regresar a "<<this->estadosToChar[(unsigned char)this->estadoARegresar]<<std::endl;
            break;
        case modificarPared:
            std::cout<<"wsadqeikjluory\n";
            this->describePared(*this->paredModificable);
            std::cout<<"T->Modificar Textura\nC->Copiar\nZ->Salir\nX->CambiarTipo\n";
        case modificarSuelo:
            
            break;
        case modificarEscaleras:
            std::cout<<"wsadikjluo\n";
            this->describeEscaleras(*this->escalerasModificable);
            std::cout<<"T->Modificar Textura\nC->Copiar\nS->Salir\n";
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
void Construccion::describePunto(ConstruccionPunto punto){
    std::cout<<"{"<<punto.coordenadas[0]<<", "<<punto.coordenadas[1]<<", "<<punto.coordenadas[2]<<"}";
}
void Construccion::describePared(ConstruccionPared pared){
    std::cout<<"Pared: \""<<pared.id<<"\" ";
    std::cout<<"P: ";
    this->describePunto(pared.posicion);
    std::cout<<" T: ";
    this->describePunto(pared.tam);
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
    std::cout<<"Suelo: \""<<suelo.id<<"\" ";
    std::cout<<"P: ";
    this->describePunto(suelo.posicion);
    std::cout<<" V: "<<suelo.vertices.size()<<std::endl;
}
void Construccion::describeEscaleras(ConstruccionEscaleras escaleras){
    std::cout<<"Escaleras: \""<<escaleras.id<<"\" ";
    std::cout<<"P: ";
    this->describePunto(escaleras.posicion);
    std::cout<<" T: ";
    this->describePunto(escaleras.tam);
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
            std::cout<<"Fuera menu Construccion";
            this->menuActivado = false;
            break;
        default:
            std::cout<<"Error";
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
            this->empezarABuscarUint(&this->punteroEditar, this->cuantosDisponiblesDe(this->objetoActual), editarCosa);
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
            this->empezarABuscarUint(&this->punteroEditar, this->cuantosDisponiblesDe(this->objetoActual), borrarCosa);
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
        case 'C':
        case 'c':
            std::cout<<"Copiar\n";
            this->empezarABuscarUint(&this->auxiliarBasura,(unsigned int) this->yParedes.size(), modificarPared,copiTexture);
            break;
        case 'w':
        case 'W':
            this->paredModificable->posicion.coordenadas[2] -= 1;
            break;
        case 'S':
        case 's':
            this->paredModificable->posicion.coordenadas[2] += 1;
            break;
        case 'a':
        case 'A':
            this->paredModificable->posicion.coordenadas[0] -= 1;
            break;
        case 'd':
        case 'D':
            this->paredModificable->posicion.coordenadas[0] += 1;
            break;
        case 'q':
        case 'Q':
            this->paredModificable->posicion.coordenadas[1] += 1;
            break;
        case 'e':
        case 'E':
            this->paredModificable->posicion.coordenadas[1] -= 1;
            break;
        case 'i':
        case 'I':
            this->paredModificable->tam.coordenadas[2] -= 1;
            break;
        case 'k':
        case 'K':
            this->paredModificable->tam.coordenadas[2] += 1;
            break;
        case 'j':
        case 'J':
            this->paredModificable->tam.coordenadas[0] -= 1;
            break;
        case 'l':
        case 'L':
            this->paredModificable->tam.coordenadas[0] += 1;
            break;
        case 'u':
        case 'U':
            this->paredModificable->tam.coordenadas[1] += 1;
            break;
        case 'o':
        case 'O':
            this->paredModificable->tam.coordenadas[1] -= 1;
            break;
        case 'r':
        case 'R':
            this->paredModificable->angulo += 45;
            break;
        case 'y':
        case 'Y':
            this->paredModificable->angulo -= 45;
            break;
        default:
            break;
    }
}
void Construccion::teclaDeMenuModificarSuelo(unsigned char tecla){
    std::cout<<"No implementado AUN\n";
    this->estado = this->estadoARegresarModificar;
    this->escribeMenu();
    this->drawCursor();
}
void Construccion::teclaDeMenuModificarEscaleras(unsigned char tecla){
    switch (tecla) {
        case 't':
        case 'T':
            //Textura
            std::cout<<"Textura\n";
            this->empezarAModificarTextura(&(this->paredModificable->texturaMain), modificarEscaleras);
            break;
        case 's':
        case 'S':
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
        default:
            break;
    }
}
void Construccion::teclaDeMenuTextura(unsigned char tecla){
    std::cout<<"No implementado AUN\n";
    this->estado = this->estadoARegresarModificar;
    this->escribeMenu();
    this->drawCursor();
}
void Construccion::empezarAModificar(int cual, Construccion::ConstruccionEstados regresar){
    PrimitivasSelectTexture temporalTexture = PrimitivasSelectTexture();
    temporalTexture.cualTextura = 3;
    this->estadoARegresarModificar = regresar;
    if (cual == -1) {
        switch (this->objetoActual) {
            case pared:
                this->paredTemporal = ConstruccionPared();
                sprintf(this->paredTemporal.id, "Pared%lu+%d",this->yParedes.size(),rand());
                for (int i = 0; i<PRIMITIVARVTPRISMAESTANDAR; i++) {
                    this->paredTemporal.texturaMain.push_back(temporalTexture);
                }
                for (int i = 0; i<3; i++) {
                    this->paredTemporal.tam.coordenadas[i] = 5;
                }
                this->empezarAModificarPared(&this->paredTemporal);
                break;
            case escalera:
                this->escalerasTemporales = ConstruccionEscaleras();
                sprintf(this->escalerasTemporales.id, "Escalera%lu+%d",this->yEscaleras.size(),rand());
                this->empezarAModificarEscalera(&this->escalerasTemporales);
                break;
            case suelo:
                this->sueloTemporal = ConstruccionSuelo();
                sprintf(this->sueloTemporal.id, "Pared%lu+%d",this->ySuelos.size(),rand());
                this->empezarAModificarSuelo(&this->sueloTemporal);
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
    this->dibujaParedT = true;
}
void Construccion::empezarAModificarSuelo(ConstruccionSuelo *suelo){
    this->estado = modificarSuelo;
    this->sueloModificable = suelo;
    this->dibujaSueloT = true;
}
void Construccion::empezarAModificarEscalera(ConstruccionEscaleras *escaleras){
    this->estado = modificarEscaleras;
    this->escalerasModificable = escaleras;
    this->dibujaEscaleraT = true;
}
void Construccion::empezarAModificarTextura(std::vector<PrimitivasSelectTexture> *textura, Construccion::ConstruccionEstados estadoRegresar){
    this->estadoARegresarTextura = estadoRegresar;
    this->texturaModificable = textura;
}
void Construccion::guardarModificacionTemporal(){
    switch (this->objetoActual) {
        case pared:
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
}
void Construccion::cancelarModificacionTemporal(){
    std::cout<<"Checa si es necesario\n";
}
void Construccion::borrarObjeto(unsigned long cual, Construccion::ConstruccionTipoConstruccion tipo){
    switch (tipo) {
        case pared:
            if (cual<this->yParedes.size()) {
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
            std::cout<<"No implementado copitexture accion despues de Buscar UInt\n";
            break;
        case empezarACrear:
            this->empezarAModificar(-1, this->estado);
            break;
        default:
            std::cout<<"Error ejecuccion accion no conocida\n";
            break;
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
    std::cout<<"No implentado Cargar\n";
}
void Construccion::guardar(){
    std::cout<<"No implentado Guardar\n";
}
void Construccion::dibujaPared(ConstruccionPared *pared){
    vPrimitivas->prismaEstandar(&(pared->texturaMain), pared->posicion.coordenadas, pared->tam.coordenadas);
}
