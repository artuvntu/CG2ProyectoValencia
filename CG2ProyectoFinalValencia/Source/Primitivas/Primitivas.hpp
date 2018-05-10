//
//  Primitivas.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/26/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#ifndef primitivas_hpp
#define primitivas_hpp

#include "../../Libraries.hpp"

#include "../KeyFrame/KeyFrame.hpp"
#include "../CargadorImage/CargadorImage.hpp"

//#define GROSORPARED 1
//#define ALTOPARED 25
//#define PRIMITIVASTEXTPARED 0
//#define PRIMITIVASTEXTPAREDTAM 1
//#define PRIMITIVASTEXTPAREDINICIOX 2
//#define PRIMITIVASTEXTPAREDINICIOY 3
struct _primitivasselecttexture{
    unsigned long cualTextura = 0;
    double posicionInicio [2] = {0, 0};
}typedef PrimitivasSelectTexture;
class Primitivas {
public:
    
    void inicializar(CargadorImage * cargadorImagenes);
    void mundo(PrimitivasSelectTexture *cielo,PrimitivasSelectTexture *boveda,PrimitivasSelectTexture *suelo);
    void prismaEstandar(std::vector<PrimitivasSelectTexture>*vectorSelecTexture,double posicion[3],double tam[3]);
    
private:

    CargadorImage *vCargadorImage;
    void obtenerPosicionFinal(double *posicionFinal, PrimitivasSelectTexture * selectTexture,double x,double y);
};

#endif
