#include <stdio.h>
#include <stdlib.h>
typedef struct{
	int *elem;
	int Tablelen;
}SSTable;

int Search_Seq(SSTable ST,int key){
	int i;
	for(i=0;i<ST.Tablelen && ST.elem[i]!=key;++i){
	}
	return i==ST.Tablelen?-1:i;
} 

typedef struct{
	int *elem;
	int Tablelen;
}SSTable;

int Search_Seq(SSTable ST,int key){
	ST.elem[0]=key;
	int i;
	for(i=ST.Tablelen;ST.elem[i]!=key;--i){
	}
	return i;
}	

typedef struct{
	int *elem;
	int Tablelen;
}SSTable;

int Binary_Search(SSTable &L,int key){
	int low=0,high=L.Tablelen-1,mid; 
	while(low<=high){
		mid=(low+high)/2;
		if(L.elem[mid]==key)
			return mid;
		else if(L.elem[mid]>key)
			high=mid-1;
		else
			low=mid+1;
	}
	return -1;
} 

typedef struct{
	int max;
	int low,high;	
}Index;
int List[100]; 

struct Node{
	int keys[4];
	struct Node* child[5];
	int num;
}; 

//hash list:



































