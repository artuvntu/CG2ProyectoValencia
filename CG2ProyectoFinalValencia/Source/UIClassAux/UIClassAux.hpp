//
//  UIClassAux.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/18/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#ifndef UIClassAux_hpp
#define UIClassAux_hpp

#include "../../Libraries.hpp"

class UIClassAux {
public:
    void empezarABuscarUInt(unsigned int *dondeGuardar, unsigned int max, unsigned char *escribirEstado, unsigned char cambioCorrecto, unsigned char cambioCancelar, unsigned char parametroEjecucionCorrecto, unsigned char parametroEjecucionCancelar, unsigned char *dondeAccionEjecucion);
    void empezarABuscarString(char *dondeGuardar,unsigned int max, unsigned char *escribirEstado, unsigned char cambioCorrecto, unsigned char cambioCancelar, unsigned char parametroEjecucionCorrecto, unsigned char parametroEjecucionCancelar, unsigned char *dondeAccionEjecucion);
    void empezarABuscarMove(double *ejex, double *ejey, double *ejez, double *ejeDx, double *ejeDy, double *ejeDz, double *ejeAx, double *ejeAy, double *ejeAz,double minMove, double maxMove, double minMoveA, double maxMoveA);
    bool teclaMove(unsigned char tecla);
    bool teclaDeMenu(unsigned char tecla);
    void escribeMenu();
    void drawCursor();
private:
    char estadorToChar[4][30]{
        "NADA","UInt", "String","MoveMovimeinto"
    };
    enum posiblesEstados:unsigned char{
        sinBusqueda=0,buscandoUInt=1,buscandoString=2,moveMovimiento=3
    };
    posiblesEstados estadoActual = sinBusqueda;
    bool teclaDeMenuBuscandoUInt(unsigned char tecla);
    bool teclaDeMenuBuscandoString(unsigned char tecla);
    
    unsigned int temporalUIntKeyBoard = 0;
    char temporalStringKeyBoard[MAXCHAR] = "";
    unsigned int puntero = 0;
    unsigned int *dondeGuardarUInt = NULL;
    char *dondeGuardarChar = NULL;
    unsigned int maximo = 0;
    unsigned char *dondeEscribirEstado = NULL;
    unsigned char cambioCorrecto = 0;
    unsigned char cambioCancelar = 0;
    unsigned char parametroEjecucionCorrecto = 0;
    unsigned char parametroEjecucionCancelar = 0;
    unsigned char *dondeGuardarParametroEjecucion = NULL;
    
    unsigned char teclasMoveMoviemito[40] = "daeqswljoukihfyrgtDAEQSWLJOUKIHFYRGT";
    double *dondeMove[9];
    double basura = 0;
    double deltaMove[4] = {0, 0, 0, 0};
    
    
};

#endif /* UIClassAux_hpp */
