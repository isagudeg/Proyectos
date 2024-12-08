#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define MAX 10

static void gestion(int);

int llegar(int bola,int pos){ // función que dada la posición de un jugador y la posición de la bola determina si el jugador es capaz de devolver la pelota.
	if(abs(pos-bola)<=3){ // si se sitúa a tres posiciones o menos el jugador es capaz de devolver la pelota.
		printf("\nEl jugador llega a tocar la bola.\n"); // printf para informar que un jugador devuelve la pelota.
		return 0; // devolvemos 0 (nuestro valor para determinar que el jugador no pierde el turno).
	}
	printf("\nEl jugador no llega a tocar la bola\n"); // printf para informar que un jugador no llega a devolver la pelota.
	return 1;
}

int moverse(int pos, int mov){ // función que determina si el usuario ha introducido un valor correcto para situarse.
	if((pos+mov)>9 || (pos+mov)<0 ){ // si es más de nueve o menos de 0, devolvemos 0(false).
		return 0;
	}
	return 1; // si está entre nueve o cero devolvemos 1(true).
}

void escribir_archivo(int finpunto, int bola, int maquina, int puntmaq, int usuario, int puntus){ // función para escribir los datos necesarios para que los procesos se comuniquen entre ellos.
	FILE* archivo = fopen("resultados.txt","w+"); // abrimos el archivo en modo w+.
	if(archivo == NULL){ // si hay algun error al abrir el archivo devolvemos un error.
		perror("\nNo se ha podido abrir el archivo\n");
		exit(EXIT_FAILURE);
	}
	else{
		fprintf(archivo,"%d %d %d %d %d %d",finpunto,bola,maquina,puntmaq,usuario,puntus); // si no hay ningún error, imprimimos los datos necesarios en el archivo.
	}
	fclose(archivo); // cerramos el archivo (previene errores de varios procesos accediendo al archivo "simultáneamente.")
}

void leer_archivo(int* finpunto, int* bola, int* maquina, int* puntmaq, int* usuario, int* puntus){ // función para recuperar los datos necesarios para que los procesos se comuniquen entre ellos.
	FILE* archivo = fopen("resultados.txt","r"); // abrimos el archivo en modo r.
	if(archivo == NULL){ // si hay algun error al abrir el archivo devolvemos un error.
		perror("\nNo se ha podido abrir el archivo\n");
	}
	else{
		fscanf(archivo,"%d %d %d %d %d %d",finpunto,bola,maquina,puntmaq,usuario,puntus); // si no hay ningún error, guardamos los datos necesarios.
	}
	fclose(archivo); // cerramos el archivo (previene errores de varios procesos accediendo al archivo "simultáneamente.")
}

