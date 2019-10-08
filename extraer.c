#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void extraer(FILE *file, int ancho){

	//buf es el string en que se va a imprimir el nombre que se debe extraer
	char buf[ancho+1];
	//replacement es el string que va a tener la línea que debemos reemplazar finalmente en el lugar de buf en el archivo
	char replacement[ancho+1];
	//este es el string que guarda los primeros 4 caracteres del archivo (tamaño de la cola)
	char principle[4];

	int priority_pos;
	char meleon;
	
	int priority_pos_max;
	char s[6];
	int priorities_pos[5];
	
	//se posiciona el puntero al archivo al inicio de este
	fseek(file,0L,SEEK_SET);
	//se guardan en principle los primeros 4 caracteres del archivo
	fgets(principle,4,file);

	if (principle[0] == '0')
	{
		perror("error: cola.txt esta vacia");
		exit(-1);
	}
	
	//el largo de la cola en int
	int len = ((int)principle[0])-48+1;
	

	for (int i = 0; i < len; ++i)
	{
		//se obtiene la posicion del inicio de cada elemento de la cola y se guarda
		priority_pos = 4+1+i*(16+1);
		priorities_pos[i] = priority_pos;
		
		//se situa el puntero en la posicion de la prioridad de cada elemento de la cola y se guarda la prioridad
		fseek(file,priority_pos+10,SEEK_SET);
		meleon = getc(file);
		s[i] = meleon;
		
	}
	
	//se busca la maxima prioridad y con ella se obtiene la posicion del elemento
	int max_priority = s[0];

	for (int j = 0; j < len-1; ++j)
	{
		if (s[j] <= max_priority)
		{
			max_priority = s[j];
			priority_pos_max = priorities_pos[j];

		}
		
	}


	//se posiciona el puntero al inicio de la linea con mejor prioridad y se imprime el nombre en pantalla
	fseek(file,priority_pos_max,SEEK_SET);
	fgets(buf,10,file);
	printf("%s\n", buf);
	
	//se disminuye y actualiza el tamaño de la cola
	principle[0]--;
	fseek(file,0L,SEEK_SET);
	fputs(principle,file);
	
	//se obtiene el ultimo elemento de la cola para el reemplazo
	fseek(file,priorities_pos[len-1]-17,SEEK_SET);
	fgets(replacement,16,file);
	
	//se hace el reemplazo en la linea que se extrajo
	fseek(file,priority_pos_max,SEEK_SET);
	fputs(replacement,file);	
	
			

}

#define ANCHO_LIN 16


int main(int argc, const char **argv) {
    FILE *file;

    file = fopen(argv[1], "r+");


    if (file == NULL)
    {
        perror("Error while opening the file \n");
        exit(1);
    }

    extraer(file,ANCHO_LIN);

    fclose(file);


    return 0;
}
