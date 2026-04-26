#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// Definimos o caminho onde o tubo vai ser criado no teu disco
#define FIFO_PATH "/tmp/fifo_so_projeto"

int main(int argc, char *argv[]) {
    printf("[CONTROLLER] A arrancar...\n");
    
    // 1. Criar o tubo (FIFO). O 0666 dá permissões de leitura/escrita a toda a gente
    mkfifo(FIFO_PATH, 0666);
    
    printf("[CONTROLLER] À espera de pedidos no guichet...\n");

    // 2. Abrir o tubo APENAS para LER (O_RDONLY). 
    // O programa vai bloquear nesta linha até alguém abrir o tubo do outro lado para escrever!
    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir FIFO");
        return 1;
    }

    // 3. Ler o que vier do tubo
    char buffer[100];
    int bytes_lidos = read(fd, buffer, sizeof(buffer) - 1);

    if (bytes_lidos > 0) {
        buffer[bytes_lidos] = '\0'; // Colocar um ponto final na mensagem (string)
        printf("[CONTROLLER] Recebi a seguinte mensagem: %s\n", buffer);
    }

    // 4. Fechar a nossa ponta do tubo
    close(fd);

    return 0;
}