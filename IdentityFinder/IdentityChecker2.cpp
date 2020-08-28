#include"common.cpp"
#include<vector>

vector<part> partitions;

//countSuitablePartitionsでSuitableな分割を表示するかどうかのフラグ
//for debug
const bool countWithPrint = false;

//Strict分割だけを生成するかどうかフラグ.
//もし現れる分割が全てStrictならこれをtrueにすると高速化される.
const bool generateStrictPartitions = true;

bool isSuitablePartition(Par & p){
  bool isSuitable = true;
  for(int i = 0; i < p.size(); i++){
    if(p[ i ] == 0) break;
    if(p[ i + 1 ] != 0){
      isSuitable &= p[ i ] - p[ i + 1 ] >= 2;
    }
  }
  return isSuitable;
}

int main(int argc, char * argv[]){
  int maxPartitionSize = atoi( argv[1] );
  generatePartition( maxPartitionSize, partitions, generateStrictPartitions );
  //printVector(partitions); // for debug
	vector<long long> numOfPartitionsBySize( countSuitablePartitions( maxPartitionSize, partitions, isSuitablePartition, countWithPrint ) );
	printVector( numOfPartitionsBySize );
	vector<long long> exponentSeqOfFactoredGeneratingFunction( Factor( numOfPartitionsBySize ) );
	printVector( exponentSeqOfFactoredGeneratingFunction );
	printPeriodOfSeq( exponentSeqOfFactoredGeneratingFunction );
}
