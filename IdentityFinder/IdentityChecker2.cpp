#include"common.cpp"
#include<vector>
vector<part> partitions;
bool isSuitablePartition(Par & p){
  bool isSuitable=true;
  int length=lengthOfPartition(p);
  for(int i=0;i<p.size();i++){
    if(p[i]==0)break;
    if(p[i+1]!=0){
      if(p[i]==p[i+1])isSuitable &= (p[i]%5==0);
      if(p[i]%5==3)isSuitable &= (p[i+1]!=p[i]-1);
      if(p[i]%5==1)isSuitable &= (p[i+1]!=p[i]-2);
      if(p[i+2]!=0){
        isSuitable &= (p[i]-p[i+2]>=5);
        if(p[i]%5==0)isSuitable &= (p[i]-p[i+2]>5);
        if(p[i+3]!=0){
          if(p[i]%5==1)isSuitable &= (!(p[i+3]==p[i]-7));
        }
      }
    }
  }
  return isSuitable;
}

int main(int argc,char *argv[]){
  int maxPartitionSize=atoi(argv[1]);
  generatePartition(maxPartitionSize,partitions);
	//vector<long long>v(countPartitions(n,partitions,checkConditions));
	vector<long long>numOfPartitionsBySize(countPartitionsWithPirnt(maxPartitionSize,partitions,isSuitablePartition));
	printVector(numOfPartitionsBySize);
	vector<long long>A(Factor(numOfPartitionsBySize));
	printVector(A);
	printPeriodOfSeq(A);
}
