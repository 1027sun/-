#include <stdio.h>
#include <stdlib.h>
#include"AVLtree.h"

AvlTree MakeEmpty(AvlTree T){
	if(T){
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}
 
AvlTree CreateAvlTree(void){
	return NULL;
}

Position Find(ElementType X,AvlTree T){
	if(T==NULL){
		printf("未找到%d\n",X);
		return NULL;
	}
	if(X==T->Element){
		printf("找到了%d\n",X);
		return T;
	}
	else if(X<T->Element){
		return Find(X,T->Left);
	}
	else if(X>T->Element){
		return Find(X,T->Right);
	}
}

Position FindMin(AvlTree T){
	if(T==NULL){
		printf("该树为空树\n");
		return NULL;
	}
	while(T->Left){
		T=T->Left;
	}
	return T;
}

Position FindMax(AvlTree T){
	if(T==NULL){
		printf("该树为空树\n");
		return NULL;
	}
	while(T->Right){
		T=T->Right;
	}
	return T;
}

AvlTree Insert(ElementType X,AvlTree T){
	if(T==NULL){
		T=malloc(sizeof(struct AvlNode));
		if(!T){
		   printf("Out Of Space\n");
		   return NULL;
		}
		T->Left=NULL;
		T->Right=NULL;
		T->Element=X;
		T->Height=0;
	}
	else if(X<T->Element){
		T->Left=Insert(X,T->Left);
		if(GetHeight(T->Left)-GetHeight(T->Right)==2){
			if(X>T->Left->Element){
				T=DoubleRotate_LeftRight(T);
			}
			else T=SingleRotate_LeftLeft(T);
		}
	}
	else if(X>T->Element){
		T->Right=Insert(X,T->Right);
		if(GetHeight(T->Right)-GetHeight(T->Left)==2){
			if(X<T->Right->Element){
				T=DoubleRotate_RightLeft(T);
			}
			else T=SingleRotate_RightRight(T);
		}
	}
	T->Height=(GetHeight(T->Left)>GetHeight(T->Right) ? GetHeight(T->Left):GetHeight(T->Right))+1;
	return T;
}

int GetHeight(AvlTree T){
	if(!T){
		return -1;
	}
	else return T->Height;
}

AvlTree SingleRotate_LeftLeft(AvlTree T){
	Position temp;
	temp=T->Left;
	T->Left=temp->Right;
	temp->Right=T;
	T->Height=(GetHeight(T->Left)>GetHeight(T->Right) ? GetHeight(T->Left):GetHeight(T->Right))+1;
	temp->Height=(GetHeight(temp->Left)>GetHeight(temp->Right) ? GetHeight(temp->Left):GetHeight(temp->Right))+1;
	return temp;
}

AvlTree SingleRotate_RightRight(AvlTree T){
	Position temp;
	temp=T->Right;
	T->Right=temp->Left;
	temp->Left=T;
	T->Height=(GetHeight(T->Left)>GetHeight(T->Right) ? GetHeight(T->Left):GetHeight(T->Right))+1;
	temp->Height=(GetHeight(temp->Left)>GetHeight(temp->Right) ? GetHeight(temp->Left):GetHeight(temp->Right))+1;
	return temp; 
}

AvlTree DoubleRotate_LeftRight(AvlTree T){
	T->Left=SingleRotate_RightRight(T->Left);
	return SingleRotate_LeftLeft(T);
}

AvlTree DoubleRotate_RightLeft(AvlTree T){
	T->Right=SingleRotate_LeftLeft(T->Right);
	return SingleRotate_RightRight(T);
}

AvlTree Delete(ElementType X,AvlTree T){
	Position P=Find(X,T);
	if(P==NULL){
		printf("该树中没有%d",X);
	}
	P->Element=-2;//懒惰删除 
	return T;
}

ElementType Retrieve(Position P){
	if(P==NULL){
		printf("此处为空");
		return -1;
	}
	return P->Element; 
}

int Get_AvlNodeHeight(AvlTree T){
	if(!T){
		return 0;
	}
	int LeftHeight=GetHeight(T->Left);
	int RightHeight=GetHeight(T->Right);
	return (LeftHeight>RightHeight ? LeftHeight:RightHeight)+1;
} 

void calculateCoordinates(AvlTree T, int x, int y, int offset){
	if(!T||y>=MAX_HEIGHT||x<0||x>MAX_WIDTH){
		return;
	}
	treemap[y][x]=T->Element;
	int child_offset=offset/2;
	child_offset=child_offset>0 ? child_offset:1;
	if(T->Left) calculateCoordinates(T->Left,x-offset,y+2,child_offset);
	if(T->Right) calculateCoordinates(T->Right,x+offset,y+2,child_offset);
	if(T->Left){
		connmap[y+1][x-offset/2]='/';
	}
	if(T->Right){ 
		connmap[y+1][x+(offset+2)/2]='\\';
	}
}

void PrintAvlTree_anceng(AvlTree T){
	if(!T){
		printf("该树为空");
		return; 
	}
	int first_offset=Pow(2,GetHeight(T)); 
	for(int i=0;i<MAX_HEIGHT;i++){
		for(int j=0;j<MAX_WIDTH;j++){
			treemap[i][j]=-1;
			connmap[i][j]=' ';
	    }
	}
	calculateCoordinates(T,first_offset,0,first_offset/2);
	for(int y=0;y<MAX_HEIGHT;y++){
		for(int x=0;x<MAX_WIDTH;x++){
		   if(treemap[y][x]!=-1) {
			  printf("%2d",treemap[y][x]);
			  x++; 
		     }	else printf("%c",connmap[y][x]);
        }
        printf("\n");
    }
}

int Pow(int a,int b){
	int t=1;
	for(int i=1;i<=b;i++){
		t*=a;
	}
	return t;
}








