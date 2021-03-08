#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

//
//ELiana Andrea Camayo Ante
//Jorge A. Ortiz 
//Ultima modificación: 06/03/2021

void help(void);

int search ( char * dir, char * pattern);

int main(int argc, char * argv[]){
	char * dir;
	char * pattern;	

	if(argc <2 || argc> 3){
		help();
		exit(EXIT_FAILURE);
	}

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
	 printf("Total concidencias : %d\n", total);

		
exit(EXIT_SUCCESS);
}

void help (void){
	fprintf(stdout, "Uso :	./main ARCHIVO Busca un archivo en directorio actual y subdirectorios .\n");
	fprintf(stdout, "	./main DIR ARCHIVO Busca un archivo en el directorio DIR y subdirectorios. \n");
}
int search(char * dir, char * pattern){
	
  int varConcide=0;
  DIR * d;
  struct dirent * ent;
	char * fullPath;
	struct stat ss;
	//Se usa opendir sobre dir para obtener apuntador a una estructura DIR
	d = opendir(dir);

	if( d == NULL){
		perror("opendir");
		return 0;
	}

	//Recorre el directorio, se llama a readdir para leer la siguiente entreda del directorio
	while((ent = readdir(d)) != NULL){
  //printf("Entrada: %s\n", ent->d_name);
	
			//Obtener la ruta completa
			
			//reservar memoria
			fullPath = malloc(strlen(dir)+strlen(ent->d_name)+2);
			
			strcpy(fullPath, dir);
			strcat(fullPath,"/");
			fullPath = strcat(fullPath, ent-> d_name);	

	//Verificar si el nombre del archivo o directorio coincide con el patrón
	if(strstr(ent->d_name, pattern) != NULL) {
		//	printf("El nombre del archivo o director coincide con el patrón\n");
			
			printf("Ruta completa: %s \n", fullPath);
		  
			varConcide = varConcide + 1;
	}
	//Verificar si es un directori

		if(stat(fullPath,&ss)==-1){
			perror("stat");
			//	printf("No se puede acceder AQUI  la ruta \n");
		
		}
			if (S_ISDIR(ss.st_mode)) {

			//Ignorar entradas con d_name "." y ".."
			if(strcmp(ent->d_name, ".")==0 || strcmp(ent->d_name, "..")==0){
			//	printf("Peligro! %s\n", ent->d_name);
				continue;
			}
			varConcide = varConcide + search(fullPath, pattern);	
		}
}
	closedir(d); 
	return varConcide;
}
