#include"common.cpp"
#include<vector>

vector<part> partitions;

// countSuitablePartitions で Suitable な分割を表示するかどうかのフラグ
// For debug
const bool countWithPrint = false;

// Strict 分割だけを生成するかどうかフラグ.
// もし現れる分割が全て Strict ならこれを true にすると高速化される.
const bool generateStrictPartitions = true;

bool isSuitablePartition(Par & p){
  bool isSuitable = true;
  for(int i = 0; i < p.size(); i++){
    if(p[ i ] == 0) break;
    if(p[ i + 1 ] != 0){
      isSuitable &= p[ i ] - p[ i + 1 ] >= 3;
      if(p[ i ] % 3 == 0)isSuitable &= p[ i ] - p[ i + 1 ] > 3;
    }
  }
  return isSuitable;
}

vector<long long> countSuitablePartitionsByRoghWeight(int maxPartitionSize, vector<part> partitions){
  return countSuitablePartitions(maxPartitionSize, partitions, isSuitablePartition, countWithPrint);
}

int main(int argc, char * argv[]){
  // 実行時に生成する分割の大きさの上限をコマンドライン引数にとる.
  int maxPartitionSize = atoi( argv[1] );

  // 和が maxPartitionSize 以下の分割を生成して partitions に一列で保存する.
  // 長さの短い順に保存されていて各分割の終端は 0 で区切られる.
  // Option : generateStrictPartitions = true にすると Strict な分割に限って生成する.
  generatePartition( maxPartitionSize, partitions, generateStrictPartitions );

  // printVector(partitions); // for debug

  // partitions のうちで Suitable な分割を大きさごとに数える
  // Option : countWithPrint = true として Suitable な分割を数え上げと同時に表示する.
  vector<long long> numOfPartitionsBySize( countSuitablePartitionsByRoghWeight( maxPartitionSize, partitions) );

  // numOfPartitionsBySize を表示する.
	printVector( numOfPartitionsBySize );

  //分割の母関数の最初の n ( = maxPartitionSize ) 項 ( 1 + b_1 * q + b_2 * q ^ 2 + ... b_n * q ^ n ) を ( 1 - q ^ i ) ^ ( -a_i ) で因数分解した時の a_i の列. ( -a_i としていることに注意)
	vector<long long> exponentSeqOfFactoredGeneratingFunction( Factor( numOfPartitionsBySize ) );

  // exponentSeqOfFactoredGeneratingFunction を表示する.
	printVector( exponentSeqOfFactoredGeneratingFunction );

  // 上の a_i の列が周期列であればその周期と一周期ないで a_i = 1 となっている i を表示する. ( a_i = -1 なら -i　を表示する)
	printPeriodOfSeq( exponentSeqOfFactoredGeneratingFunction );
}
