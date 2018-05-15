//
//  CreadorObjetos.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/8/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "CreadorObjetos.hpp"


//Directiva Vertice orden {Posicion Angulo Tamaño}

void CreadorObjetos::inicializar(Primitivas *p, KeyFrame *k, CargadorImage *c){
    this->vPrimitivas = p;
    this->vKeyFrame = k;
    this->vCargadorImage = c;
    this->cargar();
    
}
void CreadorObjetos::teclaActivaMenu(){
    std::cout<<"Menu Crear Objetos\n";
    this->estado = inicialCO;
    this->menuActivado = true;
    this->punteroSeleccion = 0;
    this->punteroPrimitiva = 0;
    this->punteroTextura = 0;
    this->bloquearDibujo = true;
    if (this->yObjetos.size()!=0) {
        this->dibujaObjetoPuntero = true;
    }
    this->esribeMenu();
    this->drawCursor();
}
void CreadorObjetos::teclaDeMenu(unsigned char tecla){
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
            this->teclaDeMenuBuscaUInt(tecla);
            break;
        case modificarObjetoCO:
            this->teclaDeMenuModificarObjeto(tecla);
            break;
        case modificaTexturasCO:
            this->teclaDeMenuModificarTexturas(tecla);
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
                std::cout<<"Actual: "<<this->punteroSeleccion<<" Disponibles: "<<this->cuantosDisponibles()<<"\nM->Mostrar Disponibles\nC->Cambiar\nE->Editar\nD->Delete\n";
            }else{
                std::cout<<"Crea uno\n";
            }
            std::cout<<"A->Crear Objetos\nL->Cargar De Archivo(Mejor no)\nG->Guardar En Archivo\nS->Salir\nB->Bloquear Dibujo\n";
            break;
        case buscaUintCO:
            std::cout<<"Accion: \""<<this->CreadorObjetosAccionesBuscaUIntToChar[(unsigned char)this->accionDespuesBuscarUInt]<<"\" V Actual: "<<*this->dondeGuardar<<" Max: "<<this->maxDondeGuardar<<" Write: "<<this->temporalIntFromKeyBoard<<" Regresar a "<<this->CreadorObjetosEstadosToChar[(unsigned char)this->estadoARegresarBUInt]<<std::endl;
            break;
        case modificarObjetoCO:
//            std::cout<<"wsadqeikjluotgfhry\n";
            if (yObjetos[punteroSeleccion].primitivas.size()!=0) {
                this->describePrimitiva(&this->yObjetos[this->punteroSeleccion].primitivas[this->punteroPrimitiva]);
                std::cout<<" Actual: "<<this->punteroPrimitiva<<" Disponibles: "<<this->yObjetos[punteroSeleccion].primitivas.size()<<"\nM->Mostrar Disponibles\n3->Duplicar\n2->Set Cual Textura\n4->Create Texture for Actual\nC->Cambiar Primitiva\nB->Borrar\nV->Cambio Tipo\n";
            }else{
                std::cout<<"Crea una primitiva\n";
            }
            std::cout<<"1->Crea Primitiva\nZ->Set Textures\nX->Salir\n";
            break;
        case modificaTexturasCO:
