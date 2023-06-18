#include <Arduino.h>


//VARIABLESMEFBOTONES---------------------------------------------------

const int16_t bot1 = 5;
const int16_t bot2 = 6;

enum estados{noPresionado, presionado, bajando, subiendo};

estados estadoBot1;
estados estadoBot2;

estados estadoActualBotones[] = {estadoBot1, estadoBot2};

//VARIABLESMEFLUCES------------------------------------------

enum modos{normal, desconectado, alarma};

modos estadoActualSemaforo;

enum funcionBots{activa, desactivada};

funcionBots funcionBot1;
funcionBots funcionBot2;


const int16_t ledR = 2;
const int16_t ledA = 3;
const int16_t ledV = 4;

const int16_t tiempoLedR = 3000;
const int16_t tiempoLedA = 500;
const int16_t tiempoLedV = 2000;

int16_t leds[] = {ledR, ledA, ledV};
int16_t len = sizeof(leds)/sizeof(int16_t);  

int16_t tiemposModoNormal[] = {tiempoLedR, tiempoLedA, tiempoLedV};

//MEFBOTONES---------------------------------------------------

void inicializacionMEF();
void actualizacionMEF();
void comprobacion ();
int16_t temporizador1();
int16_t temporizador2();

//MEFLUCES------------------------------------------------------

void inicializacionMEFSemaforo();

void actualizacionMEFSemaforos();

//---------------------------------------------------

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
    actualizacionMEFSemaforos();
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
    //UNICAMENTE DESTINADO A COMPROBAR EL FUNCIONAMIENTO DE LA MEF
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

void inicializacionMEFSemaforo(){
    estadoActualSemaforo = normal;
}

void actualizacionMEFFuncionesBots(){

    static estados estadoPrevioBot1 = estadoActualBotones[0];
    static estados estadoPrevioBot2 = estadoActualBotones[0];

    switch (funcionBot1)
    {


        case desactivada:
            if ((estadoActualBotones[0] == presionado)){
                if((estadoActualBotones[0] != estadoPrevioBot1)){
                    funcionBot1 = activa;
                }
                
            }

            estadoPrevioBot1 = estadoActualBotones[0];
            break;

        case activa:
            funcionBot1 = desactivada;

            break;
        default:
            break;
    }

    switch (funcionBot2)
    {


        case desactivada:
            if ((estadoActualBotones[1] == presionado)){
                if((estadoActualBotones[1] != estadoPrevioBot2)){
                    funcionBot2 = activa;
                }
                
            }

            estadoPrevioBot2 = estadoActualBotones[1];
            break;

        case activa:
            funcionBot2 = desactivada;

            break;
        default:
            break;
    }

}

void actualizacionMEFSemaforos(){

    switch (estadoActualSemaforo)
    {
        case normal:
            if (funcionBot1 == activa){
                estadoActualSemaforo = desconectado;
            }
            digitalWrite(2, HIGH);
            break;

        case desconectado:
            if (funcionBot1 == activa){
                estadoActualSemaforo = alarma;
            }
            digitalWrite(3, HIGH);
            break;

        case alarma:
            if (funcionBot1 == activa){
                estadoActualSemaforo = normal;
            }
            digitalWrite(4, HIGH);
            break;
        
        default:
            break;
    }
}

void lucesModoNormal(int16_t leds, int16_t len){

    static int16_t i = len-1;

    if(temporizadorSemaforos(i)){
        i++;
        if (i==len-2)
        {
            i = 0
        }
        turnOffLeds(leds, len);    
        digitalWrite(arreglo[i], HIGH); //DEBO UTILIZAR PUNTEROS DE LOS VALORES, NO SIRVE
    }

}

void turnOffLeds(int16_t arreglo, int16_t largoArreglo){

  for (int16_t i = 0; i<largoArreglo; i++){
    digitalWrite(arreglo[i], LOW); //DEBO UTILIZAR PUNTEROS
  }
}

int16_t temporizadorSemaforos(int16_t i){
    static int16_t contador = tiemposModoNormal[i];
    static int16_t iPrev = tiemposModoNormal[i];
    
    if (iPrev != tiemposModoNormal[i]){
        contador = tiemposModoNormal[i];
    }

    contador--;
    delay(1);

    if(contador == 0){
        i++;
        return 1;
    }

    return 0;

}   



