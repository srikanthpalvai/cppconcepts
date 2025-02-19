#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char *name;
	char sirname[] = "palvai";

//	printf("hello main \n");
	name = (char*)malloc(sizeof(char)* 10);
//	printf("name:%s\n", name);
//	memset(name, '\0', 10);
//	strcpy(name, "srikanth");
	//free(name);
	return 0;
}
