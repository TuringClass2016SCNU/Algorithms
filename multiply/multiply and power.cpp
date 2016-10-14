#include <iostream>
#include <vector>
using namespace std;
long multiply(int a,int b);
long power(int a, int b);
int main()

{
  //consideraion of this using plus instead of multiply;
   int a,b;
   long result_mul;
   long result_pow;
   cin>>a>>b;

   if (a==0 || b==0) {
     cout<<"0";
     return 0;
   }//check zero;

   result_mul=multiply(a,b);
   result_pow=power(a,b);

   cout<<result_mul<<endl<<result_pow;
   return 0;
}

/*-----------------------------------------*/

long multiply(int a,int b)
{
  //plus recurrence;
  if (a==1) {
    return b;
  }         //check if the number is 1;

  if (b==1) {
    return a;
  }

return multiply(a,b-1)+a;
//Avoid *,/;
}

/*--------------------------------------*/

long power(int a,int b)
{
  //Judge b?=0;
  if (b==0) {
    return 1;
  }

  //To find out which should be multiply，use vector to make an array;
  vector<bool> position;

  int temp,mul,count;
  temp=b;
  mul=a;
  count=0;

  // Below: judge whether it should be multiplied;
  while (temp>0)
  {
    position.push_back(temp % 2);
    if (temp % 2==1) {
      count+=1;
    }
    temp/=2;
  }

  int *sum=new int [count];

  for (int i = 0; i<position.size(); i++)
  {

    if (position[i]==1) {
      sum[i]=mul;
    }
      mul*=mul;
  }


  int sum_amount=1;
for (int i = 0; i < position.size(); i++) {
  if(position[i]==1){sum_amount*=sum[i];}

}
delete [] sum;

return sum_amount;

}
