#include"common.cpp"
vector<part> partitions;
bool checkConditions(Par & p){	
  bool f=true;
  for(int i=0;i<p.size();i++){
    if(p[i]==0)break;
    if(p[i+1]!=0){
    /*  if(p[i]%3==0)f=f&&(p[i]-p[i+1]==2||p[i]-p[i+1]>=4);
      if(p[i]%3==1)f=f&&(p[i]-p[i+1]==0||p[i]-p[i+1]>=2);
      if(p[i]%3==2)f=f&&(p[i]-p[i+1]==0||p[i]-p[i+1]>=2);*/
      f=f&&(p[i]-p[i+1]!=1);
      if(p[i]%3==0)f=f&&(p[i]-p[i+1]!=0&&p[i]-p[i+1]!=3);
/*      f=f&&(p[i]!=2 || p[i+1]!=2);
      f=f&&(p[i]-p[i+1]!=1);
      if(p[i]%2==1)f=f&&(p[i]-p[i+1]!=0);*/
    }
    /*
     if(p[i+2]!=0){
        if(p[i+1]%2==0)f=f&&(p[i]-p[i+2]>=4);
     }*/
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
