//
//  KeyFrame.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/02/18.
//  Copyright © 2018 vApps. All rights reserved.
//
#include "../../Libraries.hpp"

#define KEYFRAMEPATHFILE "CG2ProyectoFinalValencia.vkf" //vKeyFrame
enum KeyFrameEstados{inicial,pmovimiento,animacion,pmovimientoCambio,animacionCambio,animacionNueva};
enum KeyFrameTipoRepeticion: unsigned char {
    nulo=0,volverAlInicio=1,circular=2,regresivo=3,regresivoCircular=4
};
struct _keyframemovemovimiento{
    unsigned int cual;
    double cantidad = 0;
}typedef KeyFrameMoveMovimiento;
struct _keyframemovimiento{
    double value;
    std::string name;
}typedef KeyFrameMovimiento;
struct _keyframekeyframe{
    std::vector<KeyFrameMoveMovimiento> movimientos ;
    double duracion = 0;
}typedef KeyFrameKeyFrame;
struct _keyframeanimacion{
    std::vector<KeyFrameKeyFrame> cuadrosClaves;
    KeyFrameTipoRepeticion repeticion = nulo;
    bool ascendente = true;
    unsigned int cuadroActual=0;
}typedef  keyFrameAnimacion;

class KeyFrame{
public:
	void teclaActivaMenu();
    void teclaDeMenu(unsigned char tecla);
    void inicializar(unsigned int cantidad,std::string nombre = "Inicializado ");
    void guardar();
    void cargar();
    void actualizaAnimacion();
    bool menuActivado = false;
    void resetAnimacionesEnCurso();
//private:
    void teclaDeMenuInicial(unsigned char tecla);
    void teclaDeMenuPruebaMovimiento(unsigned char tecla);
    void teclaDeMenuPruebaMovimientoCambio(unsigned char tecla,KeyFrameEstados proximoestado = pmovimiento);
    void teclaDeMenuAnimacion(unsigned char tecla);
    void teclaDeMenuAnimacionCambio(unsigned char tecla);
    void teclaDeMenuanimacionNueva(unsigned char tecla);
    
    void escribeMenu(int tipo = 0);
    void escribeCabecera(int tipo = 0);
    void drawCursor();
    void escribeMovimientos();
    void escribeTiposRepeticion();
    void escribeTipoRepeticionSegun(KeyFrameTipoRepeticion rep);
    void describeAnimacion(keyFrameAnimacion animacion);
    void moverMovimiento(int mov);
    void reproduceAnimacion(keyFrameAnimacion animacion);
    KeyFrameEstados estado = inicial;
    std::vector<KeyFrameMovimiento> varMovimientos;
    std::vector<keyFrameAnimacion> vAnimaciones;
    std::vector<unsigned long> vAnimacionesForever;
    
    int reproduccionExterna = -1;
    
    keyFrameAnimacion temporalAnimacion;
    KeyFrameKeyFrame temporalCuadroClave;
    KeyFrameMoveMovimiento temporalMoveMovimiento;
    
    unsigned int pruebamovimientoActualPuntero = 0;
    unsigned int animcacionActualPuntero = 0;
    unsigned int temporalIntFromKeyBoard = 0;
};
