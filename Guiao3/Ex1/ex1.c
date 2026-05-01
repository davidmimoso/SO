#include <unistd.h> // Para usar o exec
#include <stdio.h>  // Para usar o printf

int main() {
    
   printf("Inicio:Vai transformar em ls -l \n");

   execlp("ls","ls","-l",NULL);

   printf("se apareceu esta mensagem nao funcionou \n");

    return 0;
}

