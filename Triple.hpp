#define MAX_SIZE 100
#define MAX_ROW 10
#define MAXRC 100
#include <iostream>
#include <vector>
using namespace std;

//三元组结点定义
typedef int ELEM;
typedef struct
{
    int row;    //行下标
    int col;    //列下标
    ELEM value; //元素值
} Triple;

//三元组顺序表定义
typedef struct
{
    int rn; //行数
    int cn; //列数
    int tn; //非0元素 个数
    Triple data[MAX_SIZE];
} TMatrix;

typedef struct
{
    Triple data[MAX_SIZE];
    int rpos[MAX_ROW] = {0};
    int rn, cn, tn;
} RLSMatrix;

void TransMatrix(TMatrix a, TMatrix &b)
{
    int p, q, col;
    b.rn = a.cn;
    b.cn = a.rn;
    b.tn = a.tn;
    if (b.tn == 0)
        cout << "The Matrix A = 0" << endl;
    else
    {
        q = 0;
        for (col = 1; col <= a.cn; col++)
            for (p = 0; p <= a.tn; p++)
                if (a.data[p].col == col)
                {
                    b.data[q].row = a.data[p].col;
                    b.data[q].col = a.data[p].row;
                    b.data[q].value = a.data[p].value;
                    q++;
                }
    }
}

void FastTransMatrix(TMatrix a, TMatrix &b)
{
    int p, q, col, k;
    int num[MAX_SIZE], cpot[MAX_SIZE];
    b.rn = a.cn;
    b.cn = a.rn;
    b.tn = a.tn;
    /* 置三元组表b.data的行、列数和非0元素个数 */
    if (b.tn == 0)
        cout << "The Matrix A = 0" << endl;
    else
    {
        for (col = 1; col <= a.cn; ++col)
            num[col] = 0;
        for (k = 1; k <= a.tn; ++k)
            ++num[a.data[k].col];
        for (cpot[1] = 1, col = 2; col <= a.cn; ++col)
            cpot[col] = cpot[col - 1] + num[col - 1];
        for (p = 1; p <= a.tn; ++p)
        {
            col = a.data[p].col;
            q = cpot[col];
            b.data[q].row = a.data[p].col;
            b.data[q].col = a.data[p].row;
            b.data[q].value = a.data[p].value;
            ++cpot[col];
        }
    }
}

//打印三元组
void printTriple(TMatrix T)
{
    for (int i = 0; i < T.tn; i++)
    {
        cout << '[' << T.data[i].row << ' ' << T.data[i].col << ']' << ' ' << T.data[i].value << endl;
    }
}

void printTriple(RLSMatrix T)
{
    for (int i = 0; i < T.tn; i++)
    {
        cout << '[' << T.data[i].row << ' ' << T.data[i].col << ']' << ' ' << T.data[i].value << endl;
    }
}