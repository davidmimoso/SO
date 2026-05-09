#include <stdio.h>
#include "mysystem.h"

void controller(int N, char** commands) {

	int ciclos[N];
	pid_t pid[N];
	
	for(int i =0;i<N;i++){
			ciclos[i]=1;

			pid[i]=fork();

			if(pid[i]==0){
				execlp(commands[i],commands[i],NULL);
				exit(1);

			}

	}

	//Ciclo do pai 
	int terminados=0 ;

	while(terminados<N){
		int status;
		pid_t pid_terminados = wait(&status);
		int i_do_filho= -1;
		for(int j=0;j<N;j++){

			if(pid[j]==pid_terminados){
				i_do_filho=j;
				break;
			}
		}

if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
            printf("O filho %d morreu normal\n", pid_terminados);
            terminados++;
		}
		else {
					ciclos[i_do_filho]++; // Registamos +1 tentativa 
					
					pid[i_do_filho] = fork(); 
					
					if (pid[i_do_filho] == 0) {
			
						execlp(commands[i_do_filho], commands[i_do_filho], NULL);
						_exit(1);
					}
				
				}

	}
	for (int i = 0; i < N; i++) {
        printf("%s %d\n", commands[i], ciclos[i]);
    }

}

int main(int argc, char* argv[]) {

    char *commands[argc-1];
    int N = 0;
	for(int i=1; i < argc; i++){
		commands[N] = strdup(argv[i]);
		printf("command[%d] = %s\n", N, commands[N]);
        N++;
	}

    controller(N, commands);

	return 0;
} 