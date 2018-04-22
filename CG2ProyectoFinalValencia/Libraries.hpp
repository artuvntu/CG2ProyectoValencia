//
//  Libraries.hpp
//  CG2ProyectoFinalValencia
//
//  Created by Arturo Ventura on 4/20/18.
//  Copyright © 2018 vApps. All rights reserved.
//

//#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#elif _WIN32
#include "LibW\glut.h"
#elif __linux__
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#else
#error "Unknown compiler"
#endif
