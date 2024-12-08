#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>



void escribir_archivo(float raiz){ //función que escribe en un archivo una línea con un float (para guardar la ultima raiz calculada)
	FILE* archivo = fopen("ultimaraiz.txt","w+"); // abrimos el archivo en modo w+
	if(archivo == NULL){ // si no se puede abrir devolvemos un error
		perror("\nNo se ha podido abrir el archivo\n");
		exit(EXIT_FAILURE);
	}
	else{
		fprintf(archivo,"%.5f",raiz); // si no hay errores imprimimos el valor en el archivo
	}
	fclose(archivo); // cerramos el archivo
}

void leer_archivo(float* raiz){ // funcion para leer el valor guardado en el archivo
	FILE* archivo = fopen("ultimaraiz.txt","r"); // abrimos el archivo en modo r
	if(archivo == NULL){ // si no se puede abrir devolvemos un error
		perror("\nNo se ha podido abrir el archivo\n");
	}
	else{
		fscanf(archivo,"%f",raiz); // guardamos el valor leído del archivo
	}
	fclose(archivo); // cerramos el archivo
}

int es_primo(int numero) { // función que determina si un número es primo o no (devuelve 1 si es primo, 0 si no es primo)
    if (numero<=1){
		return 0; 
	}
    if (numero<=3){ 
		return 1;  
	}
    if (numero%2 == 0 || numero%3 == 0){
        return 0;
	}

    // Probar divisores desde 5 hasta la raíz cuadrada del número
    for (int i=5; i*i <= numero; i+=6) {
        if (numero%i == 0 || numero%(i+2) == 0){
            return 0;
		}
    }
    return 1;
}


static void gestion(int);

int main(int argc, char** argv){
	int i=0,hijo,padre;

	if (signal(SIGALRM, gestion) == SIG_ERR){ // designamos el comportamiento de la señal SIGALRM, y devolvemos un error si no se ha podido completar.
		perror("Error al crear SIGALARM\n");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGUSR1, gestion) == SIG_ERR){ // designamos el comportamiento de la señal SIGUSR1, y devolvemos un error si no se ha podido completar.
		perror("Error al crear SIGUSR1\n");
		exit(EXIT_FAILURE);
	}
	printf("PID: %d\n",getpid()); // imprimimos el PID del proceso para saber a quien hacer un kill con la señal SIGUSR1

	if((hijo = fork()) == -1){ // creamos un hijo que ejecutará un alarm(1) cada segundo. Devolvemos error si no se puede crear.
		perror("Error al crear el hijo");
		exit(EXIT_FAILURE);
	}
	else if(hijo == 0){ // ACCIONES DEL HIJO
		padre=getppid(); // guardamos el pid de su padre original
		while(1){ // bucle que itera infinitamente
			alarm(1); // se envía una señal SIGALRM dentro de 1 segundo
			sleep(1); // esperamos 1 segundo para que no se superpongan los alarm()
			if(getppid()!=padre){ // si el padre es distinto (el proceso pierde su padre original y es adoptado) terminamos el proceso hijo.
				exit(0);
			}
		}
	}
	else{ // ACCIONES DEL PADRE
		while(1){
			if(es_primo(i)==1){ // comprobamos si el siguiente numero es primo
				sleep(1);
				escribir_archivo(sqrt(i)); // escribimos en el archivo su raíz, en caso de que sea primo
			}
			i++; // avanzamos al siguiente numero
		}
	}
	return (EXIT_SUCCESS);
}
static void gestion(int numero_de_senhal) { /* Funcion de gestion de señales*/
	switch (numero_de_senhal) {
		case SIGALRM: /*Entra señal SIGALARM*/
			float valor; // creamos una variable valor
			leer_archivo(&valor); // guardamos en valor la ultima raiz calculada
			printf("\nÚltima raíz calculada: %.5f\n",valor); // imprimimos la ultima raiz calculada.
		break;
		case SIGUSR1: /*Entra señal SIGUSR1*/
			exit(0);
		break;
	}
	return; 
}
