# Instrucciones de ejecución

- Compilar programa:
```
$> make
```

- Ejecutar programa:
```
$> ./main <instancia> <q> <tmax> <qt> <qm>
```

- Parametros:
  - El parametro <instancia> es la ruta del archivo .txt que contiene la instancia del problema a evaluar.
  - \<q\> : temperatura inicial del S.A.
  - \<tmax\> : máximo de iteraciones.
  - \<qt\> : Velocidad de cambio de la temperatura.
  - \<qm\> : Magnitud de cambio de la temperatura.


Ejemplo:
```
$> ./main instances/InstanceBEP-1-4-2-4.txt 100 10000 1 5
```

- Limpiar archivos de compilado y ejecutable:
```
$> make clean
```

# Datos adicionales del Output
Se imprime el tiempo de evacuación conseguido en la Solución inicial, como comparación con el resultado final conseguido por Simulated Annealing.

