#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DATA_SIZE 100

static int cfor=0,cwhile=0,cdoWhile=0,bigOLen=0,yildiz=0,cwhile2=0,cdoWhile2=0;

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

void recursive_fonk(FILE *from,char *bigO){
	
	char *kod=(char*)malloc(DATA_SIZE*sizeof(char));
	char *parameters=(char*)malloc(DATA_SIZE*sizeof(char));
	char *fonksiyon_ismi=(char*)malloc(DATA_SIZE*sizeof(char));
	char *fonksiyon=(char*)malloc(DATA_SIZE*sizeof(char));
	
	int i=0;
	rewind(from);
	for(kod=getc(from);kod!=')';kod=getc(from)){
		if(kod!='>'){
			fonksiyon[i]=kod;
			i++;
		}else if(kod=='>'){
			i=0;
			free(fonksiyon);
		}
	}
	fonksiyon[i]='\0';
			
	int j=0;
	printf("\nRecursive fonksiyonun; döndürdügü deger, ismi ve parametresi: \n %s)\n",fonksiyon);
	
	bigO[bigOLen]='*';
	yildiz++;		
	bigO[++bigOLen]='n';
	bigO[++bigOLen]='*';
	yildiz++;
	bigO[++bigOLen]='n';
	bigOLen++;	
	bigO[bigOLen]='\0';
	
	printf("\n\nZaman Karmasikligi:\n");
	print_bigO(bigO);
	printf("\n\nYer Karmasikligi:\n");
	printf("\n4*");
	print_bigO(bigO);
		
	free(fonksiyon);
	free(fonksiyon_ismi);
	free(parameters);
	free(kod);
	free(fonksiyon_ismi);
}

void counting_keywords(char *bigO,FILE *from){//dongünün hangisi olduguna karar verme
	
	char *kod=(char*)malloc(DATA_SIZE*sizeof(char));
	char *keywords=(char*)malloc(DATA_SIZE*sizeof(char));
	char *parameters=(char*)malloc(DATA_SIZE*sizeof(char));
	
	int i=0,kontrol2=0,kontrol=0,kontrol1=0,temp=0;
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
					cwhile2++;
					printf("\nWhile\n");
					printf("Kosul ve islemi:\n");
					for(i=6;keywords[i]!=')';i++){
						printf("%c",keywords[i]);
					}
					printf(" ");
					if(cwhile!=0){
						while(fscanf(from,"%s",kod)!=EOF){
							if(kod[0]=='i'&&kod[1]=='='&&cwhile2==1){
								kontrol2++;
								break;
							}else if(kod[0]=='i'&&kod[1]=='+'&&cwhile2==1){
								kontrol2++;
								break;
							}else if(kod[0]=='i'&&kod[1]=='-'&&cwhile2==1){
								kontrol2++;
								break;
							}else if(kod[0]=='j'&&kod[1]=='='&&cwhile2==2){
								kontrol2++;
								break;
							}else if(kod[0]=='j'&&kod[1]=='+'&&cwhile2==2){
								kontrol2++;
								break;
							}else if(kod[0]=='j'&&kod[1]=='-'&&cwhile2==2){
								kontrol2++;
								break;
							}else if(kod[0]=='k'&&kod[1]=='='&&cwhile2==3){
								kontrol2++;
								break;
							}else if(kod[0]=='k'&&kod[1]=='+'&&cwhile2==3){
								kontrol2++;
								break;
							}else if(kod[0]=='k'&&kod[1]=='-'&&cwhile2==3){
								kontrol2++;
								break;
							}
						}
						if(kontrol2!=0){
							for(i=0;kod[i]!=';';i++){
								parameters[i]=kod[i];
							}
						}
						
						parameters[i]='\0';
						printf("%s\n",parameters);
						calculating_BigO(bigO,parameters);
						
					}
					kontrol++;
					
				}else if(keywords[0]=='}'&&keywords[1]=='w'&&keywords[2]=='h'&&keywords[3]=='i'&&keywords[4]=='l'&&keywords[5]=='e'){
					cdoWhile++;
					cdoWhile2++;
					printf("\nDo While\n");
					printf("Kosul ve islemi:\n");
					
					for(i=7;kod[i]!=')';i++){
						printf("%c",kod[i]);
					}
					temp=ftell(from);
					fseek(from,temp-25,SEEK_SET);
					
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
						}else if(kod[0]=='j'&&kod[1]=='='){
							kontrol2++;
							break;
						}else if(kod[0]=='j'&&kod[1]=='+'){
							kontrol2++;
							break;
						}else if(kod[0]=='j'&&kod[1]=='-'){
							kontrol2++;
							break;
						}else if(kod[0]=='k'&&kod[1]=='='){
							kontrol2++;
							break;
						}else if(kod[0]=='k'&&kod[1]=='+'){
							kontrol2++;
							break;
						}else if(kod[0]=='k'&&kod[1]=='-'){
							kontrol2++;
							break;
						}
					}
						
					if(kontrol2!=0){
						for(i=0;kod[i]!=';';i++){
							parameters[i]=kod[i];
						}
					}
						
					parameters[i]='\0';
					printf(" %s\n",parameters);
					calculating_BigO(bigO,parameters);
					kontrol++;
					fseek(from,temp,SEEK_SET);
				}
		}
	
	free(parameters);
	free(kod);
	free(keywords);
}

