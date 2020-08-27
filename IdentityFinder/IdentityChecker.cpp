#include"common.cpp"

bool isSuitablePartition(Par & p){
  return true;
//  return diffAtDist(p,2,1)&&smallestPart(p,1)&&congruenceAtDist(p,1,0,0,3);
}
int countSuitablePartitions(int requiredPartitionSize, int appendingPart, int sumOfLeadingPartition, Par leadingPartition){
  if(sumOfLeadingPartition!=0)leadingPartition.push_back(appendingPart);
  Par nowParition(leadingPartition);
  if(requiredPartitionSize < sumOfLeadingPartition || !isSuitablePartition(nowParition))return 0;
  if(requiredPartitionSize == sumOfLeadingPartition){
    //print_vector(now);
    return 1;
  }
  int partitionCounter=0;
  for(int i=appendingPart;i>=1;i--){
     partitionCounter+=countSuitablePartitions(requiredPartitionSize, i, sumOfLeadingPartition+i,nowParition);
  }
  return partitionCounter;
}
int countPartition(int n){
  Par p;
  return countSuitablePartitions(n,n,0,p);
}

void enumPartition(int n){
  vector<long long> B;
  for(int i=0;i<=n;i++)B.push_back(countPartition(i));
  bool f=false;
  for(int i=0;i<B.size();i++)if(B[i]!=0)f=true;
  if(!f)return;
  vector<long long> A(Factor(B));
  int l=detect(A);
  printVector(B);
  printVector(A);
  if(l>2){
    cout<<"n="<<l<<" ";
    vector<long long>v(A.begin()+1,A.begin()+l+1);
    printVector(v);
  }
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  enumPartition(n);
}
