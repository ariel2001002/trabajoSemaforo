#include <Arduino.h>
#include "teclas.h"

//VARIABLESGLOBALES-----------------------------------------

funcionBots estadoFunBot1;
funcionBots estadoFunBot2;
funcionBots estadoFuncionesBots[] = {estadoFunBot1, estadoFunBot2};

void setup() {
    pinMode(5, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);

    inicializacionMEF();
    inicializacionMEFSemaforo();
}

void loop() {
    actualizacionMEF();
    actualizacionMEFFuncionesBots(estadoFuncionesBots);

    actualizacioMEFBaseDeTiempo();
    actualizacionMEFSemaforos();
}


