#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

static void gestion(int);

int main(int argc, char** argv){
	int padre,hijo1,hijo2,estado, miembro, pendientes;
	double overhead, t;
	struct sigaction act;
	sigset_t set;
    struct timeval inicio,tiempo;

	//medimos el tiempo inicial
	gettimeofday(&inicio,NULL);
    gettimeofday(&tiempo,NULL);

	//calculamos el overhead de la medición de tiempo
    overhead = (tiempo.tv_sec-inicio.tv_sec + (tiempo.tv_usec-inicio.tv_usec)/1.e6);

	//configuramos la acción de ignorar señales para SIGINT con SA_RESTART
	act.sa_handler=SIG_IGN; //configuramos el manejador para ignorar la señal
	act.sa_flags=SA_RESTART;

	//configuramos el gestor de señales para las señales SIGUSR1 y SIGUSR2
	if (signal(SIGUSR1, gestion) == SIG_ERR){
		printf("Error al crear gestor 1\n");
	}
	if (signal(SIGUSR2, gestion) == SIG_ERR){
		printf("Error al crear gestor 1\n");
	}

	padre=getpid(); //guardamos el PID del padre

	//creamos el proceso hijo1
	if((hijo1 = fork()) == -1){
		printf("Error al crear el hijo 1");
	}
	else if(hijo1 == 0){ //PROCESO HIJO1
		printf("Soy el hijo 1, con PID %d. \n", getpid());

		kill(padre,SIGUSR1); //envía la señal SIGUSR1 al proceso padre

		//medimos el tiempo
		gettimeofday(&tiempo,NULL);
        t = (tiempo.tv_sec-inicio.tv_sec + (tiempo.tv_usec-inicio.tv_usec)/1.e6);
        t=t-overhead;
		printf("Soy el hijo 1, y he tardado %.15f en mandar la señal SIGUSR1.\n",t);

		sleep(20);

		kill(padre,SIGUSR2); //envía la señal SIGUSR2 al proceso padre

		//medimos el tiempo
		gettimeofday(&tiempo,NULL);
        t = (tiempo.tv_sec-inicio.tv_sec + (tiempo.tv_usec-inicio.tv_usec)/1.e6);
        t=t-overhead;
		printf("Soy el hijo 1, y he tardado %.15f en mandar la señal SIGUSR2.\n",t);

		sleep(20);

		//medimos el tiempo
		gettimeofday(&tiempo,NULL);
        t = (tiempo.tv_sec-inicio.tv_sec + (tiempo.tv_usec-inicio.tv_usec)/1.e6);
        t=t-overhead;
		printf("Soy el hijo1, y he tardado %.15f en finalizar.\n",t);

		exit(0); //termina el hijo1
	}
	else{
		//creamos el proceso hijo2
		if((hijo2 = fork()) == -1){
			printf("Error al crear el hijo 2");
		}
		else if(hijo2 == 0){ //PROCESO HIJO2
			sleep(5);
			printf("Soy el hijo 2, con PID %d.\n", getpid());

			kill(padre,SIGINT); //envía la señal SIGINT al proceso padre

			//medimos el tiempo
			gettimeofday(&tiempo,NULL);
			t = (tiempo.tv_sec-inicio.tv_sec + (tiempo.tv_usec-inicio.tv_usec)/1.e6);
			t=t-overhead;
			printf("Soy el hijo2, y he tardado %.15f en mandar la señal SIGINT.\n",t);
		}
	}

	if(hijo2!=0){ //PROCESO PADRE

		sigaction(SIGINT,&act,NULL); //ignorar la señal SIGINT
		sigaddset(&set, SIGUSR1); //añadimoa SIGUSR1 al conjunto de señales bloqueadas
		sigprocmask(SIG_BLOCK,&set,NULL); //bloqueamos la señal SIGUSR1

		//medimos el tiemepo
		gettimeofday(&tiempo,NULL);
        t = (tiempo.tv_sec-inicio.tv_sec + (tiempo.tv_usec-inicio.tv_usec)/1.e6);
        t=t-overhead;
		printf("Soy el padre, y he tardado %.15f en prepararme para bloquear la señal SIGUSR1.\n",t);

		sleep(1);
		if((pendientes=sigpending(&set))== -1){  //comprobamos que SIGUSR1 esta en el conjunto de señales pendientes
			printf("Error en la señal SIGUSR1 al ponerla en pendiente.\n");
		}

		if((miembro=sigismember(&set,SIGUSR1))==1){ //comprobamos que SIGUSR1 esta en el conjunto de señales pendientes
			printf("La señas SIGUSR1 está pendiente.\n");
		}
		if(miembro==0){
			printf("La señas SIGUSR1 no está en la lista de pendientes.\n");
		}
		if(miembro==-1){
			printf("Error en la señal SIGUSR1 al ponerla en pendiente.\n");
		}
		sleep(22);

		sigprocmask(SIG_UNBLOCK,&set,NULL); //desbloqueamos la señal SIGUSR1

		//medimos el tiempo
		gettimeofday(&tiempo,NULL);
        t = (tiempo.tv_sec-inicio.tv_sec + (tiempo.tv_usec-inicio.tv_usec)/1.e6);
        t=t-overhead;
		printf("Soy el padre, y he tardado %.15f en desbloquear la señal SIGUSR1.\n",t);

		//esperamos a que hijo1 termine y obtenemos su código de salida
		waitpid(hijo1,&estado,0);
		printf("El código de salida del hijo 1 es: %d\n",estado);
	}

	return (EXIT_SUCCESS);
}
static void gestion(int numero_de_senhal) { /* Funcion de gestion de señales*/
	switch (numero_de_senhal) {
		case SIGUSR1: /*Entra señal SIGUSR1*/
		printf("Señal 1 enviada. Soy %d\n",getpid()); 
		break;
		case SIGUSR2: /*Entra señal SIGUSR2*/
		printf("Señal 2 enviada. Soy %d\n",getpid()); 
		break;
	}
	return; 
}
