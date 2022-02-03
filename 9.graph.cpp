#include <stdio.h>
//Adjacency Matrix:
typedef char VertexType;
typedef int EdgeType;
#define MAXVEX 100
#define INFINITY 65535
typedef struct{
	VertexType vexs[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVertexs,numEdges;
}MGraph;

void Create_MGraph(MGraph *G){
	int i,j,k,w;
	printf("Please input numbers of vertexs and edges:\n");
	scanf("%d%d",&G->numVertexs,&G->numEdges);
	for(i=0;i<G->numVertexs;i++){
		scanf("%c",&G->vexs[i]);
	}
	for(i=0;i<G->numEdges;i++){
		for(j=0;j<G->numEdges;j++){
			G->arc[i][j]=INFINITY;
		}
	}
	for(k=0;k<G->numEdges;k++){
		printf("Please input start,end and weight of the edge\n");
		scanf("%d%d%d",&i,&j,&w);
		G->arc[i][j]=w;;
		G->arc[j][i]=G->arc[i][j];
	}
}

//Adjacency List:
typedef struct EdgeNode{
	int adjvex;
	EdgeType weight;
	struct EdgeNode *next;
}EdgeNode;

typedef struct VertexNode{
	VertexType data;
	EdgeNode *firstedge;
}VertexNode,AdjList[MAXVEX];

typedef struct{
	AdjList adjlist;
	int numVertexs,numEdges;
}AdjGraph;

void Create_AdjGraph(AdjGraph *G){
	int i,j,k;
	EdgeNode *e;
	printf("Please input the number of edges & vertexs:\n");
	scanf("%d%d",&G->numEdges,&G->numVertexs);
	for(i=0;i<G->numVertexs;i++){
		scanf("%c",&G->adjlist[i].data);
		G->adjlist[i].firstedge=NULL;
	}
	for(k=0;k<G->numEdges;k++){
		printf("Please input start and end of the edge:\n");
		scanf("%d%d",&i,&j);
		if(i==j){continue;}
		//first edge
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		e->adjvex=j;
		e->next=G->adjlist[i].firstedge;
		G->adjlist[i].firstedge=e;//Head Insert of LinkList;
		//second edge
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		e->adjvex=i;
		e->next=G->adjlist[j].firstedge;
		G->adjlist[j].firstedge=e;
	}
}

//DFS:
#define MAX 100
typedef int Boolean;
Boolean visited[MAX];
//Adjacency Matrix:
void DFS(MGraph G,int i){
	int j;
	visited[i]=true;
	printf("%c",G.vexs[i]);
	for(j=0;j<G.numVertexes;j++){
		if(G.arc[i][j]!=INFINITY&&!visited[j]){
			DFS(G,j);
		}
	}
}
void DFSTraverse(MGraph G){
	int i;
	for(i=0;i<G.numVertexes;i++){
		visited[i]=false;
	}
	for(i=0;i<G.numVertexes;i++){
		if(visited[i]!=false){
			DFS(G,i);
		}
	}
}
//Adjaency List:
void DFS(AdjGraph G,int i){
	EdgeNode *p;
	visited[i]=true;
	printf("%c",G.adjlist[i].data);
	p=G.adjlist[i].firstedge;
	while(p){
		if(!visited[p->adjvex]){
			DFS(G,p->adjvex);
		}
		p=p->next;
	}
}

void DFSTraverse(AdjGraph G){
	int i;
	for(i=0;i<G.numVertexs;i++){
		visited[i]=false;
	}
	for(i=0;i<G.numVertexs;i++){
		if(!visited[i]){
			DFS(G,i);
		}
	}
}

//BFS:
#define MaxSize 10
typedef struct{
	int data[MaxSize];
	int front,rear;
}SqQueue;

void InitQueue(SqQueue &Q){
	Q.rear=Q.front=0;
}
bool QueueEmpty(SqQueue Q){
	if(Q.rear==Q.front)
		return true;
	else
		return false;
}
bool EnQueue(SqQueue &Q,int x){
	if((Q.rear+1)%MaxSize==Q.front)
		return false;
	Q.data[Q.rear]=x;
	Q.rear=(Q.rear+1)%MaxSize;
	return true;
}
bool DeQueue(SqQueue &Q,int &x){
	if(Q.rear==Q.front)
		return false;
	x=Q.data[Q.front];
	Q.front=(Q.front+1)%MaxSize;
	return true;
}

void BFSTraverse(MGraph G){
	int i,j;
	SqQueue Q;
	for(i=0;i<G.numVertexes;i++){
		visited[i]=0;
	}
	InitQueue(&Q);
	for(i=0;i<G.numVertexes;i++){
		if(!visited[i]){
			visited[i]=true;
			printf("%c",G.vexs[i]);
			EnQueue(&Q,i);
			while(!QueueEmpty(Q)){
				DeQueue(&Q,&i);
				for(j=0;j<G.numVertexes;j++){
					if(G.arc[i][j]!=0&&!visited[j]){
						visited[j]=true;
						printf("%c",G.vexs[j]);
						EnQueue(&Q,j);
					}
				}
			}
		}
	}
}

void BFSTraverse(AdjGraph G){
	int i;
	EdgeNode *p;
	SqQueue Q;
	for(i=0;i<G.numVertexs;i++){
		visited[i]=false;
	}
	InitQueue(&Q);
	for(i=0;i<G.numVertexs;i++){
		if(!visited[i]){
			visited[i]=true;
			printf("%c",G.adjlist[i].data);
			EnQueue(&Q,i);
			while(!QueueEmpty(Q)){
				DeQueue(&Q,&i);
				p=G.adjlist[i].firstedge;
				while(p){
					if(!visited[p->adjvex]){
						visited[p->adjvex]=true;
						printf("%c",G.adjlist[p->adjvex].data);
						EnQueue(&Q,p->adjvex);
					}
					p=p->next;
				}
			}
		}
	}
}

//MST:
void MST_Prim(MGraph G){
	int min,i,j,k;
	int adjvex[MAXVEX];//save adjvex number
	int lowcost[MAXVEX];//save the min cost to adjvex
	lowcost[0]=0;//V0 is set as the first Node
	adjvex[0]=0;
	for(i=1;i<G.numVertexes;i++){
		lowcost[i]=G.arc[0][i];
		adjvex[i]=0;
	}
	for(i=1;i<G.numVertexes;i++){
		min=INFINITY;
		j=1;k=0;
		while(j<G.numVertexes){
			if(!lowcost[j]&&lowcost[j]<min){
				min=lowcost[j];
				k=j;
			}
			j++;
		}
		printf("(%d,%d)",adjvex[k],k);
		lowcost[k]=0;
		for(j=1;j<G.numVertexes;j++){
			if(lowcost[j]!=0&&G.arc[k][j]<lowcost[j]){
				lowcost[j]=G.arc[k][j];
				adjvex[j]=k;
			}
		}
	}
}

//Kruskal:
#define MAXEDGE 100
typedef struct{
	int begin;
	int end;
	int weight;
}Edge;

void MST_Kruskal(MGraph G){
	int i,n,m;
	Edge edge[MAXEDGE];
	int parent[MAXVEX];
	for(i=0;i<G.numVertexes;i++){
		parent[i]=0;
	}
	for(i=0;i<G.numEdges;i++){
		n=Find(parent,edge[i].begin);
		m=Find(parent,edge[i].end);
		if(m!=n){
			parent[n]=m;
			printf("(%d,%d) %d",
			edge[i].begin,edge[i].end,edge[i].weight);
		}
	}
}

int Find(int *parent,int f){
	while(parent[f]>0){f=parent[f];}
	return f;
}

//Dijkstra:
#define MAXVEX 9
typedef int Patharc[MAXVEX];
typedef int ShortPathTable[MAXVEX];

void ShortestPath_Dijkstra(MGraph G, int v0, Patharc *p, ShortPathTable *D){
	int v,w,k,min;
	int final[MAXVEX];
	for(v=0;v<G.numVertexes;v++){
		final[v]=0;
		(*D)[v]=G.arc[v0][v];
		(*p)[v]=0;
	}
	(*D)[v0]=0;final[v0]=1;
	for(v=1;v<G.numVertexes;v++){
		min=INFINITY;
		for(v=1;v<G.numVertexes;v++){
			if(!final[w]&&(*D)[w]<min){
				k=w;
				min=(*D)[w];
			}
		}
		final[k]=1;
		for(w=0;w<G.numVertexes;w++){
			if(!final[w]&&(min+G.arc[k][w]<(*D)[w])){
				(*D)[w]=min+G.arc[k][w];
				(*p)[w]=k;
			}
		}
	}
}

//Floyd:
typedef int PathMatrix[MAXVEX][MAXVEX];
typedef int ShortPathMatrix[MAXVEX][MAXVEX];

void ShortestPath_Floyd(MGraph G,PathMatrix *P,ShortPathTable *D){
	int v,w,k;
	for(v=0;v<G.numVertexes;++v){
		for(w=0;w<G.numVertexes;++w){
			(*D)[v][w]=G.arc[v][w];
			(*P)[v][w]=w;
		}
	}//Initialization
	for(k=0;k<G.numVertexes;k++){
		for(v=0;v<G.numVertexes;v++){
			for(w=0;w<G.numVertexes;w++){
				if((*D)[v][w]>(*D)[v][k]+(*D)[k][w]){
					(*D)[v][w]=(*D)[v][k]+(*D)[k][w];
					(*P)[v][w]=(*P)[v][k];
				}
			}
		}
	}
	//output:
	for(v=0;v<G.numVertexes;v++){
		for(w=v+1;w<G.numVertexes;w++){
			printf("v%d-x%d weight%d",v,w,D[v][w]);
			k=P[v][w];
			printf("path:%d",v);
			while(k!=w){
				printf("-> %d",k);
				k=P[k][w];
			}
			printf("-> %d",w);
		}
		printf("\n");
	}
}

//topo logical sort:
typedef struct EdgeNode{
	int adjvex;
	EdgeType weight;
	struct EdgeNode *next;
}EdgeNode;

typedef struct VertexNode{
	VertexType data;
	int in,out;
	EdgeNode *firstedge;
}VertexNode,AdjList[MAXVEX];

typedef struct{
	AdjList adjlist;
	int numVertexs,numEdges;
}AdjGraph;

bool Topologicalsort(AdjGraph GL){
	EdgeNode *e;
	int i,k,gettop;
	int top=-1,count=0;
	int *Stack;
	Stack=(int*)malloc(GL.numVertexs*sizeof(int));
	for(i=0;i<GL.numVertexs;i++){
		if(GL.adjlist[i].in==0){
			Stack[++top]=i;
		}
	}
	while(top!=-1){
		gettop=Stack[top--];
		printf("%d->",GL.adjlist[gettop].data);
		count++;
		for(e=GL.adjlist[gettop].firstedge;e;e=e->next){
			k=e->adjvex;
			if(!(--GL.adjlist[k].in)){
				Stack[++top]=k;
			}
		}
	}
	if(count<GL.numVertexs){return false;}
	else{return true;}
}

//AOE Net:
int *etv,*ltv;//early/late incident time
int *stack2;
int top2;
//step1:use topologicsort to get etv&ltv:
bool Topologicalsort1(AdjGraph GL){
	EdgeNode *e;
	int i,k,gettop;
	int top=-1,count=0;
	int *Stack;
	Stack=(int*)malloc(GL.numVertexs*sizeof(int));
	for(i=0;i<GL.numVertexs;i++){
		if(GL.adjlist[i].in==0){
			Stack[++top]=i;
		}
	}
	top2=0;
	etv=(int*)malloc(GL.numVertexs*sizeof(int));
	for(i=0;i<GL.numVertexs;i++){
		etv[i]=0;
	}
	stack2=(int*)malloc(GL.numVertexs*sizeof(int));
	while(top!=-1){
		gettop=Stack[top--];
		count++;
		stack2[++top2]=gettop;
		for(e=GL.adjlist[gettop].firstedge;e;e=e->next){
			k=e->adjvex;
			if(!(--GL.adjlist[k].in)){
				Stack[++top]=k;
			}
			if((etv[gettop]+e->weight)>etv[k]){
				etv[k]=etv[gettop]+e->weight;
			}
		}
	}
	if(count<GL.numVertexs){return false;}
	else{return true;}
}
//step2:get critical path:
void CriticalPath(AdjGraph GL){
	EdgeNode *e;
	int i,gettop,j,k;
	int ete,lte;//early/late activity time
	Topologicalsort1(GL);
	ltv=(int*)malloc(GL.numVertexs*sizeof(int));
	for(i=0;i<GL.numVertexs;i++){
		ltv[i]=etv[GL.numVertexs-1];
	}
	while(top2!=0){
		gettop=stack2[top2--];
		for(e=GL.adjlist[gettop].firstedge;e!=NULL;e=e->next){
			k=e->adjvex;
			if(ltv[k]-e->weight<ltv[gettop]){
				ltv[gettop]=ltv[k]-e->weight;
			}
		}
	}
	for(j=0;j<GL.numVertexs;j++){
		for(e=GL.adjlist[j].firstedge;e;e=e->next){
			k=e->adjvex;
			ete=etv[j];
			lte=ltv[k]-e->weight;
			if(ete==lte){
				printf("<v%d,v%d> length:%d"
				,GL.adjlist[j].data,GL.adjlist[k].data,e->weight);
			}
		}
	}
}




