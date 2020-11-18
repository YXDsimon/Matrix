#include <stdlib.h>
#include <stdio.h>
#define MAXSIZE 100	//非零元的最大个数
#define MAX_ROW_NUM 20//最大行列数
#define ElenType int
#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW -1
 

typedef struct {
	int row,col;
	ElenType data;
}Triple;
typedef struct {
	Triple dataArray[MAXSIZE+1];
	int rpos[MAX_ROW_NUM+1];
	int row_count,col_count,data_count;
}*TSMatrix,Matrix;
 
/*创建一个矩阵*/
Status CreateTSMatrix(TSMatrix &M){
	M = (TSMatrix)malloc(sizeof(Matrix));
	if(!M){
		exit(OVERFLOW);
	}
	printf("输入三元组的行数，列数和非零元个数：");
	int rc,cc,dc;
	scanf("%d%d%d",&rc,&cc,&dc);
	M->row_count = rc;
	M->col_count = cc;
	M->data_count = dc;
	int i = 0;
	printf("开始构造矩阵\n");
	int r,c,d;
	while(i<dc){
		printf("输入第%d个非零元的行号，列号和值：",i+1);
		scanf("%d%d%d",&r,&c,&d);
		if(r>rc || c>cc){	
			printf("此组数据不合法，请重新输入\n");
			continue;
		}else{
			M->dataArray[i+1].row = r;
			M->dataArray[i+1].col = c;
			M->dataArray[i+1].data = d;
			i++;
		}
	}

	for(i=1;i<=M->row_count;i++){
		M->rpos[i] = 0;
	}
	for(i=1;i<=M->data_count;i++){
		M->rpos[M->dataArray[i].row]++;
	}
	
	for(i=M->row_count;i>=1;i--){
		M->rpos[i] = 1;
		for(int j=i-1;j>=1;j--){
			M->rpos[i] += M->rpos[j];
		}
	}
	printf("构造矩阵成功\n");
	return OK;
}
/*打印三元组矩阵*/
Status PrintTSMatrix(TSMatrix M){
	//用描述法吧
	for(int i=1;i<=M->data_count;i++){
		printf("行号 列号 值：%d %d %d",M->dataArray[i].row,M->dataArray[i].col, M->dataArray[i].data);
		printf("\n");
	}
	return OK;
}
Status MultTSMatrix(TSMatrix M,TSMatrix N,TSMatrix &Q){
	int arow,brow,p,q,ccol,ctemp[MAX_ROW_NUM+1],t,tp;
	if(M->col_count != N->row_count){
		return ERROR;
	}
	if(0 == M->data_count * N->data_count ){
		return ERROR;
	}

	Q->row_count = M->row_count;
	Q->col_count = N->col_count;
	Q->data_count = 0;

	for(arow=1;arow<=M->row_count;arow++){
		for(ccol=1;ccol<=Q->col_count;ccol++){
			ctemp[ccol] = 0;
		}
		Q->rpos[arow] = Q->data_count + 1;
		if(arow < M->row_count){
			tp = M->rpos[arow+1];
		}else{
			tp = M->data_count + 1;
		}
		for(p=M->rpos[arow];p<tp;p++){		
			brow = M->dataArray[p].col;
			if(brow<N->row_count){
				t = N->rpos[brow+1];
			}else{
				t = N->data_count+1;
			}
			for(q=N->rpos[brow];q<t;q++){
				ccol = N->dataArray[q].col;
				ctemp[ccol] += M->dataArray[p].data * N->dataArray[q].data;
			}
		}

		for(ccol=1;ccol<=Q->col_count;ccol++){
			if(0!=ctemp[ccol]){
				if(++Q->data_count > MAXSIZE){
					return ERROR;
				}
				Q->dataArray[Q->data_count].row = arow;
				Q->dataArray[Q->data_count].col = ccol;
				Q->dataArray[Q->data_count].data = ctemp[ccol];
			}
		}
	}//for_arow
	return OK;
}
int main(){
	TSMatrix M,N,Q;
	Q = (TSMatrix)malloc(sizeof(TSMatrix));
	CreateTSMatrix(M);
	printf("矩阵M：\n");
	PrintTSMatrix(M);
	CreateTSMatrix(N);
	printf("矩阵N：\n");
	PrintTSMatrix(N);
	MultTSMatrix(M,N,Q);
	printf("矩阵Q：\n");
	PrintTSMatrix(Q);
	return 0;
}