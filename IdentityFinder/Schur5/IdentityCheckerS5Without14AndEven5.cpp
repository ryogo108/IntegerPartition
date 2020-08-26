#include"../common.cpp"
#include<vector>
vector<part> partitions;
bool checkConditions(Par & p){
  bool f=true;
  bool tmp=false;
  int l=lengthOfPartition(p);
  vector<int> sub;
  for(int i=0;i<p.size();i++){
    if(p[i]==0)break;
    f=f&&(p[i]%5!=1 && p[i]%5!=4 && p[i]%10!=0);
    if(p[i+1]!=0){
      if(p[i]==p[i+1])f=f&&(p[i]%5==0);
      if(p[i]%5==3)f=f&&(p[i+1]!=p[i]-1);
      if(p[i]%5==1)f=f&&(p[i+1]!=p[i]-2);
      if(p[i+2]!=0){
        f=f&&(p[i]-p[i+2]>=5);
        if(p[i]%5==0)f=f&&(p[i]-p[i+2]>5);
        if(p[i+3]!=0){
          if(p[i]%5==1)f=f&&(!(p[i+3]==p[i]-7));
        }
      }
    }
  }
  return f;
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  generatePartition(n,partitions);
	//vector<long long>v(countPartitions(n,partitions,checkConditions));
	vector<long long>v(countPartitionsWithPirnt(n,partitions,checkConditions));
	printVector(v);
	vector<long long>A(Factor(v));
	printVector(A);
	printPeriodOfSeq(A);
}
