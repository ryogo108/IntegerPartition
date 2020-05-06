#include"common.cpp"
vector<part> partitions;
bool checkConditions(Par & p){	
  bool f=true;
  for(int i=0;i<p.size();i++){
    if(p[i]==0)break;
    f=f&&(p[i]!=2);
    if(p[i+1]!=0){
      if(p[i]%8==1)f=f&&(p[i]-p[i+1]>=5);
      if(p[i]%8==2)f=f&&(p[i]-p[i+1]>=9);
      if(p[i]%8==3)f=f&&(p[i]-p[i+1]>=6);
      if(p[i]%8==4)f=f&&(p[i]-p[i+1]==5||p[i]-p[i+1]>=7);
      if(p[i]%8==5)f=f&&(p[i]-p[i+1]==6||p[i]-p[i+1]>=8);
      if(p[i]%8==6)f=f&&(p[i]-p[i+1]==7||p[i]-p[i+1]>=9);
      if(p[i]%8==7)f=f&&(p[i]-p[i+1]>=6);
      if(p[i]%8==0)f=f&&(p[i]-p[i+1]>=7);
    }
  }
  return f;
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  generatePartition(n,partitions);
	vector<long long>v(countPartitions(n,partitions,checkConditions));
	printVector(v);
	vector<long long>A(Factor(v));
	printVector(A);
	printPeriodOfSeq(A);
}
