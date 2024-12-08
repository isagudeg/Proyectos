/*
 * PROGRAMA PARA CALCULAR LA RAÍZ CUADRADA Y EL MÁXIMO COMÚN DIVISOR DE DOS NÚMEROS ENTEROS
 * PEDIDOS AL USUARIO/A POR TECLADO.
 *
 * OBJETIVO: DEPURAR USANDO LAS HERRAMIENTAS DE VS CODE. 
 * EL PROGRAMA TIENE COMO MÍNIMO SEIS ERRORES. DOCUMENTAR LAS CORRECCIONES 
 * INTRODUCIDAS, PONIENDO UN COMENTARIO CON LA SENTENCIA INCORRECTA AL
 * LADO DE LA SENTENCIA CORREGIDA
 * 
 * PRUEBAS: USAR LOS SIGUIENTES CASOS PASANDOLOS TANTO COMO ARGUMENTOS COMO DEJANDO QUE EL PROGRAMA PIDA LOS VALORES
 * 10 2 (sqrt=3.162278, gcd=2)
 * 2 10 (sqrt=1.414214, gcd=2)
 * 49 7 (sqrt=7., gcd=7)
 * -5 1 (sqrt no existe por ser negativo, gcd=1)
 * -5 -3 (sqrt no existe por ser negativo, gcd=1)
 * 3 0  (sqrt=1.732051, gcd=3)
 * 0 10 (sqrt=0.000977, gcd=10) // La raíz cuadrada de 0 es 0, pero el método de Newton es un método estimado. Podéis comprobarlo jugando con el parámetro margen
 * 0 0 (sqrt=0.000977, gcd=0)
 */

/* a) Corregir los errores comentando la línea incorrecta y poniendo la incorrecta a continuación
 * b) Fija un breakpoint e inicia la ejecución en modo depuración ¿Qué sucede al ejecutar paso a paso
 *    (botón “Step into” [F11]) la sentencia donde se invoca la función sqrt()?
 *    RESPUESTA: 
 * 
 * c) Al llegar a la función sqrt(), utiliza el botón “STEP OVER” [F10]  en  lugar  del  botón  “Step into” [F11]
 *   ¿Qué  diferencias observas frente a la ejecución del apartado b?
 *   RESPUESTA: 
 * 
 * d) Repite la ejecución en modo depuración visualizando todas las variables. 
 *    Indica qué sucede con la ventana de variables cuando el flujo del programa continúa DENTRO de la función
 *    Justifica la información que aparece en la solapa "Call Stack"
 *    RESPUESTA:
 * 
 * */

#include <stdio.h>
#include <stdlib.h>
#include "operaciones.h"

int main(int argc, char** argv) {

    int a, b;
    float s;
    float g;
    
    if (argc == 0){
        printf("Introduce dos números enteros: ");
        scanf("%f%d", a, &b);
    } else {
        a = argv[0];
        b = argv[1];
    }
    
    if (a > 0){
        s = sqrt(a);
        printf("Raíz cuadrada(%d) = %f\n", a, s);
    }else{
        printf("Error raíz: el parámetro (%d) no es un entero positivo\n", a);
    }
        
    g = gcd(a, b);
    printf("Máximo común divisor(%f,%d) = %f\n", a, b, g);
    
    return (EXIT_SUCCESS);
}

