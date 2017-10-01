#include<iostream>

#define MAX 9   // Change the Value of MAX to Print Number Spirals of Different Sizes

using namespace std;

int mat[MAX][MAX],count=1;
int i=1,j=0;


void fill(int ring)
{
   int m;
   if((2*ring-1)<= MAX)
   {
       if(ring==1)
       {
          mat[MAX/2][MAX/2]=count;
          count++;
       }
       else
       {
          j--;
          m=0;
          while(m < 2*(ring-1))
          {
             i--;
             mat[(MAX/2)-i][(MAX/2)-j]=count;
             count++;
             m++;
          }
          m=0;
          while(m<2*(ring-1))
          {
             j++;
             mat[(MAX/2)-i][(MAX/2)-j]=count;
             count++;
             m++;
          }
          m=0;
          while(m<2*(ring-1))
          {
             i++;
             mat[(MAX/2)-i][(MAX/2)-j]=count;
             count++;
             m++;
          }
          m=0;
          while(m < 2*(ring-1))
          {
             j--;
             mat[(MAX/2)-i][(MAX/2)-j]=count;
             count++;
             m++;
          }
          i++;
       }
       fill(ring+1);
   }
}

int main()
{
    int x,y;
    fill(1);
    cout<<"\n";
    for(x=0;x<MAX;x++)
    {
        for(y=0;y<MAX;y++)
        {
            cout<<"\t"<<mat[x][y];
        }
        cout<<"\n\n";
    }
    return 0;
}
