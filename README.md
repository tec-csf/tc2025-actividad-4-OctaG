### Demo de Fork() y argumentos cortos

Implementación en c de un programa que utiliza estructuras, apuntadores, fork() y argumentos cortos para:

- crear *n* procesos hijos a partir del mismo padre.
- esperar a que los hijos terminen su procesamiento en el mismo orden en el que fueron creados.
- guardar el valor de retorno (promedio de PPID y PID) en un arreglo dinámico.
- regresar el valor de retorno al proceso padre.
- imprimir una tabla PID | PROMEDIO | HISTOGRAMA.

#### Correr el demo

A través de la terminal:
1. gcc main.c
2. ./a.out -n [número de procesos hijos a crear]

Si no se le pasa el parámetro *-n* se crea únicamente un proceso por default.

#### Creación de los *n* procesos hijos

###### Estructura process

La estructura ```process``` almacena la información de cada proceso hijo creado:

```C
typedef struct{
  pid_t pid;
  float avg;
}process;
```

Los procesos creados se almacenan en un arreglo dinámico:
```C
process *process_list_head = (process *) malloc(cvalue * sizeof(process));
process *process_list_tail = process_list_head + cvalue;
```

###### Procesos hijos
Dentro de cada proceso hijo se:
- obtiene el promedio del PID y PPID
- imprime "Soy el proceso hijo con PID = $PID y mi promedio es = $PROMEDIO
- regresa el promedio al proceso padre

###### Proceso padre
En el proceso padre se:
- espera a que terminen todos los procesos hijos en el mismo orden en que se crearon.
- almacena el valor de retorno de cada proceso en la estructura correspondiente del arreglo dinámico.
- se imprime la tabla PID | PROMEDIO | HISTOGRAMA.

#### Impresión de la tabla PID | PROMEDIO | HISTOGRAMA.
Itera la lista de procesos creados e imprime una table con los datos de la estructura.
El histograma lo calcula a partir de ```avg / 10```.

```C
void print_process_table(process *process_list_head, process *process_list_tail){}
```
