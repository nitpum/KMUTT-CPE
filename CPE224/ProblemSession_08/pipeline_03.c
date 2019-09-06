#include <stdio.h>

int main()
{
	int i,j;
	long sum,x;
	
	for (i=0;i<10;i++){
		for(j=0;j<10;j++){
			x=i+j;
			sum = sum+x;
		}
	}
	printf("%ld\n",sum);
}