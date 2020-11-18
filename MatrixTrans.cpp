//矩阵转置
#include "Triple.hpp"
int main()
{
    int nline;
    int ncol;
    cout << "请输入矩阵M的行数：" << endl;
    cin >> nline;
    cout << "请输入矩阵M的列数：" << endl;
    cin >> ncol;
    cout << "请输入矩阵M的数据：" << endl;
    vector<vector<int> > M(nline, vector<int>(ncol));
    int i = 0;
    int j = 0;
    while (cin >> M[i][j])
    {
        if (cin.get() == '\n')
            break;
        j++;
        if (j == ncol)
        {
            j = 0;
            i++;
        }
    }
    TMatrix T;
    T.rn = nline;
    T.cn = ncol;
    T.tn = 0;
    for (int i = 0; i < nline; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            if (M[i][j] != 0)
            {
                Triple t;
                t.row = i+1;
                t.col = j+1;
                t.value = M[i][j];
                T.data[T.tn] = t;
                T.tn++;
            }
        }
    }
    TMatrix Tb;
    TMatrix Tc;
    TransMatrix(T,Tb);
    TransMatrix(T,Tc);
    cout<<"简单转置算法的结果是："<<endl;
    printTriple(Tb);
    cout<<"快速转置算法的结果是："<<endl;
    printTriple(Tc);
    return 0;
}