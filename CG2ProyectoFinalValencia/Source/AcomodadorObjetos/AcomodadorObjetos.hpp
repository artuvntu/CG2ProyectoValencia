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
#include "../UIClassAux/UIClassAux.hpp"
#include "../Camara/Camera.hpp"

#define ACOMODADOROBJETOSPATHFILE "CG2ProyectoFinalValencia/Documents/CG2ProyectoFinalValencia.vao"

//Directiva {Posicion, Angulo, Tam}

class AcomodadorObjetos{
public:
    void inicializar(CreadorObjetos *co,UIClassAux *uic,Camara *cam);
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
    enum AcomodadorObjetosAccionesBuscaUInt:unsigned char {
        nada=0, cambioPuntero=1
    };
    char AcomodadorObjetosEstadosToChar[2][30] = {"Inicial","BuscaUInt"};
    enum AcomodadorObjetosEstados:unsigned char{
        inicialAO=0,BuscaUInt=1
    };
    
    void ejecutaAccionDespuesBuscarUInt(unsigned char accion);

    unsigned char teclasMovimientoModificarObjeto[40] = "daeqswljoukihfyrgtDAEQSWLJOUKIHFYRGT";
    bool moviminetoModificarObjeto(unsigned char tecla,AcomodadorObjetosAcomodo *acomodo);
    
    std::vector<AcomodadorObjetosAcomodo> yAcomodos;
    AcomodadorObjetosEstados estado = inicialAO;
    
    void teclaDeMenuInicial(unsigned char tecla);
    
    void escribeMenu();
    void drawCursor();
    
    unsigned char accionDespuesBuscarUInt = nada;
    
    CreadorObjetos *vCreadorObjetos;
    UIClassAux *vUIClassAux;
    Camara *vCamara;
    
    unsigned int puntero = 0;
    
    void escribeAcomodosDisponibles();
    
    void describeAcomodo(AcomodadorObjetosAcomodo *acomodo);
    
    bool pintaPunteroSeleccion;
    
    void cargar();
    
};

#endif /* AcomodadorObjetos_hpp */
