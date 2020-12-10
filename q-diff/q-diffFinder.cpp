#include"../IdentityFinder/common.cpp"
#include"../Polynomial/Polynomial.cpp"

typedef vector<vector<long long> > Matrix;

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
    if(p[i] == 0) break;
    if(p[i + 1] != 0){
      isSuitable &= p[i] - p[i + 1] >= 2;
    }
  }
  return isSuitable;
}

unsigned int refineFunction(Par & p){
  unsigned int refineValue = 0;
  for(int i = 0; i < p.size(); i++){
    if(p[i] == 0) break;
    refineValue++;
  }
  return refineValue;
}

Matrix transpose(const Matrix & m){
  if(m.empty()) return Matrix(0);
  Matrix result(m[0].size(), vector<long long>(m.size(), 0));
  for(int mRowIndex = 0; mRowIndex < m.size(); mRowIndex++){
    for(int mColIndex = 0; mColIndex < m[mRowIndex].size(); mColIndex++){
      result[mColIndex][mRowIndex] = m[mRowIndex][mColIndex];
    }
  }
  return result;
}

void printMatrix(const Matrix & m){
  cout << "Matrix([";
  for(int mRowIndex = 0; mRowIndex < m.size(); mRowIndex++){
    if(mRowIndex) cout << ", ";
    cout << "[";
    for(int mColIndex = 0; mColIndex < m[mRowIndex].size(); mColIndex++){
      if(mColIndex) cout << ", ";
      cout << m[mRowIndex][mColIndex];
    }
    cout << "]";
  }
  cout << "])" << endl;
}

int main(int argc,char *argv[]){
  Matrix m = Matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix mt = transpose(m);
  printMatrix(m);
  printMatrix(mt);
  // 実行時に生成する分割の大きさの上限をコマンドライン引数にとる.
  int maxPartitionSize = atoi( argv[1] );

  // 和が maxPartitionSize 以下の分割を生成して partitions に一列で保存する.
  // 長さの短い順に保存されていて各分割の終端は 0 で区切られる.
  // Option : generateStrictPartitions = true にすると Strict な分割に限って生成する.
  // remark : 0 の分割は生成されない.
  generatePartition( maxPartitionSize, partitions, generateStrictPartitions );

  //printVector(partitions); // for debug

  // partitions のうちで Suitable な分割を大きさごと, refineFunction の値ごとに数える
  // Option : countWithPrint = true として Suitable な分割を数え上げと同時に表示する.
  Polynomial refinedGeneratingFunction = countSuitableRefinedPartitions( maxPartitionSize, partitions, isSuitablePartition, refineFunction, countWithPrint ) + Polynomial({{1}});

  print_Polynomial(refinedGeneratingFunction);
}
