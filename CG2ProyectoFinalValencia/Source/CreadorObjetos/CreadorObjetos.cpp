//
//  CreadorObjetos.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/8/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "CreadorObjetos.hpp"

#define CREADOROBJETOSVERSIONARCHIVOS 0x18FF
//Directiva Vertice orden {Posicion Angulo Tamaño}

void CreadorObjetos::inicializar(Primitivas *p, KeyFrame *k, CargadorImage *c,Camara *cam){
    this->vPrimitivas = p;
    this->vKeyFrame = k;
    this->vCargadorImage = c;
    this->vCamara = cam;
    this->cargar();
//CamaraPos: P:{6.75014, 6, 7.08554, 6.09043, 5.61058, 6.44278, 0, 1, 0, } A:{3.94, -0.4, 1.57, }
    this->posicionPorDefecto.XYZ[0] = 6.75014;
    this->posicionPorDefecto.XYZ[1] = 6;
    this->posicionPorDefecto.XYZ[2] = 7.08554;
    this->posicionPorDefecto.XYZ[3] = 6.09043;
    this->posicionPorDefecto.XYZ[4] = 5.61058;
    this->posicionPorDefecto.XYZ[5] = 6.44278;
    
    this->posicionPorDefecto.Angles[0] = 3.94;
    this->posicionPorDefecto.Angles[1] = -0.4;
    this->posicionPorDefecto.Angles[2] = 1.57;
    
}
void CreadorObjetos::teclaActivaMenu(){
    std::cout<<"Menu Crear Objetos\n";
    this->estado = inicialCO;
    this->menuActivado = true;
    this->punteroSeleccion = 0;
    this->punteroPrimitiva = 0;
    this->punteroTextura = 0;
    if (!bloquearDibujo) {
        this->posicionAnterior = vCamara->posActual;
        this->vCamara->posActual = this->posicionPorDefecto;
        this->bloquearDibujo = true;
    }
    if (this->yObjetos.size()!=0) {
        this->dibujaObjetoPuntero = true;
    }
    this->esribeMenu();
    this->drawCursor();
}
void CreadorObjetos::teclaDeMenu(unsigned char tecla){
    guardar();
    if (tecla == '|') {
        std::cout<<"Menu actual\n";
        this->esribeMenu();
        this->drawCursor();
    }
    switch (estado) {
        case inicialCO:
            this->teclaDeMenuInicial(tecla);
            break;
        case buscaUintCO:
            if(this->vUIClassAux.teclaDeMenu(tecla)){
                ejecutaAccionDespuesBuscarUInt();
            }
            break;
        case modificarObjetoCO:
            this->teclaDeMenuModificarObjeto(tecla);
            break;
        case modificaTexturasCO:
//            this->teclaDeMenuModificarTexturas(tecla);
            if(this->vPrimitivas->teclaDeMenuTextura(tecla)){
                this->ejecutarAccionTexture();
            }
            break;
        default:
            break;
    }
}
void CreadorObjetos::esribeMenu(){
    switch (this->estado) {
        case inicialCO:
            if (cuantosDisponibles()!=0) {
                this->describeObjeto(&this->yObjetos[this->punteroSeleccion]);
                std::cout<<"Actual: "<<this->punteroSeleccion<<" Disponibles: "<<this->cuantosDisponibles()<<"\nM->Mostrar Disponibles\nC->Cambiar\nP->Editar\nX->Delete\n";
            }else{
                std::cout<<"Crea uno\n";
            }
            std::cout<<"N->Crear Objetos\n2->Cargar De Archivo(Mejor no)\n1->Guardar En Archivo\nz->Salir\nZ->Bloquear Dibujo\n";
            break;
        case buscaUintCO:
            this->vUIClassAux.escribeMenu();
            break;
        case modificarObjetoCO:
            if (yObjetos[punteroSeleccion].primitivas.size()!=0) {
                this->describePrimitiva(&this->yObjetos[this->punteroSeleccion].primitivas[this->punteroPrimitiva]);
                std::cout<<" Actual: "<<this->punteroPrimitiva<<" Disponibles: "<<this->yObjetos[punteroSeleccion].primitivas.size()<<"\nm->Mostrar Primitivas Disponibles\nM->Mostrar Texturas Disponibles\n3->Duplicar\n5->Set Cual Textura\n4->Create Texture for Actual\nC->Cambiar Primitiva\nX->Borrar\nP->Cambio Tipo\n6->Set Special value\n7->Set Transparencia\n8->Cambiar Posicion\n";
            }else{
                std::cout<<"Crea una primitiva\n";
            }
            std::cout<<"N->Crea Primitiva\nB->Set Textures\nZ->Salir\n";
            break;
        case modificaTexturasCO:
            this->vPrimitivas->escribeMenu();
            break;
        default:
            break;
    }
}
void CreadorObjetos::dibuja(){
    vPrimitivas->cruceta();
    if (this->dibujaObjetoPuntero){
        dibujaObjeto(this->punteroSeleccion,true);
    }
}
void CreadorObjetos::dibujaObjeto(unsigned int cual,bool dVertice){
    if (cual>this->yObjetos.size()) {
        std::cout<<"Error al dibujar objeto fuera de rango";
        return;
    }
    this->contadorPushPop = 0;
    objetoDibujando = &yObjetos[cual];
    glPushMatrix();
    for (int dop = 0; dop<objetoDibujando->primitivas.size(); dop++) {
        primitivaDibujando = &objetoDibujando->primitivas[dop];
        switch (primitivaDibujando->tipoTransparencia) {
            case desactivado:
                break;
            case blend:
                glEnable(GL_BLEND);
                break;
            case removeTest:
                glEnable(GL_ALPHA_TEST);
                break;
            default:
                break;
        }
        switch (primitivaDibujando->tipoPrimitiva) {
            case cilindro:
                glPushMatrix();
                glTranslated(primitivaDibujando->vertices[0].coordenadas[0], primitivaDibujando->vertices[0].coordenadas[1], primitivaDibujando->vertices[0].coordenadas[2]);
                glRotated(primitivaDibujando->vertices[1].coordenadas[0], 1, 0, 0);
                glRotated(primitivaDibujando->vertices[1].coordenadas[1], 0, 1, 0);
                glRotated(primitivaDibujando->vertices[1].coordenadas[2], 0, 0, 1);
                vPrimitivas->cilindroEstandar(&objetoDibujando->texturas, primitivaDibujando->desdeCualTexture, primitivaDibujando->vertices[2].coordenadas[0], primitivaDibujando->vertices[2].coordenadas[1], primitivaDibujando->valorEspecial);
                glPopMatrix();
                break;
            case esfera:
                glPushMatrix();
                glTranslated(primitivaDibujando->vertices[0].coordenadas[0], primitivaDibujando->vertices[0].coordenadas[1], primitivaDibujando->vertices[0].coordenadas[2]);
                glRotated(primitivaDibujando->vertices[1].coordenadas[0], 1, 0, 0);
                glRotated(primitivaDibujando->vertices[1].coordenadas[1], 0, 1, 0);
                glRotated(primitivaDibujando->vertices[1].coordenadas[2], 0, 0, 1);
                vPrimitivas->esferaEstandar(&objetoDibujando->texturas, primitivaDibujando->desdeCualTexture, primitivaDibujando->vertices[2].coordenadas[0], primitivaDibujando->valorEspecial);
                glPopMatrix();
                break;
            case plano:
//                glPushMatrix();
//                glTranslated(primitivaDibujando->vertices[0].coordenadas[0], primitivaDibujando->vertices[0].coordenadas[1], primitivaDibujando->vertices[0].coordenadas[2]);
//                glRotated(primitivaDibujando->vertices[1].coordenadas[0], 1, 0, 0);
//                glRotated(primitivaDibujando->vertices[1].coordenadas[1], 0, 1, 0);
//                glRotated(primitivaDibujando->vertices[1].coordenadas[2], 0, 0, 1);
//                vPrimitivas->planoEstandar(&objetoDibujando->texturas, primitivaDibujando->desdeCualTexture, puntoCentro.coordenadas, primitivaDibujando->vertices[2].coordenadas);
                glPopMatrix();
                break;
            case popm:
                if (contadorPushPop>=0) {
                    std::cout<<"Error contador pop ";
                    this->describeObjeto(objetoDibujando);
                }else {
                    glPopMatrix();
                    contadorPushPop--;
                }
                break;
            case nadaPrimiva:
                break;
            case prisma:
                glPushMatrix();
                glTranslated(primitivaDibujando->vertices[0].coordenadas[0], primitivaDibujando->vertices[0].coordenadas[1], primitivaDibujando->vertices[0].coordenadas[2]);
                glRotated(primitivaDibujando->vertices[1].coordenadas[0], 1, 0, 0);
                glRotated(primitivaDibujando->vertices[1].coordenadas[1], 0, 1, 0);
                glRotated(primitivaDibujando->vertices[1].coordenadas[2], 0, 0, 1);
                vPrimitivas->prismaEstandar(&objetoDibujando->texturas, primitivaDibujando->desdeCualTexture, this->puntoCentro.coordenadas, primitivaDibujando->vertices[2].coordenadas, 0);
                glPopMatrix();
                break;
            case translate:
                glPushMatrix();
                glTranslated(vKeyFrame->varMovimientos[primitivaDibujando->cualkey[0]].value, vKeyFrame->varMovimientos[primitivaDibujando->cualkey[1]].value,vKeyFrame->varMovimientos[primitivaDibujando->cualkey[2]].value);
                contadorPushPop++;
                break;
            case verticeAngulo:
                glPushMatrix();
                glTranslated(primitivaDibujando->vertices[0].coordenadas[0], primitivaDibujando->vertices[0].coordenadas[1], primitivaDibujando->vertices[0].coordenadas[2]);
                if (dVertice) {
                    this->vPrimitivas->cruceta(true);
                }
                glRotated(vKeyFrame->varMovimientos[primitivaDibujando->cualkey[0]].value, 1, 0, 0);
                glRotated(vKeyFrame->varMovimientos[primitivaDibujando->cualkey[1]].value, 0, 1, 0);
                glRotated(vKeyFrame->varMovimientos[primitivaDibujando->cualkey[2]].value, 0, 0, 1);
                glTranslated(-primitivaDibujando->vertices[0].coordenadas[0], -primitivaDibujando->vertices[0].coordenadas[1], -primitivaDibujando->vertices[0].coordenadas[2]);
                contadorPushPop++;
                break;
            case scaled:
                glPushMatrix();
                glScaled(vKeyFrame->varMovimientos[primitivaDibujando->cualkey[0]].value+1, vKeyFrame->varMovimientos[primitivaDibujando->cualkey[1]].value+1,vKeyFrame->varMovimientos[primitivaDibujando->cualkey[2]].value+1);
                contadorPushPop++;
                break;
            case otroObjeto:
                if (cual != this->primitivaDibujando->valorEspecial) {
                    glPushMatrix();
                    glTranslated(primitivaDibujando->vertices[0].coordenadas[0], primitivaDibujando->vertices[0].coordenadas[1], primitivaDibujando->vertices[0].coordenadas[2]);
                    glRotated(primitivaDibujando->vertices[1].coordenadas[0], 1, 0, 0);
                    glRotated(primitivaDibujando->vertices[1].coordenadas[1], 0, 1, 0);
                    glRotated(primitivaDibujando->vertices[1].coordenadas[2], 0, 0, 1);
                    glScaled(primitivaDibujando->vertices[2].coordenadas[0], primitivaDibujando->vertices[2].coordenadas[1], primitivaDibujando->vertices[2].coordenadas[2]);
                    this->dibujaObjeto(this->primitivaDibujando->valorEspecial);
                    glPopMatrix();
                }else std::cout<<"Error Recursividad de Objetos";
                break;
            default:
                break;
        }
        switch (primitivaDibujando->tipoTransparencia) {
            case desactivado:
                break;
            case blend:
                glDisable(GL_BLEND);
                break;
            case removeTest:
                glDisable(GL_ALPHA_TEST);
                break;
            default:
                break;
        }
    }
    for (long i =0; i<contadorPushPop; i++) {
        glPopMatrix();
    }
    glPopMatrix();
}
void CreadorObjetos::drawCursor(){
    if (estado == buscaUintCO) {
        this->vUIClassAux.drawCursor();
    }else{
    std::cout<<"CG2ProyectoFinalValenciaC "<< this->CreadorObjetosEstadosToChar[(unsigned char)this->estado] << " $ ";
    }
}
void CreadorObjetos::describeObjeto(CreadorObjetos::CreadorObjetosObjeto *objeto){
    std::cout<<objeto->id<<" Primitivas: "<<objeto->primitivas.size()<<" Texturas "<<objeto->texturas.size();
}
void CreadorObjetos::describePrimitiva(CreadorObjetos::CreadorObjetosPrimitivas *primitiva){
    std::cout<<this->CreadorObjetosTipoPrimitivaToChar[(unsigned int)primitiva->tipoPrimitiva]<<" Vertices: "<<primitiva->vertices.size()<<" Texture: "<<primitiva->desdeCualTexture;
}
unsigned int CreadorObjetos::cuantosDisponibles(){
    return (unsigned int) yObjetos.size();
}
void CreadorObjetos::teclaDeMenuInicial(unsigned char tecla){
    bool saltar = true;
    if (cuantosDisponibles()!=0) {
        switch (tecla) {
            case 'm':
            case 'M':
                std::cout<<"Mostar\n";
                this->escribeObjetosDisponibles();
                this->drawCursor();
                break;
            case 'c':
            case 'C':
                std::cout<<"Cambio\n";
                this->escribeObjetosDisponibles();
                this->empezarABuscarUint(&this->punteroSeleccion, this->cuantosDisponibles(), inicialCO,cambioPrimitiva);
                break;
            case 'p':
            case 'P':
                std::cout<<"Editando\n";
                this->estado = modificarObjetoCO;
                this->punteroPrimitiva = 0;
                if (yObjetos[punteroSeleccion].primitivas.size()!=0) {
                    this->empiezaMoveByPrimitiva(&yObjetos[punteroSeleccion].primitivas[0].vertices);
                }
                this->esribeMenu();
                this->drawCursor();
                break;
            case 'x':
            case 'X':
                if (punteroSeleccion < yObjetos.size()) {
                    std::cout<<"Borrado\n";
                    this->yObjetos.erase(yObjetos.begin()+punteroSeleccion);
                    if (punteroSeleccion >= yObjetos.size()) {
                        punteroSeleccion = (unsigned int)yObjetos.size()-1;
                    }
                }else{
                    std::cout<<"Posible error incial Creador Objetos\n";
                }
                if (yObjetos.size()==0){
                    punteroSeleccion = 0;
                    dibujaObjetoPuntero = false;
                }
                this->esribeMenu();
                this->drawCursor();
                break;
            default:
                saltar = false;
                break;
        }
        if (saltar) return;
    }
    switch (tecla) {
        case 'n':
        case 'N':
            std::cout<<"Agregar Name: ";
            this->estado = buscaUintCO;
            this->vUIClassAux.empezarABuscarString(nombreT, 10, (unsigned char *)&this->estado, (unsigned char)inicialCO, (unsigned char)inicialCO, (unsigned char) crearObj, (unsigned char) nadaCO, (unsigned char *)&this->accionDespuesBuscarUInt);
            break;
        case '2':
            std::cout<<"Cargando Archivo\n";
            this->cargar();
            this->drawCursor();
            break;
        case '1':
            std::cout<<"guardando Archivo\n";
            this->guardar();
            this->drawCursor();
            break;
        case 'z':
            std::cout<<"Fuera de menu Creador Objeto\n";
            this->estado = inicialCO;
            this->dibujaObjetoPuntero = false;
            this->bloquearDibujo = false;
            this->menuActivado = false;
            this->vCamara->posActual = posicionAnterior;
            break;
        case 'Z':
            std::cout<<"Fuera menu Blqueado\n";
            this->menuActivado = false;
            this->estado = inicialCO;
            break;
        default:
            break;
    }
}
void CreadorObjetos::empezarABuscarUint(unsigned int *a, unsigned int max, CreadorObjetos::CreadorObjetosEstados estadoRegresar,CreadorObjetosAccionesBuscaUInt acc){
    CreadorObjetosEstados est = estado;
    this->estado = buscaUintCO;
    this->vUIClassAux.empezarABuscarUInt(a, max,(unsigned char *) &estado,(unsigned char) estadoRegresar,(unsigned char) est, (unsigned char)acc, (unsigned char)nadaCO, (unsigned char*)&accionDespuesBuscarUInt);
}
void CreadorObjetos::teclaDeMenuModificarObjeto(unsigned char tecla){
    bool saltar = true;
    if (yObjetos[punteroSeleccion].primitivas.size()!=0) {
        switch (tecla) {
            case 'm':
                std::cout<<"Mostrar\n";
                this->escribePrimitivasDisponibles(&yObjetos[punteroSeleccion]);
                this->drawCursor();
                break;
            case 'M':
                this->vPrimitivas->describeSelecTextureVector(&yObjetos[punteroSeleccion].texturas);
                this->drawCursor();
                break;
            case 'c':
            case 'C':
                std::cout<<"Cambio\n";
                this->escribePrimitivasDisponibles(&yObjetos[punteroSeleccion]);
                this->empezarABuscarUint(&punteroPrimitiva, (unsigned int)yObjetos[punteroSeleccion].primitivas.size(), modificarObjetoCO,cambioPrimitiva);
                break;
            case 'x':
            case 'X':
                if (punteroPrimitiva<this->yObjetos[punteroSeleccion].primitivas.size()) {
                    std::cout<<"Borrado\n";
                    this->yObjetos[punteroSeleccion].primitivas.erase(this->yObjetos[punteroSeleccion].primitivas.begin()+punteroSeleccion);
                    if (punteroPrimitiva>=this->yObjetos[punteroSeleccion].primitivas.size()){
                        punteroPrimitiva = (unsigned int) this->yObjetos[punteroSeleccion].primitivas.size() - 1;
                    }
                    if (this->yObjetos[punteroSeleccion].primitivas.size()!=0) {
                        this->empiezaMoveByPrimitiva(&yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].vertices);
                    }
                }else{
                    std::cout<<"Error fuera de rango modificar Objeto crecion de objetos\n";
                }
                this->esribeMenu();
                this->drawCursor();
                break;
            case 'p':
            case 'P':
                std::cout<<"Cambiar tipo\n";
                this->escribeTiposDePrimitivasDispnibles();
                this->empezarABuscarUint((unsigned int *)&this->yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].tipoPrimitiva,MAXTIPOPRIMITIVA, modificarObjetoCO,modificacionCabio);
                break;
            case '3':
                std::cout<<"Duplicando "<<this->punteroPrimitiva;
                this->yObjetos[punteroSeleccion].primitivas.push_back(this->yObjetos[punteroSeleccion].primitivas[punteroPrimitiva]);
                this->punteroPrimitiva = (unsigned int) this->yObjetos[punteroSeleccion].primitivas.size() -1;
                this->esribeMenu();
                this->drawCursor();
                break;
            case '5':
                std::cout<<"Cambiando Desde donde Texture\n";
                this->vPrimitivas->describeSelecTextureVector(&this->yObjetos[punteroSeleccion].texturas);
                this->empezarABuscarUint(&this->yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].desdeCualTexture,(unsigned int) this->yObjetos[punteroSeleccion].texturas.size(), modificarObjetoCO);
                break;
            case '4':
                std::cout<<"Creando texturas\n";
                this->yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].desdeCualTexture =(unsigned int) this->yObjetos[punteroSeleccion].texturas.size();
                for (int i = 0; i<this->textureNecesariasPorTipoPrimitiva(yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].tipoPrimitiva); i++) {
                    yObjetos[punteroSeleccion].texturas.push_back(PrimitivasSelectTexture());
                }
                
                break;
            case '6':
                std::cout<<"Cambiar valor especial\n";
                if (this->yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].tipoPrimitiva == otroObjeto) {
                    this->escribeObjetosDisponibles();
                    this->empezarABuscarUint(&this->yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].valorEspecial,(unsigned int) this->yObjetos.size(), modificarObjetoCO);
                }else{
                    this->empezarABuscarUint(&this->yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].valorEspecial, 1000,modificarObjetoCO);

                }
                break;
            case '7':
                std::cout<<"Set Transparencia";
                this->escribeTiposDeTranspareciasDisponibles();
                this->empezarABuscarUint((unsigned int*)&this->yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].tipoTransparencia, MAXTIPOTRANSPARENCIA, modificarObjetoCO);
                break;
            case '8':
                std::cout<<"Intercambiar\n";
                this->empezarABuscarUint(&this->cambioLugarPrimitiva, (unsigned int)this->yObjetos[punteroSeleccion].primitivas.size(), modificarObjetoCO,interCambiarPosPrimitiva);
                break;
            default:
                saltar = this->vUIClassAux.teclaMove(tecla);
                break;
        }
        if (saltar) return;
    }
    switch (tecla) {
        case 'n':
        case 'N':
            std::cout<<"Creando nueva Primitiva\n";
            this->yObjetos[punteroSeleccion].primitivas.push_back(CreadorObjetosPrimitivas());
            this->punteroPrimitiva = (unsigned int) this->yObjetos[punteroSeleccion].primitivas.size() - 1;
            if (punteroPrimitiva == 0) {
                this->esribeMenu();
            }
            this->empiezaMoveByPrimitiva(&yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].vertices);
            drawCursor();
            
            break;
        case 'b':
        case 'B':
            if (yObjetos[punteroSeleccion].texturas.size()== 0) {
                std::cout<<"No hay texturas que editar\n";
            }else{
                std::cout<<"Editando Textura\n";
                this->estado = modificaTexturasCO;
//                this->punteroPrimitiva = 0;
//                this->esribeMenu();
//                this->drawCursor();
                this->vPrimitivas->empiezaAModificarTexture(&this->yObjetos[punteroSeleccion].texturas, (unsigned char*)&estado, (unsigned char) modificarObjetoCO, 0, &this->accionTexture,yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].desdeCualTexture);
            }
            break;
        case 'z':
        case 'Z':
            std::cout<<"Salir de Modificar Objeto\n";
            this->punteroTextura = 0;
            this->punteroPrimitiva = 0;
            this->estado = inicialCO;
            this->esribeMenu();
            this->drawCursor();
            break;
        default:
            break;
    }
}
void CreadorObjetos::ejecutaAccionDespuesBuscarUInt(){
    bool auxiliarBoleana = true;
    CreadorObjetosPrimitivas tprimitiva;
    switch (accionDespuesBuscarUInt) {
        case copiTexture:
            for (int i = 1; i<=auxiliarCopiarTexture; i++) {
                if (i+punteroTextura >= this->yObjetos[punteroSeleccion].texturas.size()) {
                    std::cout<<"Error Copi Texture ejecuta accion\n";
                    drawCursor();
                    break;
                }else{
                    this->yObjetos[punteroSeleccion].texturas[punteroTextura+i].cualTextura= this->yObjetos[punteroSeleccion].texturas[punteroTextura].cualTextura;
                    this->yObjetos[punteroSeleccion].texturas[punteroTextura+i].posicionInicio[0]= this->yObjetos[punteroSeleccion].texturas[punteroTextura].posicionInicio[0];
                    this->yObjetos[punteroSeleccion].texturas[punteroTextura+i].posicionInicio[1]= this->yObjetos[punteroSeleccion].texturas[punteroTextura].posicionInicio[1];
                }
            }
            break;
        case modificacionCabio:
            aseguraIntegridadCambio();
            this->empiezaMoveByPrimitiva(&yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].vertices);
            break;
        case cambioPrimitiva:
            if (punteroPrimitiva<yObjetos[punteroSeleccion].primitivas.size()) {
                this->empiezaMoveByPrimitiva(&yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].vertices);
            }
            break;
        case crearObj:
            this->yObjetos.push_back(CreadorObjetosObjeto());
            this->punteroSeleccion = (unsigned int)yObjetos.size() - 1;
            this->punteroPrimitiva = 0;
            this->estado = modificarObjetoCO;
            for (int i = 0; auxiliarBoleana; i++) {
                sprintf(yObjetos[punteroSeleccion].id, "%s+%04d",nombreT, i);
                auxiliarBoleana = false;
                for (int i = 0; i<yObjetos.size()-1; i++) {
                    if(!memcmp(yObjetos[i].id, yObjetos[punteroSeleccion].id, sizeof(char)*50)){
                        auxiliarBoleana = true;
                    }
                }
            }
            this->dibujaObjetoPuntero = true;
            break;
        case interCambiarPosPrimitiva:
            tprimitiva = yObjetos[punteroSeleccion].primitivas[cambioLugarPrimitiva];
            yObjetos[punteroSeleccion].primitivas[punteroPrimitiva] = yObjetos[punteroSeleccion].primitivas[cambioLugarPrimitiva];
            yObjetos[punteroSeleccion].primitivas[punteroPrimitiva] = tprimitiva;
            break;
        case nadaCO:
        default:
            break;
    }
    this->esribeMenu();
    this->drawCursor();
}
void CreadorObjetos::teclaDeMenuModificarTexturas(unsigned char tecla){
    if (yObjetos[punteroSeleccion].texturas.size()==0) std::cout<<"Error Textura vacia : ";
    
    switch (tecla) {
        case 'm':
        case 'M':
            std::cout<<"Mostrando\n";
            this->vPrimitivas->describeSelecTextureVector(&this->yObjetos[punteroSeleccion].texturas);
            this->drawCursor();
            break;
        case 'c':
        case 'C':
            std::cout<<"Cambiando\n";
            this->vPrimitivas->describeSelecTextureVector(&this->yObjetos[punteroSeleccion].texturas);
            this->empezarABuscarUint(&punteroTextura, (unsigned int) yObjetos[punteroSeleccion].texturas.size(), modificaTexturasCO);
            break;
        case 'V':
        case 'v':
            std::cout<<"Set Value\n";
            this->vCargadorImage->escribeTexturasDisponibles();
            this->empezarABuscarUint(&this->yObjetos[punteroSeleccion].texturas[punteroTextura].cualTextura, (unsigned int)vCargadorImage->texturas.size(), modificaTexturasCO);
            break;
        case 'g':
        case 'G':
            std::cout<<"Copiando\n";
            this->empezarABuscarUint(&this->auxiliarCopiarTexture, (unsigned int)this->yObjetos[punteroSeleccion].texturas.size()-this->punteroTextura, modificaTexturasCO,copiTexture);
            break;
        case 'x':
        case 'X':
            std::cout<<"Salir\n";
            this->estado = modificarObjetoCO;
            this->punteroTextura = 0;
            this->esribeMenu();
            this->drawCursor();
            break;
        case 'w':
        case 'W':
            this->yObjetos[punteroSeleccion].texturas[punteroTextura].posicionInicio[1] += 0.1;
            break;
        case 'S':
        case 's':
            this->yObjetos[punteroSeleccion].texturas[punteroTextura].posicionInicio[1] -= 0.1;
            break;
        case 'a':
        case 'A':
            this->yObjetos[punteroSeleccion].texturas[punteroTextura].posicionInicio[0] -= 0.1;
            break;
        case 'd':
        case 'D':
            this->yObjetos[punteroSeleccion].texturas[punteroTextura].posicionInicio[0] += 0.1;
            break;
        default:
            break;
    }
}
void CreadorObjetos::aseguraIntegridadCambio(){
    char nomT[50] = "";
    long cantidadTexturas =(long) yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].desdeCualTexture + textureNecesariasPorTipoPrimitiva(yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].tipoPrimitiva) - yObjetos[punteroSeleccion].texturas.size();
    unsigned int cantidadPuntos = puntosNecesariosPorTipoPrimitiva(yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].tipoPrimitiva);
    for (int i = 0; i<cantidadTexturas; i++) {
        yObjetos[punteroSeleccion].texturas.push_back(PrimitivasSelectTexture());
    }
    for (unsigned int i =(unsigned int) yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].vertices.size(); i < cantidadPuntos; i++) {
        yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].vertices.push_back(Cg2ValenciaPunto3D());
    }
    if (yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].tipoPrimitiva == verticeAngulo || yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].tipoPrimitiva == translate||yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].tipoPrimitiva == scaled) {
        sprintf(nomT,"%s@%04d0",yObjetos[punteroSeleccion].id,punteroPrimitiva);
        yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].cualkey[0] = this->vKeyFrame->crearVarMovimiento(nomT);
        sprintf(nomT,"%s@%04d1",yObjetos[punteroSeleccion].id,punteroPrimitiva);
        yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].cualkey[1] = this->vKeyFrame->crearVarMovimiento(nomT);
        sprintf(nomT,"%s@%04d2",yObjetos[punteroSeleccion].id,punteroPrimitiva);
        yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].cualkey[2] = this->vKeyFrame->crearVarMovimiento(nomT);
    }
}
void CreadorObjetos::escribeObjetosDisponibles(){
    for (int i = 0; i<yObjetos.size(); i++) {
        std::cout<<i<<".- ";
        this->describeObjeto(&yObjetos[i]);
        std::cout<<std::endl;
    }
}
unsigned int CreadorObjetos::puntosNecesariosPorTipoPrimitiva(CreadorObjetos::CreadorObjetosTipoPrimitiva tipo){
    switch (tipo) {
        case cilindro:
            return 3;
        case esfera:
            return 3;
        case nadaPrimiva:
            return 0;
        case plano:
            return 3;
        case popm:
            return 0;
        case prisma:
            return 3;
        case translate:
            return 0;
        case verticeAngulo:
            return 2;
        case otroObjeto:
            return 3;
        case scaled:
            return 0;
        default:
            break;
    }
    return 0;
}
unsigned int CreadorObjetos::textureNecesariasPorTipoPrimitiva(CreadorObjetos::CreadorObjetosTipoPrimitiva tipo){
    switch (tipo) {
        case cilindro:
            return PRIMITIVARVTCILINDRO;
        case esfera:
            return PRIMITIVAVRTESFERA;
        case nadaPrimiva:
            return 0;
        case plano:
            return PRIMITIVAVRTPLANO;
        case popm:
            return 0;
        case prisma:
            return PRIMITIVARVTPRISMAESTANDAR;
        case translate:
            return 0;
        case verticeAngulo:
            return 0;
        case otroObjeto:
            return 0;
        case scaled:
            return 0;
        default:
            break;
    }
    return 0;
}
void CreadorObjetos::escribeTiposDePrimitivasDispnibles(){
    for (unsigned int i = 0;i<MAXTIPOPRIMITIVA;i++){
        std::cout<<i<<".- "<<this->CreadorObjetosTipoPrimitivaToChar[i];
        std::cout<<std::endl;
    }
}
void CreadorObjetos::escribePrimitivasDisponibles(CreadorObjetos::CreadorObjetosObjeto *objeto){
    for (unsigned int i = 0;i<objeto->primitivas.size();i++){
        std::cout<<i<<".- ";
        this->describePrimitiva(&objeto->primitivas[i]);
        std::cout<<std::endl;
    }
}
void CreadorObjetos::guardar(){
    FILE * archivo = fopen(CREADOROBJETOSPATHFILE, "w");
    unsigned int cabecera = CREADOROBJETOSVERSIONARCHIVOS;
    unsigned int cantidadObj = (unsigned int) this->yObjetos.size();
    unsigned int cantidadPrimitivas = 0;
    unsigned int cantidadVertices = 0;
    unsigned int cantidadTexturas = 0;
    unsigned int aux = 0;
    CreadorObjetosPrimitivas *cualPrimitiva;
    PrimitivasSelectTexture *cualTexture;
    
    if (archivo == NULL) {
        std::cout<<"NO pude abrir el archivo";
    }
    fwrite(&cabecera, sizeof(unsigned int), 1, archivo);
    //objetos
    fwrite(&cantidadObj, sizeof(unsigned int), 1, archivo);
    for (unsigned int  i = 0; i<cantidadObj; i++) {
        fwrite(yObjetos[i].id, sizeof(char), MAXCHAR, archivo);
        //Primitivas
        cantidadPrimitivas = (unsigned int)yObjetos[i].primitivas.size();
        fwrite(&cantidadPrimitivas, sizeof(unsigned int), 1, archivo);
        for (unsigned int j = 0; j<cantidadPrimitivas; j++) {
            cualPrimitiva = &yObjetos[i].primitivas[j];
            aux = (unsigned int) cualPrimitiva->tipoPrimitiva;
            fwrite(&aux, sizeof(unsigned int), 1, archivo);
            aux = (unsigned int) cualPrimitiva->tipoTransparencia;
            fwrite(&aux, sizeof(unsigned int), 1, archivo);
            fwrite(&cualPrimitiva->desdeCualTexture, sizeof(unsigned int), 1, archivo);
            fwrite(&cualPrimitiva->valorEspecial, sizeof(unsigned int), 1, archivo);
            cantidadVertices = this->puntosNecesariosPorTipoPrimitiva(cualPrimitiva->tipoPrimitiva);
            while (cualPrimitiva->vertices.size()<cantidadVertices) {
                std::cout<<"Error al guardar corrupto ";
                this->describeObjeto(&yObjetos[i]);
                cualPrimitiva->vertices.push_back(Cg2ValenciaPunto3D());
            }
            fwrite(&cantidadVertices, sizeof(unsigned int), 1, archivo);
            for (unsigned int k = 0; k<cantidadVertices; k++) {
                fwrite(&cualPrimitiva->vertices[k].coordenadas, sizeof(double), 3, archivo);
            }
        }
        //Texturas
        cantidadTexturas = (unsigned int) yObjetos[i].texturas.size();
        fwrite(&cantidadTexturas, sizeof(unsigned int), 1, archivo);
        for (unsigned int l = 0; l<cantidadTexturas; l++) {
            cualTexture = &yObjetos[i].texturas[l];
            fwrite(cualTexture->posicionInicio, sizeof(double), 2, archivo);
            fwrite(vCargadorImage->texturas[cualTexture->cualTextura].nombreTexture, sizeof(char), MAXCHAR, archivo);
        }
    }
    fclose(archivo);
}
void CreadorObjetos::cargar(){
    FILE * archivo = fopen(CREADOROBJETOSPATHFILE, "r");
    unsigned int cabecera = 0;
    unsigned int cantidadObj = 0;
    unsigned int cantidadPrimitivas = 0;
    unsigned int cantidadVertices = 0;
    unsigned int cantidadTexturas = 0;
    unsigned int aux = 0;
    char auxname[MAXCHAR] = "";
    CreadorObjetosPrimitivas *cualPrimitiva;
    PrimitivasSelectTexture *cualTexture;
    
    if (archivo == NULL) {
        std::cout<<"NO esta el archivo";
        this->guardar();
        return;
    }
    fread(&cabecera, sizeof(unsigned int), 1, archivo);
    if (cabecera != CREADOROBJETOSVERSIONARCHIVOS) {
        std::cout<<cabecera<<" Cabecera incompatible posible incompatibilidad de versiones\n";
        fclose(archivo);
        return;
    }
    //objetos
    fread(&cantidadObj, sizeof(unsigned int), 1, archivo);
    for (unsigned int  i = 0; i<cantidadObj; i++) {
        yObjetos.push_back(CreadorObjetosObjeto());
        fread(yObjetos[i].id, sizeof(char), MAXCHAR, archivo);
        //Primitivas
        fread(&cantidadPrimitivas, sizeof(unsigned int), 1, archivo);
        for (unsigned int j = 0; j<cantidadPrimitivas; j++) {
            yObjetos[i].primitivas.push_back(CreadorObjetosPrimitivas());
            cualPrimitiva = &yObjetos[i].primitivas[j];
            fread(&aux, sizeof(unsigned int), 1, archivo);
            cualPrimitiva->tipoPrimitiva = (CreadorObjetosTipoPrimitiva) aux;
            fread(&aux, sizeof(unsigned int), 1, archivo);
            cualPrimitiva->tipoTransparencia = (CreadorObjetosTipoTransparencia) aux;
            fread(&cualPrimitiva->desdeCualTexture, sizeof(unsigned int), 1, archivo);
            fread(&cualPrimitiva->valorEspecial, sizeof(unsigned int), 1, archivo);
            //Vertices
            fread(&cantidadVertices, sizeof(unsigned int), 1, archivo);
            if (cantidadVertices != this->puntosNecesariosPorTipoPrimitiva(cualPrimitiva->tipoPrimitiva))std::cout<<"Error Con lectura";
            for (unsigned int k = 0; k<cantidadVertices; k++) {
                cualPrimitiva->vertices.push_back(Cg2ValenciaPunto3D());
                fread(&cualPrimitiva->vertices[k].coordenadas, sizeof(double), 3, archivo);
            }
        }
        //Texturas
        fread(&cantidadTexturas, sizeof(unsigned int), 1, archivo);
        for (unsigned int l = 0; l<cantidadTexturas; l++) {
            yObjetos[i].texturas.push_back(PrimitivasSelectTexture());
            cualTexture = &yObjetos[i].texturas[l];
            fread(cualTexture->posicionInicio, sizeof(double), 2, archivo);
            fread(auxname, sizeof(char), MAXCHAR, archivo);
            if(!this->vCargadorImage->echateABuscarTexture(auxname, &cualTexture->cualTextura))std::cout<<"Textura no encontrada "<<auxname<<std::endl;
        }
    }
    fclose(archivo);
    std::cout<<"Creador Objetos "<<yObjetos.size()<<" Cargadas\n";
    
    for (unsigned int m = 0; m<yObjetos.size(); m++) {
        this->punteroSeleccion = m;
        for (unsigned int n = 0; n<yObjetos[punteroSeleccion].primitivas.size(); n++) {
            punteroPrimitiva = n;
            this->aseguraIntegridadCambio();
        }
    }
    
}
long CreadorObjetos::calculaBalancePushPop(CreadorObjetos::CreadorObjetosObjeto *objeto){
    long r = 0;
    for (unsigned int i = 0; i<objeto->primitivas.size(); i++) {
        if (objeto->primitivas[i].tipoPrimitiva == translate||objeto->primitivas[i].tipoPrimitiva == verticeAngulo) {
            r++;
        }else if (objeto->primitivas[i].tipoPrimitiva == popm){
            r--;
        }
    }
    return r;
}
bool CreadorObjetos::echateABuscar(char *nombre, unsigned int *donde){
    for (unsigned int i = 0; i<yObjetos.size(); i++) {
        if (!memcmp(yObjetos[i].id, nombre, sizeof(char)*MAXCHAR)) {
            *donde = i;
            return true;
        }
    }
    return false;
}
void CreadorObjetos::escribeTiposDeTranspareciasDisponibles(){
    for (int i =0; i<MAXTIPOTRANSPARENCIA; i++) {
        std::cout<<i<<".- "<<this->CreadorObjetosTipoTransparenciaToChar[i]<<std::endl;
    }
}
void CreadorObjetos::empiezaMoveByPrimitiva(std::vector<Cg2ValenciaPunto3D> *cuales){
    switch (cuales->size()) {
        case 0:
            vUIClassAux.empezarABuscarMove(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0);
            break;
        case 1:
            vUIClassAux.empezarABuscarMove(&cuales->at(0).coordenadas[0], &cuales->at(0).coordenadas[1], &cuales->at(0).coordenadas[2], NULL, NULL, NULL, NULL, NULL, NULL, 0.1, 1, 0, 0);
            break;
        case 2:
            vUIClassAux.empezarABuscarMove(&cuales->at(0).coordenadas[0], &cuales->at(0).coordenadas[1], &cuales->at(0).coordenadas[2], NULL, NULL, NULL, &cuales->at(1).coordenadas[0], &cuales->at(1).coordenadas[1], &cuales->at(1).coordenadas[2], 0.1, 1, 11.25, 45);
            break;
        case 3:
        default:
            vUIClassAux.empezarABuscarMove(&cuales->at(0).coordenadas[0], &cuales->at(0).coordenadas[1], &cuales->at(0).coordenadas[2], &cuales->at(2).coordenadas[0], &cuales->at(2).coordenadas[1], &cuales->at(2).coordenadas[2], &cuales->at(1).coordenadas[0], &cuales->at(1).coordenadas[1], &cuales->at(1).coordenadas[2], 0.1, 1, 11.25, 45);
            break;
    }
}
void CreadorObjetos::ejecutarAccionTexture(){
    switch (this->accionTexture) {
        case 0:
            
            break;
            
        default:
            break;
    }
    this->esribeMenu();
    this->drawCursor();
}
