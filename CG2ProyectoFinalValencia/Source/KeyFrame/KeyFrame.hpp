//
//  KeyFrame.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/02/18.
//  Copyright © 2018 vApps. All rights reserved.
//
#ifndef keyframe_hpp
#define keyframe_hpp
#include "../../Libraries.hpp"

#define KEYFRAMEPATHFILE "CG2ProyectoFinalValencia.vkf" //vKeyFrame

enum KeyFrameTipoReproduccion: unsigned int {
    nulo=0,brincarAlInicio=1,regresivo=2,regresarAlInicio=3
};
struct _keyframemovemovimiento{
    unsigned int cual =0;
    double posicionFinal = 0;
    double incremento = 0;
    double posicionInicial = 0;
}typedef KeyFrameMoveMovimiento;
struct _keyframemovimiento{
    double value;
    char name[30] = "NULO";
}typedef KeyFrameMovimiento;
struct _keyframekeyframe{
    std::vector<KeyFrameMoveMovimiento> movimientos ;
    unsigned int duracion = 0;
}typedef KeyFrameKeyFrame;
struct _keyframeanimacion{
    std::vector<KeyFrameKeyFrame> cuadrosClaves;
    KeyFrameTipoReproduccion tipoReproduccion = nulo;
    bool repetitivo = false;
    bool ascendente = true;
    long cuadroActual = 0;
    unsigned int pasoActual = 0;
}typedef  keyFrameAnimacion;

class KeyFrame{
public:

	void teclaActivaMenu();
    void teclaDeMenu(unsigned char tecla);
    void inicializar();
    void guardar();
    void cargar();
    void actualizaAnimacion();
    bool menuActivado = false;
    bool animacionInfinitasActivas = true;
    void pararTodasLasAnimacionesEnCurso();
    bool reproduceAlgunaAnimacion(unsigned long cual);
    std::vector<KeyFrameMovimiento> varMovimientos;
    
private:
    
    enum KeyFrameTipoAccionDespuesBuscarUInt{nada,cambioPunteroMovimientoSetPosicionInicial,necesitoCrearUltimoKeyFrame,cambioPunteroMovimientoSetTemporal};
    enum KeyFrameEstados{inicial,pmovimiento,animacion,animacionNueva,buscandoUIntKF};
    
    void teclaDeMenuInicialReset();
    void teclaDeMenuInicial(unsigned char tecla);
    void teclaDeMenuPruebaMovimiento(unsigned char tecla);
    void teclaDeMenuAnimacion(unsigned char tecla);
    void teclaDeMenuAnimacionNueva(unsigned char tecla);
    void teclaDeMenuBuscandoUInt(unsigned char tecla);
    const char * nameEstado(KeyFrameEstados estado);

    void escribeMenu(KeyFrameEstados tipo = inicial);
    void escribeCabecera(KeyFrameEstados tipo = pmovimiento);
    void drawCursor();
    void escribeMovimientos();
    void escribeTiposRepeticion();
    void escribeTipoRepeticionSegun(KeyFrameTipoReproduccion rep);
    void escribeAnimacionesDisponibles();
    void describeAnimacion(keyFrameAnimacion animacion);
    
    double moverMovimiento(int mov);
    void empezarABuscarUInt(unsigned int *a,unsigned int max,KeyFrameEstados actual,KeyFrameTipoAccionDespuesBuscarUInt accion = nada);
    
    void pararAnimacionesFromVector(std::vector<unsigned long> vector);
    void aCeroTodosMovimientosDisponibles();
    
    bool reproduceAnimacion(keyFrameAnimacion *animacion);
    void pararAnimacion(keyFrameAnimacion *animacion);
    void recargarAnimacionesForever();
    void crearKeyFrameForCircular(keyFrameAnimacion * animacion,unsigned int duracion);
    void interpolarMoveMovimiento(KeyFrameMoveMovimiento *moveMovimiento);
    
    KeyFrameEstados estado = inicial;
    std::vector<keyFrameAnimacion> vAnimaciones;
    std::vector<unsigned long> vAnimacionesForever;
    std::vector<unsigned long> vAnimacionesActivas;
    
    int reproduccionExterna = -1;
    KeyFrameTipoAccionDespuesBuscarUInt tipoAccionDespuesBuscarInt = nada;
    
    keyFrameAnimacion temporalAnimacion = keyFrameAnimacion();
    KeyFrameKeyFrame temporalCuadroClave = KeyFrameKeyFrame();
    KeyFrameMoveMovimiento temporalMoveMovimiento = KeyFrameMoveMovimiento();
    
    unsigned int movimientoActualPuntero = 0;
    unsigned int animacionActualPuntero = 0;
    
    double temporalPosicionAnteriorPruebaMovimiento = 0;
    
    unsigned int *dondeGuardar = NULL;
    unsigned int maxDondeGuardar = 0;
    KeyFrameEstados estadoARegresar = inicial;
    unsigned int temporalIntFromKeyBoard = 0;
};
#endif
