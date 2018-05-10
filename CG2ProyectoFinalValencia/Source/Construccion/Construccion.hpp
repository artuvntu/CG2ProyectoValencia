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
    paredNormal,paredVentana,paredPuerta
};
enum ConstruccionTipoVentana: unsigned int {
    ventanaNormal
};
enum ConstruccionTipoPuerta: unsigned int {
    puertaNormal
};
struct _construccionpared {
    double posicion[3] = {0, 0, 0};
    double tam[3] = {0, 0, 0};
    double angulo = 0;
    std::vector<PrimitivasSelectTexture> texturaMain;
    ConstruccionTipoPared tipoPared = paredNormal;
    ConstruccionTipoVentana tipoVentana = ventanaNormal;
    ConstruccionTipoPuerta tipoPuerta = puertaNormal;
}typedef ConstruccionPared;
struct _construccionsuelo {
    double posicion[3] = {0, 0, 0};
    std::vector<double> vertices;
    int repeticionText = 1;
    double grosor = 0;
    unsigned int typeText = 0;
}typedef ConstruccionSuelo;
struct _construccionescaleras {
    double posicion[3] = {0, 0, 0};
    double angulo = 0;
    double tam[3] = {0, 0, 0};
    int repeticionText = 1;
    unsigned int typeText = 0;
    
}typedef ConstruccionEscaleras;

class Construccion{
public:
    void teclaActivaMenu();
    void teclaDeMenu(unsigned char tecla);
    void inicializar(Primitivas *primitivas,CargadorImage *cargadorImage,KeyFrame *keyFrame);
    bool menuActivado = false;

private:
    enum ConstruccionEstados{inicial,agregarCosas,buscaUInt};
    ConstruccionEstados estado = inicial;
    
    void escribeMenu(ConstruccionEstados estado = inicial);
    void drawCursor(ConstruccionEstados estado = inicial);
    
    void teclaDeMenuInicial(unsigned char tecla);
    void teclaDeMenuAgregarCosa(unsigned char tecla);
    void teclaDeMenuBuscaUInt(unsigned char tecla);
    
    Primitivas *vPrimitivas;
    CargadorImage *vCargadorImage;
    KeyFrame *vKeyFrame;
};

#endif
