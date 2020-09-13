#include"common.cpp"
#include<vector>

vector<part> partitions;

// Strict 分割だけを生成するかどうかフラグ.
// もし現れる分割が全て Strict ならこれを true にすると高速化される.
const bool generateStrictPartitions = true;

bool isSuitablePartition(Par & p){
  bool isSuitable = true;
  for(int i = 0; i < p.size(); i++){
    if(p[ i ] == 0)break;
    isSuitable &= p[ i ] % 5 != 0;
    if(p[ i + 1 ] != 0){
      isSuitable &= p[ i ] - p[ i + 1 ] >= 1;
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

  // partitions のうちで Suitable な分割を大きさごとに表示する
  printSuitablePartitionsBySize( maxPartitionSize, partitions, isSuitablePartition);

}
