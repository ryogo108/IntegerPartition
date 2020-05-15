#include"common.cpp"
vector<part> partitions;
bool checkConditions(Par & p){	
  bool f=true;
  for(int i=0;i<p.size();i++){
    if(p[i]==0)break;
    if(p[i+1]!=0){
      if(p[i]%3==0)f=f&&(p[i]-p[i+1]==3||p[i]-p[i+1]>=5);
      if(p[i]%3==1)f=f&&(p[i]-p[i+1]==3||p[i]-p[i+1]==4||p[i]-p[i+1]>=6);
      if(p[i]%3==2)f=f&&(p[i]-p[i+1]>=2);
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
