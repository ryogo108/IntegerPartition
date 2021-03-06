#include"common.cpp"
#include<vector>

vector< part > partitions;

// countSuitablePartitions で Suitable な分割を表示するかどうかのフラグ
// For debug
const bool countWithPrint = true;

// Strict 分割だけを生成するかどうかフラグ.
// もし現れる分割が全て Strict ならこれを true にすると高速化される.
const bool generateStrictPartitions = true;

// colorOf6ColorPart に対応する Color の定数.
// todo : 説明が適切か考える.
// todo : color をハードコーディングしている箇所をこれらの定数で書き換える.
const part a1 = 1;
const part a2 = 2;
const part a3 = 3;
const part a4 = 4;
const part a5 = 5;
const part a6 = 0;

// 4ColorStrictPartitionsの大きさ 30 以下のデータセット.
// memo : 適当な 6ColorStrict の部分集合 C に対して #(6ColorStrict & C)( n ) がこれに一致すればそれが S5Weighted の候補になる.
// memo : ある n で #(6ColorStrict & C)( n ) < #4ColorStrict( n ) となればそのような C を含むような部分集合は S5_weighted を定める禁止列として適当でない. (はず, 証明をしていない.)
vector< long long> numsOf4ColorStrictPartitions = {0, 4, 10, 24, 51, 100, 190, 344, 601, 1024, 1702, 2768, 4422, 6948, 10752, 16424, 24782, 36972, 54602, 79872, 115805, 166540, 237664, 336720, 473856, 662596, 920934, 1272728, 1749407, 2392268, 3255410};

const part diffMatrixByColor[6][6] = {
  //       a6, a1, a2, a3, a4, a5
  /* a6 */ {1,  1,  1,  1,  1,  1},
  /* a1 */ {2,  2,  2,  2,  2,  2},
  /* a2 */ {2,  2,  2,  2,  2,  2},
  /* a3 */ {2,  1,  1,  1,  2,  2},
  /* a4 */ {2,  1,  1,  1,  1,  2},
  /* a5 */ {2,  1,  1,  1,  1,  1}
};

part absOf6ColorPart(part p){
  return p /6 + (p % 6 != 0);
}

part colorOf6ColorPart(part p){
  return p % 6;
}

bool checkDiff6ColorCondition(part l, part r){
  return absOf6ColorPart( l ) - absOf6ColorPart( r ) >= diffMatrixByColor [ colorOf6ColorPart( l ) ][colorOf6ColorPart( r ) ];
}

