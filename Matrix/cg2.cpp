#include<bits/stdc++.h>
#include<Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/IterativeLinearSolvers>

using namespace std;
using namespace Eigen;

using Eigen::MatrixXd;
//void func(ofstream &f1,ofstream &f2,ofstream &f3)
//{
//    srand(time(NULL));
//    double siz=20;
//    f1<<siz<<endl;
//    for(int i=0;i<siz;i++)
//    {
//        for(int j=0;j<siz;j++)
//            f1<<i+j<<" ";
//        f1<<endl;
//    }
//    for(int i=0;i<siz;i++)
//    {
//        f2<<i<<" ";
//    }
//    f3<<20;
//}


vector<double> mult(vector<double> val,double alpha)
{
    for(int i=0;i<val.size();i++)
        val[i]*=alpha;
    return val;
}

MatrixXd vm(int rows,vector<double> &row_ptr,vector<double> &col_ind,vector<double> &val,MatrixXd X0)
{
    //cout<<"vm\n";
    //vector<double> y;
    MatrixXd y(rows,1);
    for(int i=0;i<rows;i++)
        y(i,0)=0;
    for(int i=0;i<rows;i++)
    {
        for(int j=row_ptr[i];j<row_ptr[i+1];j++)
        {
          y(i,0)=y(i,0)+val[j]*X0(col_ind[j],0);
        }
      //  cout<<y(i,0)<<"\t";
    }
    //cout<<"vm\n";
    return y;
}

MatrixXd vm1(int rows,vector<double> &row_ptr,vector<double> &col_ind,vector<double> &val,MatrixXd X0)
{
  //  cout<<"vm1\n";
    //vector<double> y;
    MatrixXd y(rows,1);
    for(int i=0;i<rows;i++)
        y(i,0)=0;
    for(int i=0;i<rows;i++)
    {
        for(int j=row_ptr[i];j<row_ptr[i+1];j++)
        {
            y(i,0)=y(i,0)+val[j]*X0(col_ind[j],0);
        }
        //cout<<y[i]<<"\t";
    }
      //cout<<"vm1\n";
    return y.transpose();
}


