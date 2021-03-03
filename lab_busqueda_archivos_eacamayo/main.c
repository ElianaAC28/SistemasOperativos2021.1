#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

//ELiana Andrea Camayo Ante 
//Ultima modificación: 03/03/2021

void help(void);

int search (char * dir, char * pattern);

int main(int argc, char * argv[]){
	char * dir;
	char * pattern;
	if(argc <2 || argc> 3){
	help();
	exit(EXIT_FAILURE);
}

//POST: argc==2 || argc ==3
//Si argc ==2, buscar en el directorio actual
//"." hace referencia al directorio actuañ
	if(argc==2){
		dir = ".";
		pattern = argv[1];
	}else{
		dir = argv[1];
		pattern = argv[2];
	}
int total = search(dir, pattern);
		if(total > 0){
		printf("Total : %d\n, total");
		}
		
		printf("TODO bucar %s en %s\n", pattern, dir);
exit(EXIT_SUCCESS);
}

void help (void){
	fprintf(stdout, "Uso :	./main ARCHIVO Busca un archivo en directorio actual y subdirectorios .\n");
	fprintf(stdout, "	./main DIR ARCHIVO Busca un archivo en el directorio DIR y subdirectorios. \n");
}
int search(char * dir, char * pattern){
	
	//1.opendir
  DIR * d;
	d = opendir(dir);

	if( d == NULL){
		perror("opendir");
		return 0;
	}

	//2. Readdir
	struct dirent * ent;
	

	while((ent = readdir(d)) != NULL){
	printf("Entrada: %s\n", ent->d_name);
	if(strcmp(ent->d_name, ".")==0){
		printf("Peligro! %s\n", ent->d_name);
		continue;
	}
	}

	return 0;
}