// Main purpose : isSuitablePartition として S5Weighted に適当な条件( 4ColorStrict に分割の集合として同型 )を見つける.
// memo : ここで 分割の集合として同型とは, 分割の大きさを保存する全単射写像が存在することをいう.
// memo : またそれぞれの分割の集合で分割に対して大きさを定める 分割 -> 自然数 の写像が定まっているものとする. ここでは S5Weighted の大きさを定める写像は Color を忘れたパートの和とする. また, 4ColorStrict の大きさについても同様に Color を忘れたパートの和とする.
// memo : 単に Strict として 6ColorStrict これは #6ColorStrict( n ) >= #4ColorStrict( n ) ,n = 1 ... 10 を直接確かめた.
// memo : #( 6ColorStrict & (forbid a6, a1) ) == #4ColorStrict( n ), n = 1 ... 10 を直接確かめた.
// Todo : 適当な禁止列を決めて #( 6ColorStrict & C ) ( n )=  #4ColorStrict( n ) となる 6ColorStrictの部分集合 C を決める.
// memo : S5 の条件を weighted ( 1 -> 1_a3, 2 -> 1_a4, 3 -> 1_a5, 4-> 1_a6, 5 -> 2_a1 or 2_a2, ... ) として考える.
// Done : Color を定数として書き出す. ( 0 -> a_6, 1 -> a_1, 2 -> a_2, 3 -> a_3, 4 -> a_4, 5 -> a_5)
// Forbidden pattern memo : forbid 1_a1 and 1_a2 として It's OK under 15.
// Forbidden pattern memo : forbid ( k_a5, k_a4 ) (k >= 1) を追加して It's OK under 15.
// Forbidden pattern memo( to be removed) : forbid absOf6ColorPart( p[ i ] ) - absOf6ColorPart(  p[ i + 2 ] ) >= 1 && colorOf6ColorPart( p[ i ] ) == a1 or a2 ならば >= は >. を追加して It's OK under 15.
// issue( to be removed) : 上の条件は不十分. s.t. ( 2_a4, 1_a6, 1_a5 ) が禁止されていない. これは特殊化すると( 7, 4, 3) だが, 7 - 3 = 4 < 5 より S5 の元ではない.
// Forbidden pattern memo : add difference condition absOf6ColorPart( p[ i ] ) - absOf6ColorPart( p[ i + 2 ] ) >= 1 && colorOf6ColorPart( p[ i ] ) < colorOf6ColorPart( p[ i + 2 ] ) の時 ( a1 < a2 < a3 < a4 < a5 < a6 とする.) >= 1 は >= 2. また colorOf6ColorPart( p[ i ] ) == a1 or a2 の時 >=1 は >= 2. として It's OK under 15.
// Forbidden pattern memo : forbid ( (k + 1)_a3, (k)_a6 ) (k >= 1) を追加して It's OK under 15.
// Forbidden pattern memo : forbid ( (k + 2)_a3, *, *, (k)_a6 ) (k >= 1) を追加して It's OK under 15.
// Done : Tsuchioka, Watanabe を参考に上の weighted における禁止パターンを追加したものを C_prototype として #( 6ColorStrict & C_prototype )( n ) >= #4ColorStrict( n ) であるかどうかを確かめた. これが成り立たなければおそらくこの weighted word は存在しない.
// todo : 上の "おそらくこの weighted word は存在しない" を厳密に書き下す.
// issue : 2_a2, 2_a1 がそれぞれ現れる. これらは S5 への変換で 2_a2 -> 5, 2_a1 -> 5 となり、#( 6ColorStrict & C )( 2 ) == #4ColorStrict( 2 ) + 1 である. 単純には 2_a2 もしくは 2_a1 を禁止列にすることが考えられる.
// Forbidden pattern memo : k_a1 を全て禁止列にすると n >= 4 で It's NOT OK. ( ( 2_a2, 2_a1 ) が禁止列になってしまう. )
// Forbidden pattern issue : n = 2 で 2_a2, 2_a1 がそれぞれ現れる.
// Forbidden pattern memo : 2_a1 だけからなる分割を禁止する. を追加して It's OK under 15. で n = 2 まで #4ColorStrict( n ) に一致.
//   Forbidden pattern issue : 3_a2, 3_a1 が それぞれ現れる.
//   Forbidden pattern issue : (2_a2, 1_a6), (2_a1, 1_a6)が それぞれ現れる.
//   Forbidden pattern issue : (2_a2, 1_a5), (2_a1, 1_a5)が それぞれ現れる.
//   Forbidden pattern issue : (2_a2, 1_a4), (2_a1, 1_a4)が それぞれ現れる.
//   Forbidden pattern issue : (2_a2, 1_a3), (2_a1, 1_a3)が それぞれ現れる.
//   Forbidden pattern todo : 3_a2 で 長さ 1 の禁止
//   Forbidden pattern todo : 3_a1 で 長さ 1 の禁止
//   Forbidden pattern memo : forbid (2k)_a1, ( 2k + 1 )_a2 で長さ 1 の禁止.
//   Forbidden pattern memo : forbid ( 2_a2 , ( 1_a5 or 1_a4 ) ) and ( 2_a1 , ( 1_a6 or 1_a3 ) )
//     Forbidden pattern issue : (2_a6, 2_a2), (2_a6, 2_a1)が それぞれ現れる.
//     Forbidden pattern issue : (2_a5, 2_a2), (2_a5, 2_a1)が それぞれ現れる.
//     Forbidden pattern issue : (2_a4, 2_a2), (2_a4, 2_a1)が それぞれ現れる.
//     Forbidden pattern issue : (2_a3, 2_a2), (2_a3, 2_a1)が それぞれ現れる.
//     Forbidden pattern memo :  forbid ( 2_a6 or 2_a5 or 2_a4 or 2_a3, 2_a1 ) ( この場合 2_a1 -> (1_a6, 1_a3) として S5 の元が存在する.) を追加して It's OK under 15.
//     Forbidden pattern issue : (3_a2, 1_a6), /(3_a1, 1_a6)が それぞれ現れる.
//     Forbidden pattern issue : /(3_a2, 1_a5), (3_a1, 1_a5)が それぞれ現れる.
//     Forbidden pattern issue : (3_a2, 1_a4), /(3_a1, 1_a4)が それぞれ現れる.
//     Forbidden pattern issue : (3_a2, 1_a3), /(3_a1, 1_a3)が それぞれ現れる.
//     Forbidden pattern todo : forbid (3_a1, 1_a6) and (3_a1, 1_a3)
//     Forbidden pattern todo : forbid (3_a2, 1_a5) and (3_a2, 1_a4).
bool isSuitablePartition(Par & p){
  // EQ6CP( 1_a3, 1, a3 ) -> true (ここで 1_a3 = 0 + 3 )
  // EQ6CP( 2_a3, 1, a3 ) -> false ( ここで 2_a3 = 6 + 3 )
  #define EQ6CP( part, value, color ) ( ( absOf6ColorPart( part ) == value ) && ( colorOf6ColorPart( part ) == color ) )
  bool isSuitable = true;
  for(int i = 0; i < p.size(); i++){
    if(p[ i ] == 0) break;
    // forbid 1_a1 and 1_a2
    isSuitable &= !EQ6CP( p[ i ], 1, a1 )&&!EQ6CP( p[ i ], 1, a2);
    isSuitable &= !(colorOf6ColorPart( p[ i ] ) == a1 && absOf6ColorPart( p[ i ] ) % 2 == 0 && lengthOfPartition( p ) == 1);
    isSuitable &= !(colorOf6ColorPart( p[ i ] ) == a2 && absOf6ColorPart( p[ i ] ) % 2 == 1 && lengthOfPartition( p ) == 1);
    if(p[ i + 1 ] != 0){
      isSuitable &= p[ i ] - p[ i + 1 ] >= 1;
      isSuitable &= !(absOf6ColorPart( p[ i ] ) == absOf6ColorPart( p[ i + 1 ]) && colorOf6ColorPart( p[ i ]) == a5 && colorOf6ColorPart( p[ i + 1] ) == a4);
      isSuitable &= !(absOf6ColorPart( p[ i ] ) - absOf6ColorPart( p[ i + 1 ]) == 1 && colorOf6ColorPart( p[ i ]) == a3 && colorOf6ColorPart( p[ i + 1] ) == a6);

      // forbid (2_a2, (1_a5 or 1_a4))
      isSuitable &= !(colorOf6ColorPart( p[ i ] ) == a2 && absOf6ColorPart( p[ i ] ) == 2
                  && absOf6ColorPart( p[ i + 1 ] ) == 1 && (colorOf6ColorPart( p[ i + 1 ] ) == a5 || colorOf6ColorPart( p[ i + 1 ] ) == a4 ));
      // forbid (2_a1, (1_a6 or 1_a3))
      isSuitable &= !(colorOf6ColorPart( p[ i ] ) == a1 && absOf6ColorPart( p[ i  ] ) == 2
                  && absOf6ColorPart( p[ i + 1 ] ) == 1 && (colorOf6ColorPart( p[ i + 1 ] ) == a6 || colorOf6ColorPart( p[ i + 1 ] ) == a3 ));
      // forbid ( 2_a6 or 2_a5 or 2_a4 or 2_a3, 2_a1 )
      isSuitable &= !(colorOf6ColorPart( p[ i  + 1 ] ) == a1 && absOf6ColorPart( p[ i + 1 ] ) == 2
                  && absOf6ColorPart( p[ i  ] ) == 2
                  && (colorOf6ColorPart( p[ i ] ) == a6
                  ||  colorOf6ColorPart( p[ i ] ) == a5
                  ||  colorOf6ColorPart( p[ i ] ) == a4
                  ||  colorOf6ColorPart( p[ i ] ) == a3));
      if(p[ i + 2 ] != 0){
        isSuitable &= checkDiff6ColorCondition( p[ i ] , p[ i + 2 ] );
        if(p[ i + 3 ] != 0){
          isSuitable &= !(absOf6ColorPart( p[ i ] ) - absOf6ColorPart( p[ i + 3 ]) == 2 && colorOf6ColorPart( p[ i ]) == a3 && colorOf6ColorPart( p[ i + 3] ) == a6);
        }
      }
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
  printVector( numsOf4ColorStrictPartitions );

  bool isLarger = true;
  bool isEqual = true;
  for(int i = 0; i < min(numsOf4ColorStrictPartitions.size(), numOf6ColorPartitionsBySize.size() ); i++){
    isLarger &= numOf6ColorPartitionsBySize[ i ] >= numsOf4ColorStrictPartitions[ i ];
    isEqual &= numOf6ColorPartitionsBySize[ i ] == numsOf4ColorStrictPartitions[ i ];
  }

  // #(6ColorStrict & C )( n ) >= #4ColorStrict( n )であれば "It's OK." と表示する.そうでなければ "It's NOT OK." と表示する.
  if( isLarger ) cout << "It's OK. Under " << min(numsOf4ColorStrictPartitions.size(), numOf6ColorPartitionsBySize.size()) - 1 << endl;
  else cout << "It's NOT OK." << endl;

  // #(6ColorStrict & C )( n ) >= #4ColorStrict( n )であれば "The number of this partitions is exactly equal to 4ColorStrict by size under hoge " と表示する.そうでなければ "The number of this partitions is NOT equal to 4ColorStrict by size." と表示する.
  if( isEqual ) cout << "The number of this partitions is exactly equal to 4ColorStrict by size under "<< min(numsOf4ColorStrictPartitions.size(), numOf6ColorPartitionsBySize.size()) - 1 << endl;
  else cout<<"The number of this partitions is NOT equal to 4ColorStrict by size." << endl;

}
