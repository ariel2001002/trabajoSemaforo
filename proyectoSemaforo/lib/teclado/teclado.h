#ifndef _TECLADO_H
#define _TECLADO_H

#include "Arduino.h"

int16_t bot1 = 5;
int16_t bot2 = 6;
int16_t bots[] = {bot1, bot2};

enum estado{noPresionado, presionado, bajando, subiendo};

void botonesMEF(int16_t nombreBoton);

#endif