/*
  Octavio Garduza
  A01021660

  Actividad 4

  Implementación de un programa que crea n hijos del mismo padre, espera a
  que los hijos terminen en el mismo orden en el que fueron creados y guarda el
  valor de retorno (promedio PPID y PID) para después imprimir una tabla
  PID | PROMEDIO | HISTOGRAMA.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

//Aquí se almacena la info de cada proceso
typedef struct{
  pid_t pid;
  float avg;
}process;

//Auxiliar para impresión de la info de los procesos
void print_process_table(process *process_list_head, process *process_list_tail);

int main(int argc, char* const *argv) {

    pid_t pid;

    process *process_list_head;
    process *process_list_tail;

    int estado;
    int c; //Aux para almacenar cada opt en argv
    int nvalue = 1; //Default 1 (sin argumento -n)
    int succesful_process = 0;

    double avg;

    //Mientras existan chars en argv
    while ((c = getopt (argc, argv, "n:")) != -1){
      if(c == 'n'){//Exito
        nvalue = atoi(optarg);//Asegura que el argumento es un int
      }else if(c == '?'){//Errores
        if (optopt == 'n')
          fprintf(stderr, "Opción -%c requiere un argumento.\n", optopt);
        else if(isprint(optopt))
          fprintf(stderr, "Opción desconocida '-%c'.\n", optopt);
        else
          fprintf(stderr, "Opción desconocida '\\x%x'.\n", optopt);
        return 1;
      }
      else{
        abort();
      }
    }

    //Por cada arg invalido pasado
    for (int index = optind; index < argc; index++){
      printf ("El argumento no es una opción válida %s\n", argv[index]);
      return(1);
    }

    //Si nvalue no es int o es menor/igual a 0
    if(nvalue <= 0){
      printf ("El valor de -n debe ser un int mayor a 0\n");
      return(1);
    }

    process_list_head = (process *) malloc(nvalue * sizeof(process));
    process_list_tail = process_list_head + nvalue;

    printf("\n\nProceso padre: %d\n\n", getpid());

    //Crea n procesos
    for(process *aux = process_list_head; aux < process_list_tail; ++aux){
      pid = fork();
      //Ambos procesos ejecutan
      aux->pid = pid;
      if(pid == -1){//Error
        printf("Error al crear el proceso hijo\n");
        break; //No crea el resto de los procesos
      }
      else if(pid == 0){//Hijo
        avg = (getpid() + getppid())/2.0;
        printf("Soy el proceso hijo con PID = %d y mi promedio es = %.2f\n", getpid(), avg);
        return(avg);//Solo regresa los primeros 8 bits
      }
      else{//Padre
        succesful_process++;
      }
    }
    //Unicamente el padre ejecuta
    //Espera a que cada proceso termine
    for(process *aux = process_list_head; aux < process_list_tail; ++aux){
      if (waitpid(aux->pid, &estado, 0) != -1)
       {
         if (WIFEXITED(estado)){
           aux->avg = WEXITSTATUS(estado); //Return de cada proceso hijo
         }
       }
    }

    printf("\nSe crearon %d/%d procesos de forma exitosa\n\n", succesful_process, nvalue);
    print_process_table(process_list_head, process_list_tail);

    free(process_list_head); //Liberar memoria

    return 0;

}//Fin de main


/*
 * Function:  print_process_table
 * --------------------
 * Itera la lista de procesos creados e imprime una table con los datos:
 * PID HIJO | PROMEDIO | HISTOGRAMA de procesos.
 *
 *  process_list_head: Apuntador al elemento inicial de la lista de procesos.
 *  process_list_tail: Apuntador al elemento final de la lista de procesos
 *
 */
void print_process_table(process *process_list_head, process *process_list_tail){
  printf("PID HIJO:             PROMEDIO:             HISTOGRAMA (* = 10):\n");
  printf("-------------------------------------------------------------------------------\n");
  for(process *aux = process_list_head; aux < process_list_tail; ++aux){
    printf("%d                  %.2f                ", aux->pid, aux->avg);
    for(int i = 0; i<ceil((aux->avg)/10); ++i){
      printf("*");
    }
    printf("\n-------------------------------------------------------------------------------\n");
  }
  printf("\n\n");
}
