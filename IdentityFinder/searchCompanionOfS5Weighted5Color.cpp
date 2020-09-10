#include"common.cpp"
#include<vector>

vector< part > partitions;

// countSuitablePartitions で Suitable な分割を表示するかどうかのフラグ
// For debug
const bool countWithPrint = true;

// Strict 分割だけを生成するかどうかフラグ.
// もし現れる分割が全て Strict ならこれを true にすると高速化される.
const bool generateStrictPartitions = false;

// colorOf5ColorPart に対応する Color の定数.
// todo : 説明が適切か考える.
// todo : color をハードコーディングしている箇所をこれらの定数で書き換える.
const part a1 = 1;
const part a2 = 2;
const part a3 = 3;
const part a4 = 4;
const part a5 = 0;

// 4ColorStrictPartitionsの大きさ 30 以下のデータセット.
// memo : 適当な 5ColorStrict の部分集合 C に対して #(5ColorStrict & C)( n ) がこれに一致すればそれが S5Weighted の候補になる.
// memo : ある n で #(5ColorStrict & C)( n ) < #4ColorStrict( n ) となればそのような C を含むような部分集合は S5_weighted を定める禁止列として適当でない. (はず, 証明をしていない.)
vector< long long> numsOf4ColorStrictPartitions = {0, 4, 10, 24, 51, 100, 190, 344, 601, 1024, 1702, 2768, 4422, 6948, 10752, 16424, 24782, 36972, 54602, 79872, 115805, 166540, 237664, 336720, 473856, 662596, 920934, 1272728, 1749407, 2392268, 3255410};

// issue : 以下のように( 1_a2 < 1_a3 < 2_a1 < 1_a4 < 1_a5 として)差の条件を変えただけでは n = 5 で 4ColorStrict の個数を下回る.
// todo : 1_a2 < 1_a3 < 2_a1 < 1_a4 < 1_a5 とした時に禁止列も変えなくてはならない.
const part diffMatrixByColor[5][5] = {
  //       a5, a1, a2, a3, a4
  /* a5 */ {1,  0,  1,  1,  1},
  /* a1 */ {3,  2,  2,  2,  3},
  /* a2 */ {2,  1,  1,  2,  2},
  /* a3 */ {2,  1,  1,  1,  2},
  /* a4 */ {2,  0,  1,  1,  1}
};

part absOf5ColorPart(part p){
  return p / 5 + (p % 5 != 0);
}

part colorOf5ColorPart(part p){
  return p % 5;
}

bool checkDiff5ColorCondition(part l, part r){
  return absOf5ColorPart( l ) - absOf5ColorPart( r ) >= diffMatrixByColor [ colorOf5ColorPart( l ) ][colorOf5ColorPart( r ) ];
}

