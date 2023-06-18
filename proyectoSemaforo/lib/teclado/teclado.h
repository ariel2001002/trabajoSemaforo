#ifndef _TECLADO_H
#define _TECLADO_H

#include "Arduino.h"

int16_t bot1 = 5;
int16_t bot2 = 6;
int16_t bots[] = {bot1, bot2};

//SE DECLARAN LAS VARIABLES

enum estados{noPresionado, presionado, bajando, subiendo};

estados estado  = noPresionado;

//SE DECLARAN FUNCIONES

void botonesMEF(int16_t nombreBoton);

int16_t temporizador1();

void comprobacion(estados estado);

#endif
