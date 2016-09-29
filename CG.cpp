#include<bits/stdc++.h>
#include<Eigen/Dense>

using namespace std;
using namespace Eigen;

using Eigen::MatrixXd;

int main()
{
    cout<<"Enter desired number of rows of square Matrix:\n";
    int rows;
    cin>>rows;
    MatrixXd matrix(rows,rows);
    for(int i=0;i<rows;i++)
    {
        cout<<"Enter "<<i+1<<" row\n";
        for(int j=0;j<rows;j++)
        {
            cin>>matrix(i,j);
        }
        cout<<"\n";
    }
    MatrixXd X0(rows,1),b(rows,1),r0(rows,1);
    for(int i=0;i<rows;i++)
        X0(i,0)=0;
    cout<<"Enter values for the Right-Hand Matrix\n";
    for(int i=0;i<rows;i++)
        cin>>b(i,0);
    cout<<"\n\n";
    MatrixXd dir(rows,1);
    for(int i=0;i<rows;i++)
    {
        dir(i,0)=b(i,0);
        r0(i,0)=b(i,0);
    }

    double alpha;
    double Beta;
    MatrixXd X1;

    MatrixXd r1;
    MatrixXd temp;
    MatrixXd temp1;
    MatrixXd dir1;
    cout<<"Enter number of steps you desire: ";
    int step;
    cin>>step;
    bool flag=1;
    for(int i=0;i<step;i++)
    {
        if(flag)
        {
            temp=(dir.transpose()*matrix)*dir;
            temp=temp.inverse();
            temp1=r0.transpose()*r0;
            alpha=(temp1.cwiseProduct(temp)).sum();
            X1=X0+dir*alpha;
            r1=r0-(matrix*alpha)*dir;

            temp=r0.transpose()*r0;
            temp=temp.inverse();
            temp1=r1.transpose()*r1;
            Beta=(temp.cwiseProduct(temp)).sum();

            dir1=r1+dir*Beta;
            flag=false;
        }
        else if(!flag)
        {

            temp=(dir1.transpose()*matrix)*dir1;
            temp=temp.inverse();
            temp1=(r1.transpose()*r1);
            alpha=(temp1.cwiseProduct(temp)).sum();

            X0=X1+dir1*alpha;
            r0=r1-(matrix*alpha)*dir1;

            temp=r1.transpose()*r1;
            temp=temp.inverse();
            temp1=r0.transpose()*r0;
            Beta=(temp.cwiseProduct(temp)).sum();

            dir=r0+dir1*Beta;
            flag=true;
        }
    }

    if(flag)
        cout<<"\n"<<X0<<"\n";
    else
        cout<<"\n"<<X1<<"\n";
}
