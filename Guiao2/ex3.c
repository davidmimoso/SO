#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>


        int main (){


                for(int i = 0;i<10;i++){

                     pid_t pid = fork();

                        if(pid==0){
                            //Imprime as cenas do filho
                            printf("Olá eu sou o filho %d o meu pid é: %d e o do meu pai é: %d\n",i,getpid(),getppid());
                            
                            _exit(i);    

                        }
                        else if(pid>0){
                            int status;

                            wait(&status);
                            
                            // WIFEXITED(status): Verifica se o filho terminou de forma "natural" (chegou ao fim ou chamou _exit). Devolve Verdadeiro 
                            //se a morte foi natural,com o _exit() ou Falso.
                            if(WIFEXITED(status)){
                                //// WEXITSTATUS(status): Vai buscar o número exato que o filho enviou dentro do _exit() 
                                //(neste caso, o nosso número 'i'). Só deve ser usada se o WIFEXITED for verdadeiro
                                printf("Ola eu sou o pai o meu pid é: %d e o pid do meu filho é: %d e terminou com o numero:%d \n\n",getppid(),getpid(),WEXITSTATUS(status));
                            }
                        }


                }
                return 0;


        }    