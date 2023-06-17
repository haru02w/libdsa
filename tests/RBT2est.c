#include <stdlib.h>
#include <stdio.h>
#include <dsa.h>

int comparator(const void *a, const void *b){
	return ((int *) b) - ((int *) a); 
}

void printer(const void *a){
	printf("%d", *((int *) a));
}

int main(){
	dsRedBlackTree_t *tree = dsRBTNew(&comparator, &printer);
	int *value =(int *) malloc(sizeof(int));
	*value = 10;
	dsRBTAddNode(tree, value);
	dsPrintRBTree(tree);
	value =(int *) malloc(sizeof(int));
	*value = 12;
	dsRBTAddNode(tree, value);
	dsPrintRBTree(tree);
	value =(int *) malloc(sizeof(int));
	*value = 13;
	dsRBTAddNode(tree, value);
	dsPrintRBTree(tree);
	value =(int *) malloc(sizeof(int));
	*value = 9;
	dsRBTAddNode(tree, value);
	dsPrintRBTree(tree);
	value =(int *) malloc(sizeof(int));
	*value = 3;
	dsRBTAddNode(tree, value);
	dsPrintRBTree(tree);
	*value = 10;
	if(dsRBTRemoveElem(tree, value))
		puts("sim");
	else	
		puts("não");
	dsPrintRBTree(tree);
	dsRBTclear(tree);
	return 0;
}
