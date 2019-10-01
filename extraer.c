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

	int max_priority;

	fseek(file,0L,SEEK_SET);
	fgets(principle,4,file);
	

	for (int i = 1; i <= 5; ++i)
	{
		priority_pos = 4+1+i*(16+1);
		priorities_pos[i] = priority_pos;
		
		fseek(file,priority_pos+10,SEEK_SET);
		meleon = getc(file);
		s[i-1] = meleon;

		
	}

	for (int j = 0; j < 5; ++j)
	{
		if (s[j]>s[j+1])
		{
			max_priority = s[j+1];
			priority_pos_max = priorities_pos[j+1];

		}
		
	}
	fseek(file,priority_pos_max,SEEK_SET);
	fgets(buf,10,file);
	printf("%s\n", buf);

	//Hacer algo con principle


	fseek(file,priorities_pos[5]-17,SEEK_SET);
	fgets(replacement,ancho,file);
	
	
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
