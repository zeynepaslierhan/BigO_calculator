#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DATA_SIZE 1000

void time_spent(){
	
		printf("\nOutput:\n");
    	printf("------------------------------------------------------------\n\n");
    
		double time = 0.0;		
		
		clock_t begin = clock();	
		system("C:/Users/zerha/OneDrive/Belgeler/GitHub/BigO_calculator/yeni/kod.c");
		clock_t end = clock();
		
		printf("\n\n------------------------------------------------------------\n");
	    	
		time+= (double)(end - begin) / CLOCKS_PER_SEC;
		
		printf("\nThe elapsed time is %f seconds\n", time);
	
}

int main()
{
	char kod_blok,fonksiyon_ismi[DATA_SIZE];
	int parantez=0,virgul=0,i=0;
    FILE *from = fopen("for.txt", "r");
    FILE *to =fopen("kod.c","w");

    if (from == NULL)
    {
        printf("Error: could not open file %s", "for.txt");
        return 1;
    }
    else{
    	
    	fputs(from,to);
    	fclose(to);
    	fclose(from);
    	time_spent();
		
	}HAZAR SEN �OK TATLI B�R �NSANSIN
    
  return 0;
}
