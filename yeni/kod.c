#include <stdio.h>
int main(){
	int i,j;
	int sum = 0;
	int n=10;
	int arr[n][n];
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
		    arr[i][j]=i*j;
			sum = sum + arr[i][j];
		}
	}
        printf("%d", sum);	
        return 0;
        
}