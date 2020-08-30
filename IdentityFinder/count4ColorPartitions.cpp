#include"common.cpp"
#include<vector>

vector< part > partitions;

// countSuitablePartitions で Suitable な分割を表示するかどうかのフラグ
// For debug
const bool countWithPrint = true;

// Strict 分割だけを生成するかどうかフラグ.
// もし現れる分割が全て Strict ならこれを true にすると高速化される.
const bool generateStrictPartitions = true;

const part diffMatrix[4][4] = {
  {1, 1, 1},
  {2, 2, 2},
  {2, 1, 1}
};

part absOf4ColorPart(part p){
  return p / 4 + (p % 4 != 0);
}

part colorOf4ColorPart(part p){
  return p % 4;
}

bool checkDiff4ColorCondition(part l, part r){
  return absOf4ColorPart( l ) - absOf4ColorPart( r ) >= diffMatrix [ colorOf4ColorPart( l ) ][colorOf4ColorPart( r ) ];
}

bool isSuitablePartition(Par & p){
  bool isSuitable = true;
  for(int i = 0; i < p.size(); i++){
    if(p[ i ] == 0) break;
    if(p[ i + 1 ] != 0){
      isSuitable &= p[ i ] - p[ i + 1 ] >= 1;
    }
  }
  return isSuitable;
}

part sumPartitionAs4Color(Par & p){
  part sum = part(0);
  for(int i = 0; i < p.size(); i++){
    sum += absOf4ColorPart( p[i] ); // p[i] -> ceil( p[i] / 4 ) として和を計算している.
  }
  return sum;
}

void printPartitionAs4Color(Par & p){
  // todo : 4ColorPartitionとして分割を表示するようにする. ( 4k - 3 -> k_a1, 4k - 2 -> k_a2, 4k - 1 -> k_a3, 4k -> k_a4 とする.)
	for(int i = 0; i < p.size(); i++){
		if(i > 0 && p[i] == 0) break;
		if(i > 0) cout << " ";
		cout << (short) absOf4ColorPart( p[i] ) << "_";
    switch( colorOf4ColorPart( p[i] ) ){
      case 0 : cout<<"a4"; break;
      case 1 : cout<<"a1"; break;
      case 2 : cout<<"a2"; break;
      case 3 : cout<<"a3"; break;
    }
	}
	cout << endl;
}

vector<long long> count4ColorPartitions(int maxSizeOfPartition, vector<part> & rawPartitions, function<bool(Par &)> isSuitable, bool withPrint = false){
  vector<long long> numOf4ColorStrictPartitionsBySize( maxSizeOfPartition + 1 );
  Par examinedPartition;
  examinedPartition.reserve( maxSizeOfPartition + 1 );
  for(auto itr = rawPartitions.begin(); itr != rawPartitions.end(); itr++){
    if(*itr == part(0)){
      examinedPartition.push_back(part(0)); //0は分割の終端を表す.
      part sumOfExaminedPartition = sumPartitionAs4Color(examinedPartition);
      if( isSuitable( examinedPartition ) && sumOfExaminedPartition <= maxSizeOfPartition ){
        numOf4ColorStrictPartitionsBySize[ sumOfExaminedPartition ]++;
        if( withPrint ) printPartitionAs4Color( examinedPartition );
      }
      examinedPartition.clear();
    }
    else {
      examinedPartition.push_back( *itr );
    }
  }
  return numOf4ColorStrictPartitionsBySize;
}


int main(int argc, char * argv[]){
  // 実行時に生成する分割の大きさの上限をコマンドライン引数にとる.
  int maxPartitionSize = atoi( argv[1] );

  // 和が maxPartitionSize 以下の分割を生成して partitions に一列で保存する.
  // 長さの短い順に保存されていて各分割の終端は 0 で区切られる.
  // Option : generateStrictPartitions = true にすると Strict な分割に限って生成する.
  // 4ColorPartition を数える場合分割の大きさが 1 / 4 になるので maxPartitionSize を 4 倍して生成している.
  generatePartition( 4 * maxPartitionSize, partitions, generateStrictPartitions );

  // printVector(partitions); // for debug

  // partitions を 4ColorPartitions とみなして( 4k - 3 -> k_a1, 4k - 2 -> k_a2, 4k - 1 -> k_a3, 4k -> k_a4 とする.(ここで k >= 1, a1 ... a4 は Color に対応する) )分割を大きさ( Color を忘れたパートの和 )ごとに数える.
  // 
  // Option : countWithPrint = true として分割を数え上げと同時に表示する.
  vector<long long> numOf4ColorPartitionsBySize( count4ColorPartitions( maxPartitionSize, partitions, isSuitablePartition, countWithPrint ) );

  // numOfPartitionsBySize を表示する.
	printVector( numOf4ColorPartitionsBySize );
}
