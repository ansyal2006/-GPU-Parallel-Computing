//SOLUTION FOR the equation (y=Ax)(where A is a sparse matrix) using ELL Method.
#include<bits/stdc++.h>
using namespace std;
int main()
{
    cout<<"Solving the equation y=Ax for a sparse matrix A.\n";
    int n,nnz=0;//n represents the size of (n X n) array A, nnz represents the maximum number of non-zero elements in a row of A.
    cout<<"Enter the size of square matrix A :";
    cin>>n;
    vector<vector<int> >A;
    A.resize(n,vector<int>(n));
    for(int i=0;i<n;i++)
    {
        int cnt=0;
        cout<<"\nEnter the "<<i<<"th row of matrix A :";
        for(int j=0;j<n;j++)
        {
            int x;
            cin>>x;
            A[i][j]=x;
            if(x)
                cnt++;
        }
        nnz=max(cnt,nnz);
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
    vector<vector<int> >data,indices;
    data.resize(n,vector<int>(nnz,INT_MAX));
    indices.resize(n,vector<int>(nnz,INT_MAX));
    for(int i=0;i<n;i++)
    {
        int k=0;
        for(int j=0;j<n;j++)
        {
            if(A[i][j])
            {
                data[i][k]=A[i][j];
                indices[i][k]=j;
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
    cout<<"\n\nThe two sparse storage vectors are:";
    cout<<"\ndata[]:\n\t";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<nnz;j++)
        {
            if(data[i][j]==INT_MAX)
                cout<<"*"<<" ";
            else
                cout<<data[i][j]<<" ";
        }
        cout<<"\n\t";
    }
    cout<<"\nindices[]:\n\t";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<nnz;j++)
        {
            if(indices[i][j]==INT_MAX)
                cout<<"*"<<" ";
            else
                cout<<indices[i][j]<<" ";
        }
        cout<<"\n\t";
    }

    //The arrays val,col_ind and row_ptr are established now.
    //Solving the equation y=Ax.
    cout<<"\n\nThe solution matrix y :\n\t";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<nnz;j++)
        {
            if(data[i][j]==INT_MAX)
                break;
            y[i]=y[i]+(data[i][j])*x[indices[i][j]];
        }
        cout<<y[i]<<"\t";
    }
    return 0;
}
