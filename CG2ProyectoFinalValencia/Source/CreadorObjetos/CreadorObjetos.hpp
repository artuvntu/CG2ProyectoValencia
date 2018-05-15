//
//  CreadorObjetos.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/8/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#ifndef CreadorObjetos_hpp
#define CreadorObjetos_hpp

#include "../../Libraries.hpp"
#include "../Primitivas/Primitivas.hpp"

#define CREADOROBJETOSPATHFILE "CG2ProyectoFinalValencia/Documents/CG2ProyectoFinalValencia.vco"

#define MAXTIPOPRIMITIVA 11

class CreadorObjetos{
public:
    char CreadorObjetosTipoPrimitivaToChar[MAXTIPOPRIMITIVA][30] = {
        "Nulo","Vertice Angulo","Translate","PopMatrix","Prisma","Esfera","Cilindro","Plano","Otro Objeto","Plano Alpha","Prisma Alpha"
    };
    enum CreadorObjetosTipoPrimitiva:unsigned int{
        nadaPrimiva=0,verticeAngulo=1,translate=2,popm=3,prisma=4,esfera=5,cilindro=6,plano=7,otroObjeto=8,planoTransparente=9,prismaTransparente=10
    };
    struct _creadorobjetosprimitivas{
        CreadorObjetosTipoPrimitiva tipoPrimitiva = nadaPrimiva;
        std::vector<Cg2ValenciaPunto3D> vertices;
        unsigned int desdeCualTexture = 0;
        unsigned int valorEspecial = 0;
        unsigned int cualkey[3] = {0,0,0};
    }typedef CreadorObjetosPrimitivas;
    struct _creadorobjetosobjeto{
        char id[MAXCHAR]= "NULO";
        std::vector<PrimitivasSelectTexture> texturas;
        std::vector<CreadorObjetosPrimitivas> primitivas;
    }typedef CreadorObjetosObjeto;

    std::vector<CreadorObjetosObjeto> yObjetos;
    bool menuActivado = false;
    bool bloquearDibujo = false;
    
    void inicializar(Primitivas *p, KeyFrame *k, CargadorImage *c);
    void teclaActivaMenu();
    void teclaDeMenu(unsigned char tecla);
    void dibuja();
    void dibujaObjeto(unsigned int cual,bool dVertice = false);

private:
    char CreadorObjetosAccionesBuscaUIntToChar[3][30] = {"NADA","Asegurar Integridad Objeto","Copiar en Texturas"};
    enum  CreadorObjetosAccionesBuscaUInt:unsigned char{
        nadaCO=0,modificacionCabio=1,copiTexture=2
    };
    
    Cg2ValenciaPunto3D puntoCentro = Cg2ValenciaPunto3D();
    
    CreadorObjetosAccionesBuscaUInt accionDespuesBuscarUInt;
    char CreadorObjetosEstadosToChar[4][30]={
        "inicial","buscaUint","modificarObjeto","modificaTexturas"
    };
    enum CreadorObjetosEstados: unsigned char{
        inicialCO=0,buscaUintCO=1,modificarObjetoCO=2,modificaTexturasCO=3,
    };
    CreadorObjetosEstados estado = inicialCO;
    
//    unsigned char teclasMovimientoModificarObjeto[40] = "wsadqeikjluotgfhryWSADQEIKJLUOTGFHRY";
    unsigned char teclasMovimientoModificarObjeto[40] = "daeqswljoukihfyrgtDAEQSWLJOUKIHFYRGT";
    
    bool moviminetoModificarObjeto(unsigned char tecla,CreadorObjetosPrimitivas *primitiva);
    
    void escribeObjetosDisponibles();
    void escribePrimitivasDisponibles(CreadorObjetosObjeto *objeto);
    void escribeTiposDePrimitivasDispnibles();
    
    void describeObjeto(CreadorObjetosObjeto *objeto);
    void describePrimitiva(CreadorObjetosPrimitivas *primitiva);
    
    long calculaBalancePushPop(CreadorObjetosObjeto *objeto);
    
    void teclaDeMenuInicial(unsigned char tecla);
    void teclaDeMenuBuscaUInt(unsigned char tecla);
    void teclaDeMenuModificarObjeto(unsigned char tecla);
    void teclaDeMenuModificarTexturas(unsigned char tecla);
    
    void esribeMenu();
    void drawCursor();
    
    void cargar();
    void guardar();
    
    Primitivas *vPrimitivas;
    KeyFrame *vKeyFrame;
    CargadorImage *vCargadorImage;
    
    void empezarABuscarUint(unsigned int *a, unsigned int max, CreadorObjetosEstados estadoRegresar, CreadorObjetosAccionesBuscaUInt accion = nadaCO);
    void ejecutaAccionDespuesBuscarUInt();
    
    unsigned int punteroSeleccion = 0;
    unsigned int punteroPrimitiva = 0;
    unsigned int punteroTextura = 0;
    
    unsigned int auxiliarCopiarTexture = 0;
    
    unsigned int cuantosDisponibles();
    
    bool dibujaObjetoPuntero = false;
    
    CreadorObjetosEstados estadoARegresarBUInt;
    CreadorObjetosEstados estadoAnterior;
    
    unsigned int *dondeGuardar = NULL;
    unsigned int maxDondeGuardar = 0;
    unsigned int temporalIntFromKeyBoard = 0;
    
    unsigned int textureNecesariasPorTipoPrimitiva(CreadorObjetosTipoPrimitiva tipo);
    unsigned int puntosNecesariosPorTipoPrimitiva(CreadorObjetosTipoPrimitiva tipo);
    
    void aseguraIntegridadCambio();
    long contadorPushPop = 0;
    
    CreadorObjetosObjeto *objetoDibujando = NULL;
    CreadorObjetosPrimitivas *primitivaDibujando = NULL;
};


#endif /* CreadorObjetos_hpp */
