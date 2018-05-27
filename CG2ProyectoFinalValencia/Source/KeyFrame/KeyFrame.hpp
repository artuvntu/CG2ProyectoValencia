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
#include "../UIClassAux/UIClassAux.hpp"

#define KEYFRAMEPATHFILE "CG2ProyectoFinalValencia/Documents/CG2ProyectoFinalValencia.vkf" //vKeyFrame

class KeyFrame{
public:
    struct _keyframemovemovimiento{
        unsigned int cual =0;
        double posicionFinal = 0;
        double incremento = 0;
        double posicionInicial = 0;
    }typedef KeyFrameMoveMovimiento;
    struct _keyframemovimiento{
        double value = 0;
        char name[50] = "NULO";
    }typedef KeyFrameMovimiento;
    struct _keyframekeyframe{
        std::vector<KeyFrameMoveMovimiento> movimientos ;
        unsigned int duracion = 10;
    }typedef KeyFrameKeyFrame;
    struct _keyframeanimacion{
        std::vector<KeyFrameKeyFrame> cuadrosClaves;
        bool regresivo = false;
        bool repetitivo = false;
        bool ascendente = true;
        long cuadroActual = 0;
        unsigned int pasoActual = 0;
        char id[MAXCHAR]="NULO";
    }typedef  keyFrameAnimacion;

    
	void teclaActivaMenu();
    void teclaDeMenu(unsigned char tecla);
    void inicializar();
    void guardar();
    void actualizaAnimacion();
    unsigned int crearVarMovimiento(char nombre[MAXCHAR]);
    bool menuActivado = false;
    bool animacionInfinitasActivas = true;
//    void pararTodasLasAnimacionesEnCurso();
    bool reproduceAlgunaAnimacion(unsigned int cual);
    std::vector<KeyFrameMovimiento> varMovimientos;
    
    void pararTodaAnimacionDisponible();

    
private:
    char KeyFrameEstadosToChar[4][30]{
        "Inicial", "Prueba Movimiento","Editando KF", "BuscandoUInt"
    };
    enum KeyFrameTipoAccionDespuesBuscarUInt:unsigned char{
        nadaKF=0,pruebaMovimientoEmpezarMove=1,cambioCuadroClave=2,eliminacionCuadro=3,cambioMvMVKf=4
    };
    enum KeyFrameEstados:unsigned char{
        inicialKF=0,pmovimiento=1,editandoCuadroClave=2,buscandoUIntKF=3
    };
    
//    void teclaDeMenuInicialReset();
    void teclaDeMenuInicial(unsigned char tecla);
    void teclaDeMenuEditarKF(unsigned char tecla);
    void teclaDeMenuPruebaMovimiento(unsigned char tecla);
//    void teclaDeMenuAnimacion(unsigned char tecla);
//    void teclaDeMenuAnimacionNueva(unsigned char tecla);
//    void teclaDeMenuBuscandoUInt(unsigned char tecla);
//    const char * nameEstado(KeyFrameEstados estado);

    void escribeMenu();
//    void escribeCabecera(KeyFrameEstados tipo = pmovimiento);
    void drawCursor();
    
    void escribeCuadrosClaveDisponiles(keyFrameAnimacion *animacion);
    void escribeMoveMovimientoDisponibles(KeyFrameKeyFrame *kf);
    void escribeMovimientosDisponibles();
    void escribeAnimacionesDisponibles();
//    void escribeTiposRepeticion();
//    void escribeTipoRepeticionSegun(KeyFrameTipoReproduccion rep);
    
    void describeAnimacion(keyFrameAnimacion *animacion);
    void describeKeyFrame(KeyFrameKeyFrame *kf);
    void describeMoveMovimiento(KeyFrameMoveMovimiento *mvmv);
    
    void asegurarIntegridadCuadroClave(KeyFrameKeyFrame *kf);
    void asegurarIntegridadAnimacion(keyFrameAnimacion *animacion);
//    double moverMovimiento(int mov);
    
//    void empezarABuscarUInt(unsigned int *a,unsigned int max,KeyFrameEstados actual,KeyFrameTipoAccionDespuesBuscarUInt accion = nadaKF);
    
//    void pararAnimacionesFromVector(std::vector<unsigned int> *vector);
    void aCeroTodosMovimientosDisponibles();
    
    
    KeyFrameKeyFrame *tkf;
    KeyFrameMoveMovimiento *tmvmv;
    
    bool reproduceAnimacion(keyFrameAnimacion *animacion);
    void pararAnimacion(keyFrameAnimacion *animacion);
    void recargarAnimacionesForever();
//    void crearKeyFrameForCircular(keyFrameAnimacion * animacion,unsigned int duracion);
    void interpolarMoveMovimiento(KeyFrameMoveMovimiento *moveMovimiento,unsigned int duracion);
    
    KeyFrameEstados estado = inicialKF;
    std::vector<keyFrameAnimacion> vAnimaciones;
    std::vector<unsigned int> vAnimacionesForever;
    std::vector<unsigned int> vAnimacionesActivas;
    
//    int reproduccionExterna = -1;
    
//    keyFrameAnimacion temporalAnimacion = keyFrameAnimacion();
//    KeyFrameKeyFrame temporalCuadroClave = KeyFrameKeyFrame();
//    KeyFrameMoveMovimiento temporalMoveMovimiento = KeyFrameMoveMovimiento();
    unsigned int keyframeActualPuntero = 0;
    unsigned int movimientoActualPuntero = 0;
    unsigned int animacionActualPuntero = 0;
    unsigned int moveMovimientoActualPuntero = 0;
    
    double temporalPosicionAnteriorPruebaMovimiento = 0;
    
//    unsigned int *dondeGuardar = NULL;
//    unsigned int maxDondeGuardar = 0;
//    KeyFrameEstados estadoARegresar = inicialKF;
//    unsigned int temporalIntFromKeyBoard = 0;
    KeyFrameTipoAccionDespuesBuscarUInt tipoAccionDespuesBuscarInt = nadaKF;

    void ejecutaAccionBuscarUInt();
    
    void modificarCual(KeyFrameKeyFrame *kf,unsigned int *donde,unsigned int cualMove);
    void cargar();
    bool echateABuscarPorNombre(char *nombre,unsigned int *donde);
    
    void recrearAnimacionHastaFinal(keyFrameAnimacion *animacion, unsigned int hastaDonde);
    void creaKeyFrameAlInicio(keyFrameAnimacion *animacion);
    UIClassAux vUIClassAux;
};
#endif
