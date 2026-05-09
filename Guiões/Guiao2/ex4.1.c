#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>   // Para o printf e o perror
#include <string.h>  // Para o strcmp e o strcpy
#include <stdlib.h>  // Para o atoi

    int main(int argc, char* argv[]) {

        int Linhas=100;
        int Colunas=1000;
        int Salto=0;

             if (argc < 2) {
                printf("Erro: Tens de dizer qual o nuumero a procurar!-->./<nome do ficheiro> <numero>\n");
                return 1;
            }

                int alvo = atoi(argv[1]);


                    int fd_destino=open("matriz.bin",O_WRONLY|O_CREAT,0666);
                        if (fd_destino == -1) {
                            perror("Erro ao criar o ficheiro de destino");
                            return 1;
                        }

                        int matriz[Linhas][Colunas];


                    for(int l=0;l<Linhas;l++){
                        for(int c=0;c<Colunas;c++){
                            matriz[l][c]=rand() % 1000;// Gera um numero de 0 a 99
                        }
                    }    

                    write(fd_destino,&matriz,sizeof (matriz));
                    close(fd_destino);

                    pid_t pidFilhos[Linhas];
                    for(int l=0 ; l<Linhas ; l++){

                        pid_t pid = fork();
                        if(pid>0){
                            pidFilhos[l]=pid;
                        }

                        if(pid==0){

                               int fd_leitura = open("matriz.bin", O_RDONLY);

                                Salto=l* Colunas*sizeof(int);
                                
                                lseek(fd_leitura,Salto,SEEK_SET);

                                int minhaLinha[Colunas];

                                read(fd_leitura, minhaLinha, sizeof(minhaLinha));

                                    for(int c=0 ; c<Colunas ;c++){

                                            if(minhaLinha[c]==alvo){
                                                close (fd_leitura);
                                                _exit(1);//sucesso
                                            }   
                                    }
                                    close (fd_leitura);
                                _exit(0);//falhou    
                        }


                     }  
                for(int i=0;i<Linhas;i++){
                    int status;
                    pid_t pidFilho = waitpid(pidFilhos[i],&status,0);

                    if(WIFEXITED(status)){
                        int result = WEXITSTATUS(status);// vai buscar o resultado que deu o exit 

                        if(result==1){
                            printf("O filho %d com id %d encontrou correspondencia na linha\n",i,pidFilho);
                        }
                        else {printf("O filho %d com pid %d nao encontrou nada\n",i,pidFilho);}
                    }

                }

                printf("FIM DO PROGAMA\n");
                return 0;


     }
                                    