// Main purpose : isSuitablePartition として S5Weighted に適当な条件( 4ColorStrict に分割の集合として同型 )を見つける.
// memo : ここで 分割の集合として同型とは, 分割の大きさを保存する全単射写像が存在することをいう.
// memo : またそれぞれの分割の集合で分割に対して大きさを定める 分割 -> 自然数 の写像が定まっているものとする. ここでは S5Weighted の大きさを定める写像は Color を忘れたパートの和とする. また, 4ColorStrict の大きさについても同様に Color を忘れたパートの和とする.
// Forbidden pattern memo : Tsuchioka Watanabe の S5 の条件を 精密化 ( 5k - 5 -> k_a1, 5k - 4 -> k_a2, 5k - 3 -> k_a3, 5k - 2 -> k_a4, 5k - 1 -> k_a5 ) して得られる次の条件を禁止して #4ColorStrict( n ) と n <= 15 で一致.
// Forbidden pattern memo : p[ i ] != 1_a1.
// Forbidden pattern memo : p[ i ] == p[ i + 1 ] => colorOf5ColorPart( p[ i ] ) = a1.
// Difference condition memo : absOf5ColorPart( p[ i ] ) - absOf5ColorPart( p[ i + 2 ] ) >= 1 && colorOf5ColorPart( p[ i ] ) < colorOf5ColorPart( p[ i + 2] ) の時 (a1 < a2 < a3 < a4 < a5 とする.) >= 1 は >= 2 また, colorOf5ColorPart( p[ i ] ) == a1 の時 >= 1 は >= 2.
// Forbidden pattern memo : forbid ( k_a4, k_a3 ) ( k >= 1).
// Forbidden pattern memo : forbid ( ( k + 1 )_a2, k_a5 ) ( k >= 1 ).
// Forbidden pattern memo : foebid ( ( k + 2 )_a2, *, *, k_a5 ) ( k >= 1).
// Remark : Strict 分割でない.( ( 2_a1, 2_a1 ) が現れる. ):w
bool isSuitablePartition(Par & p){
  bool isSuitable = true;
  for(int i = 0; i < p.size(); i++){
    if(p[ i ] == 0) break;
    isSuitable &= !(colorOf5ColorPart( p[ i ] ) == a1 && absOf5ColorPart( p[ i ] ) == 1);
    if(p[ i + 1 ] != 0){
      if( colorOf5ColorPart( p[ i ] ) != a1 )isSuitable &= p[ i ] - p[ i + 1 ] >= 1;
      isSuitable &= !(absOf5ColorPart( p[ i ] ) == absOf5ColorPart( p[ i + 1 ]) && colorOf5ColorPart( p[ i ]) == a4 && colorOf5ColorPart( p[ i + 1] ) == a3);
      isSuitable &= !(absOf5ColorPart( p[ i ] ) - absOf5ColorPart( p[ i + 1 ]) == 1 && colorOf5ColorPart( p[ i ]) == a2 && colorOf5ColorPart( p[ i + 1] ) == a5);

      if(p[ i + 2 ] != 0){
        isSuitable &= checkDiff5ColorCondition( p[ i ] , p[ i + 2 ] );
        if(p[ i + 3 ] != 0){
          isSuitable &= !(absOf5ColorPart( p[ i ] ) - absOf5ColorPart( p[ i + 3 ]) == 2 && colorOf5ColorPart( p[ i ]) == a2 && colorOf5ColorPart( p[ i + 3] ) == a5);
        }
      }
    }
  }
  return isSuitable;
}

part sumPartitionAs5Color(Par & p){
  part sum = part(0);
  for(int i = 0; i < p.size(); i++){
    sum += absOf5ColorPart( p[i] ); // p[i] -> ceil( p[i] / 5 ) として和を計算している.
  }
  return sum;
}

void printPartitionAs5Color(Par & p){
  // todo : 5ColorPartitionとして分割を表示するようにする. ( 5k - 4 -> k_a1, 5k - 3 -> k_a2, 5k - 2 -> k_a3, 5k - 1 -> k_a4, 5k -> k_a5 とする.)
	for(int i = 0; i < p.size(); i++){
		if(i > 0 && p[i] == 0) break;
		if(i > 0) cout << " ";
		cout << (short) absOf5ColorPart( p[i] ) << "_";
    switch( colorOf5ColorPart( p[i] ) ){
      case 0 : cout<<"a5"; break;
      case 1 : cout<<"a1"; break;
      case 2 : cout<<"a2"; break;
      case 3 : cout<<"a3"; break;
      case 4 : cout<<"a4"; break;
    }
	}
	cout << endl;
}

