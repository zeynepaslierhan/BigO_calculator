#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int toplam(int dizi[], int n)
        {
                int x = 0
                for (int i = 0; i < n; i++)
                {
                        x = x +  dizi[i];
                }
                return x;
        }
int main()
{
	int dizi[20];

	toplam(dizi,20); 
	return 0;
}