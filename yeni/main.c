#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DATA_SIZE 1000

void time_spent(){
		printf("------------------------------------------------------------");
		printf("\nOutput:\n");
    	printf("------------------------------------------------------------\n\n");
    
		double time = 0.0;		
		
		clock_t begin = clock();	
		system("C:/Users/zerha/OneDrive/Belgeler/GitHub/BigO_calculator/yeni/kod.exe");
		clock_t end = clock();
		
		printf("\n\n------------------------------------------------------------\n");
	    	
		time+= (double)(end - begin) / CLOCKS_PER_SEC;
		
		printf("\nVerilen kodun calisma suresi: %f saniye\n\n", time);
	
}

void reading_file(){
	
	char kod_blok;
	FILE *from = fopen("for.txt","r");
    FILE *to =fopen("kod.c","w");

    if (from == NULL)
    {
        printf("Error: could not open file %s", "for.txt");
        return 1;
    }
    else{
    	
    	do{
			kod_blok=getc(from);
			if( kod_blok!=EOF){
				putc(kod_blok,to);
			}
		}while(kod_blok!=EOF);
    	
    	fclose(to);
    	fclose(from);
	}
}

int main()
{
    time_spent();
    reading_file();
    
  return 0;
}
