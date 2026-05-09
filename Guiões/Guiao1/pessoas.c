#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>   // Para o printf e o perror
#include <string.h>  // Para o strcmp e o strcpy
#include <stdlib.h>  // Para o atoi

    int main(int argc, char* argv[]) {

                    // A estrutura
            typedef struct {
                char nome[100];
                int idade;
            } Pessoa;


                    if(argc < 3){
                        printf("Bem vindo a base de dados, as opções são:\n");
                        printf("(./pessoas -i <Nome> <Idade>) - para adicionar pessoa\n");
                        printf("(./pessoas -l <Indice da lista>) - para ver a lista\n ");
                        printf("(./pessoas -u <Nome> <Idade>) - para atualizar idade\n");
                        printf("Para sair faça (./pessoas 0)\n");
                        
                        return 1; 
                    }


                if(strcmp(argv[1], "-i") == 0){
                    int fd_destino=open("pessoas.bin",O_WRONLY|O_CREAT|O_APPEND,0644);//o 0644 significa posso ler e escrever e o 0600 so o dono do ficheior pode escrever 
                    Pessoa novaPessoa;
                        if (fd_destino == -1) {
                            perror("Erro ao criar o ficheiro de destino");
                            return 1;
                        }

                        else {
                            //strcpy--copia a string
                            strcpy(novaPessoa.nome,argv[2]);

                            //O atoi pega no texto que entregamos e passa pa inteiro
                            novaPessoa.idade=atoi(argv[3]);

                            write(fd_destino,&novaPessoa,sizeof (Pessoa));
                        
                            close (fd_destino);
                            printf("A pessoa '%s' foi inserida com sucesso\n",novaPessoa.nome);
                        }

                }

                

                else if (strcmp(argv[1], "-l") == 0){
                    int quantidade = atoi(argv[2]);
                    Pessoa pessoaLida;

                    //  Abrir o ficheiro  
                    int fd = open("pessoas.bin", O_RDONLY);
                    if (fd == -1) {
                        perror("Erro ao abrir a base de dados");
                        return 1;
                    }

                    for(int i=0;i<quantidade;i++){

                        int lidos = read(fd, &pessoaLida, sizeof(Pessoa));

                // Se nao ler nada acabou
                if (lidos <= 0) {
                    printf("--- Chegámos ao fim do ficheiro! ---\n");
                    break; // O break para o ciclo
                }

                    printf("Pessoa %d : Nome %s  | Idade %d \n",i+1 ,pessoaLida.nome,pessoaLida.idade);
                    }

                }
                else if (strcmp(argv[1], "-u") == 0){
                    
                // 1. Abrir o ficheiro para LER E ESCREVER (O_RDWR)
                        int fd = open("pessoas.bin", O_RDWR);

                        if (fd == -1) {
                            perror("Erro ao abrir a base de dados");
                            return 1;
                        }

                        Pessoa pessoa_lida;
                        int encontrou=0;

                            while(read(fd,&pessoa_lida,sizeof(Pessoa))>0){
                                //Se a pessoa lida bater entra no ciclo
                                    if(strcmp(pessoa_lida.nome,argv[2])==0){
                                        encontrou=1;
                                        //Guarda a idade
                                        pessoa_lida.idade=atoi(argv[3]);

                                        // o lseek vai parar 
                                        // o -sizeof diz que vai andar para tras
                                        //o seek_curl esta a dizer para continuar de onde esta 

                                        lseek(fd,-sizeof(Pessoa),SEEK_CUR);

                                        //escrever por cima

                                        write(fd,&pessoa_lida,sizeof (Pessoa));
                                        printf("A pessoa %s foi alterada com sucesso\n",pessoa_lida.nome);
                                        break;
                                    }
                            }
                                if(encontrou==0){
                                    printf("A pessoa %s nao foi encontrada\n",argv[2]);
                                }
                                

                            
                                close(fd);
                }
     }