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

void comunicacionCambioEstadoBots(estados estadoActual, int16_t boton){
    static estados estadoPrev = estadoActual;


    if (estadoActual != estadoPrev)
    {
        if (estadoActual == noPresionado)
        {
            Serial.print("Botón presionado: ");
            if (boton == 5){
                Serial.println("Botón 1");
            } else if(boton == 6) {
                Serial.println("Botón 2");
            }

            Serial.print("Estado MEF antirrebote: ");
            Serial.println("No Presionado");    
        }
        if (estadoActual == presionado)
        {
            Serial.print("Botón presionado: ");
            if (boton == 5){
                Serial.println("Botón 1");
            } else if(boton == 6) {
                Serial.println("Botón 2");
            }

            Serial.print("Estado MEF antirrebote: ");
            Serial.println("Presionado");    
        }
        if (estadoActual == bajando)
        {
            Serial.print("Estado MEF antirrebote: ");
            Serial.println("Bajando");    
        }
        if (estadoActual == subiendo)
        {
            Serial.print("Estado MEF antirrebote: ");
            Serial.println("Subiendo");    
        }
        
    }

    estadoPrev = estadoActual;
    
    
}
