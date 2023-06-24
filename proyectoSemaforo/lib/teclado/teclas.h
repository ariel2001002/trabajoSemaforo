#ifndef _TECLAS_H
#define _TECLAS_H

#include "Arduino.h"
#include "funciones.h"
#include "uart.h"

enum estados{noPresionado, presionado, bajando, subiendo};


//SE DECLARAN LAS FUNCIONES DE LA LIBRERIA

void inicializacionMEF();

void actualizacionMEF();

void comprobacion ();

int16_t temporizador1();

int16_t temporizador2();

void actualizacionMEFFuncionesBots(funcionBots* ptr);


#endif
