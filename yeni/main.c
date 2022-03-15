#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DATA_SIZE 100

static int cfor=0,cwhile=0,cdoWhile=0;


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
		
		printf("\nVerilen kodun calisma suresi: %f saniye\n\n",time);
	
}

void reading_file(){
	
	char kod_blok;
	FILE *from = fopen("for.txt","r");
    FILE *to =fopen("kod.c","w");

    if (from == NULL)
    {
        printf("Error: could not open file %s", "for.txt");
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

void counting_keywords(char *bigO){
	
	char *kod=(char*)malloc(DATA_SIZE*sizeof(char));
	char *keywords=(char*)malloc(DATA_SIZE*sizeof(char));
	char *parameters=(char*)malloc(DATA_SIZE*sizeof(char));
	
	FILE *from = fopen("while.txt","r");
    if (from == NULL)
    {
        printf("\nError: could not open file %s\n", "while.txt");
    }else{
		int i=0;
		while(fscanf(from,"%s",kod)!=EOF){
				for(i=0;kod[i]!='\0';i++){
					keywords[i]=kod[i];
				}
				if(keywords[0]=='f'&&keywords[1]=='o'&&keywords[2]=='r'){
					cfor++;
					printf("\ncfor: %d\n", cfor);
					if(cfor!=0){
						fscanf(from,"%s",kod);
						for(i=0;kod[i]!='{';i++){
							parameters[i]=kod[i];
						}
						printf("%s\n",parameters);
						
						calculating_BigO(bigO,parameters);
							
					}
				}else if(keywords[0]=='w'&&keywords[1]=='h'&&keywords[2]=='i'&&keywords[3]=='l'&&keywords[4]=='e'){
					cwhile++;
					printf("\n%d\n",cwhile);
					if(cwhile!=0){
						fscanf(from,"%s",kod);
						for(i=0;kod[i]!='{';i++){
							parameters[i]=kod[i];
						}
						printf("%s\n",parameters);
					}
				}else if(keywords[0]=='d'&&keywords[1]=='o'&&keywords[2]=='{'){
					cdoWhile++;
				}
			}
		}
	
	free(kod);
	free(keywords);
	free(parameters);
}


void calculating_BigO(char *bigO,char *parameters){
	int i=0,j=0,semicolon=0;
	char *condition=(char*)malloc(DATA_SIZE*sizeof(char));
	
	if(cfor!=0&&cwhile==0&&cdoWhile==0){
		for(i=0;parameters[i]!='\0';i++){//for parametresi için
				if(semicolon!=1&&semicolon!=2&&parameters[i]!=';'&&parameters[i]!='('){
					printf("%c",parameters[i]);
					continue;
				}else if(parameters[i]==';'){
					printf(" %c ",parameters[i]);
					semicolon++;
					if(semicolon==2){
						condition[j]='$';//for döngüsündeki kosul ile islemi condition dizisinde birbirinden ayrildi.
						j++;
					}
					continue;
				}else if(semicolon==1||semicolon==2){
					if(parameters[i]!=')'){
						condition[j]=parameters[i];
						printf("%c",condition[j]);
						j++;
					}else{
						condition[j]='$';//for döngüsündeki kosul ile islemi condition dizisinde birbirinden ayrildi.
						condition[++j]='\0';//condition sonuna bitti isareti konuldu.
					}
				}
		}
		printf("\n%s\n",condition);
		
		
		cfor=0;//parametrenin hangi loop için kullanildigini anlamak için.
		printf("\n\n!!!!UYARI: calculating_bigO fonksiyonunda cfor=0 yapildi.!!!!!\n");		
	}	
	
	
	
	free(condition);
	
}

int main(){
	
    char *bigO=(char*)malloc(DATA_SIZE*(sizeof(char)));
	reading_file();
	time_spent();
    counting_keywords(bigO);
    
    free(bigO);
  return 0;
}