//            wsda
            if (yObjetos[punteroSeleccion].texturas.size()==0) std::cout<<"Error Textura vacia :/\n";
            else{
                this->vCargadorImage->describeTextura(&this->vCargadorImage->texturas[this->yObjetos[punteroSeleccion].texturas[punteroTextura].cualTextura]);
                std::cout<<"Actual: "<<this->punteroTextura<<" Disponibles: "<< this->yObjetos[punteroSeleccion].texturas.size()<<"\nM->Mostrar Disponibles\nC->Cambiar\nV->Set Value\nX->Salir\nG->Copiar hasta\n";
            }
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
        switch (primitivaDibujando->tipoPrimitiva) {
            case cilindro:
                //Cilindro;
                break;
            case esfera:
                //Esfera
                break;
            case plano:
                glPushMatrix();
                glTranslated(primitivaDibujando->vertices[0].coordenadas[0], primitivaDibujando->vertices[0].coordenadas[1], primitivaDibujando->vertices[0].coordenadas[2]);
                glRotated(primitivaDibujando->vertices[1].coordenadas[0], 1, 0, 0);
                glRotated(primitivaDibujando->vertices[1].coordenadas[1], 0, 1, 0);
                glRotated(primitivaDibujando->vertices[1].coordenadas[2], 0, 0, 1);
                vPrimitivas->planoEstandar(&objetoDibujando->texturas, primitivaDibujando->desdeCualTexture, puntoCentro.coordenadas, primitivaDibujando->vertices[2].coordenadas);
                glPopMatrix();
            case planoTransparente:
                //Plano alpha
                break;
            case popm:
                if (contadorPushPop>=0) {
                    std::cout<<"Error contador pop ";
                    this->describeObjeto(objetoDibujando);
                }else glPopMatrix();
                break;
            case nadaPrimiva:
                break;
            case prismaTransparente:
                glPushMatrix();
                glEnable(GL_BLEND);
                glTranslated(primitivaDibujando->vertices[0].coordenadas[0], primitivaDibujando->vertices[0].coordenadas[1], primitivaDibujando->vertices[0].coordenadas[2]);
                glRotated(primitivaDibujando->vertices[1].coordenadas[0], 1, 0, 0);
                glRotated(primitivaDibujando->vertices[1].coordenadas[1], 0, 1, 0);
                glRotated(primitivaDibujando->vertices[1].coordenadas[2], 0, 0, 1);
                vPrimitivas->prismaEstandar(&objetoDibujando->texturas, primitivaDibujando->desdeCualTexture, this->puntoCentro.coordenadas, primitivaDibujando->vertices[2].coordenadas, 0);
                glDisable(GL_BLEND);
                glPopMatrix();
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
                glTranslated(vKeyFrame->varMovimientos[primitivaDibujando->cualkey[0]].value, vKeyFrame->varMovimientos[primitivaDibujando->cualkey[1]].value,vKeyFrame->varMovimientos[primitivaDibujando->cualkey[2]].value);
                contadorPushPop++;
                break;
            case verticeAngulo:
                glTranslated(primitivaDibujando->vertices[0].coordenadas[0], primitivaDibujando->vertices[0].coordenadas[1], primitivaDibujando->vertices[0].coordenadas[2]);
                if (dVertice) {
                    this->vPrimitivas->cruceta(true);
                }
                glRotated(vKeyFrame->varMovimientos[primitivaDibujando->cualkey[0]].value, 1, 0, 0);
                glRotated(vKeyFrame->varMovimientos[primitivaDibujando->cualkey[1]].value, 0, 1, 0);
                glRotated(vKeyFrame->varMovimientos[primitivaDibujando->cualkey[2]].value, 0, 0, 1);
                glTranslated(-primitivaDibujando->vertices[0].coordenadas[0], -primitivaDibujando->vertices[0].coordenadas[1], -primitivaDibujando->vertices[0].coordenadas[2]);
                contadorPushPop--;
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
    }
    for (long i =0; i<contadorPushPop; i++) {
        glPopMatrix();
    }
    glPopMatrix();
}
void CreadorObjetos::drawCursor(){
    std::cout<<"CG2ProyectoFinalValenciaC "<< this->CreadorObjetosEstadosToChar[(unsigned char)this->estado] << " $ ";
    if (this->estado == buscaUintCO && this->temporalIntFromKeyBoard != 0) {
        std::cout<<temporalIntFromKeyBoard;
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
    bool auxiliarBoleana = true;
    char nombre[100] = "prueba";
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
                this->empezarABuscarUint(&this->punteroSeleccion, this->cuantosDisponibles(), inicialCO);
                break;
            case 'e':
            case 'E':
                std::cout<<"Editando\n";
                this->estado = modificarObjetoCO;
                this->punteroPrimitiva = 0;
                this->esribeMenu();
                this->drawCursor();
                break;
            case 'd':
            case 'D':
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
        case 'A':
        case 'a':
            std::cout<<"Agregar Name: ";
//            std::cin>>nombre;
            this->yObjetos.push_back(CreadorObjetosObjeto());
            this->punteroSeleccion = (unsigned int)yObjetos.size() - 1;
            this->punteroPrimitiva = 0;
            this->estado = modificarObjetoCO;
            for (int i = 0; auxiliarBoleana; i++) {
                sprintf(yObjetos[punteroSeleccion].id, "%s+%04d",nombre, i);
                auxiliarBoleana = false;
                for (int i = 0; i<yObjetos.size()-1; i++) {
                    if(!memcmp(yObjetos[i].id, yObjetos[punteroSeleccion].id, sizeof(char)*50)){
                        auxiliarBoleana = true;
                    }
                }
            }
            this->dibujaObjetoPuntero = true;
            this->esribeMenu();
            this->drawCursor();
            break;
        case 'L':
        case 'l':
            std::cout<<"Cargando Archivo\n";
            this->cargar();
            this->drawCursor();
            break;
        case 'G':
        case 'g':
            std::cout<<"guardando Archivo\n";
            this->guardar();
            this->drawCursor();
            break;
        case 's':
        case 'S':
            std::cout<<"Fuera de menu Creador Objeto\n";
            this->estado = inicialCO;
            this->dibujaObjetoPuntero = false;
            this->bloquearDibujo = false;
            this->menuActivado = false;
            break;
        case 'b':
        case 'B':
            std::cout<<"Fuera menu Blqueado\n";
            this->menuActivado = false;
            this->estado = inicialCO;
            break;
        default:
            break;
    }
}
void CreadorObjetos::teclaDeMenuBuscaUInt(unsigned char tecla){
    if (tecla >= 48 && tecla <= 57) {
        std::cout << (tecla -48);
        this->temporalIntFromKeyBoard= (this->temporalIntFromKeyBoard * 10)+(tecla - 48);
        if (this->temporalIntFromKeyBoard >= this->maxDondeGuardar){
            std::cout<<"\nNumero mayor a los disponibles\n";
            this->estado = this->estadoAnterior;
            this->estadoAnterior = inicialCO;
            this->estadoARegresarBUInt = inicialCO;
            this->drawCursor();
        }
    }else if (tecla == 13){
        std::cout <<std::endl;
        *this->dondeGuardar = this->temporalIntFromKeyBoard;
        this->temporalIntFromKeyBoard = 0;
        this->estado = this->estadoARegresarBUInt;
        this->estadoARegresarBUInt = inicialCO;
        this->estadoAnterior = inicialCO;
        this->ejecutaAccionDespuesBuscarUInt();
        this->esribeMenu();
        this->drawCursor();
    }else{
        std::cout<<"\nCancelado\n";
        this->estado = this->estadoAnterior;
        this->estadoARegresarBUInt = inicialCO;
        this->estadoAnterior = inicialCO;
        this->drawCursor();
    }
}
void CreadorObjetos::empezarABuscarUint(unsigned int *a, unsigned int max, CreadorObjetos::CreadorObjetosEstados estadoRegresar,CreadorObjetosAccionesBuscaUInt acc){
    if (max == 0) {
        std::cout<<"No hay donde elegir "<<this->CreadorObjetosEstadosToChar[(unsigned char)estadoRegresar]<<std::endl;
        return;
    }
    this->estadoAnterior = this->estado;
    this->estado = buscaUintCO;
    this->dondeGuardar = a;
    this->maxDondeGuardar = max;
    this->accionDespuesBuscarUInt = acc;
    this->estadoARegresarBUInt = estadoRegresar;
    this->temporalIntFromKeyBoard = 0;
    this->esribeMenu();
    this->drawCursor();
}
void CreadorObjetos::teclaDeMenuModificarObjeto(unsigned char tecla){
    bool saltar = true;
    if (yObjetos[punteroSeleccion].primitivas.size()!=0) {
        switch (tecla) {
            case 'm':
            case 'M':
                std::cout<<"Mostrar\n";
                this->escribePrimitivasDisponibles(&yObjetos[punteroSeleccion]);
                this->drawCursor();
                break;
            case 'c':
            case 'C':
                std::cout<<"Cambio";
                this->escribePrimitivasDisponibles(&yObjetos[punteroSeleccion]);
                this->empezarABuscarUint(&punteroPrimitiva, (unsigned int)yObjetos[punteroSeleccion].primitivas.size(), modificarObjetoCO);
                break;
            case 'B':
            case 'b':
                if (punteroPrimitiva<this->yObjetos[punteroSeleccion].primitivas.size()) {
                    std::cout<<"Borrado\n";
                    this->yObjetos[punteroSeleccion].primitivas.erase(this->yObjetos[punteroSeleccion].primitivas.begin()+punteroSeleccion);
                    if (punteroPrimitiva>=this->yObjetos[punteroSeleccion].primitivas.size()){
                        punteroPrimitiva = (unsigned int) this->yObjetos[punteroSeleccion].primitivas.size() - 1;
                    }
                    
                }else{
                    std::cout<<"Error fuera de rango modificar Objeto crecion de objetos\n";
                }
                this->esribeMenu();
                this->drawCursor();
                break;
            case 'v':
            case 'V':
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
            case '2':
                std::cout<<"Cambiando Desde donde Texture";
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
            case '5':
                std::cout<<"Cambiar valor especial\n";
                if (this->yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].tipoPrimitiva == otroObjeto) {
                    this->escribeObjetosDisponibles();
                    this->empezarABuscarUint(&this->yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].valorEspecial,(unsigned int) this->yObjetos.size(), modificarObjetoCO);
                }else{
                    this->empezarABuscarUint(&this->yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].valorEspecial, 1000,modificarObjetoCO);

                }
                break;
            default:
                saltar = this->moviminetoModificarObjeto(tecla, &yObjetos[punteroSeleccion].primitivas[punteroPrimitiva]);
                break;
        }
        if (saltar) return;
    }
    switch (tecla) {
        case '1':
            std::cout<<"Creando nueva Primitiva\n";
            this->yObjetos[punteroSeleccion].primitivas.push_back(CreadorObjetosPrimitivas());
            this->punteroPrimitiva = (unsigned int) this->yObjetos[punteroSeleccion].primitivas.size() - 1;
            if (punteroPrimitiva == 0) {
                this->esribeMenu();
            }
            drawCursor();
            
            break;
        case 'z':
        case 'Z':
            if (yObjetos[punteroSeleccion].texturas.size()== 0) {
                std::cout<<"No hay texturas que editar\n";
            }else{
                std::cout<<"Editando Textura\n";
                this->estado = modificaTexturasCO;
                this->punteroPrimitiva = 0;
                this->esribeMenu();
                this->drawCursor();
            }
            break;
        case 'x':
        case 'X':
            std::cout<<"Salir de Modificar Objeto\n";
            this->punteroTextura = 0;
            this->punteroSeleccion = 0;
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
            break;
        default:
            break;
    }
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
    if (yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].tipoPrimitiva == verticeAngulo || yObjetos[punteroSeleccion].primitivas[punteroPrimitiva].tipoPrimitiva == translate) {
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
        this->describeObjeto(&yObjetos[i]);
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
    }
}
void CreadorObjetos::guardar(){
    std::cout<<"Objetos Adicionales: Aun no puedo guardar\n";

}
void CreadorObjetos::cargar(){
    std::cout<<"Objetos Adicionales: Aun no puedo cargar\n";
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
bool CreadorObjetos::moviminetoModificarObjeto(unsigned char tecla, CreadorObjetos::CreadorObjetosPrimitivas *primitiva){
    int signo = 1;
    int cual = 0;
    int coor = 0;
    for (int i =0 ; i<18*2; i++) {
        if (tecla == this->teclasMovimientoModificarObjeto[i]) {
            i = i%18;
            if (i%2) {
                signo = -1;
            }
            i = i/2;
            cual = i/3;
            coor = i%3;
            if (cual < primitiva->vertices.size()) {
                if (cual == 1) {
                    primitiva->vertices[cual].coordenadas[coor] += 22.5*signo;
                }else{
                    if (cual == 2&&coor == 2) {
                        primitiva->vertices[cual].coordenadas[coor] -= 0.1*signo;
                    }else{
                        primitiva->vertices[cual].coordenadas[coor] += 0.1*signo;
                    }
                }
                glutPostRedisplay();
                return true;
            }else{
                std::cout<<"Movimiento Fuera de vertices\n";
                drawCursor();
                return false;
            }
        }
    }
    return false;
}

