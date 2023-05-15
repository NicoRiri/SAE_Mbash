#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h> 
#define MAXLI 2048

char cmd[MAXLI];
char path[MAXLI];
int pathidx;
char res[256];
char * envs;
char biiin[256];
void mbash();

int main (int argc, char* argv[]) {
  while (1) {
    envs = getenv("PWD");
    printf("variable d'env au début : %s\n",envs);

    const char * path1 = getcwd(res,MAXLI);
    //affiche le chemin de prompt
    printf("%s$ ",res);

    //ATTENTION : fgets met un '\n'
    fgets(cmd, MAXLI, stdin);
    
    
    char*newline = strchr(cmd,'\n');
    if (newline) *newline = 0;
    
    //contains 
    char * s = strstr(cmd,"cd ");


    //si s est pas null cad qu'il contient "cd "
    if (s!=0){

      //split le tableau
      char * sSplit = strtok(s," ");

      //récupérer le 2e élément
      sSplit = strtok(NULL," ");


      char chemin[MAXLI];
      strcpy(chemin,envs);
      strcat(chemin,"/");
      strcat(chemin,sSplit);
      printf("%s\n",chemin);

      //change la variable PATH avec le chemin voulu
      int ret = chdir(chemin);
      //printf("%d",errno);
      //printf("%d",ret);

      //si le chdir n'a pas fonctionné alors on retourne un message d'erreur 
      if (ret == -1){
	printf("cd : %s : No such file or directory\n",sSplit);
      }

      
      //enregistre la nouvelle variable PATH d'en la variable envs
      envs = getcwd(res, MAXLI);
      printf("\n%s\n",envs);
      //setenv("PWD", envs, 1);
  
    }else{
      printf("\nEnvs dans le else : %s\n",res);
      mbash(cmd,res);
    }
    
  }
 
}


void mbash() {

  strcpy(biiin, "/bin/");
  strcat(biiin, cmd);
  char *newargv2[] = { biiin, NULL, NULL};
  int pid = 0;
  pid = fork();

  if (pid == 0){
    char *res[] = {envs};
    printf("%s",envs);
    printf("le res : %s",*res);
    execve(biiin ,newargv2,res);
    
  }else{
    
    waitpid(pid, NULL, 0);

    
  }


}

