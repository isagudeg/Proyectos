#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>
#include <math.h> 

#define PI 3.14159265358979323846 //Constante para el valor de π
#define NHILOS 4 //Número de hilos que vamos a usar

//Variables globales
double final=1e9; //Número final de iteraciones para aproximar la serie
double resultados[NHILOS];

/*
Respuesta apartado h:
    Al ejecutar el programa con un número de hilos mayor al número de núcleos de la CPU, observamos que el tiempo de
    ejecución no mejora significativamente si no que en algunos casos incluso aumenta, los casos en los que este tiempo mejora 
    insignificativamente es cuando aumentamos mucho el numero de cores, en mi caso (4 núcleos), comenzamos a ver esta mejora a 
    partir de los 18 hilos.
    Además, pese a que el uso de la CPU es alto, este no es eficiente, ya que el sistema gasta mucho tiempo en los cambios de 
    contexto entre todos los hilos.
*/

//Función para realizar la suma praial de la serie de Basilea para cada hilo en específico
void *funcionsuma(void *arg) {
    int numero = *(int *)arg,contador=0,i;
    double sumatorio=0,num=1;
    int desde,hasta=0,nvueltas=0;

    //En este bucle cada hilo calcula su suma en el vector de resultados en iteraciones de 10 en 10
    while(hasta<final){
        hasta=(10*numero)+(10*NHILOS*nvueltas); //Calculamos el rango máximo del bloque de 10 iteraciones
        desde=hasta-9; //Calculamos el rango mínimo
        if(hasta<=final){
            num=desde;
            //En este bucle cada se calcula la operación en cada iteración y se van sumando en la variable sumatorio
            for(i=desde;i<=hasta;i++){
                sumatorio=sumatorio+(1/(num*num));
                num++;
                contador++;
            }
            nvueltas+=1;
            resultados[numero-1]=resultados[numero-1]+sumatorio;
            sumatorio=0;

            //Comprobación de que el número total de iteraciones es correcto
            //resultados[numero-1]=resultados[numero-1]+contador;
            //contador=0;
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char** argv){
    double calculoSecuancials,calculoParalelo,numero;
	int num[NHILOS],i;
	pthread_t hilo[NHILOS];
    //clock_t inicio, fin; //Variables usadas para medir el tiempo de ejecución para la resolución del apartado h
    //inicio = clock(); 

    //Creamos los hilos y los mandamos a la función 
	for(i=0;i<NHILOS;i++){
        num[i]=i+1; //Asignar un número a cada hilo
        if (pthread_create(&hilo[i], NULL, funcionsuma, &num[i]) != 0) {
            perror("Error al crear el hilo");
            exit(1);
        }
    }

    //Esperamos a que todos los hilos acaben
	for(i=0;i<NHILOS;i++){
        pthread_join(hilo[i], NULL);
    }

    //Sumamos los resultados parciales de cada hilo para obtener el resultado paralelo total
    for(i=0;i<NHILOS;i++){
        calculoParalelo=calculoParalelo+resultados[i];
    }
    
    //El hilo principal hace el cálculo secuencial de la serie de Basilea
    for(i=1;i<=final;i++){
        numero=i;
        calculoSecuancials=calculoSecuancials+(1/(numero*numero));
        numero++;
    }

    //fin = clock(); 

    //Mostramos resultados
    printf("Valor exacto de ((π^2)/6): %.15f\n",(PI*PI)/6);
    printf("Diferencia entre el cálculo secuencial y el paralelo: %.15f\n",fabs(calculoParalelo-calculoSecuancials));
    printf("Valor obtenido mediante el calculo paralelo: %.15f, diferencia con respecto al valor exacto: %.15f\n",calculoParalelo, fabs(((PI*PI)/6)-calculoParalelo));
    printf("Valor obtenido mediante el calculo secuancial: %.15f, diferencia con respecto al valor exacto: %.15f\n",calculoSecuancials, fabs(((PI*PI)/6)-calculoSecuancials));
    //printf("Tiempo de ejecución: %.6f seg con %d hilos\n", (double)(fin - inicio) / CLOCKS_PER_SEC,NHILOS);

	return (EXIT_SUCCESS);
}