int main()
{

//    ofstream f1("matrix.txt");
//    ofstream f2("right.txt");
//    ofstream f3("step.txt");
//    func(f1,f2,f3);
int iteration;
cin>>iteration;
ofstream myfileans("soln.txt");
ifstream myfile1[iteration];
ifstream myfile5[iteration];
ifstream myfile6[iteration];
ifstream myfile7[iteration];
ifstream myfile2[iteration];
string name="matrix";
string name5="row_ptr";
string name6="col_ind";
string name7="val";
string name2="right";

//for(int it=0;it<iteration;it++)
int it=23;
{
     stringstream ss;
    ss<<it+1;
    string s=ss.str();
    myfile1[it].open(name+s+".txt");
    myfile5[it].open(name5 + s+ ".txt");
    myfile6[it].open(name6 + s+ ".txt");
    myfile7[it].open(name7 + s+ ".txt");
    myfile2[it].open(name2 + s+ ".txt");
    //ifstream myfile3("step.txt");

    int val_size,row_size,col_size;
    myfile5[it]>>row_size;
    myfile6[it]>>col_size;
    myfile7[it]>>val_size;


    vector<double> val(val_size),col_ind(col_size),row_ptr(row_size);
    for(int i=0;i<row_size;i++)
        myfile5[it]>>row_ptr[i];
    for(int i=0;i<col_size;i++)
        myfile6[it]>>col_ind[i];
    for(int i=0;i<val_size;i++)
        myfile7[it]>>val[i];
    //cout<<"Enter desirednumber of rows of square Matrix:\n";
    int rows;
    //rows=(it+1)*(it+1);
    myfile1[it]>>rows;
    //cout<<rows<<"\n";
    myfileans<<rows<<"\t";
    MatrixXd matrix(rows,rows);
    for(int i=0;i<rows;i++)
    {
        //cout<<"Enter "<<i+1<<" row\n";
        for(int j=0;j<rows;j++)
        {
            myfile1[it]>>matrix(i,j);
        }
      //  cout<<"\n";
    }

    //cout<<endl<<matrix<<endl;*/
    MatrixXd X0(rows,1),b(rows,1),r0(rows,1);
    //for(int i=0;i<rows;i++)
    for(int i=0;i<rows;i++)
        X0(i,0)=0;
    //cout<<X0<<endl;
    //cout<<"Enter values for the Right-Hand Matrix\n";
    for(int i=0;i<rows;i++)
        myfile2[it]>>b(i,0);
    //cout<<b<<endl;
    //cout<<"\n\n";
    MatrixXd dir(rows,1);


    r0=b- vm(rows,row_ptr,col_ind,val,X0);//matrix*X0;
    dir=r0;
    //cout<<r0<<endl;
    //cout<<dir<<endl;
    double alpha;
    double Beta;
    MatrixXd X1;

    MatrixXd r1;
    MatrixXd temp;
    MatrixXd temp1;
    MatrixXd dir1;
    //cout<<"Enter number of steps you desire: ";
    int step=rows;
    //myfile3>>step;
    bool flag=1;
    int i;
    int start= clock();
    for(i=0;i<step;i++)
    {
            temp= vm1(rows,row_ptr,col_ind,val,dir)*dir;//( dir.transpose()*matrix)*dir;//vm1(rows,row_ptr,col_ind,val,dir.transpose())*dir;
    //        cout<<endl<<temp<<endl;
            temp=temp.inverse();
      //      cout<<temp<<endl;
            temp1=r0.transpose()*r0;
        //    cout<<temp1<<endl;
            alpha=(temp1.cwiseProduct(temp)).sum();
          //  cout<<alpha<<"\n";
            X1=X0+dir*alpha;
            //cout<<X1<<endl;
            vector<double> valtemp(val_size);
            valtemp=mult(val,alpha);
            r1=r0- vm(rows,row_ptr,col_ind,valtemp,dir);//(matrix*alpha)*dir;  //
            //cout<<r1<<endl;
            temp=r0.transpose()*r0;
           // cout<<temp<<endl;
            temp=temp.inverse();
            //cout<<temp<<endl;
            temp1=r1.transpose()*r1;
            //cout<<temp1<<endl;
            Beta=(temp1.cwiseProduct(temp)).sum();
            //cout<<Beta<<endl;
            dir1=r1+dir*Beta;
            //cout<<dir1<<endl;
            if(X0==X1)
                break;
            X0=X1;
            dir=dir1;
            r0=r1;
    }
    int stop=clock();
        double total_time=(double)(stop-start)/CLOCKS_PER_SEC;
      myfileans<<total_time<<"\t";
       //cout<<total_time<<endl<<endl<<endl;
//        else if(!flag)
//        {
//
//            temp=(dir1.transpose()*matrix)*dir1;
//            temp=temp.inverse();
//            temp1=(r1.transpose()*r1);
//            alpha=(temp1.cwiseProduct(temp)).sum();
//
//            X0=X1+dir1*alpha;
//            r0=r1-(matrix*alpha)*dir1;
//
//            temp=r1.transpose()*r1;
//            temp=temp.inverse();
//            temp1=r0.transpose()*r0;
//            Beta=(temp.cwiseProduct(temp)).sum();
//
//            dir=r0+dir1*Beta;
//            flag=true;
//        }
//        cout<<"\n"<<X0<<"\n"<<endl<<endl;
//    cout<<endl<<i<<endl;


       VectorXd x(rows);
       SparseMatrix<double> mat(rows,rows);
       mat.reserve(VectorXi::Constant(rows,2));

    int l=0;
     for(int i=0;i<rows;i++)
     {
         for(int j=0;j+row_ptr[i]<row_ptr[i+1];j++)
            {
                mat.insert(row_ptr[i]+j,col_ind[l])=matrix(row_ptr[i]+j,col_ind[l]);
                l++;
            }
     }
        mat.makeCompressed();

        //cout<<endl<<mat<<endl;


        ConjugateGradient<SparseMatrix<double> > cg;
        int s1=clock();
        cg.compute(mat);
        x = cg.solve(b);
        int s2=clock();
        total_time=(double)(s2-s1)/CLOCKS_PER_SEC;
        myfileans<<total_time<<"\n";
       cout<<endl<<total_time<<endl;
//            BiCGSTAB<SparseMatrix<double> > solver;
//             solver.compute(mat);
//             x = solver.solve(b);
           std::cout << "#iterations:     " << cg.iterations() << std::endl;
              //std::cout << "estimated error: " << cg.error()      << std::endl;
        cout<<endl<<endl<<x<<endl;
    }
}
