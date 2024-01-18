#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_CARTAS 52
#define VALORES_CARTAS 13
#define MAX_MANO 10

// Representación de las cartas
char *valores[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K","A"};
char *palos[] = {"Corazones", "Diamantes", "Picas", "Treboles"};

// Estructura para una carta
struct carta {
    char *valor;
    char *palo;
    int valorNumerico;
};
struct carta mazo[TOTAL_CARTAS];
struct carta manoJugador[MAX_MANO];
int numCartasJugador = 0;
int sumaJugador = 0;
char eleccion;

// Función para sumar los valores de una mano y ajustar 'A' según sea necesario
int sumarMano(struct carta mano[], int numCartas) {
    int suma = 0;
    int numAses = 0;

    for (int i = 0; i < numCartas; i++) {
        suma += mano[i].valorNumerico;

        // Contar la cantidad de 'A' en la mano
        if (mano[i].valorNumerico == 11) {
            numAses++;
        }
    }

    // Ajustar el valor de 'A' si la suma supera 21
    while (suma > 21 && numAses > 0) {
        suma -= 10;
        numAses--;
    }

    return suma;
}

// Función para que el jugador elija el valor de 'A' (1 o 11)
int elegirValorA() {
    int valor;
    printf("Elige el valor para 'A' (1/11): ");
    scanf("%d", &valor);
    while (valor != 1 && valor != 11) {
        printf("Por favor, elige 1 o 11 para 'A': ");
        scanf("%d", &valor);
    }
    return valor;
}

int main() {
    // Inicializar el mazo de cartas
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        mazo[i].valor = valores[i % VALORES_CARTAS];
        mazo[i].palo = palos[i / VALORES_CARTAS];
        mazo[i].valorNumerico = (i % VALORES_CARTAS) + 2;
        if (mazo[i].valorNumerico > 10) mazo[i].valorNumerico = 10;
        if (i % VALORES_CARTAS == VALORES_CARTAS - 1) mazo[i].valorNumerico = 11;
    }

    // Barajar el mazo
    srand(time(NULL));
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        int j = rand() % TOTAL_CARTAS;
        struct carta temp = mazo[i];
        mazo[i] = mazo[j];
        mazo[j] = temp;
    }

    printf("Bienvenido al Blackjack!\n");

    // Repartir las dos primeras cartas al jugador
    manoJugador[numCartasJugador++] = mazo[0];
    manoJugador[numCartasJugador++] = mazo[1];
    sumaJugador = sumarMano(manoJugador, numCartasJugador);

    // Mostrar las cartas iniciales y la suma total
    printf("Tus cartas:\n");
    printf("  %s de %s\n", manoJugador[0].valor, manoJugador[0].palo);
    printf("  %s de %s\n", manoJugador[1].valor, manoJugador[1].palo);
    printf("Suma total: %d\n", sumaJugador);

    // Bucle principal del juego
    while (sumaJugador < 21) {
        printf("Quieres otra carta? (s/n): ");
        scanf(" %c", &eleccion);

        if (eleccion == 's' || eleccion == 'S') {
            // Extraer una nueva carta y permitir al jugador elegir el valor de 'A'
            manoJugador[numCartasJugador] = mazo[numCartasJugador + 1];
            if (manoJugador[numCartasJugador].valorNumerico == 11) {
                manoJugador[numCartasJugador].valorNumerico = elegirValorA();
            }

            // Actualizar la suma de la mano y mostrar la nueva carta y la suma total
            sumaJugador = sumarMano(manoJugador, ++numCartasJugador);
            printf("Nueva carta:\n");
            printf("  %s de %s\n", manoJugador[numCartasJugador - 1].valor, manoJugador[numCartasJugador - 1].palo);
            printf("Suma total: %d\n", sumaJugador);
        } else {
            break;
        }
    }

    // Determinar el resultado del juego y mostrar el mensaje correspondiente
    if (sumaJugador == 21) {
        printf("¡Blackjack! Has ganado.\n");
    } else if (sumaJugador > 21) {
        printf("Te has pasado. Fin del juego.\n");
    } else {
        printf("Te has plantado con %d. Fin del juego.\n", sumaJugador);
    }

    return 0;
}
