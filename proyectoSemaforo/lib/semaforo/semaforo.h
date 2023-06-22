#ifndef _SEMAFORO_H
#define _SEMAFORO_H

#include <Arduino.h>


//SE DEFINEN LOS TIPOS DE VARIABLES
enum modos{normal, desconectado, alarma};

typedef struct {
    int16_t* pleds;
    int16_t len;
} controlleds;

enum colores {rojo, amarillo, verde};

//SE DECLARAN LAS FUNCIONES
void inicializacionMEFSemaforo();

void actualizacionMEFSemaforos();

void actualizacioMEFBaseDeTiempo();

void lucesModoNormal(controlleds nombreLeds);

void lucesModoDesconectado(controlleds nombreLeds);

void lucesModoAlarma(controlleds nombreLeds);

void turnOffLeds(controlleds nombreLeds);

int16_t temporizadorSemaforos(colores colorActual);

#endif