#include"common.cpp"
#include<vector>

vector< part > partitions;

// countSuitablePartitions で Suitable な分割を表示するかどうかのフラグ
// For debug
const bool countWithPrint = true;

// Strict 分割だけを生成するかどうかフラグ.
// もし現れる分割が全て Strict ならこれを true にすると高速化される.
const bool generateStrictPartitions = true;

const part diffMatrix[3][3] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};

part absOf3ColorPart(part p){
  return p /3 + (p % 3 != 0);
}

part colorOf3ColorPart(part p){
  return p % 3;
}

bool checkDiff3ColorCondition(part l, part r){
  return absOf3ColorPart( l ) - absOf3ColorPart( r ) >= diffMatrix [ colorOf3ColorPart( l ) ][colorOf3ColorPart( r ) ];
}

bool isSuitablePartition(Par & p){
  bool isSuitable = true;
  for(int i = 0; i < p.size(); i++){
    if(p[ i ] == 0) break;
    if(p[ i + 1 ] != 0){
      isSuitable &= p[ i ] - p[ i + 1 ] >= 1;
      isSuitable &= checkDiff3ColorCondition( p[ i ] , p[ i + 1] );
    }
  }
  return isSuitable;
}

part sumPartitionAs3Color(Par & p){
  part sum = part(0);
  for(int i = 0; i < p.size(); i++){
    sum += absOf3ColorPart( p[i] ); // p[i] -> ceil( p[i] / 3 ) として和を計算している.
  }
  return sum;
}

void printPartitionAs3Color(Par & p){
  // todo : 3ColorPartitionとして分割を表示するようにする. ( 3k - 2 -> k_c, 3k - 1 -> k_a, 3k -> k_b とする.)
	for(int i = 0; i < p.size(); i++){
		if(i > 0 && p[i] == 0) break;
		if(i > 0) cout << " ";
		cout << (short) absOf3ColorPart( p[i] ) << "_";
    switch( colorOf3ColorPart( p[i] ) ){
      case 0 : cout<<"b"; break;
      case 1 : cout<<"c"; break;
      case 2 : cout<<"a"; break;
    }
	}
	cout << endl;
}

vector<long long> count3ColorPartitions(int maxSizeOfPartition, vector<part> & rawPartitions, function<bool(Par &)> isSuitable, bool withPrint = false){
  vector<long long> numOf3ColorStrictPartitionsBySize( maxSizeOfPartition + 1 );
  Par examinedPartition;
  examinedPartition.reserve( maxSizeOfPartition + 1 );
  for(auto itr = rawPartitions.begin(); itr != rawPartitions.end(); itr++){
    if(*itr == part(0)){
      examinedPartition.push_back(part(0)); //0は分割の終端を表す.
      part sumOfExaminedPartition = sumPartitionAs3Color(examinedPartition);
      if( isSuitable( examinedPartition ) && sumOfExaminedPartition <= maxSizeOfPartition ){
        numOf3ColorStrictPartitionsBySize[ sumOfExaminedPartition ]++;
        if( withPrint ) printPartitionAs3Color( examinedPartition );
      }
      examinedPartition.clear();
    }
    else {
      examinedPartition.push_back( *itr );
    }
  }
  return numOf3ColorStrictPartitionsBySize;
}


int main(int argc, char * argv[]){
  // 実行時に生成する分割の大きさの上限をコマンドライン引数にとる.
  int maxPartitionSize = atoi( argv[1] );

  // 和が maxPartitionSize 以下の分割を生成して partitions に一列で保存する.
  // 長さの短い順に保存されていて各分割の終端は 0 で区切られる.
  // Option : generateStrictPartitions = true にすると Strict な分割に限って生成する.
  // 3ColorPartition を数える場合分割の大きさが 1 / 3 になるので maxPartitionSize を 3 倍して生成している.
  generatePartition( 3 * maxPartitionSize, partitions, generateStrictPartitions );

  // printVector(partitions); // for debug

  // partitions を 3ColorPartitions とみなして( 3k - 2 -> k_c, 3k - 1 -> k_a, 3k -> k_b とする.(ここで k >= 1, a, b, c は Color に対応する) )分割を大きさ( Color を忘れたパートの和 )ごとに数える.
  // 
  // Option : countWithPrint = true として分割を数え上げと同時に表示する( 通常の分割として表示する. ( 3k - 2 -> k_c, 3k - 1 -> k_a, 3k -> k_b だと思うと 3ColorPartition だとみなせる) ).
  vector<long long> numOf3ColorPartitionsBySize( count3ColorPartitions( maxPartitionSize, partitions, isSuitablePartition, countWithPrint ) );

  // numOfPartitionsBySize を表示する.
	printVector( numOf3ColorPartitionsBySize );
}
