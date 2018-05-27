//
//  Construccion.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/8/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#ifndef construccion_hpp
#define construccion_hpp

#include "../../Libraries.hpp"

#include "../Primitivas/Primitivas.hpp"

#define CONSTRUCCIONPATHFILE "CG2ProyectoFinalValencia/Documents/CG2ProyectoFinalValencia.vc"

#define ConstruccionTipoPuertaToCharTAM 7
#define ConstruccionTipoVentanaToCharTAM 3

class Construccion{
public:

    void inicializar(Primitivas *primitivas,CargadorImage *cargadorImage,KeyFrame *keyFrame);
    void teclaActivaMenu();
    void teclaDeMenu(unsigned char tecla);
    void dibujaAntes();
    void dibujaDespues();
    bool menuActivado = false;

    void guardar();
    
private:
    enum ConstruccionTipoPared: unsigned int {
        paredNormal=0,paredVentana=1,paredPuerta=2
    };
    enum ConstruccionTipoVentana: unsigned int {
        ventananulo=0,ventanaNormal=1,ventanaEspacio=2
    };
    enum ConstruccionTipoPuerta: unsigned int {
        puertanulo=0,puertaNormal=1,zaguanDerecho=2,zaguanIzquiedo=3,cortinaAccesoria=4,puertaVerde=5,puertaEspacio=6
    };
    struct _construccionpared {
        char id[50] = "NULO";
        std::vector<Cg2ValenciaPunto3D> vertice={Cg2ValenciaPunto3D(),Cg2ValenciaPunto3D()};
        double angulo = 0;
        unsigned int cualVarMovimiento = 0;
        std::vector<PrimitivasSelectTexture> texturaMain;
        ConstruccionTipoPared tipoPared = paredNormal;
        ConstruccionTipoVentana tipoVentana = ventananulo;
        ConstruccionTipoPuerta tipoPuerta = puertanulo;
    }typedef ConstruccionPared;
    struct _construccionsuelo {
        char id[50] = "NULO";
        std::vector<Cg2ValenciaPunto3D> vertices;
        std::vector<PrimitivasSelectTexture> texturaMain;
        unsigned int cualVarMovimiento[2] = {0, 0};
    }typedef ConstruccionSuelo;
    struct _construccionescaleras {
        char id[50] = "@NULO";
        std::vector<Cg2ValenciaPunto3D> vertice={Cg2ValenciaPunto3D(),Cg2ValenciaPunto3D()};
        double angulo = 0;
        unsigned int cantidadEscalones = 0;
        std::vector<PrimitivasSelectTexture> texturaMain;
    }typedef ConstruccionEscaleras;
    
    char ConstruccionTipoParedToChar[3][30]={
        "Pared Normal","Pared Ventana","Pared Puerta"
    };
    char ConstruccionTipoVentanaToChar[ConstruccionTipoVentanaToCharTAM][30]={
        "NULO","Ventana Normal","Ventana Espacio"
    };
    char ConstruccionTipoPuertaToChar[ConstruccionTipoPuertaToCharTAM][30]={
        "NULO","Puerta Normal","Zaguan D","Zaguan I","Cortina A","Puerta Verde","Puesta Espacio"
    };
    char estadosToChar[9][30] = {
        "Inicial","Buscando UInt","Agregar","Editar","Borrar","MPared","MSuelo","MEscaleras","Textura"
    };
    enum ConstruccionEstados:unsigned char{
        inicial=0,buscaUInt=1,agregarCosa=2,editarCosa=3,borrarCosa=4,modificarPared=5,modificarSuelo=6,modificarEscaleras=7,modificarTextura=8
    };
//    char accionesBuscarUIntToChar[3][30] = {"Nada","CopiTexture","Empezar A Crear"};
    enum ConstruccionAccionDespuesBuscarUInt:unsigned char{
        nada,copiTexture,empezarACrear,modificarParedAsegurateCambioTipoCompleto,cambiaNodoSuelo,borraPared
    };
    char tipoConstruccionToChar[3][30] = {"Pared","Escalera","Suelo"};
    enum ConstruccionTipoConstruccion:unsigned int {pared=0, escalera=1, suelo=2};
    
    ConstruccionEstados estado = inicial;
    ConstruccionTipoConstruccion objetoActual = pared;
    
    std::vector<ConstruccionPared> yParedes;
    std::vector<ConstruccionSuelo> ySuelos;
    std::vector<ConstruccionEscaleras> yEscaleras;
    
//    ConstruccionPared paredTemporal = ConstruccionPared();
//    ConstruccionSuelo sueloTemporal = ConstruccionSuelo();
//    ConstruccionEscaleras escalerasTemporales = ConstruccionEscaleras();
    
    //ConstruccionPared *paredModificable = NULL;
    //ConstruccionSuelo *sueloModificable = NULL;
    //ConstruccionEscaleras *escalerasModificable = NULL;
    
    unsigned int punteroParedModificable = 0;
    unsigned int punteroSueloModificable = 0;
    unsigned int punteroEscaleraModificable = 0;
    
//    bool dibujaParedT = false;
//    bool dibujaEscaleraT = false;
//    bool dibujaSueloT = false;
    
