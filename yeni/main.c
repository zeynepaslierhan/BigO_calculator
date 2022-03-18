#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DATA_SIZE 100

static int cfor=0,cwhile=0,cdoWhile=0,bigOLen=0,yildiz=0;

FILE *open_file(char *fileName){
	
	FILE *from = fopen(fileName,"r");
	if (from == NULL)
    {
        printf("\nError: could not open file %s\n", "doWhile.txt");
        exit(1);
    }else{
		return from;
	}
}

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

void reading_file(FILE *from){
	
	char kod_blok;
    FILE *to =fopen("kod.c","w");
    if (to == NULL)
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
	}
}

void counting_keywords(char *bigO,FILE *from){//dong�n�n hangisi olduguna karar verme
	
	char *kod=(char*)malloc(DATA_SIZE*sizeof(char));
	char *keywords=(char*)malloc(DATA_SIZE*sizeof(char));
	char *parameters=(char*)malloc(DATA_SIZE*sizeof(char));
	char *fonksiyon_ismi=(char*)malloc(DATA_SIZE*sizeof(char));
	
	int i=0, kontrol=0, kontrol2=0;
	fseek(from,0,SEEK_END);
	printf("\n\nIcerdigi karakter sayisi: %d \n",ftell(from));
	rewind(from);
		
		while(fscanf(from,"%s",kod)!=EOF){
				for(i=0;kod[i]!='\0';i++){
					keywords[i]=kod[i];
				}
				if(keywords[0]=='f'&&keywords[1]=='o'&&keywords[2]=='r'){
					cfor++;
					printf("\n\nFor\n");
					printf("Kosul ve islemi:");
					if(cfor!=0){
						fscanf(from,"%s",kod);
						for(i=0;kod[i]!='{';i++){
							parameters[i]=kod[i];
						}
						printf("\n%s\n",parameters);
						calculating_BigO(bigO,parameters);
					kontrol++;		
					}
				}else if(keywords[0]=='w'&&keywords[1]=='h'&&keywords[2]=='i'&&keywords[3]=='l'&&keywords[4]=='e'){
					cwhile++;
					printf("\nWhile\n");
					printf("Kosul ve islemi:\n");
					if(cwhile!=0){
						while(fscanf(from,"%s",kod)!=EOF){
							if(kod[0]=='i'&&kod[1]=='='){
								kontrol2++;
								break;
							}else if(kod[0]=='i'&&kod[1]=='+'){
								kontrol2++;
								break;
							}else if(kod[0]=='i'&&kod[1]=='-'){
								kontrol2++;
								break;
							}
						}
						if(kontrol2!=0){
							for(i=0;kod[i]!=';';i++){
								parameters[i]=kod[i];
							}
						}
						parameters[i]='$';
						printf("%s\n",parameters);
						calculating_BigO(bigO,parameters);
					}
					kontrol++;
					
				}else if(keywords[0]=='}'&&keywords[1]=='w'&&keywords[2]=='h'&&keywords[3]=='i'&&keywords[4]=='l'&&keywords[5]=='e'){
					cdoWhile++;
					printf("\nDo While\n");
					printf("Kosul ve islemi:\n");
					if(cdoWhile!=0){
						for(i=0;kod[i]!=';';i++){
							parameters[i]=kod[i];
						}
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
			printf("\nRecursive fonksiyonun d�nd�rd�g� deger, ismi ve parametresi: %s)\n",fonksiyon_ismi);
			free(kod);
			free(keywords);
				
		}	
	
	free(parameters);
	free(kod);
	free(keywords);
}

void calculating_BigO(char *bigO,char *parameters){//dongudeki parametre ve islemlerin ayristirilmasi
	
	int i=0,j=0,kontrol=0,semicolon=0;
	char *condition=(char*)malloc(DATA_SIZE*sizeof(char));
	
	if(cfor!=0&&cwhile==0&&cdoWhile==0){
		
		for(i=0;parameters[i]!='\0';i++){//for parametresi i�in
				if(semicolon!=1&&semicolon!=2&&parameters[i]!=';'&&parameters[i]!='('){
					printf("%c",parameters[i]);
					continue;
				}else if(parameters[i]==';'){
					printf(" %c ",parameters[i]);
					semicolon++;
					continue;
				}else if(semicolon==1){
					printf("%c",parameters[i]);
					continue;
				}else if(semicolon==2){
					if(parameters[i]!=')'){
						condition[j]=parameters[i];
						printf("%c",condition[j]);
						j++;
					}else{
						condition[j]='$';//for d�ng�s�ndeki kosul ile islemi condition dizisinde birbirinden ayrildi.
						condition[++j]='\0';//condition sonuna bitti isareti konuldu.
					}
				}
		}
		
		save_bigO(bigO,condition);
		cfor=0;//parametrenin hangi loop i�in kullanildigini anlamak i�in.	
		
		
	}else if(cfor==0&&cwhile!=0&&cdoWhile==0){
		save_bigO(bigO,parameters);
		
		cwhile=0;//parametrenin hangi loop i�in kullanildigini anlamak i�in.	
			
	}else if(cfor==0&&cwhile==0&&cdoWhile!=0){
	
		for(i=0;parameters[i]!=')';i++){//for parametresi i�in
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
		condition[j]='\0';
		printf("%s\n",condition);
		save_bigO(bigO,condition);
		
		cdoWhile=0;//parametrenin hangi loop i�in kullanildigini anlamak i�in.	
	
	}
	bigO[bigOLen]='\0';
	free(condition);
}

void save_bigO(char *bigO,char *condition){//dongulerin islemlerine g�re bigO kaydedilmesi
	
	if(condition_integerValue(condition)==1){
			bigO[bigOLen]='*';
			yildiz++;
			bigO[++bigOLen]='n';
		}else{
			bigO[bigOLen]='*';
			yildiz++;
			bigO[++bigOLen]='l';
			bigO[++bigOLen]='o';
			bigO[++bigOLen]='g';
			bigO[++bigOLen]='n';
		}
		bigOLen++;
}

int condition_integerValue(char *condition){//dong�deki islemlerin ne olduguna karar verilmesi

	int i=0;
		for(i=0;condition[i]!='$';i++){
			if(condition[i]=='+'||condition[i]=='-'){
				return 1;
			}else if(condition[i]=='*'||condition[i]=='/'){
				return 2;//logn
			}else{
				continue;
			}
		}
	
}

void print_bigO(char *bigO){
	int i=0;
	if(yildiz==0){
		printf("%s",bigO);
	}else{
		for(i=2;i<bigOLen;i++){
			printf("%c",bigO[i]);
		}
	}
}

int main(){
	
    char *bigO=(char*)malloc(DATA_SIZE*(sizeof(char)));
    
    printf("Incelemek istediginiz kodun(text dosyasi uzantisiyla) ismini giriniz:\n");
    char *fileName=(char*)malloc(DATA_SIZE*(sizeof(char)));
    scanf("%s",fileName);
    FILE *from=open_file(fileName);
    free(fileName);
    
	bigO[bigOLen]='1';
    bigOLen++;
	reading_file(from);
	time_spent();
    counting_keywords(bigO,from);
    
    
    
	printf("\n\nZaman Karmasikligi:\n");
	print_bigO(bigO);
	printf("\n\nYer Karmasikligi:\n");
	printf("4*");
	print_bigO(bigO);
	
    free(bigO);
    fclose(from);
  return 0;
}
