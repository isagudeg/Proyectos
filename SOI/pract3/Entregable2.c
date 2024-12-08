#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

static void gestion(int); /*Declaracion de la funcion de gestion de señales recibidas*/
int ultima_posicion(int* array, int longitud); // funcion que obtiene la posicion del ultimo elemento.

int main(int argc, char** argv) {
  int padre=0, n, hijo=0, *array, estado, resultado;
  if (signal(SIGUSR2,gestion) == SIG_ERR) printf("Error al crear gestor 2\n"); // cambiamos el comportamiento de la señal SIGUSR2, y devolvemos un error si no se ha podido crear.
  padre=getpid(); // guardamos el pid del padre
  printf("Introduce cuantos hijos se pueden crear: ");
  scanf("%d",&n); // preguntamos cuantos hijos se crean
  array = (int*)malloc(n*sizeof(int)); // reservamos un array dinamico de longitud n (tanta longitud como hijos se pidan)
  for(int i=0;i<n;i++){// bucle for en el que el padre crea nuevos hijos
    if(getpid()==padre){ // si el proceso es el padre
      hijo = fork(); // si el proceso es el padre, crea un nuevo hijo
      if(hijo==0){ // el hijo inmediatamente abandona le bucle for
        break;
      }
      if(hijo!=0){ // el padre guarda el pid del hijo en su posición correspondiente en el array.
        printf("\n%d guarda en el array.\n",getpid());
        *(array+i)=hijo;
        // AVISO: UTILIZANDO ESTE ARRAY DINAMICO, CADA HIJO SOLAMENTE ALMACENA LOS PIDS DE SUS HERMANOS MAYORES (ANTERIORES)
        // LO CUAL SE AJUSTA A NUESTRO PROBLEMA, EN EL QUE SOLAMENTE NECESITAMOS SABER EL PID DEL HERMANO INMEDIATAMENTE MAYOR (O INMEDIATAMENTE ANTERIOR)
        // POSTERIORMENTE, CON LA FUNCION ULTIMA_POSICION CADA HIJO SERA CAPAZ DE CONOCER EL PID DE SU HERMANO INMEDIATAMENTE ANTERIOR
      }
    }
  }
  if(getpid()==padre){ // si es el proceso padre
    // AVISO. LAS SIGUIENTES AYUDAN A SABER LOS PID DE LOS HIJOS DEL PROCESO
    printf("\nSe imprimirá por pantalla los pids de todos los hijos. PRINTF MERAMENTE COMPROBATIVO\n");
    for(int i=0;i<n;i++){ // se imprime el array completo para comprobar que se han almacenado los hijos correctamente.
      printf("\n%d\n",*(array+i));
    }
    waitpid(*(array),&estado,0); // y se espera a que finalice el primer hijo (el que ocupa la primera posicion del array).
  }
  else{
    pause(); // cada proceso se pausa, hasta que les llega una señal (en este caso continúan normalmente si reciben SIGUSR2)
    if(getpid()!=*(array)){ // se comprueba que no se haya enviado una señal al primer hijo (ya que este no puede eliminar a su hermano anterior, ya que no tiene).
      resultado = ultima_posicion(array,n); // guardamos la posicion en la que se encuentra el hermano inmmediatamente anterior.
      if(resultado==-1){ // devolvemos un error si no se encuentra la ultima posicion
        printf("\nError al encontrar la ultima posicion del array del proceso\n");
      }
      else{ // avisamos de que vamos a eliminar al hermano inmediatamente anterior
        printf("\nEl proceso con PID %d ha sido eliminado\n",*(array+resultado));
        // enviamos una señal que termina al hermano inmediatamente anterior
        kill(*(array+resultado),SIGKILL);
      }
    }
  }
  return(EXIT_SUCCESS);
}

static void gestion(int numero_de_senhal) { /* Funcion de gestion de señales*/
  switch (numero_de_senhal) {
  case SIGUSR2: /*Entra señal SIGUSR1*/
    printf("\nEl hijo %d ha recibido la senhal SIGUSR2, y llama al hijo anterior para que termine.\n",getpid());
    break;
  }
  return; 
}

int ultima_posicion(int* array, int longitud){ // función que encuentra la posición del ultimo valor distinto de cero.
  // AVISO: ESTA FUNCION SE BASA EN QUE CADA PROCESO ALMACENA UNICAMENTE EN EL ARRAY DINAMICO SUS HERMANOS ANTERIORES A EL.
  // A PARTIR DE SU HERMANO INMEDIATAMENTE ANTERIOR, EN EL ARRAY DE CADA PROCESO SOLO SE ALMACENAN CEROS.
  // POR LO TANTO, PARA CADA PROCESO SE CONOCE LA POSICION DEL ARRAY DE SU HERMANO INMEDIATAMENTE ANTERIOR COMPROBANDO EN QUE POSICION ESTA EL ULTIMO VALOR DISTINTO DE CERO.
  for(int j=0; j<longitud; j++){
    if(0==(*(array+j))){
      return j-1; // devolvemos la ultima posicion con un valor distinto de cero
    }
  }
  return -1; // devolvemos -1 como valor que indica un error.
}
