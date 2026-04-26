#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h>

int main() {
    
    pid_t meu_pid = getpid();
    pid_t pid_pai = getppid();

    printf("Olá! Eu sou o processo filho.\n");
    printf("O meu PID é: %d\n", meu_pid);
    printf("O PID do meu processo pai é: %d\n", pid_pai);

    return 0;
} 