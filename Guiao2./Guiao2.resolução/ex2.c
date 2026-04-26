#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> // Para o wait()

int main() {
    printf("Vou criar um processo filho...\n\n");
    
    // O fork() cria o processo filho e devolve o valor para a variável pid
    pid_t pid = fork(); 

    if (pid == 0) {
        // --- CÓDIGO DO PROCESSO FILHO ---
        // Como o pid é 0, sabemos que estamos no filho
        printf("[FILHO] Olá! Eu sou o Filho.\n");
        printf("[FILHO] O meu PID é: %d\n", getpid());
        printf("[FILHO] O PID do meu Pai é: %d\n\n", getppid());
        
        // O filho termina a sua execução aqui
        _exit(0); 
        
    } else if (pid > 0) {
        // --- CÓDIGO DO PROCESSO PAI ---
        // Como o pid é maior que 0 (é o PID do filho), sabemos que estamos no pai
        printf("[PAI] Olá! Eu sou o Pai.\n");
        printf("[PAI] O meu PID é: %d\n", getpid());
        printf("[PAI] O PID do meu Pai (a shell) é: %d\n", getppid());
        printf("[PAI] O PID do meu filho recém-criado é: %d\n\n", pid);
        
        // O pai espera que o filho termine antes de fechar (boa prática!)
        int status;
        wait(&status); 
        
    } else {
        // Se o fork devolveu -1, houve um erro
        perror("Erro ao fazer o fork");
        return 1;
    }

    return 0;
}