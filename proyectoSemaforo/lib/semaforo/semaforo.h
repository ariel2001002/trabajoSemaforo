#ifndef _SEMAFORO_H
#define _SEMAFORO_H

#include <Arduino.h>
#include "funciones.h"

//SE DEFINEN LOS TIPOS DE VARIABLES

typedef struct {
    int16_t* pleds;
    int16_t len;
} controlleds;

enum colores {rojo, amarillo, verde};

//SE DECLARAN LAS FUNCIONES
void inicializacionMEFSemaforo();

void actualizacionMEFSemaforos(funcionBots* ptr);

void actualizacioMEFBaseDeTiempo(funcionBots* ptr);

void lucesModoNormal(controlleds nombreLeds);

void lucesModoDesconectado(controlleds nombreLeds);

void lucesModoAlarma(controlleds nombreLeds);

void turnOffLeds(controlleds nombreLeds);

int16_t temporizadorSemaforos(colores colorActual);

#endif