//SOLUTION FOR the equation (y=Ax)(where A is a sparse matrix) using Compressed Row Storage(CRS) Method.
#include<bits/stdc++.h>
#include<Eigen/Dense>

using namespace std;
using namespace Eigen;

using Eigen::MatrixXd;
int main()
{
    int iteration;
    cin>>iteration;

    ifstream myfile1[iteration];
    ofstream myfile5[iteration];
    ofstream myfile6[iteration];
    ofstream myfile7[iteration];

    string name1="matrix";
    string name5="row_ptr";
    string name6="col_ind";
    string name7="val";

    for(int it=0;it<iteration;it++)
    {

    //cout<<"Solving the equation y=Ax for a sparse matrix A.\n";
    double n,nnz=0;//n represents the size of (n X n) array A, nnz represents the number of non-zero elements in A.
    //cout<<"Enter the size of square matrix A :";
    //cin>>n;
//    vector<vector<int> >A;
//    A.resize(n,vector<int>(n));
//    for(int i=0;i<n;i++)
//    {
//        cout<<"\nEnter the "<<i<<"th row of matrix A :";
//        for(int j=0;j<n;j++)
//        {
//            int x;
//            cin>>x;
//            A[i][j]=x;
//            if(x!=0)
//                nnz++;
//        }
//    }
    stringstream ss;
    ss<<it+1;
    string s=ss.str();
//    myfile1[it].open(name1+s+".txt");
//    myfile5[it].open(name5+s+".txt");
//    myfile6[it].open(name6+s+".txt");
//    myfile7[it].open(name7+s+".txt");
    myfile1[it].open(name1+s+".txt");
    myfile5[it].open(name5+s+".txt");
    myfile6[it].open(name6+s+".txt");
    myfile7[it].open(name7+s+".txt");
    //cout<<"ff\n";
    int rows;
    myfile1[it]>>rows;
    //cout<<rows<<"\n";
    //cout<<"ff\n";
    //cout<<rows<<"\n";
    MatrixXd A(rows,rows);
    for(int i=0;i<rows;i++)
    {
    //    cout<<"Enter "<<i+1<<" row\n";
        for(int j=0;j<rows;j++)
        {
            myfile1[it]>>A(i,j);
            if(A(i,j)!=0)
                nnz++;
        }
      //  cout<<"\n";
    }
    //cout<<"h";
    n=rows;
    //Printing matrix A
//    cout<<"\nMatrix A is:\n";
//    for(int i=0;i<n;i++)
//    {
//        cout<<"\t";
//        for(int j=0;j<n;j++)
//        {
//            cout<<A[i][j]<<"\t";
//        }
//        cout<<"\n";
//    }
    //cout<<"\n";
    vector<double>val,col_ind,row_ptr;
    val.resize(nnz);
    col_ind.resize(nnz);
    row_ptr.resize(n+1);
    row_ptr[n]=nnz;//the last index row_ptr[n] is equal to (nnz+1)
    int k=0,q=0;
    //cout<<n<<"\n";
    for(int i=0;i<n;i++)
    {
        int flag=0;
        //cout<<"g\n";
        for(int j=0;j<n;j++)
        {
            if(A(i,j)!=0)
            {
                //cout<<"f\n";
                val[k]=A(i,j);
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

//    vector<double>y,x;
//    x.resize(n);
//    y.resize(n,0);
//    cout<<"Enter the matrix x :";
//    for(int i=0;i<n;i++)
//    {
//        double t;
//        cin>>t;
//        x[i]=t;
//    }
//    cout<<"Matrix x is :\n\t";
//    for(int i=0;i<n;i++)
//    {
//        cout<<x[i]<<"\t";
//    }
//    cout<<"\n\nThe three sparse storage vectors are:";
//
//    cout<<"\nval[]:\n\t";
//    for(int i=0;i<val.size();i++)
//        cout<<val[i]<<" ";
//    cout<<"\ncol_ind[]:\n\t";
//    for(int i=0;i<col_ind.size();i++)
//        cout<<col_ind[i]<<" ";
//    cout<<"\nrow_ptr[]:\n\t";
//    for(int i=0;i<row_ptr.size();i++)
//        cout<<row_ptr[i]<<" ";
//
//    ofstream myfile5("row_ptr.txt");
//    ofstream myfile6("col_ind.txt");
//    ofstream myfile7("val.txt");

    myfile5[it]<<row_ptr.size()<<endl;
    for(int i=0;i<row_ptr.size();i++)
        myfile5[it]<<row_ptr[i]<<"\t";

    myfile6[it]<<col_ind.size()<<endl;
    for(int i=0;i<col_ind.size();i++)
        myfile6[it]<<col_ind[i]<<"\t";

    myfile7[it]<<val.size()<<endl;
    for(int i=0;i<val.size();i++)
        myfile7[it]<<val[i]<<"\t";
    //The arrays val,col_ind and row_ptr are established now.
    //Solving the equation y=Ax.
//    cout<<"\n\nThe solution matrix y :\n\t";
//    for(int i=0;i<n;i++)
//    {
//        for(int j=row_ptr[i];j<row_ptr[i+1];j++)
//        {
//            y[i]=y[i]+val[j]*x[col_ind[j]];
//        }
//        cout<<y[i]<<"\t";
//    }
    }
    return 0;
}
