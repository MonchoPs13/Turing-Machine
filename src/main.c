#include <stdio.h>
#include "TuringMachine.h"
#include "utils.h"

int main(int argc, char* argv[]) {
  bool running = true;
  do {  
    int num1, num2;
    printf("Ingrese el primer operando: ");
    scanf("%d", &num1);
    printf("Ingrese el segundo operando: ");
    scanf("%d", &num2);

    printf("Realizando la operacion %d x %d\n", num1, num2);

    char* input = create_input(num1, num2);
    TuringMachine* tm = TuringMachine_Create(input);
    printf("Entrada: \n\tc1: %s\n\tc2: %s\n", tm->tapes[0]->string, tm->tapes[1]->string);

    TuringMachine_Run(tm);

    printf("Salida: \n\tc1: %s\n\tc2: %s\n", tm->tapes[0]->string, tm->tapes[1]->string);
    printf("Resultado: %d\n", bin_to_int(tm->tapes[1]->string));
    
    TuringMachine_Destroy(&tm);

    char ans;
    printf("Desea continuar con otro caso? (s/n) ");
    scanf(" %c", &ans);

    if (ans == 'n' || ans == 'N')
      running = false;

  } while (running);

  return 0;
}