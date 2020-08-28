#include"common.cpp"
#include<vector>

vector< part > partitions;

// countSuitablePartitions で Suitable な分割を表示するかどうかのフラグ
// For debug
const bool countWithPrint = false;

// Strict 分割だけを生成するかどうかフラグ.
// もし現れる分割が全て Strict ならこれを true にすると高速化される.
const bool generateStrictPartitions = false;

bool isSuitablePartition(Par & p){
  bool isSuitable = true;
  return isSuitable;
}


part sumPartitionAs2Color(Par & p){
  part sum = part(0);
  for(int i = 0; i < p.size(); i++){
    sum += p[i]; // todo : ここを p[i] -> ceil( p[i] / 2 ) とする.
  }
  return sum;
}

vector<long long> count2ColorPartitions(int maxSizeOfPartition, vector<part> & rawPartitions, function<bool(Par &)> isSuitable, bool withPrint = false){
  vector<long long> numOf2ColorStrictPartitionsBySize( maxSizeOfPartition + 1 );
  Par examinedPartition;
  examinedPartition.reserve( maxSizeOfPartition + 1 );
  for(auto itr = rawPartitions.begin(); itr != rawPartitions.end(); itr++){
    if(*itr == part(0)){
      examinedPartition.push_back(part(0)); //0は分割の終端を表す.
      if( isSuitable( examinedPartition ) ){
        numOf2ColorStrictPartitionsBySize[ sumPartitionAs2Color(examinedPartition) ]++;
        if( withPrint ) printPartition( examinedPartition );
      }
      examinedPartition.clear();
    }
    else {
      examinedPartition.push_back( *itr );
    }
  }
  return numOf2ColorStrictPartitionsBySize;
}


int main(int argc, char * argv[]){
  // 実行時に生成する分割の大きさの上限をコマンドライン引数にとる.
  int maxPartitionSize = atoi( argv[1] );

  // 和が maxPartitionSize 以下の分割を生成して partitions に一列で保存する.
  // 長さの短い順に保存されていて各分割の終端は 0 で区切られる.
  // Option : generateStrictPartitions = true にすると Strict な分割に限って生成する.
  generatePartition( maxPartitionSize, partitions, generateStrictPartitions );

  // printVector(partitions); // for debug

  // partitions を 2ColorPartitions とみなして( 2k - 1 -> k_a, 2k -> k_b とする.(ここで k >= 1, a, b は Color に対応する) )分割を大きさ( Color を忘れたパートの和 )ごとに数える.
  // 
  // Option : countWithPrint = true として分割を数え上げと同時に表示する( 通常の分割として表示する. ( 2k - 1 -> k_a, 2k -> k_b だと思うと 2ColorPartition だとみなせる) ).
  //expectedOutput : 0 2 3 4 ...
  vector<long long> numOf2ColorPartitionsBySize( count2ColorPartitions( maxPartitionSize, partitions, isSuitablePartition, countWithPrint ) );

  // numOfPartitionsBySize を表示する.
	printVector( numOf2ColorPartitionsBySize );
}
