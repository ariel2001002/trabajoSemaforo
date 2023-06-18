#ifndef _TECLADO_H
#define _TECLADO_H

#include "Arduino.h"

//int16_t bot1 = 5;
//int16_t bot2 = 6;
//int16_t bots[] = {bot1, bot2};

enum estados{noPresionado, presionado, bajando, subiendo};

estados estadoActual;

//SE DECLARAN FUNCIONES

void inicializacionMEF();

int16_t temporizador1();

void botonesMEF();

void comprobacion ();

#endif
