#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DATA_SIZE 100

static int cfor=0,cwhile=0,cdoWhile=0,parantezK=0;


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
	char *fonksiyon_ismi=(char*)malloc(DATA_SIZE*sizeof(char));

	FILE *from = fopen("recursive.txt","r");
    if (from == NULL)
    {
        printf("\nError: could not open file %s\n", "doWhile.txt");
    }else{
		int i=0, kontrol=0;
		fseek(from,0,SEEK_END);
		printf("\nbu dosya su kadar karakter icerir: %d \n",ftell(from));
		rewind(from);
		
		while(fscanf(from,"%s",kod)!=EOF){
				for(i=0;kod[i]!='\0';i++){
					keywords[i]=kod[i];
				}
				if(kod[0]=='}'){
					parantezK++;
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
					kontrol++;		
					}
				}else if(keywords[0]=='w'&&keywords[1]=='h'&&keywords[2]=='i'&&keywords[3]=='l'&&keywords[4]=='e'){
					cwhile++;
					printf("\n%d\n",cwhile);
					if(cwhile!=0){
						fscanf(from,"%s",kod);
						for(i=0;kod[i]!='{';i++){
							parameters[i]=kod[i];
						}
						parameters[i]='\0';
						printf("%s\n",parameters);
						calculating_BigO(bigO,parameters);
					}
					kontrol++;
					
				}else if(keywords[0]=='}'&&keywords[1]=='w'&&keywords[2]=='h'&&keywords[3]=='i'&&keywords[4]=='l'&&keywords[5]=='e'){
					cdoWhile++;
					printf("\ndoWhile komutunun bittigi karakter: %d \n",ftell(from));
					printf("\n%d\n",cdoWhile);
					if(cdoWhile!=0){
						for(i=0;kod[i]!=';';i++){
							parameters[i]=kod[i];
						}
						printf("%s\n",parameters);
						calculating_BigO(bigO,parameters);
					}
					kontrol++;
				}
		}
		if(kontrol==0){
			free(kod);
			rewind(from);
			for(kod=getc(from);kod!=')';kod=getc(from)){
				if(kod!='>'){
					fonksiyon_ismi[i]=kod;
					i++;
				}else if(kod=='>'){
					i=0;
					free(fonksiyon_ismi);
				}
			}
			fonksiyon_ismi[i]='\0';
			printf("\nRecursive fonksiyonun döndürdügü deger, ismi ve parametresi: %s)\n",fonksiyon_ismi);
			free(kod);
			free(keywords);
			
			
		}
			
	
		fclose(from);
		}
	
	
	free(parameters);
	free(kod);
	free(keywords);
}



void condition_integerValue(char *condition, int semicolon){
	int *condition_i=(int*)malloc(4*sizeof(int));// 0. index='<' 1. index ='>' 2. index ='=' 3. index= '!'
	int i=0;
	for(i=0;i<4;i++){
		condition_i[i]=0;
	}
	if(semicolon!=0){
		for(i=0;condition[i]!='$';i++){
		if(condition[i]=='='){
			condition_i[2]++;	
		}else if(condition_i[i]=='<'){
			condition_i[0]++;
		}else if(condition_i[i]=='>'){
			condition_i[1]++;
		}else if(condition[i]=='!'){
			condition_i[3]++;
		}
		if(condition[i]=='n'){
			
		}}
	}else{
		
	}
}


void calculating_BigO(char *bigO,char *parameters){
	int i=0,j=0,kontrol=0,semicolon=0;
	char *condition=(char*)malloc(DATA_SIZE*sizeof(char));
	
	if(cfor!=0&&cwhile==0&&cdoWhile==0){
		
		for(i=0;parameters[i]!='\0';i++){//for parametresi iï¿½in
				if(semicolon!=1&&semicolon!=2&&parameters[i]!=';'&&parameters[i]!='('){
					printf("%c",parameters[i]);
					continue;
				}else if(parameters[i]==';'){
					printf(" %c ",parameters[i]);
					semicolon++;
					if(semicolon==2){
						condition[j]='$';//for dï¿½ngï¿½sï¿½ndeki kosul ile islemi condition dizisinde birbirinden ayrildi.
						j++;
					}
					continue;
				}else if(semicolon==1||semicolon==2){
					if(parameters[i]!=')'){
						condition[j]=parameters[i];
						printf("%c",condition[j]);
						j++;
					}else{
						condition[j]='$';//for dï¿½ngï¿½sï¿½ndeki kosul ile islemi condition dizisinde birbirinden ayrildi.
						condition[++j]='\0';//condition sonuna bitti isareti konuldu.
					}
				}
		}
		printf("\n%s\n",condition);
		
		
		cfor=0;//parametrenin hangi loop iï¿½in kullanildigini anlamak iï¿½in.
		printf("\n\n!!!!UYARI: calculating_bigO fonksiyonunda cfor=0 yapildi.!!!!!\n");		
		
		
	}else if(cfor==0&&cwhile!=0&&cdoWhile==0){
		
		for(i=0;parameters[i]!='\0';i++){//for parametresi iï¿½in
				if(parameters[i]=='('){
					printf(" /%c/",parameters[i]);
					continue;
				}else if(parameters[i]==')'){
					printf("/%c/",parameters[i]);
					condition[j]='$';//for dï¿½ngï¿½sï¿½ndeki kosul ile islemi condition dizisinde birbirinden ayrildi.
					condition[++j]='\0';//condition sonuna bitti isareti konuldu.
				}else{
					condition[j]=parameters[i];
					printf("%c",condition[j]);
					j++;
				}
		}
				
		printf("\n%s\n",condition);
		
		cwhile=0;//parametrenin hangi loop iï¿½in kullanildigini anlamak iï¿½in.
		printf("\n\n!!!!UYARI: calculating_bigO fonksiyonunda cwhile=0 yapildi.!!!!!\n");	
			
	}else if(cfor==0&&cwhile==0&&cdoWhile!=0){
	
		for(i=0;parameters[i]!=')';i++){//for parametresi iï¿½in
				if(parameters[i]!='('&&kontrol==0){
					i++;
					continue;
				}else if(parameters[i]=='('){
					kontrol++;
				}else{
					condition[j]=parameters[i];
					j++;
				}
		}
				
		printf("\n%s\n",condition);
		
		cdoWhile=0;//parametrenin hangi loop iï¿½in kullanildigini anlamak iï¿½in.
		printf("\n\n!!!!UYARI: calculating_bigO fonksiyonunda cdoWhile=0 yapildi.!!!!!\n");	
	
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