void calculating_BigO(char *bigO,char *parameters){//dongudeki parametre ve islemlerin ayristirilmasi
	
	int i=0,j=0,kontrol=0,semicolon=0;
	char *condition=(char*)malloc(DATA_SIZE*sizeof(char));
	
	if(cfor!=0&&cwhile==0&&cdoWhile==0){
		
		for(i=0;parameters[i]!='\0';i++){//for parametresi iï¿½in
				if(semicolon!=1&&semicolon!=2&&parameters[i]!=';'&&parameters[i]!='('){
					continue;
				}else if(parameters[i]==';'){
					semicolon++;
					continue;
				}else if(semicolon==1){
					continue;
				}else if(semicolon==2){
					if(parameters[i]!=')'){
						condition[j]=parameters[i];
						j++;
					}else{
						condition[j]='$';//for dï¿½ngï¿½sï¿½ndeki kosul ile islemi condition dizisinde birbirinden ayrildi.
						condition[++j]='\0';//condition sonuna bitti isareti konuldu.
					}
				}
		}
		
		save_bigO(bigO,condition);
		cfor=0;//parametrenin hangi loop iï¿½in kullanildigini anlamak iï¿½in.	
		
		
	}else if(cfor==0&&cwhile!=0&&cdoWhile==0){
		save_bigO(bigO,parameters);
		
		cwhile=0;//parametrenin hangi loop iï¿½in kullanildigini anlamak iï¿½in.	
			
	}else if(cfor==0&&cwhile==0&&cdoWhile!=0){
	
		save_bigO(bigO,parameters);
		
		cdoWhile=0;//parametrenin hangi loop iï¿½in kullanildigini anlamak iï¿½in.	
	
	}
	free(condition);
}

void save_bigO(char *bigO,char *condition){//dongulerin islemlerine göre bigO kaydedilmesi
	
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

int condition_integerValue(char *condition){//dongüdeki islemlerin ne olduguna karar verilmesi

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

int virgul(char *kod,FILE *from){
	int i=0,virSayisi=0;
	fscanf(from,"%s",kod);
	for(i=0;kod[i]!=';';i++){
		if(kod[i]==','){
			virSayisi++;
		}
	}
	return virSayisi;
}

void space_complexity(FILE *from,char *bigO){
	
	char *kod=(char*)malloc(DATA_SIZE*sizeof(char));
	char *variables=(char*)malloc(DATA_SIZE*sizeof(char));
	
	rewind(from);
	int cint=0,cfloat=0,cchar=0,cdouble=0;
	int i=0,j=0,v=0;
	while(fscanf(from,"%s",kod)!=EOF){
		if(strcmp(kod,"int")==0){
			cint++;
			v=virgul(kod,from);
			printf("\n4*");
			print_bigO(bigO);
			printf("+%d",(v+1)*4);
			break;
		}else if(strcmp(kod,"float")==0){
			cfloat++;
			v=virgul(kod,from);
			printf("\n4*");
			print_bigO(bigO);
			printf("+%d",(v+1)*4);
			break;
		}else if(strcmp(kod,"char")==0){
			cchar++;
			v=virgul(kod,from);
			print_bigO(bigO);
			printf("+%d",(v+1)*1);
			break;
		}else if(strcmp(kod,"double")==0){
			cdouble++;
			v=virgul(kod,from);
			printf("\n8*");
			print_bigO(bigO);
			printf("+%d",(v+1)*8);
			break;
		}
	}
	
	
	
	
	fclose(kod);	
	fclose(variables);
}

void print_bigO(char *bigO){
	
	int i=0;
	printf("O(");
	if(yildiz==0){
		printf("%s",bigO);
	}else{
		for(i=2;i<bigOLen;i++){
			printf("%c",bigO[i]);
		}
	}
	printf(")");
	
}

int main(){
	
    char *bigO=(char*)malloc(DATA_SIZE*(sizeof(char)));
    
    printf("Incelemek istediginiz kodun(text dosyasi uzantisiyla) ismini giriniz:\n");
    char *fileName=(char*)malloc(DATA_SIZE*(sizeof(char)));
    scanf("%s",fileName);
    printf("\nRecursive fonksiyon içeriyor mu?(evet veya hayir)\n");
    char *cevap=(char*)malloc(5*(sizeof(char)));;
    scanf("%s",cevap);
    FILE *from=open_file(fileName);
    free(fileName);
	bigO[bigOLen]='1';
    bigOLen++;
    
    reading_file(from);
	time_spent();
	if(strcmp(cevap,"hayir")==0){
		
		counting_keywords(bigO,from);
		bigO[bigOLen]='\0';
		printf("\n\nZaman Karmasikligi:\n");
		print_bigO(bigO);
		printf("\n\nYer Karmasikligi:\n");
		fseek(from,30,SEEK_SET);
		space_complexity(from,bigO);
	}else if(strcmp(cevap,"evet")==0){
		recursive_fonk(from,bigO);
	}
	
	
	
	free(cevap);
    free(bigO);
    fclose(from);
    
  return 0;
}
