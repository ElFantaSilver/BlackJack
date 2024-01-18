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
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        mazo[i].valor = valores[i % VALORES_CARTAS];
        mazo[i].palo = palos[i / VALORES_CARTAS];
        mazo[i].valorNumerico = (i % VALORES_CARTAS) + 2;
        if (mazo[i].valorNumerico > 10) mazo[i].valorNumerico = 10;
        if (i % VALORES_CARTAS == VALORES_CARTAS - 1) mazo[i].valorNumerico = 11;
    }
    srand(time(NULL));
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        int j = rand() % TOTAL_CARTAS;
        struct carta temp = mazo[i];
        mazo[i] = mazo[j];
        mazo[j] = temp;
    }

    printf("Bienvenido al Blackjack!\n");

    manoJugador[numCartasJugador++] = mazo[0];
    manoJugador[numCartasJugador++] = mazo[1];
    sumaJugador = sumarMano(manoJugador, numCartasJugador);

    printf("Tus cartas:\n");
    printf("  %s de %s\n", manoJugador[0]);
    printf("  %s de %s\n", manoJugador[1]);
    printf("Suma total: %d\n", sumaJugador);

    while (sumaJugador < 21) {
    printf("¿Quieres otra carta? (s/n): ");
    scanf(" %c", &eleccion);

    if (eleccion == 's' || eleccion == 'S') {
        manoJugador[numCartasJugador] = mazo[numCartasJugador + 1];
        
        // Verificar si la carta es un 'A' y permitir al jugador elegir su valor
        if (manoJugador[numCartasJugador].valorNumerico == 11) {
            manoJugador[numCartasJugador].valorNumerico = elegirValorA();
        }

        sumaJugador = sumarMano(manoJugador, ++numCartasJugador);

        printf("Nueva carta:\n");
        printf("  %s de %s\n", manoJugador[numCartasJugador - 1].valor, manoJugador[numCartasJugador - 1].palo);
        printf("Suma total: %d\n", sumaJugador);
    } else {
        break;
    }
    }

    if (sumaJugador == 21) {
        printf("¡Blackjack! Has ganado.\n");
    } else if (sumaJugador > 21) {
        printf("Te has pasado. Fin del juego.\n");
    } else {
        printf("Te has plantado con %d. Fin del juego.\n", sumaJugador);
    }

    return 0;
}
