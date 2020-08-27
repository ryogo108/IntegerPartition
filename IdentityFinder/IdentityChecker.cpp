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
int numOfSuitablePartition(int requiredPartitionSize){
  Par emptyPartition(0);
  return countSuitablePartitions(requiredPartitionSize, requiredPartitionSize, 0, emptyPartition);
}

void enumPartition(int maxPartitionSize){
  vector<long long> generatingFunction;
  for(int i=0;i<=maxPartitionSize;i++)generatingFunction.push_back(numOfSuitablePartition(i));
  vector<long long> exponentSeqOfGeneratingFunction(Factor(generatingFunction));
  int lengthOfPeriodicSeq=detectLengthOfPeriodOfSeq(exponentSeqOfGeneratingFunction);
  printVector(generatingFunction);
  printVector(exponentSeqOfGeneratingFunction);
  if(lengthOfPeriodicSeq > 2){
    cout<<"lengthOfPeriodicSeq="<<lengthOfPeriodicSeq<<" ";
    vector<long long>onePeriod(exponentSeqOfGeneratingFunction.begin()+1,exponentSeqOfGeneratingFunction.begin()+lengthOfPeriodicSeq+1);
    printVector(onePeriod);
  }
}

int main(int argc,char *argv[]){
  int maxPartitionSize=atoi(argv[1]);
  enumPartition(maxPartitionSize);
}
