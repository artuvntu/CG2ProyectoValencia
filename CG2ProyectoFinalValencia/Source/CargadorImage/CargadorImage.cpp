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
    
    return defaultTypeTexture = (unsigned int)this->types.size() - 1;
}
bool CargadorImage::newTexture(char* path){
    unsigned char plantillaTGA[12] = {0,0,2,0,0,0,0,0,0,0,0,0};
    unsigned char lecturaTGA[12];
    unsigned char metaDatos[6];
    unsigned char depthImage;
    unsigned char * dataImage;
    unsigned char tempParsheBGR;
    unsigned int tamImage;
    unsigned int tipoContextoImagen;
    GLuint tempIndex = 0;

    FILE *archivo = fopen(path, "rb");
    
    if (archivo == NULL) {
        std::cout << "Archivo " << path << " no encontrado" << std::endl;
        return false;
    }

    if (fread(lecturaTGA, 1, sizeof(lecturaTGA), archivo)!=sizeof(lecturaTGA)||memcmp(lecturaTGA, plantillaTGA, sizeof(lecturaTGA))!=0||fread(metaDatos, 1, sizeof(metaDatos), archivo)!=sizeof(metaDatos)){
        std::cout << "Archivo "<< path <<" no coincide con TGA\n";
        fclose(archivo);
        return false;
    }
    this->ancho = metaDatos[0] + (metaDatos[1]<<8);
    this->alto = metaDatos[2] + (metaDatos[3]<<8);
    if (this->alto < 1 || this->ancho < 1 || (metaDatos[4] != 24 && metaDatos[4] != 32)) {
        std::cout << "Archivo "<< path << " error Profundidad de imagen\n";
        fclose(archivo);
        return false;
    }
    depthImage = metaDatos[4]/8;
    tamImage = alto * ancho * depthImage;
    dataImage = new unsigned char [tamImage];
    if (dataImage == NULL) {
        std::cout << "Archivo "<< path << " memoria Insuficiente " << ancho <<"X" << alto << std::endl;
        fclose(archivo);
        return false;
    }
    if (fread(dataImage, 1, tamImage, archivo)!=tamImage){
        std::cout << "Archivo "<< path << " lectura incompleta\n";
        fclose(archivo);
        delete [] dataImage;
        return false;
    }
    fclose(archivo);
    for (unsigned int i = 0; i<tamImage; i+=depthImage) {
        tempParsheBGR = dataImage[i];
        dataImage[i] = dataImage[i+2];
        dataImage[i+2] = tempParsheBGR;
    }
    if (depthImage == 3) tipoContextoImagen = GL_RGB;
    else tipoContextoImagen = GL_RGBA;
    glGenTextures(1, &tempIndex);
    glBindTexture(GL_TEXTURE_2D, tempIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, tipoContextoImagen, this->ancho,
                 this->alto, 0, tipoContextoImagen, GL_UNSIGNED_BYTE,
                 dataImage);
    this->glindexs.push_back(tempIndex);
    delete [] dataImage;
    return true;
}
bool CargadorImage::setDefaultTypeTexture(unsigned int type){
    if (type < this->types.size()){
        this->defaultTypeTexture = type;
        return true;
    }
    return false;
}
int CargadorImage::get(int element,int type){
    int tType;
    try {
        if (type == -1) {
            type = this->defaultTypeTexture;
        }
        tType=this->types.at(type);
        return this->glindexs.at(tType+element);
    } catch (const std::out_of_range& error) {
        return -1;
    }
}
bool CargadorImage::easyGetText(int element,int type){
    int t = this->get(element,type);
    if (t == -1) {
        return false;
    }
    glBindTexture(GL_TEXTURE_2D, (GLuint) t);
    return true;
}
