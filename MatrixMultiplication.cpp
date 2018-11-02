#include <iostream>

using namespace std;
int arr1[20][20];
int arr2[20][20];
int result[20][20];
int m,n,k;

void calculateCell(int x,int y){
    int sum=0;
    for(int i=0;i<k;i++){
        sum+=arr1[x][i]*arr2[i][y];
    }
    result[x][y]=sum;


}

void calculateRow(int x)
{
    for(int i=0;i<m;i++){
        calculateCell(x,i);
    }


}



void multiply()
{
    for(int i=0; i<n; i++)
    {

        calculateRow(i);
    }




}



int main()
{
    cin>>n>>k;
    for(int i=0; i<n; i++)
        for(int j=0; j<k; j++)
            cin>>arr1[i][j];
    cin>>k>>m;
    for(int i=0; i<k; i++)
        for(int j=0; j<m; j++)
            cin>>arr2[i][j];

    multiply();

for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            cout<<result[i][j]<<" ";
cout<<endl;
}
    return 0;
}
