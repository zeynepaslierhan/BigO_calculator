#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DATA_SIZE 1000

static int cfor,cwhile,cdoWhile,cint,parantez,virgul;



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

void counting_keywords(){
	
	char kod;
	char *keywords=(char*)malloc(DATA_SIZE*sizeof(char));
	FILE *from = fopen("for.txt","r");
    if (from == NULL)
    {
        printf("\nError: could not open file %s\n", "for.txt");
    }else{
		int i=0;
		do{
			kod=getc(from);
			if(kod!=EOF){
				printf("%c",kod);//okuma kontrolü
				if(kod!=' '&&kod!='('&&kod!='\n'&&kod!='{'){
					keywords[i]=kod;
					i++;
				}else if(keywords[0]=='f'&&keywords[1]=='o'&&keywords[2]=='r'){
					cfor++;
					i=0;
					printf("\n\n%d",cfor);//kontrol
					free(keywords);
				}else{
					i=0;
					free(keywords);
				}
			}
		}while(kod!=EOF);
	}
	
}

int main(){
    
	reading_file();
	time_spent();
    
    counting_keywords();
    printf("%d",cfor);//kontrol
    
  return 0;
}
