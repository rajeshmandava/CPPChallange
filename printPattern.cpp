#include <iostream>
using namespace std;

int main()
{

  int r,i,j;
  cin>>r;
  for(i=1;i<=r;i++)
  {
    for(j=i;j<r;j++)
    {
      cout<<" ";
    }
    for(j=1;j<=(2*i-1);j++)
    {
      cout<<"*";
    }
    cout<<endl;
  }
}


