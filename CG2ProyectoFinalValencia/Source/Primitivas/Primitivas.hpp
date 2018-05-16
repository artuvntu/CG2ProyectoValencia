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

#define PRIMITIVARVTPRISMAESTANDAR 6
#define PRIMITIVARVTSUELOPOLIGONAL 2
#define PRIMITIVARVTCILINDRO 3
#define PRIMITIVAVRTESFERA 1
#define PRIMITIVAVRTPLANO 1

//#define GROSORPARED 1
//#define ALTOPARED 25
//#define PRIMITIVASTEXTPARED 0
//#define PRIMITIVASTEXTPAREDTAM 1
//#define PRIMITIVASTEXTPAREDINICIOX 2
//#define PRIMITIVASTEXTPAREDINICIOY 3
struct _primitivasselecttexture{
    unsigned int cualTextura = 0;
    double posicionInicio [2] = {0, 0};
}typedef PrimitivasSelectTexture;
class Primitivas {
public:
    
    void inicializar(CargadorImage * cargadorImagenes);
    void describeSelecTextureVector(std::vector<PrimitivasSelectTexture> *vector);
    void mundo(PrimitivasSelectTexture *cielo,PrimitivasSelectTexture *boveda,PrimitivasSelectTexture *suelo);
    
    void cilindroEstandar(std::vector<PrimitivasSelectTexture>*vector,unsigned int desdeDonde,double diametro,double altura,unsigned int porcion);
    void esferaEstandar(std::vector<PrimitivasSelectTexture>*vector,unsigned int desdeDonde,double diametro,unsigned int porcion);
    void planoEstandar(std::vector<PrimitivasSelectTexture>*vector,unsigned int desdeDonde,double posicion[3],double tam[3]);
    void prismaEstandar(std::vector<PrimitivasSelectTexture>*vectorSelecTexture,unsigned int desdeDonde,double posicion[3],double tam[3],double angulo);
    void escaleras(std::vector<PrimitivasSelectTexture>*vectorSelectTexture,unsigned int desdeDonde,double posicion[3],double tam[3],unsigned int canEscalones,double angulo);
    void sueloPoligonal(std::vector<PrimitivasSelectTexture>*vectorSelecTexture,unsigned int desdeDonde,std::vector<Cg2ValenciaPunto3D>*vectorVertices);
    void cruceta(bool swithColor = false);
    void describePunto(Cg2ValenciaPunto3D punto);
private:

    CargadorImage *vCargadorImage;
    void obtenerPosicionFinalEInicial(double *posicionFinal,double *posicionInicial, PrimitivasSelectTexture * selectTexture,double x,double y);

};

#endif
