#include<iostream>

using namespace std;

const int COUNT_PARTITION_MAX_LENGTH=300;

long long dp[COUNT_PARTITION_MAX_LENGTH+1];

long long numOfPartition(int n){//Eulerの五角数定理から得られる分割数を数えるO(n*sqrt(n))のアルゴリズム
  if(dp[n]!=0)return dp[n];
  dp[0]=1;
  for(int i=1;i<=n;i++){
    if(dp[i]!=0)continue;
    int j;
    for(j=1;j*(3*j+1)<=2*i;j=j+2){
      dp[i]+=dp[i-(int)(j*(3*j+1)/2)];
    }
    for(j=2;j*(3*j+1)<=2*i;j=j+2){
      dp[i]-=dp[i-(int)(j*(3*j+1)/2)];
    }
    for(j=1;j*(3*j-1)<=2*i;j=j+2){
      dp[i]+=dp[i-(int)(j*(3*j-1)/2)];
    }
    for(j=2;j*(3*j-1)<=2*i;j=j+2){
      dp[i]-=dp[i-(int)(j*(3*j-1)/2)];
    }
  }
  return dp[n];
}
/*int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  long long sum=0;
  for(int i=0;i<=n;i++){
    sum+=numOfPartition(i);
    cout<<i<<" "<<numOfPartition(i)<<endl;
  }
}*/
