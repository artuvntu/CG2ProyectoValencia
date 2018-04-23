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
    bool newTexture(std::string path);
    bool setDefaultTypeTexture(unsigned int type);
    unsigned int getGLIndexForElement(int element,int type = -1);
private:
    std::vector<unsigned int> glindexs;
    std::vector<int> types;
    int defaultTypeTexture = -1;
};
