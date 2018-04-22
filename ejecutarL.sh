#!/bin/bash

R=$(g++ CG2ProyectoFinalValencia/*.cpp CG2ProyectoFinalValencia/Source/*/*.cpp -lGL -lGLU -lglut 2>&1)
echo $R
if [ -z "$R" ]
then
	echo "Completado"
	./a.out
else
	echo $R
fi

