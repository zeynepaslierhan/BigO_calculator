#include <stdio.h>
int factorial (int n) {    
    if (n <= 1) 
        return 1 ;
    else
        return n * factorial(n-1);
}
int main(){
    int sonuc,n=6;
    sonuc=factorial(n);
    printf("%d", sonuc);	
    return 0;
        
}