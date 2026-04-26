#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h> 

#define Linhas 10
#define Colunas 1000

int main (int argc, char *argv[]) {

            if (argc < 2) {
        printf("Erro: Tens de dizer qual o nuumero a procurar!-->./<nome do ficheiro> <numero>\n");
        return 1;
    }

    int alvo = atoi(argv[1]);


    int matriz[Linhas][Colunas];

                    // Temos de criar uma matriz aleatoria

                    for(int l=0;l<Linhas;l++){
                        for(int c=0;c<Colunas;c++){
                            matriz[l][c]=rand() % 100;// Gera um numero de 0 a 99
                        }
                    }

                    pid_t pidFilhos[Linhas];
            for(int l=0 ; l<Linhas ; l++){

                pid_t pid = fork();
                pidFilhos[l]=pid;

                    if(pid==0){

                        //cenas do filho
                        printf("Ola eu sou o filho %d o meu pid é: %d e o pid do meu pai é %d\n",l,getpid(),getppid());

                    
                
                        for(int c=0 ; c<Colunas ;c++){

                                if(matriz[l][c]==alvo){
                                    _exit(1);//sucesso
                                }   
                        }
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
