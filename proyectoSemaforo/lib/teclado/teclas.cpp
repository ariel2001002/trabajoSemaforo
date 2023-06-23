#include "teclas.h"


const int16_t bot1 = 5;
const int16_t bot2 = 6;

estados estadoBot1;
estados estadoBot2;

estados estadoPrevBot1;
estados estadoPrevBot2;

estados estadoActualBotones[] = {estadoBot1, estadoBot2};
estados estadoPrevioBotones[] = {estadoPrevBot1, estadoPrevBot2};

funcionBots funcionBot1;
funcionBots funcionBot2;

funcionBots funcionBotones[] = {funcionBot1, funcionBot2};

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

    for (int16_t i = 0; i < 2; i++)
    {
        funcionBotones[i] = desactivada;
        estadoPrevioBotones[i] = estadoActualBotones[i];
    }

    pinMode(bot1, INPUT);
    pinMode(bot2, INPUT);
    
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

void actualizacionMEFFuncionesBots(funcionBots* ptr){

    for (int16_t i = 0; i < 2; i++)
    {
        switch (funcionBotones[i])
        {
            case desactivada:
                if ((estadoActualBotones[i] == presionado)){
                    if((estadoActualBotones[i] != estadoPrevioBotones[i])){
                        funcionBotones[i] = activa;
                    }
                    
                }
                break;

            case activa:
                funcionBotones[i] = desactivada;

                break;
            default:
                break;
        }

        ptr[i] = funcionBotones[i];
        estadoPrevioBotones[i] = estadoActualBotones[i];

    }
    

}
