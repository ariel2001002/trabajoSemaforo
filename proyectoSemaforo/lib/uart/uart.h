#ifndef _UART_H
#define _UART_H

//#include "funciones.h"
#include "teclas.h"
#include "semaforo.h"

void comunicacionCambioModoSem(modos modoActual);

void comunicacionCambioEstadoBots(estados estadoActual, int16_t boton);

#endif