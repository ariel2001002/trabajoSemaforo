#ifndef _UART_H
#define _UART_H

#include "semaforo.h"
#include "funciones.h"

void comunicacionCambioModoSem(modos modoActual);

void comunicacionCambioEstadoBots(estados estadoActual, int16_t boton);

#endif