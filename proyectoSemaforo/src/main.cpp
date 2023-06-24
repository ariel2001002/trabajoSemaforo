#include <Arduino.h>
#include "teclas.h"
#include "semaforo.h"
#include "funciones.h"
#include "uart.h"




//VARIABLESGLOBALES-----------------------------------------

funcionBots estadoFunBot1;
funcionBots estadoFunBot2;
funcionBots estadoFuncionesBots[] = {estadoFunBot1, estadoFunBot2};

void setup() {
    Serial.begin(9600);
    inicializacionMEF();
    inicializacionMEFSemaforo();
}

void loop() {
    actualizacionMEF();
    actualizacionMEFFuncionesBots(estadoFuncionesBots);

    actualizacioMEFBaseDeTiempo(estadoFuncionesBots);
    actualizacionMEFSemaforos(estadoFuncionesBots);
}
