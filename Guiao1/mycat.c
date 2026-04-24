#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


/* int main() {
    char buffer[100]; 
    int bytes_lidos;

    while ((bytes_lidos = read(0, buffer, 100)) > 0) {
        write(1, buffer, bytes_lidos);
    }

    return 0;
} */


int main(int argc, char *argv[]) {
        // tem de ter tamanho 2 pois o "./mycat" ja conta como 1 e nao pode ter mais que 1 ficheiro
        if (argc != 2) {
            printf("Erro! Uso correto: ./mycat <nome_do_ficheiro>\n");
            return 1; 
        }

        // Abre o ficheiro e guarda o número do bilhete na variável 'fd'||-RDONLY->so ler
        int fd = open(argv[1], O_RDONLY);

        // Se o bilhete for -1, significa que o ficheiro não existe ou deu erro
        if (fd == -1) {
            perror("Erro ao abrir o ficheiro");
            return 1;
        }

        char buffer[1024]; //balde
        int letras_lidas;  //letras lidas

        //Lê o ficheiro e se o número de letras for maior que 0, avança!
        while ((letras_lidas = read(fd, buffer, sizeof(buffer))) > 0) {
            
            // Escreve no ecrã (canal 1) o que está no balde, usando a quantidade certa
            write(1, buffer, letras_lidas);
            
        }

        close(fd);
    return 0;
}