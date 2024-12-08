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


int llegar(int bola,int pos){
	if(abs(pos-bola)<=3){
		printf("El jugador llega a la bola.\n");
		return 0;
	}
	printf("El jugador no llega\n");
	return 1;
}

int moverse(int pos, int mov){
	if((pos+mov)>9 || (pos+mov)<0 ){
		return 0;
	}
	return 1;
}

void escribir_archivo(int finpunto, int bola, int maquina, int puntmaq, int usuario, int puntus){
	FILE* archivo = fopen("resultados.txt","w+");
	if(archivo == NULL){
		perror("\nNo se ha podido abrir el archivo\n");
		exit(EXIT_FAILURE);
	}
	else{
		fprintf(archivo,"%d %d %d %d %d %d",finpunto,bola,maquina,puntmaq,usuario,puntus);
	}
	fclose(archivo);
}

void leer_archivo(int* finpunto, int* bola, int* maquina, int* puntmaq, int* usuario, int* puntus){
	FILE* archivo = fopen("resultados.txt","r");
	if(archivo == NULL){
		perror("\nNo se ha podido abrir el archivo\n");
	}
	else{
		fscanf(archivo,"%d %d %d %d %d %d",finpunto,bola,maquina,puntmaq,usuario,puntus);
	}
	fclose(archivo);
}

