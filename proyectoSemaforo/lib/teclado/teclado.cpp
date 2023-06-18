#include "teclado.h"

void inicializacionMEF(){
    pinMode(5, INPUT);
    if(digitalRead(5)){
        estadoActual = noPresionado;
    } else {
        estadoActual = presionado;
    }
}



void botonesMEF(){

    switch (estadoActual)
    {
        case noPresionado:
            if (!digitalRead(5)){
                estadoActual = bajando;
            }
        break;
        
        case bajando:
            if(temporizador1()){
                if(!digitalRead(5)){
                    estadoActual = presionado;
                } else {
                    estadoActual = noPresionado;
                }
            }
        break;

        case presionado:
            if (digitalRead(5)){
                estadoActual = subiendo;
            }
        break;

        case subiendo:
            if(temporizador1()){
                if(digitalRead(5)){
                    estadoActual = noPresionado;
                } else {
                    estadoActual = presionado;
                }
            }
        break;

    }

}

int16_t temporizador1(){
    static int16_t i = 40;
    delay(1);
    i--;

    if(i == 0)
    {
        i = 40;
        return 1;
    }

    return 0;
}

void comprobacion(){
    switch (estadoActual)
    {
        case noPresionado:
            digitalWrite(13, LOW);
        break;
        case presionado:
            digitalWrite(13, HIGH);
        break;
        default:
        break;
    
    }
}

