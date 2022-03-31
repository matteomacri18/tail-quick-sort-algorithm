#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void SwapValue(int *A, int i, int j)
{
    int temp;
    temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

/* Algoritmo Partition */
int Partition(int *A, int p, int r)
{
    //stessa cosa del median ma senza trovare il mediano dei 3 elementi
    int x, i, j;
    x = A[r];
    i = p - 1;
    for (j = p; j <= r - 1; j++)
    {
        if (A[j] <= x)
        {
            i++;
            SwapValue(A, i, j);
        }
    }
    SwapValue(A, i + 1, r);
    return i + 1;
}

/* Algortimo Tail QuickSort */
void TailQuickSort(int *A, int p, int r)
{
    int q;
    while (p < r)
    {
        q = Partition(A, p, r);
        TailQuickSort(A, p, q - 1);
        p = q + 1;
    }
}

/* ESPERIMENTO SINGOLO */
float singoloEsperimento(int len, int maxInstance)
{
    float timeTot = 0;
    float timeStart, timeEnd, timeElapsed;
    int A[len];
    for (int i = 0; i < maxInstance; i++)
    {

        for (int j = 0; j < len; j++)    // Generatore Array di numeri Casuali:
        {                                // tramite il metodo rand()%N, genera un numero tra 0 e N-1
            A[j] = 1 + rand() % 1000000; // e metto il numero generato nell'array
        }

        // printf("Non ordinato\n");
        // for (int j = 0; j < len; j++)
        // {
        //     printf("%d\n", A[j]);
        // }

        timeStart = clock(); //inzio tempo
        TailQuickSort(A, 0, len - 1);
        timeEnd = clock(); //fine tempo

        // printf("ordinato\n");
        // for (int j = 0; j < len; j++)
        // {
        //     printf("%d\n", A[j]);
        // }

        timeElapsed = timeEnd - timeStart; //tempo trascorso
        timeTot = timeTot + timeElapsed;
    }
    return timeTot / maxInstance;
}

/* ESPERIMENTO Median of 3 QuickSort */
void esperimento(int minLen, int maxLen)
{
    int maxInstances = 50; // numero di istanze array per tentativo della lunghezza dell'array
    int STEP = 10;         // mi aumenta numero di elementi dell'array
    float time;

    for (int i = minLen; i < maxLen; i = i + STEP)
    {
        time = singoloEsperimento(i, maxInstances);
        //printf("Tempo per %d elementi per array: %f\n\n", i, time);
        printf("%.2f \n", time);
    }
}

/* Funzione Main */
int main(int argc, char *argv[])
{
    srand(15); // come parametro si mette un SEED che serve per il pseudo-RNG
    int minLength = 5;
    int maxLength = 1000;
    esperimento(minLength, maxLength); // esperimento() mi da n.Tempi per tentativo
                                       // dove n = (maxLength - minLength) / Step

    return 0;
}