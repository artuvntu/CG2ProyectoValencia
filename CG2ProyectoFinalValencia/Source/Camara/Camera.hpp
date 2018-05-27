//
//  Camera.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/16/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#ifndef camara_hpp
#define camara_hpp

#include "../../Libraries.hpp"
#include "../UIClassAux/UIClassAux.hpp"

#define CAMARAPATHFILE "CG2ProyectoFinalValencia/Documents/CG2ProyectoFinalValencia.vcam" //vCamara

class Camara{
public:
    char teclasMovimiento[25] = "wsadqejlikuoWSADQEJLIKUO";
    struct _camarapos {
        double XYZ[9] = {0, 15, 0, 0, 15, -1, 0, 1, 0};
        double Angles[3] = {3.14,0,1.57};
        char id[MAXCHAR] = "NULO";
    }typedef CamaraPos;
    void easyPosition();
    void keyboardMove(int type,double intesidad = 1);
    void inicializar();
    void teclaActivaMenu();
    void teclaDeMenu(unsigned char tecla);
    void guardar();
    
    void cambiaPosCual(unsigned int c);
    void copiaSoloNumeros(CamaraPos *destino, CamaraPos *fuente);
    
    bool teclaMove(unsigned char tecla);
    
    void describeCamaraPos(CamaraPos *pos);
    
    bool menuActivado = false;
    CamaraPos posActual = CamaraPos();
    std::vector<CamaraPos> yCamaras;
    
private:

    enum CamaraEstados{
        inicial,buscandoUInt
    };
    CamaraEstados estado = inicial;
    void teclaDeMenuInicial(unsigned char tecla);
    void cargar();
    unsigned char accionBUInt = 0 ;
    void ejecutarAccionBUint();
    
    unsigned int puntero = 0;
    
    void escribeMenu();
    void drawCursor();
    
    void describeCamarasDisponibles();
    
    UIClassAux vUIClassAux;
    
//    w,s,a,d,q,e,h,l,j,k,u,i MINMAY
    double multipler[12] = {1, 1, 1, 0.2, 0.2, 0.2, 3.5, 3.5, 3.5, 0.5, 0.5, 0.5};
    unsigned int cualInicial=0;
};
#endif