vector<long long> count5ColorPartitions(int maxSizeOfPartition, vector<part> & rawPartitions, function<bool(Par &)> isSuitable, bool withPrint = false){
  vector<long long> numOf5ColorStrictPartitionsBySize( maxSizeOfPartition + 1 );
  Par examinedPartition;
  examinedPartition.reserve( maxSizeOfPartition + 1 );
  for(auto itr = rawPartitions.begin(); itr != rawPartitions.end(); itr++){
    if(*itr == part(0)){
      examinedPartition.push_back(part(0)); //0は分割の終端を表す.
      part sumOfExaminedPartition = sumPartitionAs5Color(examinedPartition);
      if( isSuitable( examinedPartition ) && sumOfExaminedPartition <= maxSizeOfPartition ){
        numOf5ColorStrictPartitionsBySize[ sumOfExaminedPartition ]++;
        if( withPrint ) printPartitionAs5Color( examinedPartition );
      }
      examinedPartition.clear();
    }
    else {
      examinedPartition.push_back( *itr );
    }
  }
  return numOf5ColorStrictPartitionsBySize;
}


int main(int argc, char * argv[]){
  // 実行時に生成する分割の大きさの上限をコマンドライン引数にとる.
  int maxPartitionSize = atoi( argv[1] );

  // 和が maxPartitionSize 以下の分割を生成して partitions に一列で保存する.
  // 長さの短い順に保存されていて各分割の終端は 0 で区切られる.
  // Option : generateStrictPartitions = true にすると Strict な分割に限って生成する.
  // 5ColorPartition を数える場合分割の大きさが 1 / 5 になるので maxPartitionSize を 5 倍して生成している.
  generatePartition( 5 * maxPartitionSize, partitions, generateStrictPartitions );

  // printVector(partitions); // for debug

  // partitions を 5ColorPartitions とみなして( 5k - 4 -> k_a1, 5k - 3 -> k_a2, 5k - 2 -> k_a3, 5k - 1 -> k_a4, 5k -> k_a5, とする.(ここで k >= 1, a1 ... a5  は Color に対応する) )分割を大きさ( Color を忘れたパートの和 )ごとに数える.
  // 
  // Option : countWithPrint = true として分割を数え上げと同時に表示する( 通常の分割として表示する. ( 5k - 4 -> k_a1, 5k - 3 -> k_a2, 5k - 2 -> k_a3, 5k - 1 -> k_a4, 5k -> k_a5  だと思うと 5ColorPartition だとみなせる) ).
  vector<long long> numOf5ColorPartitionsBySize( count5ColorPartitions( maxPartitionSize, partitions, isSuitablePartition, countWithPrint ) );

  // numOfPartitionsBySize を表示する.
	printVector( numOf5ColorPartitionsBySize );
  printVector( numsOf4ColorStrictPartitions );

  bool isLarger = true;
  bool isEqual = true;
  for(int i = 0; i < min(numsOf4ColorStrictPartitions.size(), numOf5ColorPartitionsBySize.size() ); i++){
    isLarger &= numOf5ColorPartitionsBySize[ i ] >= numsOf4ColorStrictPartitions[ i ];
    isEqual &= numOf5ColorPartitionsBySize[ i ] == numsOf4ColorStrictPartitions[ i ];
  }

  // #(5ColorStrict & C )( n ) >= #4ColorStrict( n )であれば "It's OK." と表示する.そうでなければ "It's NOT OK." と表示する.
  if( isLarger ) cout << "It's OK. Under " << min(numsOf4ColorStrictPartitions.size(), numOf5ColorPartitionsBySize.size()) - 1 << endl;
  else cout << "It's NOT OK." << endl;

  // #(5ColorStrict & C )( n ) >= #4ColorStrict( n )であれば "The number of this partitions is exactly equal to 4ColorStrict by size under hoge " と表示する.そうでなければ "The number of this partitions is NOT equal to 4ColorStrict by size." と表示する.
  if( isEqual ) cout << "The number of this partitions is exactly equal to 4ColorStrict by size under "<< min(numsOf4ColorStrictPartitions.size(), numOf5ColorPartitionsBySize.size()) - 1 << endl;
  else cout<<"The number of this partitions is NOT equal to 4ColorStrict by size." << endl;

}
