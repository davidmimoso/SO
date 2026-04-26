#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_PATH "/tmp/fifo_so_projeto"

int main(int argc, char *argv[]) {
    printf("[RUNNER] A arrancar...\n");

    // 1. Abrir o tubo APENAS para ESCREVER (O_WRONLY)
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("Erro ao abrir o FIFO. O Controller está ligado?");
        return 1;
    }

    // 2. Preparar a nossa mensagem de teste
    char mensagem[] = "Olá Chefe! O utilizador 1 quer executar um comando!";

    // 3. Escrever a mensagem para dentro do tubo
    write(fd, mensagem, strlen(mensagem));
    printf("[RUNNER] Mensagem enviada pelo tubo!\n");

    // 4. Fechar a nossa ponta do tubo
    close(fd);

    return 0;
}