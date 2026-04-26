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
                 }          
                             int status;

                            

                                for(int i =0 ; i<10 ; i++){ 
                                    pid_t pid_morto=wait(&status);
                                    if (WIFEXITED(status)) {
                                          printf("O filho com o pid %d morreu e deixou a mensagem %d\n\n", pid_morto, WEXITSTATUS(status));
                                    }
                                    // O WTERMSIG(status) extrai do relatório o número do Sinal 
                                    // que forçou o processo filho a terminar.
                                    else{printf("O filho %d foi morto a força (Sinal: %d)\n",pid_morto, WTERMSIG(status));}

                        
                                }    
                            
                            
                            
                 

                        return 0;
        }
                


           