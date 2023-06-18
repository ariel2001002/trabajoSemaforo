#include <Arduino.h>


//VARIABLESMEFBOTONES---------------------------------------------------

int16_t bot1 = 5;
int16_t bot2 = 6;

enum estados{noPresionado, presionado, bajando, subiendo};

estados estadoBot1;
estados estadoBot2;

estados estadoActualBotones[] = {estadoBot1, estadoBot2};

//VARIABLESMEFLUCES------------------------------------------



//MEFBOTONES---------------------------------------------------

void inicializacionMEF();
void actualizacionMEF();
void comprobacion ();
int16_t temporizador1();
int16_t temporizador2();

//MEFLUCES------------------------------------------------------



//---------------------------------------------------

void setup() {
    pinMode(5, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);

    inicializacionMEF();
}

void loop() {
    actualizacionMEF();
}


//MEFBOTONES---------------------------------------------------

void inicializacionMEF(){
    if(digitalRead(bot1)){
        estadoActualBotones[0] = noPresionado;
    } else {
        estadoActualBotones[0] = presionado;
    }

    if(digitalRead(bot2)){
        estadoActualBotones[1] = noPresionado;
    } else {
        estadoActualBotones[1] = presionado;
    }
}

void actualizacionMEF(){

    switch (estadoActualBotones[0])
    {
        case noPresionado:
            if (!digitalRead(bot1)){
                estadoActualBotones[0] = bajando;
            }
        break;
        
        case bajando:
            if(temporizador1()){
                if(!digitalRead(bot1)){
                    estadoActualBotones[0] = presionado;
                } else {
                    estadoActualBotones[0] = noPresionado;
                }
            }
        break;

        case presionado:
            if (digitalRead(bot1)){
                estadoActualBotones[0] = subiendo;
            }
        break;

        case subiendo:
            if(temporizador1()){
                if(digitalRead(bot1)){
                    estadoActualBotones[0] = noPresionado;
                } else {
                    estadoActualBotones[0] = presionado;
                }
            }
        break;

    }

    switch (estadoActualBotones[1])
    {
        case noPresionado:
            if (!digitalRead(bot2)){
                estadoActualBotones[1] = bajando;
            }
        break;
        
        case bajando:
            if(temporizador2()){
                if(!digitalRead(bot2)){
                    estadoActualBotones[1] = presionado;
                } else {
                    estadoActualBotones[1] = noPresionado;
                }
            }
        break;

        case presionado:
            if (digitalRead(bot2)){
                estadoActualBotones[1] = subiendo;
            }
        break;

        case subiendo:
            if(temporizador2()){
                if(digitalRead(bot2)){
                    estadoActualBotones[1] = noPresionado;
                } else {
                    estadoActualBotones[1] = presionado;
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

int16_t temporizador2(){
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
    switch (estadoActualBotones[0])
    {
        case noPresionado:
            digitalWrite(2, LOW);
        break;
        case presionado:
            digitalWrite(2, HIGH);
        break;

        default:
        break;
    
    }

    switch (estadoActualBotones[1])
    {
        case noPresionado:
            digitalWrite(3, LOW);
        break;
        case presionado:
            digitalWrite(3, HIGH);
        break;

        default:
        break;
    
    }
}

//MEFLUCES-----------------------------------------------------

