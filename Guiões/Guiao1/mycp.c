#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
      
    if(argc != 3){
        printf("Erro! Uso correto: ./mycp <ficheiro_origem> <ficheiro_destino>\n");
        return 1;
    }
            int fd_origem = open(argv[1], O_RDONLY);

        // Se o bilhete for -1, significa que o ficheiro não existe ou deu erro
        if (fd_origem == -1) {
            perror("Erro ao abrir o ficheiro");
            return 1;
        }

            int fd_destino=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
            if (fd_destino == -1) {
                perror("Erro ao criar o ficheiro de destino");
                return 1;
            }

        char buffer[1024]; 
        int letras_lidas;  

        // Lê do ficheiro (fd) para o balde. Se o número de letras for maior que 0, avança!
        while ((letras_lidas = read(fd_origem, buffer, sizeof(buffer))) > 0) {
            
            // Escreve no ecrã (canal 1) o que está no balde, usando a quantidade certa
            write(fd_destino, buffer, letras_lidas);
            
        }

        close(fd_destino);
        close(fd_origem);
    return 0;
}
    
