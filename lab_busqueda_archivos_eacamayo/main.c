#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

//ELiana Andrea Camayo Ante
//Jorge A. Ortiz 
//Ultima modificación: 03/03/2021

void help(void);

int search ( char * dir, char * pattern, int indent);

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
int total = search(dir, pattern, 0);
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
int search(char * dir, char * pattern, int indent){
	
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
		if (ent->d_type == DT_DIR) {
			char path[1024];
			if(strcmp(ent->d_name, ".")==0 || strcmp(ent->d_name, "..")==0){
				printf("Peligro! %s\n", ent->d_name);
				continue;
			}
			

				//Concatenar ruta

            snprintf(path, sizeof(path), "%s/%s", dir, ent->d_name);
            printf("%*s[%s]\n", indent, "", ent->d_name);

			search(path, pattern, indent + 2);
		} else {

            printf("%*s- %s\n", indent, "", ent->d_name);
		}
		
		if(strstr(ent->d_name, pattern) != NULL) {
			//El nombre del archivo o directorio coincide con el patron
			printf("Exito\n");
			
			int  tam = strlen(dir)+strlen(ent->d_name)+2;
			
			char * rutaCompleta = malloc(tam);
			
			strcpy(rutaCompleta, dir);
			strcat(rutaCompleta,"/");
			
			rutaCompleta = strcat(rutaCompleta, ent-> d_name);
			
			
			printf("Ruta completa: %s \n", rutaCompleta);
			
			
		} else {
			
		}
		
		

	}
	//closedir(dir);
	return 0;
}

