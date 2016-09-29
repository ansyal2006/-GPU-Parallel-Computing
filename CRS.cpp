//SOLUTION FOR the equation (y=Ax)(where A is a sparse matrix) using Compressed Row Storage(CRS) Method.
#include<bits/stdc++.h>
using namespace std;
int main()
{
    cout<<"Solving the equation y=Ax for a sparse matrix A.\n";
    int n,nnz=0;//n represents the size of (n X n) array A, nnz represents the number of non-zero elements in A.
    cout<<"Enter the size of square matrix A :";
    cin>>n;
    vector<vector<int> >A;
    A.resize(n,vector<int>(n));
    for(int i=0;i<n;i++)
    {
        cout<<"\nEnter the "<<i<<"th row of matrix A :";
        for(int j=0;j<n;j++)
        {
            int x;
            cin>>x;
            A[i][j]=x;
            if(x!=0)
                nnz++;
        }
    }
    //Printing matrix A
    cout<<"\nMatrix A is:\n";
    for(int i=0;i<n;i++)
    {
        cout<<"\t";
        for(int j=0;j<n;j++)
        {
            cout<<A[i][j]<<"\t";
        }
        cout<<"\n";
    }
    cout<<"\n";
    vector<int>val,col_ind,row_ptr;
    val.resize(nnz);
    col_ind.resize(nnz);
    row_ptr.resize(n+1);
    row_ptr[n]=nnz;//the last index row_ptr[n] is equal to (nnz+1)
    int k=0,q=0;
    for(int i=0;i<n;i++)
    {
        int flag=0;
        for(int j=0;j<n;j++)
        {
            if(A[i][j]!=0)
            {
                val[k]=A[i][j];
                col_ind[k]=j;
                if(flag==0)
                {
                    row_ptr[q]=k;
                    q++;
                    flag=1;
                }
                k++;
            }
        }
    }

    vector<int>y,x;
    x.resize(n);
    y.resize(n,0);
    cout<<"Enter the matrix x :";
    for(int i=0;i<n;i++)
    {
        int t;
        cin>>t;
        x[i]=t;
    }
    cout<<"Matrix x is :\n\t";
    for(int i=0;i<n;i++)
    {
        cout<<x[i]<<"\t";
    }
    cout<<"\n\nThe three sparse storage vectors are:";

    cout<<"\nval[]:\n\t";
    for(int i=0;i<val.size();i++)
        cout<<val[i]<<" ";
    cout<<"\ncol_ind[]:\n\t";
    for(int i=0;i<col_ind.size();i++)
        cout<<col_ind[i]<<" ";
    cout<<"\nrow_ptr[]:\n\t";
    for(int i=0;i<row_ptr.size();i++)
        cout<<row_ptr[i]<<" ";

    //The arrays val,col_ind and row_ptr are established now.
    //Solving the equation y=Ax.
    cout<<"\n\nThe solution matrix y :\n\t";
    for(int i=0;i<n;i++)
    {
        for(int j=row_ptr[i];j<row_ptr[i+1];j++)
        {
            y[i]=y[i]+val[j]*x[col_ind[j]];
        }
        cout<<y[i]<<"\t";
    }
    return 0;
}
