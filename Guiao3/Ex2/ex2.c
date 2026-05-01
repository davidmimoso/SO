#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h> //para o wait

int main() {
    
    printf("Sou o Pai (PID: %d) e vou criar um filho...\n", getpid());

    pid_t pid = fork(); 

    if (pid == -1) {
       
        perror("Erro no fork");
        return 1;
    } 
    else if (pid == 0) {
        printf("Sou o Filho (PID: %d). Vou transformar-me no ls -l!\n", getpid());
        
        execlp("ls","ls","-l",NULL);
        
        
        
        printf("Se vires isto, o exec falhou no filho!\n");
        _exit(1); // Usamos _exit no filho para ele morrer de vez se der erro
    } 
    else {
        
        printf("Sou o Pai. Vou esperar que o meu filho acabe de listar os ficheiros...\n");
        
        wait(NULL);
        
        
        printf("Sou o Pai. O meu filho já foi à vida. O meu programa sobreviveu!\n");
    }

    return 0;
}