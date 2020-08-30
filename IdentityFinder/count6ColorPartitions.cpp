#include"common.cpp"
#include<vector>

vector< part > partitions;

// countSuitablePartitions で Suitable な分割を表示するかどうかのフラグ
// For debug
const bool countWithPrint = true;

// Strict 分割だけを生成するかどうかフラグ.
// もし現れる分割が全て Strict ならこれを true にすると高速化される.
const bool generateStrictPartitions = true;

const part diffMatrix[6][6] = {
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0}
};

part absOf6ColorPart(part p){
  return p /6 + (p % 6 != 0);
}

part colorOf6ColorPart(part p){
  return p % 6;
}

bool checkDiff6ColorCondition(part l, part r){
  return absOf6ColorPart( l ) - absOf6ColorPart( r ) >= diffMatrix [ colorOf6ColorPart( l ) ][colorOf6ColorPart( r ) ];
}

bool isSuitablePartition(Par & p){
  bool isSuitable = true;
  for(int i = 0; i < p.size(); i++){
    if(p[ i ] == 0) break;
    if(p[ i + 1 ] != 0){
      isSuitable &= p[ i ] - p[ i + 1 ] >= 1;
      isSuitable &= checkDiff6ColorCondition( p[ i ] , p[ i + 1] );
    }
  }
  return isSuitable;
}

part sumPartitionAs6Color(Par & p){
  part sum = part(0);
  for(int i = 0; i < p.size(); i++){
    sum += absOf6ColorPart( p[i] ); // p[i] -> ceil( p[i] / 6 ) として和を計算している.
  }
  return sum;
}

void printPartitionAs6Color(Par & p){
  // todo : 6ColorPartitionとして分割を表示するようにする. ( 6k - 5 -> k_a1, 6k - 4 -> k_a2, 6k - 3 -> k_a3, 6k - 2 -> k_a4, 6k - 1 -> k_a5, 6k -> k_a6 とする.)
	for(int i = 0; i < p.size(); i++){
		if(i > 0 && p[i] == 0) break;
		if(i > 0) cout << " ";
		cout << (short) absOf6ColorPart( p[i] ) << "_";
    switch( colorOf6ColorPart( p[i] ) ){
      case 0 : cout<<"a6"; break;
      case 1 : cout<<"a1"; break;
      case 2 : cout<<"a2"; break;
      case 3 : cout<<"a3"; break;
      case 4 : cout<<"a4"; break;
      case 5 : cout<<"a5"; break;
    }
	}
	cout << endl;
}

vector<long long> count6ColorPartitions(int maxSizeOfPartition, vector<part> & rawPartitions, function<bool(Par &)> isSuitable, bool withPrint = false){
  vector<long long> numOf6ColorStrictPartitionsBySize( maxSizeOfPartition + 1 );
  Par examinedPartition;
  examinedPartition.reserve( maxSizeOfPartition + 1 );
  for(auto itr = rawPartitions.begin(); itr != rawPartitions.end(); itr++){
    if(*itr == part(0)){
      examinedPartition.push_back(part(0)); //0は分割の終端を表す.
      part sumOfExaminedPartition = sumPartitionAs6Color(examinedPartition);
      if( isSuitable( examinedPartition ) && sumOfExaminedPartition <= maxSizeOfPartition ){
        numOf6ColorStrictPartitionsBySize[ sumOfExaminedPartition ]++;
        if( withPrint ) printPartitionAs6Color( examinedPartition );
      }
      examinedPartition.clear();
    }
    else {
      examinedPartition.push_back( *itr );
    }
  }
  return numOf6ColorStrictPartitionsBySize;
}


int main(int argc, char * argv[]){
  // 実行時に生成する分割の大きさの上限をコマンドライン引数にとる.
  int maxPartitionSize = atoi( argv[1] );

  // 和が maxPartitionSize 以下の分割を生成して partitions に一列で保存する.
  // 長さの短い順に保存されていて各分割の終端は 0 で区切られる.
  // Option : generateStrictPartitions = true にすると Strict な分割に限って生成する.
  // 6ColorPartition を数える場合分割の大きさが 1 / 6 になるので maxPartitionSize を 6 倍して生成している.
  generatePartition( 6 * maxPartitionSize, partitions, generateStrictPartitions );

  // printVector(partitions); // for debug

  // partitions を 6ColorPartitions とみなして( 6k - 5 -> k_a1, 6k - 4 -> k_a2, 6k - 3 -> k_a3, 6k - 2 -> k_a4, 6k - 1 -> k_a5, 6k -> k_a6 とする.(ここで k >= 1, a1 ... a6  は Color に対応する) )分割を大きさ( Color を忘れたパートの和 )ごとに数える.
  // 
  // Option : countWithPrint = true として分割を数え上げと同時に表示する( 通常の分割として表示する. ( 6k - 5 -> k_a1, 6k - 4 -> k_a2, 6k - 3 -> k_a3, 6k - 2 -> k_a4, 6k - 1 -> k_a5, 6k -> k_a6  だと思うと 6ColorPartition だとみなせる) ).
  vector<long long> numOf6ColorPartitionsBySize( count6ColorPartitions( maxPartitionSize, partitions, isSuitablePartition, countWithPrint ) );

  // numOfPartitionsBySize を表示する.
	printVector( numOf6ColorPartitionsBySize );
}
