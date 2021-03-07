#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

//ELiana Andrea Camayo Ante
//Jorge A. Ortiz 
//Ultima modificación: 06/03/2021

void help(void);
DIR * d;
struct dirent * ent;
char * fullPath;
int indent=0;
int varConcide=0;
int search ( char * dir, char * pattern, int indent);

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

	memset(ent,0,0);
	varConcide= search(dir, pattern, 0);
		if(varConcide > 0){
			printf("Total concidencias : %d\n, varConcide");
		}
		
		printf("TODO bucar %s en %s\n", pattern, dir, indent);
exit(EXIT_SUCCESS);
}

void help (void){
	fprintf(stdout, "Uso :	./main ARCHIVO Busca un archivo en directorio actual y subdirectorios .\n");
	fprintf(stdout, "	./main DIR ARCHIVO Busca un archivo en el directorio DIR y subdirectorios. \n");
}
int search(char * dir, char * pattern, int indent){
	
	//Se usa opendir sobre dir para obtener apuntador a una estructura DIR
	d = opendir(dir);

	if( d == NULL){
		perror("opendir");
		return 0;
	}

	//Recorre el directorio, se llama a readdir para leer la siguiente entreda del directorio
	while((ent = readdir(d)) != NULL){
  printf("Entrada: %s\n", ent->d_name);
	
	//Verificar si el nombre del archivo o directorio coincide con el patrón
	if(strstr(ent->d_name, pattern) != NULL) {
			printf("El nombre del archivo o director coincide con el padrón\n");
			
			//Obtener la ruta completa
			
			//reservar memoria
			fullPath = malloc(strlen(dir)+strlen(ent->d_name)+2);
			
			strcpy(fullPath, dir);
			strcat(fullPath,"/");
			fullPath = strcat(fullPath, ent-> d_name);
			
			printf("Ruta completa: %s \n", fullPath);
		  
			varConcide = varConcide + 1;
			
		}
	//Verificar si es un directorio
		if (ent->d_type == DT_DIR) {
			char path[1024];

			//Ignorar entradas con d_name "." y ".."
			if(strcmp(ent->d_name, ".")==0 || strcmp(ent->d_name, "..")==0){
				printf("Peligro! %s\n", ent->d_name);
				continue;
			}
			
				snprintf(path, sizeof(path), "%s/%s", dir, ent->d_name);
        printf("%*s[%s]\n", indent, "", ent->d_name);

			return search(path, pattern, indent + 2);
		} else {

            printf("%*s- %s\n", indent, "", ent->d_name);
		}

	}

	return varConcide;
}
