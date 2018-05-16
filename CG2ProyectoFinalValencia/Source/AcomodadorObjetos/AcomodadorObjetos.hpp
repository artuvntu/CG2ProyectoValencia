//
//  AcomodadorObjetos.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 5/15/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#ifndef AcomodadorObjetos_hpp
#define AcomodadorObjetos_hpp

#include "../../Libraries.hpp"
#include "../CreadorObjetos/CreadorObjetos.hpp"

#define ACOMODADOROBJETOSPATHFILE "CG2ProyectoFinalValencia/Documents/CG2ProyectoFinalValencia.vao"

//Directiva {Posicion, Angulo, Tam}

class AcomodadorObjetos{
public:
    void inicializar(CreadorObjetos *co);
    void dibuja();
    void teclaActivaMenu();
    void teclaDeMenu(unsigned char tecla);
    void guardar();
    bool menuActivado = false;
    
private:
    
    struct _acomodadorobjetosacomodo{
        Cg2ValenciaPunto3D ubicacion[3];
        unsigned int cual;
    }typedef AcomodadorObjetosAcomodo;
    char AcomodadorObjetosAccionesBuscaUIntToChar[1][30] = {"Nada"};
    enum AcomodadorObjetosAccionesBuscaUInt:unsigned char {
        nada=0
    };
    char AcomodadorObjetosEstadosToChar[2][30] = {"Inicial","BuscaUInt"};
    enum AcomodadorObjetosEstados:unsigned char{
        inicialAO=0,BuscaUInt=1
    };
    
    unsigned char teclasMovimientoModificarObjeto[40] = "daeqswljoukihfyrgtDAEQSWLJOUKIHFYRGT";
    bool moviminetoModificarObjeto(unsigned char tecla,AcomodadorObjetosAcomodo *acomodo);
    
    std::vector<AcomodadorObjetosAcomodo> yAcomodos;
    AcomodadorObjetosEstados estado = inicialAO;
    
    void teclaDeMenuInicial(unsigned char tecla);
    void teclaDeMenuBuscaUInt(unsigned char tecla);
    
    void escribeMenu();
    void drawCursor();
    
    
    void empezarABuscarUInt(unsigned int *dondeGuardad,unsigned int max,AcomodadorObjetosEstados estadoRegresar,AcomodadorObjetosAccionesBuscaUInt accion = nada);
    void ejecutaAccionDespuesBuscarUInt();
    
    unsigned int *dondeGuardar;
    unsigned int temporalIntFromKeyBoard = 0;
    unsigned int maxDondeGuardar = 0;
    AcomodadorObjetosEstados estadoARegresarBUInt = inicialAO;
    AcomodadorObjetosEstados estadoAnterior = inicialAO;
    AcomodadorObjetosAccionesBuscaUInt accionDespuesBuscarUInt = nada;
    
    CreadorObjetos *vCreadorObjetos;
    
    unsigned int puntero = 0;
    
    void escribeAcomodosDisponibles();
    
    void describeAcomodo(AcomodadorObjetosAcomodo *acomodo);
    
    bool pintaPunteroSeleccion;
    
    void cargar();
    
};

#endif /* AcomodadorObjetos_hpp */
