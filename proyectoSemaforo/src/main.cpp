#include <Arduino.h>


//---------------------------------------------------

int16_t bot1 = 5;
int16_t bot2 = 6;
int16_t bots[] = {bot1, bot2};

enum estados{noPresionado, presionado, bajando, subiendo};

estados estadoActual;

//---------------------------------------------------

void inicializacionMEF();

int16_t temporizador1();

void botonesMEF();

void comprobacion ();

//---------------------------------------------------

void setup() {
    pinMode(5, INPUT);
}

void loop() {
    botonesMEF();
    comprobacion();
}


//---------------------------------------------------

void inicializacionMEF(){
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
            if (!digitalRead(bot1)){
                estadoActual = bajando;
            }
        break;
        
        case bajando:
            if(temporizador1()){
                if(!digitalRead(bot1)){
                    estadoActual = presionado;
                } else {
                    estadoActual = noPresionado;
                }
            }
        break;

        case presionado:
            if (digitalRead(bot1)){
                estadoActual = subiendo;
            }
        break;

        case subiendo:
            if(temporizador1()){
                if(digitalRead(bot1)){
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