    void escribeMenu();
    void drawCursor();
    void escribeDisponibles(int cual);
    void escribeTipoConstruccion();
    void escribeParedesDisponibles();
    void escribeEscalerasDisponibles();
    void escribeSueloDisponibles();
    
    void describePared(ConstruccionPared pared);
    void describeSuelo(ConstruccionSuelo suelo);
    void describeEscaleras(ConstruccionEscaleras escaleras);
    void describePuntos(std::vector<Cg2ValenciaPunto3D> puntos);
    
    void teclaDeMenuInicial(unsigned char tecla);
//    void teclaDeMenuBuscaUInt(unsigned char tecla);
    void teclaDeMenuAgregarCosa(unsigned char tecla);
    void teclaDeMenuEditarCosa(unsigned char tecla);
    void teclaDeMenuBorrarCosa(unsigned char tecla);
    void teclaDeMenuModificarPared(unsigned char tecla);
    void teclaDeMenuModificarSuelo(unsigned char tecla);
    void teclaDeMenuModificarEscaleras(unsigned char tecla);
//    void teclaDeMenuTextura(unsigned char tecla);
    
    Primitivas *vPrimitivas;
    CargadorImage *vCargadorImage;
    KeyFrame *vKeyFrame;
    UIClassAux vUIClassAux;
    
    void empezarAModificar(int cual,ConstruccionEstados regresar);
    void empezarAModificarPared(unsigned int cual);
    void empezarAModificarEscalera(unsigned int cual);
    void empezarAModificarSuelo(unsigned int cual);
    
    void empezarAModificarTextura(std::vector<PrimitivasSelectTexture> *textura,ConstruccionEstados estadoRegresar);
    
//    std::vector<PrimitivasSelectTexture> *texturaModificable;
//    unsigned int punteroModificarTextura = 0;
    
    unsigned int punteroModificarSuelo = 0;
    
    void aseguraIntegridadParedTam(ConstruccionPared *pared);
    void aseguraIntegridadParedTamByNumber(ConstruccionPared *pared,unsigned int texturas,unsigned int segmentos);
    
    void asegurarIntegridadParedCalculos(ConstruccionPared *pared);
    void asegurarIntegridadParedVentanaNormalCalculos(ConstruccionPared *pared);
    void asegurarIntegridadParedPuertaNormalCalculos(ConstruccionPared *pared);
    void asegurarIntegridadParedPuertaNormalCalculos2(ConstruccionPared *pared);
    void asegurarIntegridadParedPuertaNormalCalculos3(ConstruccionPared *pared);

    
    void aseguraIntegridadSueloTam(ConstruccionSuelo *suelo);
    void aseguraIntegridadSueloCalculos(ConstruccionSuelo *suelo);

    
    void empezarADibujarTemporal();
    void guardarModificacionTemporal();
    void cancelarModificacionTemporal();
    
    void dibujaPared(ConstruccionPared *pared);
    void dibujaEscaleras(ConstruccionEscaleras *escalera);
    void dibujaSuelo(ConstruccionSuelo *suelo);
    void dibujaParedVentanaNormal(ConstruccionPared *pared);
    
    void borrarObjeto(unsigned long cual,ConstruccionTipoConstruccion tipo);
    
    void empezarABuscarUint(unsigned int *a, unsigned int max, ConstruccionEstados estadoRegresar, ConstruccionAccionDespuesBuscarUInt accion = nada);
    void ejecutaAccionDespuesBuscarUInt();
    
    unsigned long cuantosDisponiblesDe(ConstruccionTipoConstruccion tipo);
    
    unsigned int punteroEditar = 0;
    
    unsigned int *dondeGuardar = NULL;
    unsigned int maxDondeGuardar = 0;
    unsigned int temporalIntFromKeyBoard = 0;
    ConstruccionEstados estadoARegresar = inicial;
    ConstruccionEstados estadoAnterior = inicial;
    ConstruccionAccionDespuesBuscarUInt accionDespuesBuscarInt = nada;

    ConstruccionEstados estadoARegresarModificar = inicial;
    ConstruccionEstados estadoARegresarTextura = inicial;
    
    std::vector<PrimitivasSelectTexture> puertaNormalTexturas;
    std::vector<PrimitivasSelectTexture> ventanaNormalTexturas;
    std::vector<PrimitivasSelectTexture> accesoriaTextura;
    std::vector<PrimitivasSelectTexture> zaguanTextureD;
    std::vector<PrimitivasSelectTexture> zaguanTextureI;
    std::vector<PrimitivasSelectTexture> puertaVerdeTexture;
    PrimitivasSelectTexture defaultTexture;
    std::vector<PrimitivasSelectTexture> textureMundo;
    
    std::vector<unsigned long> ventanasADibujar;
    
    double movimientoSueloEnteroT[3] = {0,0,0};
    void movimientoSueloEnteroAjusta(ConstruccionSuelo *suelo);
    
    void cargar();
    
    void escribeEnOrdencharArray(char arreglo[][30],unsigned int cuantos);
    
//    PrimitivasSelectTexture textureMundo[3] = {PrimitivasSelectTexture(),PrimitivasSelectTexture(),PrimitivasSelectTexture()};
    
    unsigned int auxiliarBasura = 0;
    
    unsigned char accionTextura;
    void ejecutarAccionDespuesTexture();
    
};

#endif
