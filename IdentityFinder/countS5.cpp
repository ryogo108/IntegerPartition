#include"common.cpp"
#include<vector>

vector<part> partitions;

// countSuitablePartitions で Suitable な分割を表示するかどうかのフラグ
// For debug
const bool countWithPrint = true;

// Strict 分割だけを生成するかどうかフラグ.
// もし現れる分割が全て Strict ならこれを true にすると高速化される.
const bool generateStrictPartitions = false;

bool isSuitablePartition(Par & p){
  bool isSuitable = true;
  for(int i = 0; i < p.size(); i++){
    if(p[ i ] == 0) break;
    if(p[ i + 1 ] != 0){

      if(p[ i ] == p[ i + 1 ]) isSuitable &= p[ i ] % 5 == 0;

      if( p[ i ] - p[ i + 1 ] == 1 ) isSuitable &= (p[ i ] % 5 != 3 || p[ i + 1 ] % 5 != 2);
      if( p[ i ] - p[ i + 1 ] == 2 ) isSuitable &= (p[ i ] % 5 != 1 || p[ i + 1 ] % 5 != 4);
      
      if(p[ i + 2 ] != 0){
        isSuitable &= p[ i ] - p[ i + 2 ] >= 5;
        if(p[ i ] % 5 == 0)isSuitable &= p[ i ] - p[ i + 2 ] > 5;

        if(p[ i + 3 ] != 0){
          if( p[ i ] - p[ i + 3 ] == 7) isSuitable &= (p[ i ] % 5 != 1 || p[ i + 3 ] % 5 != 4);
        }
      }
    }
  }
  return isSuitable;
}

int main(int argc, char * argv[]){
  // 実行時に生成する分割の大きさの上限をコマンドライン引数にとる.
  int maxPartitionSize = atoi( argv[1] );

  // 和が maxPartitionSize 以下の分割を生成して partitions に一列で保存する.
  // 長さの短い順に保存されていて各分割の終端は 0 で区切られる.
  generatePartition( maxPartitionSize, partitions, generateStrictPartitions );

  // partitions のうちで Suitable な分割を大きさごとに数える
  // Option : countWithPrint = true として Suitable な分割を数え上げと同時に表示する.
  vector<long long> numOfPartitionsBySize( countSuitablePartitions( maxPartitionSize, partitions, isSuitablePartition, countWithPrint) );

  // numOfPartitionsBySize を表示する.
	printVector( numOfPartitionsBySize );

  //分割の母関数の最初の n ( = maxPartitionSize ) 項 ( 1 + b_1 * q + b_2 * q ^ 2 + ... b_n * q ^ n ) を ( 1 - q ^ i ) ^ ( -a_i ) で因数分解した時の a_i の列. ( -a_i としていることに注意)
	vector<long long> exponentSeqOfFactoredGeneratingFunction( Factor( numOfPartitionsBySize ) );

  // exponentSeqOfFactoredGeneratingFunction を表示する.
	printVector( exponentSeqOfFactoredGeneratingFunction );

  // 上の a_i の列が周期列であればその周期と一周期ないで a_i = 1 となっている i を表示する. ( a_i = -1 なら -i　を表示する)
	printPeriodOfSeq( exponentSeqOfFactoredGeneratingFunction );
}
