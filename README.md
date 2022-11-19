# Instrucciones de ejecución

- Compilar programa:
```
$> make
```

- Ejecutar programa:
```
$> ./Ent2 <instancia>
```

Ejemplo:
```
$> ./Ent2 instancia/InstanceBEP-1-4-2-4.txt
```

- Limpiar archivos de compilado y ejecutable:
```
$> make clean
```

# Datos adicionales en output

Si bien durante esta entrega, el objetivo del codigo es recibir y almacenar las instancias, se han dejado dos bloques de codigos comentados (**Print instanciación** y **Print solución inicial**) que permiten verificar el almacenamiento de las variables, asi como entregar la solución inicial encontrada mediante el uso de la heuristica mencionada en el documento .pdf relacionado a esta entrega. En las funciones **InitInstance** y **InitFeasibleSolution** respectivamente, en el archivo _functions.cpp_.