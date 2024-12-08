#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

static void gestion(int); /*Declaracion de la funcion de gestion de señales recibidas*/
int ultima_posicion(int* array, int longitud);

int main(int argc, char** argv) {
  int padre=0, n, hijo=0, *array, estado, resultado;
  if (signal(SIGUSR2,gestion) == SIG_ERR) printf("Error al crear gestor 1\n");
    padre=getpid();
    printf("Introduce cuantos hijos se pueden crear: ");
    scanf("%d",&n);
    array = (int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
      if(getpid()==padre){
        hijo = fork();
        if(hijo==0){
          break;
        }
        if(hijo!=0){
          printf("\n%d guarda en el array.\n",getpid());
          *(array+i)=hijo;
        }
      }
  }
  if(getpid()==padre){
    for(int i=0;i<n;i++){
      printf("\n%d\n",*(array+i));
    }
    waitpid(*(array),&estado,0);
  }
  else{
    pause();
    if(getpid()!=*(array)){
      resultado = ultima_posicion(array,n);
      if(resultado==-1){
        printf("\nError al encontrar la ultima posicion del array del proceso\n");
      }
      else{
        printf("\nEl proceso con PID %d ha sido eliminado\n",*(array+resultado));
        kill(*(array+resultado),SIGKILL);
      }
    }
  }
  return(EXIT_SUCCESS);
}

static void gestion(int numero_de_senhal) { /* Funcion de gestion de señales*/
  switch (numero_de_senhal) {
  case SIGUSR2: /*Entra señal SIGUSR2*/
    printf("\nEl hijo %d ha recibido la senhal SIGUSR2, y llama al hijo anterior para que termine.\n",getpid());
    break;
  }
  return; 
}

int ultima_posicion(int* array, int longitud){
  for(int j=0; j<longitud; j++){
    if(0==(*(array+j))){
      return j-1;
    }
  }
  return -1;
}
