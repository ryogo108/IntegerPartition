#include"common.cpp"

const int MAX_N=1005;

long long Dp[MAX_N][MAX_N];

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  Dp[1][1]=1;
  for(int i=0;i<MAX_N;i++)Dp[0][i]=1;
  for(int i=1;i<MAX_N;i++){
    for(int j=1;j<MAX_N;j++){
      if(j%2==1 && i>=j)Dp[i][j]=Dp[i][j-1]+Dp[i-j][j-1];
      else Dp[i][j]=Dp[i][j-1];
    }
  }
  vector<long long>v(n+1);
  for(int i=0;i<=n;i++){
    v[i]=Dp[i][i];
  }
  print_vector(v);
  vector<long long>A=Factor(v);
  printPeriodOfSeq(A);
}
