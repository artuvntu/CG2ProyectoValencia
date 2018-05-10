//
//  CargadorImage.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/20/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#ifndef cargadorimage_hpp
#define cargadorimage_hpp

#include "../../Libraries.hpp"

#define CARGADORIMAGEPATHFILE "CG2ProyectoFinalValencia.vci"

struct _cargadorimagetexture{
    unsigned int glIndex;
    double cantidadRep[2] = {0, 0};
    char nombreTexture [30] = "NULO";
}typedef CargadorImageTexture;

class CargadorImage{
public:
    void reCargarArchivo();
    bool inicializar();
    std::vector<CargadorImageTexture> texturas;
private:
    bool newTexture(char * path,CargadorImageTexture *texture);
    int ancho = -1;
    int alto = -1;
    char path [75] = "CG2ProyectoFinalValencia/Textureimg/";//    36
};

#endif
