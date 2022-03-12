#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DATA_SIZE 1000

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
    	
		printf("\nOutput:\n");
    	printf("------------------------------------------------------------\n\n");
    
		double time_spent = 0.0;		
		clock_t begin = clock();	
		system("C:/Users/zerha/OneDrive/Masaüstü/18_Mart_Projesi/yeni/kod.exe");
		clock_t end = clock();
		
		printf("\n\n------------------------------------------------------------\n");
	    	
		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	 
	   	printf("\nThe elapsed time is %f seconds\n", time_spent);
    	
		
	}
    
  return 0;
}
