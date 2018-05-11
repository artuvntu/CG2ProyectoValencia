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

#define CONSTRUCCIONPATHFILE "CG2ProyectoFinalValencia.vc"
enum ConstruccionTipoPared: unsigned int {
    paredNormal=0,paredVentana=1,paredPuerta=2
};
enum ConstruccionTipoVentana: unsigned int {
    ventanaNormal=0
};
enum ConstruccionTipoPuerta: unsigned int {
    puertaNormal=0,zaguanDerecho=1,zaguanIzquiedo=2,cortinaAccesoria=3
};
struct _construccionpunto {
    double coordenadas[3] = {0, 0, 0};
}typedef ConstruccionPunto;
struct _construccionpared {
    char id[50] = "NULO";
    ConstruccionPunto posicion = ConstruccionPunto();
    ConstruccionPunto tam = ConstruccionPunto();
    double angulo = 0;
    std::vector<PrimitivasSelectTexture> texturaMain;
    ConstruccionTipoPared tipoPared = paredNormal;
    ConstruccionTipoVentana tipoVentana = ventanaNormal;
    ConstruccionTipoPuerta tipoPuerta = puertaNormal;
}typedef ConstruccionPared;
struct _construccionsuelo {
    char id[50] = "NULO";
    ConstruccionPunto posicion = ConstruccionPunto();
    std::vector<ConstruccionPunto> vertices;
    std::vector<PrimitivasSelectTexture> texturaMain;
}typedef ConstruccionSuelo;
struct _construccionescaleras {
    char id[50] = "@NULO";
    ConstruccionPunto posicion = ConstruccionPunto();
    ConstruccionPunto tam = ConstruccionPunto();
    double angulo = 0;
    unsigned int cantidadEscalones = 0;
    std::vector<PrimitivasSelectTexture> texturaMain;
}typedef ConstruccionEscaleras;

class Construccion{
public:
    void inicializar(Primitivas *primitivas,CargadorImage *cargadorImage,KeyFrame *keyFrame);
    void teclaActivaMenu();
    void teclaDeMenu(unsigned char tecla);
    void dibuja();
    bool menuActivado = false;

private:
    const char ConstruccionTipoParedToChar[3][30]={
        "Pared Normal","Pared Ventana","Pared Puerta"
    };
    const char ConstruccionTipoVentanaToChar[1][30]={
        "Ventana Normal"
    };
    const char ConstruccionTipoPuertaToChar[4][30]={
        "Puerta Normal","Zaguan D","Zaguan I","Cortina A"
    };
    const char estadosToChar[9][30] = {
        "Inicial","Buscando UInt","Agregar","Editar","Borrar","MPared","MSuelo","MEscaleras","Textura"
    };
    enum ConstruccionEstados:unsigned char{
        inicial=0,buscaUInt=1,agregarCosa=2,editarCosa=3,borrarCosa=4,modificarPared=5,modificarSuelo=6,modificarEscaleras=7,textura=8
    };
    const char accionesBuscarUIntToChar[3][30] = {"Nada","CopiTexture","Empezar A Crear"};
    enum ConstruccionAccionDespuesBuscarUInt:unsigned char{nada,copiTexture,empezarACrear};
    const char tipoConstruccionToChar[3][30] = {"Pared","Escalera","Suelo"};
    enum ConstruccionTipoConstruccion:unsigned int {pared=0, escalera=1, suelo=2};
    
    ConstruccionEstados estado = inicial;
    ConstruccionTipoConstruccion objetoActual = pared;
    
    std::vector<ConstruccionPared> yParedes;
    std::vector<ConstruccionSuelo> ySuelos;
    std::vector<ConstruccionEscaleras> yEscaleras;
    
    ConstruccionPared paredTemporal = ConstruccionPared();
    ConstruccionSuelo sueloTemporal = ConstruccionSuelo();
    ConstruccionEscaleras escalerasTemporales = ConstruccionEscaleras();
    
    ConstruccionPared *paredModificable = NULL;
    ConstruccionSuelo *sueloModificable = NULL;
    ConstruccionEscaleras *escalerasModificable = NULL;
    
    bool dibujaParedT = false;
    bool dibujaEscaleraT = false;
    bool dibujaSueloT = false;
    
    void escribeMenu();
    void drawCursor();
    void escribeDisponibles(int cual);
    void escribeTipoConstruccion();
    void escribeParedesDisponibles();
    void escribeEscalerasDisponibles();
    void escribeSueloDisponibles();
    
    void describePunto(ConstruccionPunto punto);
    void describePared(ConstruccionPared pared);
    void describeSuelo(ConstruccionSuelo suelo);
    void describeEscaleras(ConstruccionEscaleras escaleras);
    
    void teclaDeMenuInicial(unsigned char tecla);
    void teclaDeMenuBuscaUInt(unsigned char tecla);
    void teclaDeMenuAgregarCosa(unsigned char tecla);
    void teclaDeMenuEditarCosa(unsigned char tecla);
    void teclaDeMenuBorrarCosa(unsigned char tecla);
    void teclaDeMenuModificarPared(unsigned char tecla);
    void teclaDeMenuModificarSuelo(unsigned char tecla);
    void teclaDeMenuModificarEscaleras(unsigned char tecla);
    void teclaDeMenuTextura(unsigned char tecla);
    
    Primitivas *vPrimitivas;
    CargadorImage *vCargadorImage;
    KeyFrame *vKeyFrame;
    
    void empezarAModificar(int cual,ConstruccionEstados regresar);
    void empezarAModificarPared(ConstruccionPared *pared);
    void empezarAModificarEscalera(ConstruccionEscaleras *escaleras);
    void empezarAModificarSuelo(ConstruccionSuelo *suelo);
    
    void empezarAModificarTextura(std::vector<PrimitivasSelectTexture> *textura,ConstruccionEstados estadoRegresar);
    
    std::vector<PrimitivasSelectTexture> *texturaModificable;
    
    void empezarADibujarTemporal();
    void guardarModificacionTemporal();
    void cancelarModificacionTemporal();
    
    void dibujaPared(ConstruccionPared *pared);
    void dibujaEscaleras(ConstruccionEscaleras *escalera);
    void dibujaSuelo(ConstruccionSuelo *suelo);
    
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
    
    void cargar();
    void guardar();
    
    unsigned int auxiliarBasura = 0;
    
};

#endif
