//
//  CargadorImage.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/20/18.
//  Copyright © 2018 vApps. All rights reserved.
//
#include "../../Libraries.hpp"

class CargadorImage{
public:
    unsigned int newTypeTexture();
    bool newTexture(char * path);
    bool setDefaultTypeTexture(unsigned int type);
    int getGLIndexForElement(int element,int type = -1);
    bool easyGetText(int element,int type = -1);
    int ancho = -1;
    int alto = -1;
private:
    std::vector<unsigned int> glindexs;
    std::vector<int> types;
    int defaultTypeTexture = -1;
};
struct _typeTexture {
    unsigned int skybox;
    unsigned int fachadaCasaExterna;
}typedef TypeTexture;
