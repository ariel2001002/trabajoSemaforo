#include <Arduino.h>


//VARIABLESMEFBOTONES---------------------------------------------------

const int16_t bot1 = 5;
const int16_t bot2 = 6;

enum estados{noPresionado, presionado, bajando, subiendo};

estados estadoBot1;
estados estadoBot2;

estados estadoActualBotones[] = {estadoBot1, estadoBot2};

enum funcionBots{activa, desactivada};

funcionBots funcionBot1;
funcionBots funcionBot2;

funcionBots funcionBotones[] = {funcionBot1, funcionBot2};


//VARIABLESMEFLUCES------------------------------------------

enum modos{normal, desconectado, alarma};

modos estadoActualSemaforo;

const int16_t ledR = 2;
const int16_t ledA = 3;
const int16_t ledV = 4;

const int16_t tiempoLedR = 3000;
const int16_t tiempoLedA = 500;
const int16_t tiempoLedV = 2000;

int16_t leds[] = {ledR, ledA, ledV};
int16_t len = sizeof(leds)/sizeof(int16_t);

typedef struct {
    int16_t* pleds;
    int16_t len;
} controlleds;

controlleds cleds = {leds, len};

int16_t tiemposModoNormal[] = {tiempoLedR, tiempoLedA, tiempoLedV};


enum colores {rojo, amarillo, verde};

//MEFBOTONES---------------------------------------------------

void inicializacionMEF();

void actualizacionMEF();

void comprobacion ();

int16_t temporizador1();

int16_t temporizador2();

void actualizacionMEFFuncionesBots();

//MEFLUCES------------------------------------------------------

void inicializacionMEFSemaforo();

void actualizacionMEFSemaforos();

void lucesModoNormal(controlleds nombreLeds);

void turnOffLeds(controlleds nombreLeds);

int16_t temporizadorSemaforos(colores colorActual);


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
    actualizacionMEFFuncionesBots();

    inicializacionMEFSemaforo();
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

    funcionBot1 = desactivada;
    funcionBot2 = desactivada;
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

void actualizacionMEFFuncionesBots(){

    static estados estadoPrevioBot1 = estadoActualBotones[0];
    static estados estadoPrevioBot2 = estadoActualBotones[1];

    switch (funcionBot1)
    {
        case desactivada:
            if ((estadoActualBotones[0] == presionado)){
                if((estadoActualBotones[0] != estadoPrevioBot1)){
                    funcionBot1 = activa;
                }
                
            }
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

            break;

        case activa:
            funcionBot2 = desactivada;

            break;
        default:
            break;
    }

    estadoPrevioBot1 = estadoActualBotones[0];
    estadoPrevioBot2 = estadoActualBotones[1];

}


//MEFLUCES-----------------------------------------------------

void inicializacionMEFSemaforo(){
    estadoActualSemaforo = normal;
}

void actualizacionMEFSemaforos(){

    switch (estadoActualSemaforo)
    {
        case normal:
            if (funcionBot1 == activa){
                estadoActualSemaforo = desconectado;
                turnOffLeds(cleds);
                break;
            }

            lucesModoNormal(cleds);

            break;

        case desconectado:
            if (funcionBot1 == activa){
                estadoActualSemaforo = alarma;
            }
            break;

        case alarma:
            if (funcionBot1 == activa){
                estadoActualSemaforo = normal;
            }
            break;
        
        default:
            break;
    }
}

void lucesModoNormal(controlleds nombreLeds){
    static colores colorActual = rojo;

    switch (colorActual)
        {
        case rojo:
            digitalWrite(*nombreLeds.pleds, HIGH); 
            break;
        case amarillo:
            digitalWrite(*nombreLeds.pleds+1, HIGH); 
            break;
        case verde:
            digitalWrite(*nombreLeds.pleds+2, HIGH); 
            break;
        
        default:
            break;
    }

    if(temporizadorSemaforos(colorActual)){

        switch (colorActual)
        {
        case rojo:
            colorActual = verde;
            break;
        case amarillo:
            colorActual = rojo;
            break;
        case verde:
            colorActual = amarillo;
            break;
        
        default:
            break;
        }

        turnOffLeds(cleds);    
    }
}

void turnOffLeds(controlleds nombreLeds){

  for (int16_t i = 0; i<len; i++){
    digitalWrite(*nombreLeds.pleds+i, LOW); //DEBO UTILIZAR PUNTEROS
  }
}

int16_t temporizadorSemaforos(colores colorActual){
   
   static colores colorPrevio = colorActual;
   static int16_t contador = tiemposModoNormal[0];
       

    if(colorPrevio != colorActual){
        switch (colorActual)
        {
        case rojo:
            contador = tiemposModoNormal[0];
            break;
        case amarillo:
            contador = tiemposModoNormal[1];
            break;
        case verde:
            contador = tiemposModoNormal[2];
            break;
        default:
            break;
        }
    }

    contador--;
    delay(1);
    colorPrevio = colorActual;

    if(contador == 0){
        return 1;
    }

    return 0;

}
 