int main(int argc, char** argv){
	int padre = 0, usuario = 0, maquina= 0, posmaq=0, posus=-1, puntmaq=0, puntus=0, bola=-1, finpunto=0, turno= 0, mov=10;

	srand(time(NULL)); // necesario para que la función srand nos devuelvan valores diferentes en cada ejecución.

	if (signal(SIGUSR2, gestion) == SIG_ERR){ // designamos el comportamiento de la señal SIGUSR2, y devolvemos un error si no se ha podido completar.
		perror("Error al crear gestor 2\n");
		exit(EXIT_FAILURE);
	}

	padre=getpid(); // guardamos el pid del padre

	if((maquina = fork()) == -1){ // creamos el primer hijo(máquina), guardamos su PID y devolvemos un error en caso de que no se pueda crear.
		printf("Error al crear la maquina");
		exit(EXIT_FAILURE);
	}
	else if(maquina == 0){ // ACCIONES DEL PROCESO "MAQUINA"
		printf("\nProceso máquina creado, con PID: %d.\n",getpid()); // Mensaje para confirmar que el proceso maquina esta preparado para comenzar.
		pause(); // el proceso máquina espera a que el padre o el usuario les envíe una señal (dependerá si inicia el turno o recibe la pelota del usuario).
		while(puntus<MAX && puntmaq<MAX){ // la máquina está en ejecución mientras el partido no acabe.
			posmaq=rand()%10; // la máquina escoge una posición aleatoria entre 0 y 9
			printf("\nLa máquina se posiciona.\n"); // MENSAJE DE COMPROBACION.
			finpunto = 0; // ponemos finpunto a valor 0 preventivamente, ya que si la máquina empieza un turno debería poder entrar en el bucle del "punto".
			while(finpunto==0){ // bucle en el que la máquina y el usuario se devuelven la pelota.
				leer_archivo(&finpunto,&bola,&maquina,&puntmaq,&usuario,&puntus); // actualizamos la información guardada por la máquina desde el archivo.
				if(finpunto==0){ // en caso de que el usuario no haya perdido:
					if(bola!=-1){ // el usuario no ha perdido y la máquina recibe la pelota.
						finpunto=llegar(bola,posmaq); // evalúa si la máquina es capaz de devolver la pelota o no.
						if(finpunto==1){ // si no es capaz de devolver la pelota(llegar retorna 1), la máquina declara que pierde el punto.
							escribir_archivo(1,-1,maquina,puntmaq,usuario,puntus+1); // actualiza en el archivo que el turno se acaba, y aumenta los puntos del usuario.
							printf("\nLa máquina ha perdido el punto\n"); // MENSAJE DE COMPROBACION.
							kill(usuario,SIGUSR2); // se envía una señal al usuario para que sepa que el turno se acaba y que se prepare para el siguiente turno.
							sleep(1); // damos tiempo al hijo para que se prepare antes de que el padre inicie un nuevo turno.
							kill(padre,SIGUSR2); // enviamos una señal al padre para que gestione quién empieza el nuevo turno, o si se acaba la partida.
							pause();// la máquina espera la siguiente señal del padre o el usuario, depende si empieza turno o no.
							break;// cuando recibe una señal, sale del while actual para que vuelva a entrar en el nuevo punto.
						}
					}
					
					bola=rand()%10; // la máquina lanza la pelota a una posición entre 0 y 9
					// printf("\nLa máquina lanza la bola a la posición %d\n",bola); // MENSAJE DE COMPROBACION
					while(moverse(posmaq,mov)==0){ // pedimos un valor aleatorio hasta que el movimiento sea correcto (quede entre 0 y 9)
						mov=(rand()% (2-(-2)+1))+(-2); // escoge valores entre -2 y 2
					}
					posmaq=posmaq+mov; // actualizamos su nueva posición
					mov=10; // iniciamos mov a 10 para que el while anterior itere la próxima vez que la máquina devuelva la pelota
					// printf("\nLa máquina se mueve a la posición %d\n",posmaq);
					escribir_archivo(0,bola,maquina,puntmaq,usuario,puntus); // la máquina ha tirado, por lo tanto actualiza el archivo.
					kill(usuario,SIGUSR2); // la máquina envía la pelota, y envía una señal al usuario con el archivo ya actualizado para que gestione su propio turno.
					pause(); // la máquina se pausa para que el padre o el hijo les envíe una señal (depende si el usuario pierde el turno o no).
				}
				else{
					escribir_archivo(0,bola,maquina,puntmaq,usuario,puntus); // la máquina recibe que el usuario ha perdido el punto, y actualiza el archivo.
					// printf("\nHe reconocido que el turno se ha acabado. Me pauso y espero a que se inicie un nuevo turno.\n"); // MENSAJE DE COMPROBACION
					pause(); // la máquina se pausa hasta que el padre o el hijo les envíe una señal (depende si empieza turno o no).
					break;
				}
			}
		}
	}
	else{
		if((usuario = fork()) == -1){ // creamos el segundo hijo(usuario), guardamos su PID y devolvemos un error en caso de que no se pueda crear.
			perror("\nError al crear el usuario\n");
			exit(EXIT_FAILURE);
		}
		else if(usuario == 0){ // ACCIONES DEL PROCESO "USUARIO"
			printf("\nProceso usuario creado, con PID: %d\n",getpid()); // Mensaje para confirmar que el proceso usuario esta preparado para comenzar.
			pause(); // el proceso usuario espera a que el padre o la maquina les envíe una señal (dependerá si inicia el turno o recibe la pelota de la máquina).
			finpunto = 0; // ponemos finpunto a valor 0 preventivamente, ya que si el usuario empieza un turno debería poder entrar en el bucle del "punto".
			while(puntus<MAX && puntmaq<MAX){ // el usuario está en ejecución mientras el partido no acabe.
				leer_archivo(&finpunto,&bola,&maquina,&puntmaq,&usuario,&puntus); // actualizamos la información guardada por el usuario desde el archivo.
				posus=-1; // iniciamos la posición del usuario a -1 (valor fuera del intervalo) para que se pueda iterar en el bucle posterior.
				while(posus<0 || posus>9){ // mientras el valor introducido no entre en el intervalo, se le pedirá al usuario dónde se situará.
					printf("\nElige una posición entre 0 y 9: ");
					scanf("%d",&posus);
				}
				while(finpunto==0){ // bucle en el que la máquina y el usuario se devuelven la pelota.
					leer_archivo(&finpunto,&bola,&maquina,&puntmaq,&usuario,&puntus); // actualizamos la información guardada por el usuario desde el archivo.
					if(finpunto==0){ // en caso de que el usuario no haya perdido:
						if(bola!=-1){ // la máquina no ha perdido y el usuario recibe la pelota.
							finpunto=llegar(bola,posus); // evalúa si el usuario es capaz de devolver la pelota o no.
							if(finpunto==1){ // si no es capaz de devolver la pelota(llegar retorna 1), el usuario declara que pierde el punto.
								escribir_archivo(1,-1,maquina,puntmaq+1,usuario,puntus); // actualiza en el archivo que el turno se acaba, y aumenta los puntos de la máquina.
								printf("\nEl usuario ha perdido el punto\n"); // MENSAJE DE COMPROBACION
								kill(maquina,SIGUSR2); // se envía una señal a la máquina para que sepa que el turno se acaba y que se prepare para el siguiente turno.
								sleep(1); // damos tiempo al hijo para que se prepare antes de que el padre inicie un nuevo turno.
								kill(padre,SIGUSR2); // enviamos una señal al padre para que gestione quién empieza el nuevo turno, o si se acaba la partida.
								pause();// el usuario espera la siguiente señal del padre o e la máquina, depende si empieza turno o no.
								break; // cuando recibe una señal, sale del while actual para que vuelva a entrar en el nuevo punto.
							}
						}
						bola=-1; // iniciamos la posición de la bola a un valor incorrecto para que el bucle posterior itere.
						while(bola<0 || bola>9){ // mientras la posición de la pelota sea incorrecta, se le pedirá al usuario que introduzca una posición para la pelota.
							printf("\nElige a que posición mandas la bola entre 0 y 9: ");
							scanf("%d",&bola);
						}
						
						while(moverse(posus,mov)==0){ // mientras la posición que se mueve el jugador sea incorrecta, se le pedirá al usuario que introduzca una posición para moverse después de lanzar la pelota.
							printf("\nElige cuantas posiciones te quieres mover ventre -2 y 2: ");
							scanf("%d",&mov);
						}
						posus=posus+mov; // actualizamos la posición del usuario.
						mov=10; // iniciamos mov a 10 para que el bucle anterior pueda iterar.

						escribir_archivo(0,bola,maquina,puntmaq,usuario,puntus); // el usuario ha tirado, por lo tanto actualiza el archivo.
						kill(maquina,SIGUSR2); // el usuario envía la pelota, y envía una señal a la máquina con el archivo ya actualizado para que gestione su propio turno.
						pause(); // el usuario se pausa para que el padre o el hijo les envíe una señal (depende si la máquina pierde el turno o no).
					}
					else{
						escribir_archivo(0,bola,maquina,puntmaq,usuario,puntus); // el usuario recibe que la máquina ha perdido el punto, y actualiza el archivo.
						// printf("\nHe reconocido que el turno se ha acabado. Me pauso y espero a que se inicie un nuevo turno.\n"); // MENSAJE DE COMPROBACION
						pause(); // el usuario se pausa hasta que el padre o el hijo les envíe una señal (depende si empieza turno o no).
						break;
					}
				}
			}
		}
		else{ // PROCESO PADRE
			sleep(1); // el padre espera a que sus hijos se pausen al inicio del programa.
			escribir_archivo(0,-1,maquina, puntmaq, usuario,puntus); // el padre escribe en el archivo los valores iniciales de cada campo.
			turno = rand()%2; // el padre escoge un número aleatorio entre 0 y 1 para determinar quién inicia el punto.
			if(turno == 0){ // caso de que le toca empezar al usuario
				printf("\nEl usuario, con PID: %d empieza el turno\n",usuario); // mensaje de comprobación
				kill(usuario,SIGUSR2); // enviamos la señal al usuario para que empiece el turno/punto.
			}
			else if (turno == 1){ // caso de que le toca empezar a la máquina.
				printf("\nLa máquina, con PID: %d empieza el turno\n",maquina); // mensaje de comprobación
				kill(maquina,SIGUSR2); // enviamos la señal a la máquina para que empiece el turno/punto.
			}
			while(puntus<MAX && puntmaq<MAX){ // el padre gestiona el partido hasta que uno de los jugadores llega a el máximo (ajustable, en este caso 10) de puntos
				//printf("\nEl padre se pausa dentro del while de los puntos\n"); // MENSAJE DE COMPROBACION
				pause(); // el padre se pausa hasta que los dos hijos están preparados y el hijo perdedor le envía una señal.
				leer_archivo(&finpunto,&bola,&maquina,&puntmaq,&usuario,&puntus); // el padre actualiza los valores de sus variables desde el archivo.
				if(puntmaq==MAX || puntus==MAX){ // if que echa al padre del while (si no, habrían MAX+1 rondas)
					printf("--------maquina: %d usuario: %d-----------",puntmaq,puntus); // imprimimos el marcador antes de finalizar la partida.
					break; // salimos del while
				}
				escribir_archivo(0,-1,maquina, puntmaq, usuario,puntus); // iniciamos finpunto a 0 y posicion_bola a -1

				printf("--------maquina: %d usuario: %d-----------",puntmaq,puntus); // el padre escribe el marcador.
				
				turno = rand()%2; // el padre escoge un hijo aleatorio para que empiece su turno.
				if(turno == 0){
					printf("\nEl usuario, con PID: %d empieza el turno\n",usuario); // mensaje de comprobación
					kill(usuario,SIGUSR2); // enviamos la señal al usuario para que empiece el turno/punto.
				}
				else if (turno == 1){
					printf("\nLa máquina, con PID: %d empieza el turno\n",maquina); // mensaje de comprobación
					kill(maquina,SIGUSR2); // enviamos la señal a la máquina para que empiece el turno/punto.
				}
			}
			if(puntmaq==MAX){ // si el usuario ha sido el que consigue MAX puntos, se imprime el mensaje correspondiente.
				printf("\nFIN DE LA PARTIDA. Ha ganado la maquina\n");
			}
			else if(puntus==MAX){ // si es la máquina la que consigue MAX puntos, se imprime el mensaje correspondiente.
				printf("\nFIN DE LA PARTIDA. Ha ganado el usuario\n");
			}
		}
	}
	return (EXIT_SUCCESS);
}
static void gestion(int numero_de_senhal) { /* Funcion de gestion de señales*/
	switch (numero_de_senhal) {
		case SIGUSR2: /*Entra señal SIGUSR2*/
		printf("\nSeñal recibida. Soy %d\n",getpid()); //Señal SIGURS2. Printf para comprobar que se reciben las señales y reanudar un proceso.
		break;
	}
	return; 
}