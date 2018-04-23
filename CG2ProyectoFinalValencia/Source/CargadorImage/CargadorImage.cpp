//
//  CargadorImage.cpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/20/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#include "CargadorImage.hpp"

unsigned int CargadorImage::newTypeTexture(){
    int where = (int)this->glindexs.size();
    this->types.push_back(where);
    return (unsigned int)this->types.size() - 1;
}
bool CargadorImage::newTexture(std::string path){
    
    
}
bool CargadorImage::setDefaultTypeTexture(unsigned int type){
    if (type < this->types.size()){
        this->defaultTypeTexture = type;
        return true;
    }
    return false;
}
