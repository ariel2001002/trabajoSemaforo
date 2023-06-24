#include "uart.h"

void comunicacionCambioModoSem(modos modoActual){
    static modos modoPrev = modoActual;
    static int16_t inicializador = 0;

    if (inicializador == 0)
    {
        Serial.println("Modo semáforo: Normal");
        inicializador++;
    }

    if (modoActual != modoPrev)
    {
        if (modoActual == normal)
        {
            Serial.println("Modo semáforo: Normal");
        }
        if (modoActual == alarma)
        {
            Serial.println("Modo semáforo: Alarma");
        }
        if (modoActual == desconectado)
        {
            Serial.println("Modo semáforo: Desconectado");
        }
        
    }

    modoPrev = modoActual;
    
    
}


