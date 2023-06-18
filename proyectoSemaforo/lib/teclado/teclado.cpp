#include "teclado.h"




void botonesMEF(int16_t nombreBoton){

    switch (estado)
    {
        case noPresionado:
            if (!digitalRead(nombreBoton)){
                estado = bajando;
            }
            break;
        
        case bajando:
            if(temporizador1()){
                if(!digitalRead(nombreBoton)){
                    estado = presionado;
                } else {
                    estado = noPresionado;
                }
            }
            break;

        case presionado:
            if (digitalRead(nombreBoton)){
                estado = subiendo;
            }
            break;

        case subiendo:
            if(temporizador1()){
                if(digitalRead(nombreBoton)){
                    estado = noPresionado;
                } else {
                    estado = presionado;
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

void comprobacion(estados estado){
    switch (estado)
    {
        case noPresionado:
            digitalWrite(13, LOW);
            break;
        case presionado:
            digitalWrite(13, HIGH);
            break;
    
    }
}
