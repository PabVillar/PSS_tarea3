#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void extraer(FILE *file, int ancho, FILE *out){

	char buf[ancho+1];
	char replacement[ancho+1];
	char principle[4];

	int priority_pos;
	char meleon;
	int priority;
	int priority_pos_max;
	char s[6], d[5];
	int priorities_pos[5];

	fseek(file,0L,SEEK_SET);
	fgets(principle,4,file);

	if (principle[0] == '0')
	{
		perror("error: cola.txt esta vacia");
		exit(-1);
	}

	int len = ((int)principle[0])-48+1;
	

	for (int i = 0; i < len; ++i)
	{
		priority_pos = 4+1+i*(16+1);
		priorities_pos[i] = priority_pos;
		
		fseek(file,priority_pos+10,SEEK_SET);
		meleon = getc(file);
		s[i] = meleon;
		
	}
	
	int max_priority = s[0];

	for (int j = 0; j < len-1; ++j)
	{
		if (s[j] <= max_priority)
		{
			max_priority = s[j];
			priority_pos_max = priorities_pos[j];

		}
		
	}



	fseek(file,priority_pos_max,SEEK_SET);
	fgets(buf,10,file);
	printf("%s\n", buf);
	
	principle[0]--;
	fseek(file,0L,SEEK_SET);
	fputs(principle,file);
	printf("%c\n", principle[0]);

	fseek(file,priorities_pos[len-1]-17,SEEK_SET);
	fgets(replacement,16,file);
	

	fseek(file,priority_pos_max,SEEK_SET);
	fputs(replacement,file);	
	
			

}

#define ANCHO_LIN 16


int main(int argc, const char **argv) {
    FILE *file,*out;

    file = fopen(argv[1], "r+");


    if (file == NULL)
    {
        perror("Error while opening the file \n");
        exit(1);
    }

    extraer(file,ANCHO_LIN,out);

    fclose(file);


    return 0;
}
