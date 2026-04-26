#include <stdio.h>
#include <stdlib.h>
#include"AVLtree.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	AvlTree T;
	T=CreateAvlTree();
	T=Insert(1,T);
	T=Insert(2,T);
	T=Insert(3,T);
	T=Insert(4,T);
	T=Insert(5,T);
    T=Insert(6,T);
    T=Insert(7,T);
    T=Insert(8,T);
	T=Delete(6,T);
    T=Insert(9,T);
	T=Delete(8,T); 
	PrintAvlTree_anceng(T);
	MakeEmpty(T);
	return 0;
}
