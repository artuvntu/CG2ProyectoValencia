//
//  Libraries.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/20/18.
//  Copyright © 2018 vApps. All rights reserved.
//

#ifndef libraries_hpp
#define libraries_hpp

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
//#include <stdarg.h>
#include <stdio.h>
//#include <string.h>
#include <list>

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#elif _WIN32
#include "LibW\glut.h"
#elif __linux__
#include <GL/gl.h>
#include <GL/glut.h>
#else
#error "Unknown compiler"
#endif

#endif
