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

const int16_t tiemposBase[] = {tiempoLedR, tiempoLedA, tiempoLedV};
volatile int16_t tiempoModos[] = {tiempoLedR, tiempoLedA, tiempoLedV};

int16_t leds[] = {ledR, ledA, ledV};
int16_t len = sizeof(leds)/sizeof(int16_t);

typedef struct {
    int16_t* pleds;
    int16_t len;
} controlleds;

controlleds cleds = {leds, len};

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

void actualizacioMEFBaseDeTiempo();

void lucesModoNormal(controlleds nombreLeds);

void lucesModoDesconectado(controlleds nombreLeds);

void lucesModoAlarma(controlleds nombreLeds);

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

    actualizacioMEFBaseDeTiempo();
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

    if(funcionBot1 == activa){

        switch (estadoActualSemaforo)
        {
            case normal:
                
                estadoActualSemaforo = desconectado;
                turnOffLeds(cleds);
                break;

            case desconectado:

                estadoActualSemaforo = alarma;
                turnOffLeds(cleds);
                break;

            case alarma:
            
                estadoActualSemaforo = normal;
                turnOffLeds(cleds);
                break;
            
            default:
                break;
        }
    }

    switch (estadoActualSemaforo)
    {
        case normal:
            lucesModoNormal(cleds);
            break;

        case desconectado:
            lucesModoDesconectado(cleds);
            break;

        case alarma:
             lucesModoAlarma(cleds);
            break;
        
        default:
            break;
    }
}

void actualizacioMEFBaseDeTiempo(){
    enum baseDeTiempo{lento, normal, rapido};
    static baseDeTiempo baseDeTiempoActual = normal;

    switch (baseDeTiempoActual)
    {
        case normal: 
            if(funcionBot2 == activa){
                baseDeTiempoActual = rapido;
            } else{
                for (int16_t i = 0; i < 3; i++)
                {
                    tiempoModos[i] = 1 * tiemposBase[i];
                }
                
            }
            break;
        case rapido:
            if(funcionBot2 == activa){
                baseDeTiempoActual = lento;
            } else{
                for (int16_t i = 0; i < 3; i++)
                {
                    tiempoModos[i] = 0.5 * tiemposBase[i];
                }
            }
            break;

        case lento:
            if(funcionBot2 == activa){
                baseDeTiempoActual = normal;
            } else{
                for (int16_t i = 0; i < 3; i++)
                {
                    tiempoModos[i] = 2 * tiemposBase[i];
                }
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

void lucesModoDesconectado(controlleds nombreLeds){

    static int16_t estado = 1;
    static int16_t contador = tiempoModos[1];

    contador--;
    delay(1);

    if(contador == 0){
        estado = !estado;
        contador = tiempoModos[1];
    }

    digitalWrite(ledA, estado);
}

void lucesModoAlarma(controlleds nombreLeds){

    static int16_t estado = 1;
    static int16_t contador = tiempoModos[2];

    contador--;
    delay(1);

    if(contador == 0){
        estado = !estado;
        contador = tiempoModos[2];
    }

    digitalWrite(ledR, estado);
}

void turnOffLeds(controlleds nombreLeds){

  for (int16_t i = 0; i<len; i++){
    digitalWrite(*nombreLeds.pleds+i, LOW); //DEBO UTILIZAR PUNTEROS
  }
}

int16_t temporizadorSemaforos(colores colorActual){
   
   static colores colorPrevio = colorActual;
   static int16_t contador = tiempoModos[0];
       

    if(colorPrevio != colorActual){
        switch (colorActual)
        {
        case rojo:
            contador = tiempoModos[0];
            break;
        case amarillo:
            contador = tiempoModos[1];
            break;
        case verde:
            contador = tiempoModos[2];
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
 