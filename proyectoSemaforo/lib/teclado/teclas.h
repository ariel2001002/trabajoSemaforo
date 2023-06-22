#ifndef _TECLAS_H
#define _TECLAS_H

#include "Arduino.h"


//SE DEFINEN LOS TIPOS DE VARIABLES

enum estados{noPresionado, presionado, bajando, subiendo};

enum funcionBots{activa, desactivada};

//SE DECLARAN LAS FUNCIONES DE LA LIBRERIA

void inicializacionMEF();

void actualizacionMEF();

void comprobacion ();

int16_t temporizador1();

int16_t temporizador2();

void actualizacionMEFFuncionesBots(funcionBots* ptr);


#endif