int main(int argc, char** argv){
	int padre = 0, usuario = 0, maquina= 0, posmaq=0, posus=-1, puntmaq=0, puntus=0, bola=-1, finpunto=0, turno= 0, mov=10;
	srand(time(NULL));

	if (signal(SIGUSR2, gestion) == SIG_ERR){
		printf("Error al crear gestor 2\n");
	}
	padre=getpid();
	if((maquina = fork()) == -1){
		printf("Error al crear la maquina");
		exit(EXIT_FAILURE);
	}
	else if(maquina == 0){ // PROCESO MAQUINA
		printf("\nProceso máquina creado, con PID: %d.\n",getpid());
		pause();
		while(puntus<MAX && puntmaq<MAX){
			posmaq=rand()%10;
			printf("\nLa máquina se posiciona");
			//printf("\nLa máquina se posiciona en a la posición %d\n",posmaq); //PARA COMPROBAR
			finpunto = 0;
			while(finpunto==0){
				leer_archivo(&finpunto,&bola,&maquina,&puntmaq,&usuario,&puntus);
				//ver en que estado acabó el otro jugador
				if(finpunto==0){
					if(bola!=-1){//partida empezada
						finpunto=llegar(bola,posmaq);
						if(finpunto==1){
							escribir_archivo(1,-1,maquina,puntmaq,usuario,puntus+1);
							printf("\nLa máquina ha perdido el punto\n");
							kill(usuario,SIGUSR2);
							sleep(1);
							kill(padre,SIGUSR2);
							pause();
							break;
						}
					}
					
					bola=rand()%10;
					printf("\nLa máquina lanza la bola");
					//printf("\nLa máquina lanza la bola a la posición %d\n",bola); //PARA COMPROBAR
					while(moverse(posmaq,mov)==0){
						mov=(rand()% (2-(-2)+1))+(-2);
					}
					posmaq=posmaq+mov;
					mov=10;
					printf("\nLa máquina se mueve");
					//printf("\nLa máquina se mueve a la posición %d\n",posmaq); //PARA COMPROBAR

					escribir_archivo(0,bola,maquina,puntmaq,usuario,puntus);
					kill(usuario,SIGUSR2);
					pause();
				}
				else{
					//escribir_archivo(0,bola,maquina,puntmaq,usuario,puntus);
					//printf("\nHe reconocido que el turno se ha acabado. Me pauso y espero a que se inicie un nuevo turno.\n"); // PARA COMPROBAR
					pause();
					break;
				}
			}
		}
	}
	else{
		if((usuario = fork()) == -1){
			perror("\nError al crear el usuario\n");
			exit(EXIT_FAILURE);
		}
		else if(usuario == 0){ // PROCESO USUARIO
			printf("\nProceso usuario creado, con PID: %d\n",getpid());
			pause();
			while(puntus<MAX && puntmaq<MAX){
				leer_archivo(&finpunto,&bola,&maquina,&puntmaq,&usuario,&puntus);
				posus=-1;
				while(posus<0 || posus>9){
					printf("\nElige una posición entre 0 y 9: ");
					scanf("%d",&posus);
				}
				while(finpunto==0){
					//ver en que estado acabó el otro jugador
					leer_archivo(&finpunto,&bola,&maquina,&puntmaq,&usuario,&puntus);
					if(finpunto==0){
						if(bola!=-1){
							finpunto=llegar(bola,posus);
							
							if(finpunto==1){
								escribir_archivo(1,-1,maquina,puntmaq+1,usuario,puntus);
								printf("\nEl usuario ha perdido el punto\n");
								kill(maquina,SIGUSR2);
								sleep(1);
								kill(padre,SIGUSR2);
								pause();
								break;
							}
						}
						
						bola=-1;
						while(bola<0 || bola>9){
							printf("\nElige a que posición mandas la bola entre 0 y 9: ");
							scanf("%d",&bola);
						}
						
						while(moverse(posus,mov)==0){
							printf("\nElige cuantas posiciones te quieres mover ventre -2 y 2: ");
							scanf("%d",&mov);
						}
						posus=posus+mov;
						mov=10;

						escribir_archivo(0,bola,maquina,puntmaq,usuario,puntus);
						kill(maquina,SIGUSR2);
						pause();
					}
					else{
						//escribir_archivo(0,bola,maquina,puntmaq,usuario,puntus);
						//printf("\nHe reconocido que el turno se ha acabado. Me pauso y espero a que se inicie un nuevo turno.\n"); //PARA COMMPROBAR
						pause();
						break;
					}
				}
			}
		}
		else{ // PROCESO PADRE
			sleep(1);// Hacemos un fprintf inicial para enviarle a la máquina el PID del usuario.
			escribir_archivo(0,-1,maquina, puntmaq, usuario,puntus);
			turno = rand()%2;
			if(turno == 0){
				printf("\nEl usuario, con PID: %d empieza el turno\n",usuario);
				kill(usuario,SIGUSR2);
			}
			else if (turno == 1){
				printf("\nLa máquina, con PID: %d empieza el turno\n",maquina);
				kill(maquina,SIGUSR2);
			}
			while(puntus<MAX && puntmaq<MAX){
				//printf("\nEl padre se pausa dentro del while de los puntos\n");
				pause();
				leer_archivo(&finpunto,&bola,&maquina,&puntmaq,&usuario,&puntus);
				if(puntmaq==MAX || puntus==MAX){
					printf("--------maquina: %d usuario: %d-----------",puntmaq,puntus);
					break;
				}
				escribir_archivo(0,-1,maquina, puntmaq, usuario,puntus); // iniciamos finpunto a 0
				sleep(1);

				printf("\n--------maquina: %d usuario: %d-----------\n",puntmaq,puntus);
				
				turno = rand()%2;
				if(turno == 0){
					kill(usuario,SIGUSR2);
					printf("\nEl padre ha envidado una señal al usuario.\n");
				}
				else if (turno == 1){
					kill(maquina,SIGUSR2);
					printf("\nEl padre ha envidado una señal a la máquina.\n");
				}
			}
			if(puntmaq==MAX){
				printf("\nFIN DE LA PARTIDA. Ha ganado la maquina\n");
			}
			else if(puntus==MAX){
				printf("\nFIN DE LA PARTIDA. Ha ganado el usuario\n");
			}
		}
	}
	return (EXIT_SUCCESS);
}
static void gestion(int numero_de_senhal) { /* Funcion de gestion de señales*/
	switch (numero_de_senhal) {
		case SIGUSR2: /*Entra señal SIGUSR2*/
		printf("\nSeñal recibida. Soy %d\n",getpid()); 
		break;
	}
	return; 
}