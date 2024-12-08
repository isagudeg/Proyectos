#include <stdio.h>
#include <math.h> // Para funciones matemáticas como sin, cos, sqrt

int main() {
    double a = 0.5, b = 2.3, resultado = 0.0;
    float x = 1.1f, y = 3.7f, resultado_f = 0.0f;

    // Bucle con muchas iteraciones
    for (long long int i = 0; i < 1000000000; i++) {
        // Operaciones con double
        resultado += sin(a) * cos(b) + sqrt(a * b);

        // Operaciones con float
        resultado_f += (x * x) - (y * y) + (x / y);

        // Cambiar ligeramente los valores para que el trabajo sea variado
        a += 0.000001;
        b -= 0.000001;
        x += 0.00001f;
        y -= 0.00001f;
    }

    // Mostrar los resultados al final
    printf("Resultado final double: %lf\n", resultado);
    printf("Resultado final float: %f\n", resultado_f);

    return 0;
}
