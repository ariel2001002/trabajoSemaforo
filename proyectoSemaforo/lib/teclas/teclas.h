#ifndef _TECLAS_H
#define _TECLAS_H

#include "Arduino.h"
#include "tipoDeVariables.h"



//SE DECLARAN LAS FUNCIONES DE LA LIBRERIA

void inicializacionMEFEstadoBotones();

void actualizacionMEFEstadoBotones();

int16_t temporizador1();

int16_t temporizador2();

void actualizacionMEFFuncionesBots(funcionBots* ptr);


#endif
