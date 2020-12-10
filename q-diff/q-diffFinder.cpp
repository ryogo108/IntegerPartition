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

void printVectorForSage(const vector<long long> & v){
  cout << "vector([";
  for(int i; i < v.size(); i++){
    if(i) cout << ", ";
    cout << v[i];
  }
  cout << "])" << endl;
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

Polynomial calcXQ(unsigned int xTimes, unsigned int qTimes){
  Polynomial result = Polynomial(MAX_Q_INDEX, vector<long long>(MAX_X_INDEX, 0));
  result[qTimes][xTimes] = 1;
  return result;
}

// findQDiffCoefMatrix は q-diff 探索用の行列を求める.
// q-diff の 係数の多項式 P_1, ... , P_r は　ZZ[x, q] / (x ^ (s + 1), q ^ (t + 1)) の元とする.
// P_i は p(x * q ^ (d * i)) の係数とする.
Matrix findQDiffMatrix(const Polynomial & p, int r, int s, int t, int d = 1){
  vector<long long> basePolyVect = polynomialToVec(p);
  printVectorForSage(basePolyVect);
  Matrix result((s + 1) * (t + 1) * r, vector<long long>(basePolyVect.size(), 0));
  for(int i = 1; i <= r; i++){
    Polynomial shiftedPoly = qShift(p, d * i);
    for(unsigned int xTimes = 0; xTimes <= s; xTimes++){
      for(unsigned int qTimes = 0; qTimes <= t; qTimes++){
        Polynomial coefTimes = calcXQ(xTimes, qTimes);
        Polynomial multipliedPoly = coefTimes * shiftedPoly;
        vector<long long> resultVect = polynomialToVec(multipliedPoly);
        copy(resultVect.begin(), resultVect.end(), result[(i - 1) * (s + 1) * (t + 1) + xTimes * (t + 1) + qTimes].begin());
      }
    }
  }

  // a^1_0_0, ... a^1_s_t, ..., a^r_s_t をかける方向に転置する.
  Matrix transposedResultMat = transpose(result);
  return transposedResultMat;
}

// "(a_0, a_1, ..., a_N)" -> [a_0, a_1, ..., a_N].
vector<long long> parseAnsString(string ans){
  vector<long long> ansVect;
  string parsedStr = "";
  for(int i = 0; i < ans.size(); i++){
    if(ans[i] == '(' ) continue;
    if(ans[i] == ')' ){
      ansVect.push_back(stoi(parsedStr));
      continue;
    }

    if(ans[i] == ','){
      ansVect.push_back(stoi(parsedStr));
      parsedStr = "";
      i++;
      continue;
    }

    parsedStr += ans[i];
  }
  return ansVect;
}

void printQDiff(string ans, int qDifforder, int maxXIndex, int maxQIndex, int qDiffD){
  vector<long long> ansVect = parseAnsString(ans);
  cout << "f(x) = " << endl;
  for(int order = 1; order <= qDifforder; order++){
    if(order > 1) cout <<" + ";
    Polynomial coef = Polynomial({{0}});
    for(unsigned int xTimes = 0; xTimes <= maxXIndex; xTimes++){
      for(unsigned int qTimes = 0; qTimes <= maxQIndex; qTimes++){
        long long coefOfXQ = ansVect[(order - 1) * (maxXIndex + 1) * (maxQIndex + 1) + xTimes * (maxQIndex + 1) + qTimes];
        coef = coef + calcXQ(xTimes, qTimes) * Polynomial({{ coefOfXQ }});
      }
    }
    print_Polynomial(coef);
    cout << "* f(x * q ^ " << order * qDiffD << ")"<<endl;
  }
}

int main(int argc,char *argv[]){
  // 実行時に生成する分割の大きさの上限をコマンドライン引数にとる.
  int maxPartitionSize = atoi( argv[1] );
  int qDiffOrder = atoi(argv[2]);
  int maxQIndex = atoi(argv[3]);
  int maxXIndex = atoi(argv[4]);
  int qDiffD = atoi(argv[5]);

  // 和が maxPartitionSize 以下の分割を生成して partitions に一列で保存する.
  // 長さの短い順に保存されていて各分割の終端は 0 で区切られる.
  // Option : generateStrictPartitions = true にすると Strict な分割に限って生成する.
  // remark : 0 の分割は生成されない.
  generatePartition( maxPartitionSize, partitions, generateStrictPartitions );

  //printVector(partitions); // for debug

  // partitions のうちで Suitable な分割を大きさごと, refineFunction の値ごとに数える
  // Option : countWithPrint = true として Suitable な分割を数え上げと同時に表示する.
  Polynomial refinedGeneratingFunction = countSuitableRefinedPartitions( maxPartitionSize, partitions, isSuitablePartition, refineFunction, countWithPrint ) + Polynomial({{1}});

  Matrix m = findQDiffMatrix(refinedGeneratingFunction, qDiffOrder, maxXIndex, maxQIndex, qDiffD);
  printMatrix(m);
  print_Polynomial(refinedGeneratingFunction);

  string ans;
  getline(cin, ans);

  printQDiff(ans, qDiffOrder, maxXIndex, maxQIndex, qDiffD);
}
