#include <stdio.h>

int main()
{
	int a;
	int b[] = {80,70,60,50};
	int *c;
	c=b+2;
	scanf("%d",&a);
	if(a>100) printf("Error\n"); 
	else if(a>80) printf("A\n"); 
	else if(a>b[1]) printf("B\n"); 
	else if(a>*c) printf("C\n"); 
	else if(b[3] <= a) printf("D\n"); 
	else if(a>=0) printf("F\n");
	else printf("Error\n"); 
	
	return 0;
}