# trabajoSemaforo
Asignatura: Control Digital

INPORTANTE: La versión final del proyecto se encuentra en el branch "programación-librería-UART"

El presente código es el algoritmo de funcionamiento de un semáforo de una vía con controlador de modo de operación y tiempo. El hardware se compone de dos pulsantes, uno destinado al control de modo de operación y otro al control de la base e tiempo de cada modo. El funcionamiento es el solicitado en la guía de actividad.



A continuación, se explican las librerías.

## Librería tipoDeVariables

Esta librería contine los tipos de variables tipo enum que se utilizan a lo largo de la programación y que son utilizadas por las demás librerías.

enum funcionBots{activa, desactivada};

enum modos{normal, desconectado, alarma};

enum estados{noPresionado, presionado, bajando, subiendo};


## Librería teclas.h

Esta librería tiene la función de codificar las entradas de los pulsantes. Mediante una MEF se implementa un sistema antirrebote. Adicionalmente, mediante otra MEF se genera un detector de flancos de bajada. Posee las siguientes funciones:

void inicializacionMEFEstadoBotones();

void actualizacionMEFEstadoBotones();

int16_t temporizador1();

int16_t temporizador2();

void actualizacionMEFFuncionesBots(funcionBots* ptr);

Las dos primeras, destinadas para el funcionamiento de la MEF del sistema antirebote. Comprueban el estado de los botones mediante temporizadores no-bloqueantes para evitar falsas pulsaciones.

La última función, corresposde a la máquina de estados finitos encargada de detectar flancos de bajada en los botones. Esta función actualiza el estado de un arreglo de tipo funcionBots, el cual contiene el estado de la función de cada botón para que otras funciones puedan realizar acciones si la función de un botón es activada.

## Librería semaforo.h

En esta, se encuetran las funciones que se ejecutan cuando los botones (flancos de baja) son activados. Las funciones se muestran a continuación:

void inicializacionMEFSemaforo();

void actualizacionMEFSemaforos(funcionBots* ptr);

void actualizacioMEFBaseDeTiempo(funcionBots* ptr);

void lucesModoNormal(controlleds nombreLeds);

void lucesModoDesconectado(controlleds nombreLeds);

void lucesModoAlarma(controlleds nombreLeds);

void turnOffLeds(controlleds nombreLeds);

int16_t temporizadorSemaforos(colores colorActual);

Adicionalmente, se incluye mediante una estructura el arreglo de luces a controlarse y los modos del semáforo cuando se encuentra operando en modo normal.

typedef struct {
    int16_t* pleds;
    int16_t len;
} controlleds;

enum colores {rojo, amarillo, verde};

Las funciones, por medio de MEF actualizan tanto el modo de operación como tambien la base tiempo.

## Librería uart.h

En esta librería, se encuentras las funciones destinadas a la comunicación serial. Las funciones son las siguientes:

void comunicacionCambioModoSem(modos modoActual);

void comunicacionCambioEstadoBots(estados estadoActual, int16_t boton);

Una destinada a informar cuando el modo del semáforo cambió y la otra a informar cuando el estado del botón cambió. 

# Implementación del código

El proyecto fue creado sobre la plataforma Arduino Nano. El led rojo, amarillo y verde fueron conectados por medio de una resistencia de 330 ohms a los pines digitales 2, 3 y 4 respectivamente. Por otro lado, los pulsantes 1 y 2 fueron conectados en configuración pull-ups a los pines digitales 5 y 6, respectivamente. Finalmente, el puerto serial fue configurado a 9600 bauds. Siguiendo esta configuración, la implmentación se puede realizar sin modificaciones de software.


