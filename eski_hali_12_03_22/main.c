#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DATA_SIZE 1000

int main()
{
	char kutuphane_kod[DATA_SIZE]="#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n";
	char main_kod[DATA_SIZE]="int main()\n{\n\tint dizi[20];\n";
	char kod_blok,fonksiyon_ismi[DATA_SIZE];
	int parantez=0,virgul=0,i=0;
    FILE *from = fopen("kod_blok.txt", "r");
    FILE *to =fopen("tam_kod.c","w");

    if (from == NULL || to == NULL)
    {
        printf("Error: could not open file %s", "kod_blok");
        return 1;
    }
    else{
    	
    	fputs(kutuphane_kod,to);
    	for(kod_blok=getc(from);kod_blok!=EOF;kod_blok=getc(from)){
    		putc(kod_blok,to);
    		if(kod_blok='['){
    			parantez++;
			}
			else if(kod_blok=','){
				virgul++;
			}
		}
		rewind(from);
		for(kod_blok=getc(from);kod_blok!='(';kod_blok=getc(from)){
			if(kod_blok!=' '){
				fonksiyon_ismi[i]=kod_blok;
				i++;
			}
			else if(strcmp(fonksiyon_ismi,"int") == 0||strcmp(fonksiyon_ismi,"void") == 0){
				i=0;
			}	
		}
		strcat(fonksiyon_ismi,"(");
		if(parantez!=0){
        	strcat(fonksiyon_ismi,"dizi");
        }
        for(i=0;i<=virgul;i++){
            strcat(fonksiyon_ismi,",20");//parametre kullanicidan alinabilirS.
        }
        strcat(fonksiyon_ismi,");");
        
		fputs("\n",to);
    	fputs(main_kod,to);
    	fputs("\n\t",to);
    	fputs(fonksiyon_ismi,to);
    	fputs(" \n\treturn 0;\n}",to);
    	
    	fclose(to);
    	fclose(from);
    	
		double time_spent = 0.0;
 		

		if(system("C:/Users/zerha/OneDrive/Masaüstü/18_Mart_Projesi/eski_hali_12_03_22/tam_kod.exe")!=0){
			printf("KOD HATALI");
		}else{
			clock_t begin = clock();
	    	
	    	
			system("C:/Users/zerha/OneDrive/Masaüstü/18_Mart_Projesi/eski_hali_12_03_22/tam_kod.exe");
	    	
			clock_t end = clock();
	    	
			time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	 
	   		printf("\nThe elapsed time is %f seconds\n", time_spent);
		}
    	
		
	}
    
  return 0;
}
