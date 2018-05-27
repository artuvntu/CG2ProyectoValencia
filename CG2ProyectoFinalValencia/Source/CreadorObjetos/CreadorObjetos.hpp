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
#include "../UIClassAux/UIClassAux.hpp"
#include "../Camara/Camera.hpp"

#define CREADOROBJETOSPATHFILE "CG2ProyectoFinalValencia/Documents/CG2ProyectoFinalValencia.vco"

#define MAXTIPOPRIMITIVA 10
#define MAXTIPOTRANSPARENCIA 3

class CreadorObjetos{
public:
    char CreadorObjetosTipoPrimitivaToChar[MAXTIPOPRIMITIVA][30] = {
        "Nulo","Vertice Angulo","Translate","PopMatrix","Prisma","Esfera","Cilindro","Plano","Otro Objeto","Scaled"
    };
    enum CreadorObjetosTipoPrimitiva:unsigned int{
        nadaPrimiva=0,verticeAngulo=1,translate=2,popm=3,prisma=4,esfera=5,cilindro=6,plano=7,otroObjeto=8,scaled=9
    };
    char CreadorObjetosTipoTransparenciaToChar[MAXTIPOTRANSPARENCIA][30] = {
        "Desactivado","Blend","Remove Test"
    };
    enum CreadorObjetosTipoTransparencia:unsigned int{
        desactivado=0,blend=1,removeTest=2
    };
    struct _creadorobjetosprimitivas{
        CreadorObjetosTipoPrimitiva tipoPrimitiva = nadaPrimiva;
        CreadorObjetosTipoTransparencia tipoTransparencia = desactivado;
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
    
    void inicializar(Primitivas *p, KeyFrame *k, CargadorImage *c,Camara *cam);
    void teclaActivaMenu();
    void teclaDeMenu(unsigned char tecla);
    void dibuja();
    void dibujaObjeto(unsigned int cual,bool dVertice = false);
    void guardar();
    bool echateABuscar(char nombre[MAXCHAR],unsigned int *donde);
    void escribeObjetosDisponibles();

private:
//    char CreadorObjetosAccionesBuscaUIntToChar[3][30] = {"NADA","Asegurar Integridad Objeto","Copiar en Texturas"};
    enum  CreadorObjetosAccionesBuscaUInt:unsigned char{
        nadaCO=0,modificacionCabio=1,copiTexture=2,cambioPrimitiva=3,crearObj=4,interCambiarPosPrimitiva=5
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
    
//    bool moviminetoModificarObjeto(unsigned char tecla,CreadorObjetosPrimitivas *primitiva);
    
    void escribePrimitivasDisponibles(CreadorObjetosObjeto *objeto);
    void escribeTiposDePrimitivasDispnibles();
    void escribeTiposDeTranspareciasDisponibles();
    
    void describeObjeto(CreadorObjetosObjeto *objeto);
    void describePrimitiva(CreadorObjetosPrimitivas *primitiva);
    
    long calculaBalancePushPop(CreadorObjetosObjeto *objeto);
    
    void teclaDeMenuInicial(unsigned char tecla);
    void teclaDeMenuModificarObjeto(unsigned char tecla);
    void teclaDeMenuModificarTexturas(unsigned char tecla);
    
    void esribeMenu();
    void drawCursor();
    
    void cargar();
    
    Primitivas *vPrimitivas;
    KeyFrame *vKeyFrame;
    CargadorImage *vCargadorImage;
    Camara *vCamara;
    
    UIClassAux vUIClassAux;
    
    
    void empezarABuscarUint(unsigned int *a, unsigned int max, CreadorObjetosEstados estadoRegresar, CreadorObjetosAccionesBuscaUInt accion = nadaCO);
    void ejecutaAccionDespuesBuscarUInt();
    
    unsigned int punteroSeleccion = 0;
    unsigned int punteroPrimitiva = 0;
    unsigned int punteroTextura = 0;
    
    unsigned int auxiliarCopiarTexture = 0;
    
    unsigned int cuantosDisponibles();
    
    bool dibujaObjetoPuntero = false;
    
    unsigned char accionTexture = 0;
    void ejecutarAccionTexture();
    
    unsigned int textureNecesariasPorTipoPrimitiva(CreadorObjetosTipoPrimitiva tipo);
    unsigned int puntosNecesariosPorTipoPrimitiva(CreadorObjetosTipoPrimitiva tipo);
    
    void aseguraIntegridadCambio();
    long contadorPushPop = 0;
    
    CreadorObjetosObjeto *objetoDibujando = NULL;
    CreadorObjetosPrimitivas *primitivaDibujando = NULL;
    
    Camara::CamaraPos posicionAnterior;
    Camara::CamaraPos posicionPorDefecto;
    
    void empiezaMoveByPrimitiva(std::vector<Cg2ValenciaPunto3D> *cuales);
    
    char nombreT[20] = "prueba";
    
    unsigned int cambioLugarPrimitiva = 0;
    
};


#endif /* CreadorObjetos_hpp */
