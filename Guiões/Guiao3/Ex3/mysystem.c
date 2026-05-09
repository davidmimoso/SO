#include "mysystem.h"


// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem (const char* command) {

	int res = -1;

	char *copia = strdup(command);
    
    char *args[20];
    int i = 0;

    // Retira o primeiro
    args[i] = strtok(copia, " ");
    
    // Ciclo para separar as palavras todas
    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " "); 
    }

    pid_t pid =fork();

        if (pid == -1) {

        } 
        else if (pid == 0) {
                printf("Eu sou o filho e o meu pid é %d e o pid do meu pai é %d\n",getpid(),getppid());
                execvp(args[0],args);

                exit(1);
            }
            else {
                printf("Eu sou o pai ,o meu pid é %d\n",getpid());
                int status;

                wait(&status);

                if(WIFEXITED(status)){
                    res=WEXITSTATUS(status);
                }
            }

            return res;
}